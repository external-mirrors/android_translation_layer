asm_jar_path = get_option('asm_jar_path')
asm_tree_jar_path = get_option('asm_tree_jar_path')
getopt_jar_path = get_option('getopt_jar_path')

download_tool_deps = get_option('download_tool_deps')

srcs = ['src/JNIUpcallWrapperGenerator.java']
out = ['jni_upcall_gen', 'JNIUpcallWrapperGenerator.class']
cmd = ['build.py', '--outdir', meson.current_build_dir()]

xmvn_resolve = find_program('xmvn5-resolve', required: (not download_tool_deps) and (asm_jar_path == '' or asm_tree_jar_path == '' or getopt_jar_path == ''))

# try to resolve jar paths if not specified manually
if (asm_jar_path != '')
	have_asm = true
elif (xmvn_resolve.found())
	have_asm = run_command([xmvn_resolve, 'org.ow2.asm:asm'], check: not download_tool_deps).returncode() == 0
else
	have_asm = false
endif

if (asm_tree_jar_path != '')
	have_asmtree = true
elif (xmvn_resolve.found())
	have_asmtree = run_command([xmvn_resolve, 'org.ow2.asm:asm-tree'], check: not download_tool_deps).returncode() == 0
else
	have_asmtree = false
endif

if (getopt_jar_path != '')
	have_getopt = true
elif (xmvn_resolve.found())
	have_getopt = run_command([xmvn_resolve, 'gnu.getopt:java-getopt'], check: not download_tool_deps).returncode() == 0
else
	have_getopt = false
endif

# build path overrides parameter
jar_path_overrides = []

if (asm_jar_path != '')
	jar_path_overrides += ('org.ow2.asm:asm=' + asm_jar_path)
endif

if (asm_tree_jar_path != '')
	jar_path_overrides += ('org.ow2.asm:asm-tree=' + asm_tree_jar_path)
endif

if (getopt_jar_path != '')
	jar_path_overrides += ('gnu.getopt:java-getopt=' + getopt_jar_path)
endif

if (jar_path_overrides != [])
	cmd += ['--path-overrides', ','.join(jar_path_overrides)]
endif

# download remaining dependencies if allowed
if (download_tool_deps and (not have_asm or not have_asmtree or not have_getopt))
	mvn = find_program('mvn-local', 'xmvn', 'mvn', required : true)

	deps_to_get = []
 
	if (not have_asm)
		deps_to_get += 'org.ow2.asm:asm'
	endif
	if (not have_asmtree)
		deps_to_get += 'org.ow2.asm:asm-tree'
	endif
	if (not have_getopt)
		deps_to_get += 'gnu.getopt:java-getopt'
	endif

	cmd += ['--download-and-vendor-in', ','.join(deps_to_get)]
	cmd += ['--use-mvn', mvn]
endif

jni_upcall_gen = custom_target('jni_upcall_gen', output: out, input: srcs, command: cmd)
