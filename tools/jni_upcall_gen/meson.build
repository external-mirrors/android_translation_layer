download_tool_deps = get_option('download_tool_deps')

srcs = ['src/JNIUpcallWrapperGenerator.java']
out = ['jni_upcall_gen', 'JNIUpcallWrapperGenerator.class']
cmd = ['build.py', '--outdir', meson.current_build_dir()]

if (download_tool_deps)
	cmd += ['--download-and-vendor-in', 'org.ow2.asm:asm,org.ow2.asm:asm-tree,gnu.getopt:java-getopt']
	cmd += ['--use-mvn', 'mvn']
endif

jni_upcall_gen = custom_target('jni_upcall_gen', output: out, input: srcs, command: cmd)
