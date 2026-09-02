// SPDX-License-Identifier: GPL-3.0-only
// © Mis012 2025

import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Stream;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import gnu.getopt.Getopt;
import gnu.getopt.LongOpt;

import org.objectweb.asm.ClassReader;
import org.objectweb.asm.Opcodes;
import org.objectweb.asm.Type;
import org.objectweb.asm.tree.AnnotationNode;
import org.objectweb.asm.tree.ClassNode;
import org.objectweb.asm.tree.FieldNode;
import org.objectweb.asm.tree.MethodNode;
import org.objectweb.asm.tree.ParameterNode;

public class JNIUpcallWrapperGenerator {
	private static PrintStream out = System.out;
	private static boolean short_class_names = false;
	private static ArrayList<JarFile> classpath = new ArrayList<JarFile>();

	/* ensure consistent ordering by using a TreeMap with the class name as the key */
	private static TreeMap<String, String> generatedSections = new TreeMap<>();

	private static Map<String, Set<String>> structMap = new TreeMap<String, Set<String>>();
	/* in case className is short class name, we need a way to get the full class name */
	private static Map<String, String> classNameToFullClassName = new TreeMap<String, String>();
	/* to check for clonflicts when short class names are enabled */
	private static HashSet<String> seenClasses = new HashSet<>();

	private static void printUsage() {
			System.err.println("Usage: jni_upcall_gen [-d output] [-c|--classpath TODO] --jar-file <path-to-jar> [extraExports.txt [moreExtraExports.txt [...]]]");
	}

	private static void printHelp() {
		printUsage();
		System.err.printf("\n" +
		                 "generates upcall wrappers for methods annotated with android/atl/annotation/Export in the --jar-file,\n" +
		                 "as well as for methods specified in passed in text files (used for stdlib methods)\n" +
		                 "\n" +
		                 "The following options are accepted:\n" +
		                 "-h --help              display this help\n" +
		                 "-j --jar-file <file>   the jar file to process\n" +
		                 "-s --short-class-names use unqualified class names and fail\n" +
		                 "                       if there are multiple classes with the same name\n" +
		                 "-c --classpath <cp>    all dependencies needed to correctly assign jstring/jclass/jthrowable\n" +
		                 "-d <file>              instead of stdout, output into <file>\n");
	}

	public static void main(String[] argv) throws IOException {

		LongOpt[] longopts = new LongOpt[] {
			new LongOpt("help", LongOpt.NO_ARGUMENT, null, 'h'),
			new LongOpt("jar-file", LongOpt.REQUIRED_ARGUMENT, null, 'j'),
			new LongOpt("classpath", LongOpt.REQUIRED_ARGUMENT, null, 'c'),
			new LongOpt("short-class-names", LongOpt.NO_ARGUMENT, null, 's'),
		};

		Getopt g = new Getopt("JNIHeaderGenerator", argv, "hd:j:c:s", longopts);

		String destPath = null;
		String jarPath = null;
		String rawClasspath = null;

		int c;
		while ((c = g.getopt()) != -1) {
			switch(c) {
				case 'h':
					printHelp();
					System.exit(1);
					break;
				case 'd':
					destPath = g.getOptarg();
					break;
				case 'j':
					jarPath = g.getOptarg();
					break;
				case 'c':
					rawClasspath = g.getOptarg();
					break;
				case 's':
					short_class_names = true;
					break;
				case '?':
					printUsage();
					System.exit(1);
					break;
			}
		}

		if (jarPath == null) {
			System.err.println("error: no jar file specified");
			printUsage();
			System.exit(1);
		}

		classpath.add(new JarFile(jarPath));
		if (rawClasspath != null) {
			for(String classpathEntry : rawClasspath.split(":"))
				classpath.add(new JarFile(classpathEntry));
		}

		if (destPath != null)
			out = new PrintStream(destPath);

		ArrayList<String> extraExportsFiles = new ArrayList<String>();
		for (int i = g.getOptind(); i < argv.length ; i++) {
			extraExportsFiles.add(argv[i]);
		}

		for (String fileName : extraExportsFiles) {
			processExtraExportsFile(fileName);
		}

		JarFile jar = new JarFile(jarPath);

		for (Enumeration<JarEntry> e = jar.entries(); e.hasMoreElements();) {
			JarEntry entry = e.nextElement();
			if (entry.getName().endsWith(".class")) {
				processClassFile(generatedSections, jar, entry);
			}
		}

		/* jclass lazy getters */
		for (String className : structMap.keySet()) {
			String fullClassName = classNameToFullClassName.get(className);
			String handleCacheClass = String.format("handle_cache.%s.class", className);
			String s = ("__attribute__((always_inline)) inline jclass J_get_class__"+className+"(JNIEnv *env)\n" +
				    "{\n" +
				    "	if (__unlikely__(!"+handleCacheClass+"))\n" +
				    "		"+handleCacheClass+" = _REF((*env)->FindClass(env, \""+fullClassName.replace('.', '/')+"\"));\n" +
				    "\n" +
				    "	return "+handleCacheClass+";\n" +
				    "}\n");

			/* massage the sorting keys to get what we want (jclass getter should get sorted before first method of said class) */
			generatedSections.put(fullClassName.replace("$", "~")+"!"+"!", s);
		}

		/* start printing the file */

		/* header guard and includes */
		out.print("#ifndef _UPCALLS_H_\n" +
		          "#define _UPCALLS_H_\n" +
		          "\n" +
		          "#include <jni.h>\n" +
		          "#include \"defines.h\"\n" +
		          "\n");

		/* handle cache struct */
		out.println("struct handle_cache {");
		int i = 0;
		for (String className : structMap.keySet()) {
			if (i > 0)
				out.print("\n");
			i++;
			out.println("\tstruct {");
			out.println("\t\tjclass class;");
			Set<String> methodNames = structMap.get(className);
			for (String method : methodNames) {
				out.println("\t\tjmethodID "+method+";");
			}
			out.println("\t} "+className+";");
		}
		out.println("};");
		out.println("extern struct handle_cache handle_cache;");

		/* functions */
		for (String generatedSection : generatedSections.values()) {
			out.print("\n" + generatedSection);
		}

		/* header guard */
		out.print("#endif\n");

		if (destPath != null)
			out.close();
	}

	private static void processExtraExportsFile(String fileName) {
		try (Stream<String> stream = Files.lines(Paths.get(fileName))) {
			stream.forEach(JNIUpcallWrapperGenerator::processExtraExportsFileLine);
		} catch (IOException e) {
			System.err.println("error: exception while processing \""+fileName+"\": "+e);
			System.exit(1);
		}
	}

	/* format: com/example/Class.method(II)V or com/example/Class.method(II)V:exportedName*/
	private static void processExtraExportsFileLine(String line) {
		String exportedName;
		String[] parts = line.split(":");
		if (parts.length == 1) { // no :
			exportedName = null;
		} else if (parts.length == 2) {
			exportedName = parts[1];
			line = parts[0];
		} else {
			throw new AssertionError("extra export line \""+line+"\" appears malformed (should contain at most one colon)");
		}

		parts = line.split("\\.");
		if (parts.length != 2)
			throw new AssertionError("extra export line \""+line+"\" appears malformed (should contain exactly one dot)");
		String className = parts[0];
		String methodName = parts[1].substring(0, parts[1].lastIndexOf("("));
		String descriptor = parts[1].substring(parts[1].lastIndexOf("("));

		/* extra exports will reference classes from the classpath */
		for (JarFile jar : classpath) {
			try {
				JarEntry entry = jar.getJarEntry(className + ".class");
				if (entry != null) {
					try (InputStream in = jar.getInputStream(entry)) {
						ClassNode classNode = new ClassNode();
						new ClassReader(in).accept(classNode, 0);
						for (MethodNode m : classNode.methods) {
							if (m.name.equals(methodName) && m.desc.equals(descriptor))
								printPrototype(generatedSections, className.replace("/", "."), m.access, m.name, (exportedName != null) ? exportedName : m.name, m.desc, m.parameters);
						}
					}
				}
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
	}

	private static void processClassFile(Map<String, String> generatedSections, JarFile jar, JarEntry entry) throws IOException {

		boolean hasExportedMethods = false; // class has at least one exported method
		String className = entry.getName().substring(0, entry.getName().lastIndexOf(".class")).replace('/', '.');

		ClassNode classNode;
		try (InputStream in = jar.getInputStream(entry)) {
			classNode = new ClassNode();
			new ClassReader(in).accept(classNode, 0);
		}

		HashMap<String, Integer> overloadCounts = new HashMap<>();
		for (MethodNode m : classNode.methods) {
			if (m.visibleAnnotations != null) {
				for (AnnotationNode annotation : m.visibleAnnotations) {
					if (annotation.desc.equals("Landroid/atl/annotation/Export;")) {
						overloadCounts.merge(m.name, 1, Integer::sum);
						break; // stop cycling through annotations early if we already found the Export annotation
					}
				}
			}
		}

		for (MethodNode m : classNode.methods) {
			if (m.visibleAnnotations != null) {
				for (AnnotationNode annotation : m.visibleAnnotations) {
					if (annotation.desc.equals("Landroid/atl/annotation/Export;")) {
						String exportedName;
						if (annotation.values == null)
							exportedName = null;
						else if (annotation.values.size() == 2 && annotation.values.get(0).equals("value"))
							exportedName = (String)annotation.values.get(1);
						else
							throw new AssertionError("method "+className+m.name+" has an invalid Export annotation (annotation.values: "+annotation.values+")");

						if (overloadCounts.get(m.name) > 1 && exportedName == null) {
							System.err.println("error: method "+className+m.name+" has multiple overloaded variants that are all exported, " +
							                   "and yet "+className+m.name+m.desc+" doesn't specify the name to use for the C wrapper function");
							System.exit(1);
						}

						hasExportedMethods = true;
						printPrototype(generatedSections, className, m.access, m.name, (exportedName != null) ? exportedName : m.name, m.desc, m.parameters);
						break; // stop cycling through annotations early if we already found the Export annotation
					}
				}
			}
		}

		if (short_class_names && hasExportedMethods) {
			if (!seenClasses.add(className.substring(className.lastIndexOf(".") + 1))) {
				System.err.println("error: --short-class-names specified but multiple classes with exported methods" +
				                   " share the same name (conflict found with: "+className+")");
				System.exit(1);
			}
		}
	}

	private static void printPrototype(Map<String, String> generatedSections, String className, int access, String name, String exportedName, String descriptor, List<ParameterNode> args) {
		boolean isStatic = (access & Opcodes.ACC_STATIC) != 0;
		String fullClassName = className;
		if (short_class_names)
			className = className.substring(className.lastIndexOf(".") + 1);
		String mangledClassName = prettyMangle(className);
		if (exportedName.equals("<init>")) {
			exportedName = "constructor";
		} else if (name.equals("constructor")) { // not checking exportedName, manually specified override is allowed 
			System.err.println("error: method name 'constructor' currently not allowed (conflicts with rename for <init>)");
			System.exit(1);
		}
		String mangledMethodName = prettyMangle(exportedName);
		String mangledName;
		if(!name.equals("<init>")) {
			mangledName = String.format("J__%s__%s", mangledClassName, mangledMethodName);
		} else {
			/* we always call the constructor method `constructor` or 'constructor_<disambiguating-suffix>' */
			String constructorSuffix = mangledMethodName.replace("constructor_", "").replace("constructor", "");
			mangledName = String.format("J_new__%s%s%s", mangledClassName, !constructorSuffix.isEmpty() ? "__" : "", constructorSuffix);
		}
		String handleCacheMethod = String.format("handle_cache.%s.%s", mangledClassName, mangledMethodName);
		if (structMap.get(mangledClassName) == null) {
			classNameToFullClassName.put(mangledClassName, fullClassName);
			structMap.put(mangledClassName, new TreeSet<String>());
		}
		structMap.get(mangledClassName).add(mangledMethodName);

		String getMethodIdFunc = isStatic ? "GetStaticMethodID" : "GetMethodID";
		String retType;
		String callMethodFunc;
		String returnString;

		if(!name.equals("<init>")) {
			retType = toJniType(Type.getReturnType(descriptor));
			callMethodFunc = toCallMethodFunc(Type.getReturnType(descriptor), isStatic);
			returnString = (callMethodFunc != "CallVoidMethod") ? "return " : "";
		} else {
			/* constructing an object looks similar to calling a method */
			retType = "jobject";
			callMethodFunc = "NewObject";
			returnString = "return ";
		}

		StringBuilder params = new StringBuilder("JNIEnv *env");
		StringBuilder passedParams = new StringBuilder("");
		boolean haveThis = (!isStatic && !name.equals("<init>"));
		if (haveThis)
			params.append(", jobject this");
		Type[] argTypes = Type.getArgumentTypes(descriptor);
		if (argTypes.length > 0) {
			/* null args means the jar was compiled without `-parameters` */
			assert(args == null || argTypes.length == args.size());
			for (int i = 0; i < argTypes.length; i++) {
				String argName = (args != null) ? args.get(i).name : "_arg"+i;
				params.append(String.format(", %s %s", toJniType(argTypes[i]), argName));
				passedParams.append(String.format(", %s", argName));
			}
		}
		String g = ("__attribute__((always_inline)) inline jmethodID J_get_method__"+mangledClassName+"__"+mangledMethodName+"(JNIEnv *env)\n" +
		            "{\n" +
		            "	if (__unlikely__("+handleCacheMethod+" == 0))\n" +
		            "		"+handleCacheMethod+" = (*env)->"+getMethodIdFunc+"(env, J_get_class__"+mangledClassName+"(env), \""+name+"\", \""+descriptor+"\");\n" +
		            "\n" +
		            "	return "+handleCacheMethod+";\n" +
		            "}\n" +
		            "\n" +
		            "__attribute__((always_inline)) inline "+retType+" "+mangledName+"("+new String(params)+")\n" +
		            "{\n" +
		            (haveThis ? "" : "\tjclass class = J_get_class__"+className+"(env);\n") +
		            "	"+returnString+"(*env)->"+callMethodFunc+"(env, "+(haveThis ? "this" : "class")+", J_get_method__"+mangledClassName+"__"+mangledMethodName+"(env)"+new String(passedParams)+");\n" +
		            "}\n");

		/* massage the sorting keys to get what we want (main class before inner classes and group methods by class) */
		generatedSections.put(fullClassName.replace("$", "~")+"!"+String.format("J__%s__%s", mangledClassName, mangledMethodName), g);
	}

	/* helpers */
	private static String prettyMangle(String orig) {
		StringBuilder mangled = new StringBuilder();
		for (int i = 0; i < orig.length(); i++) {
			char c = orig.charAt(i);
			switch (c) {
				case '/':
				case '.':
				case '$':
					mangled.append("__");
					break;
				case '_':
					mangled.append("_");
					break;
				default:
					if (c <= 0x7f &&
					   ((c >= 'A' && c <= 'Z')
					   || (c >= 'a' && c <= 'z')
					   || (c >= '0' && c <= '9'))) {
						mangled.append(c);
					} else {
						System.err.println("error: prettyMangle: name '"+orig+"' seems to contain invalid characters");
						System.exit(1);
					}

					break;
			}
		}

		return new String(mangled);
	}

	private static String toCallMethodFunc(Type t, boolean isStatic) {
		if (isStatic) {
			switch(t.getSort()) {
				case Type.VOID:    return "CallStaticVoidMethod";
				case Type.BOOLEAN: return "CallStaticBooleanMethod";
				case Type.BYTE:    return "CallStaticByteMethod";
				case Type.CHAR:    return "CallStaticCharMethod";
				case Type.SHORT:   return "CallStaticShortMethod";
				case Type.INT:     return "CallStaticIntMethod";
				case Type.LONG:    return "CallStaticLongMethod";
				case Type.FLOAT:   return "CallStaticFloatMethod";
				case Type.DOUBLE:  return "CallStaticDoubleMethod";
				case Type.ARRAY:   /* fallthrough */
				case Type.OBJECT:  return "CallStaticObjectMethod";
			}
		} else {
			switch(t.getSort()) {
				case Type.VOID:    return "CallVoidMethod";
				case Type.BOOLEAN: return "CallBooleanMethod";
				case Type.BYTE:    return "CallByteMethod";
				case Type.CHAR:    return "CallCharMethod";
				case Type.SHORT:   return "CallShortMethod";
				case Type.INT:     return "CallIntMethod";
				case Type.LONG:    return "CallLongMethod";
				case Type.FLOAT:   return "CallFloatMethod";
				case Type.DOUBLE:  return "CallDoubleMethod";
				case Type.ARRAY:   /* fallthrough */
				case Type.OBJECT:  return "CallObjectMethod";
			}
		}
		/* should be unreachable */
		return null;
	}

	private static String toJniType(Type t) {
		switch (t.getSort()) {
			case Type.ARRAY: {
				Type e = t.getElementType();
				switch(e.getSort()) {
					case Type.VOID:    throw new AssertionError("[V encountered in toJniType");
					case Type.BOOLEAN: return "jbooleanArray";
					case Type.BYTE:    return "jbyteArray";
					case Type.CHAR:    return "jcharArray";
					case Type.SHORT:   return "jshortArray";
					case Type.INT:     return "jintArray";
					case Type.LONG:    return "jlongArray";
					case Type.FLOAT:   return "jfloatArray";
					case Type.DOUBLE:  return "jdoubleArray";
					case Type.ARRAY:   /* fallthrough */
					case Type.OBJECT:  return "jobjectArray";
				}
			}

			case Type.VOID:    return "void";
			case Type.BOOLEAN: return "jboolean";
			case Type.BYTE:    return "jbyte";
			case Type.CHAR:    return "jchar";
			case Type.SHORT:   return "jshort";
			case Type.INT:     return "jint";
			case Type.LONG:    return "jlong";
			case Type.FLOAT:   return "jfloat";
			case Type.DOUBLE:  return "jdouble";
			case Type.OBJECT:
				String className = t.getClassName();
				/* String is final */
				if (className.equals("java.lang.String")) {
					return "jstring";
				/* so is Class */
				} else if (className.equals("java.lang.Class")) {
					return "jclass";
				} else if (isSubtypeOf(className, "java.lang.Throwable")) {
					return "jthrowable";
				} else {
					return "jobject";
				}
		}

		/* should be unreachable */
		return null;
	}

	static boolean isSubtypeOf(String className, String ancestor) {
		/* ancestor is always an internal class, so at some point in the hierarchy
		 * we're bound to get to classes that we can instantiate */
		try {
			Class<?> cls = Class.forName(className.replace('$', '.'));
			Class<?> anc = Class.forName(ancestor);
			return anc.isAssignableFrom(cls);
		} catch (ClassNotFoundException | NoClassDefFoundError e) {}

		/* for classes that are not part of the stdlib, we allow passing a classpath of jars
		 * the first entry is implicitly the jar file that we are generating headers for */
		for (JarFile jar : classpath) {
			try {
				String entryName = className.replace('.', '/');
				JarEntry entry = jar.getJarEntry(entryName + ".class");
				if (entry != null) {
					try (InputStream in = jar.getInputStream(entry)) {
						ClassNode node = new ClassNode();
						new ClassReader(in).accept(node, 0);

						// climb up the ancestry tree
						if (node.superName != null) {
							return isSubtypeOf(node.superName, ancestor);
						}
						return false;
					}
				}
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return false;
	}
}
