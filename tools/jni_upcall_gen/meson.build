download_tool_deps = get_option('download_tool_deps')

srcs = ['src/JNIUpcallWrapperGenerator.java']
out = ['jni_upcall_gen', 'JNIUpcallWrapperGenerator.class']
cmd = ['build.py', '--outdir', meson.current_build_dir()]

xmvn_resolve = find_program('xmvn5-resolve', required: not download_tool_deps)

have_asm = run_command([xmvn_resolve, 'org.ow2.asm:asm'], check: not download_tool_deps).returncode() == 0
have_asmtree = run_command([xmvn_resolve, 'org.ow2.asm:asm-tree'], check: not download_tool_deps).returncode() == 0
have_getopt = run_command([xmvn_resolve, 'gnu.getopt:java-getopt'], check: not download_tool_deps).returncode() == 0

if (download_tool_deps and (not have_asm or not have_asmtree or not have_getopt))
	mvn = find_program('mvn-local', 'xmvn', 'mvn', required : true)

	deps_to_get = []
 
	if (xmvn_resolve.found())
		if (not have_asm)
			deps_to_get += 'org.ow2.asm:asm'
		endif
		if (not have_asmtree)
			deps_to_get += 'org.ow2.asm:asm-tree'
		endif
		if (not have_getopt)
			deps_to_get += 'gnu.getopt:java-getopt'
		endif
	else
		deps_to_get = ['org.ow2.asm:asm','org.ow2.asm:asm-tree','gnu.getopt:java-getopt']
	endif

	cmd += ['--download-and-vendor-in', ','.join(deps_to_get)]
	cmd += ['--use-mvn', mvn]
endif

jni_upcall_gen = custom_target('jni_upcall_gen', output: out, input: srcs, command: cmd)
