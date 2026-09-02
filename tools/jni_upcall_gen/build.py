#!/usr/bin/env python
# SPDX-License-Identifier: GPL-3.0-only
import argparse
import os
import subprocess
import stat
import sys

MVN_TMP_DIR = "/dev/shm/junk"

srcs = [
	"JNIUpcallWrapperGenerator.java"
]

deps = [
	"org.ow2.asm:asm",
	"org.ow2.asm:asm-tree",
	"gnu.getopt:java-getopt",
]

deps_system = []
deps_vendor = []

deps_system_classpath = ""
deps_vendored_classpath = ""

parser = argparse.ArgumentParser()
parser.add_argument("--outdir", metavar="path-to-outdir",
                    help="Comma separated list of maven artifact names to download " +
                         "and vendor in instead of using them from the system.")
parser.add_argument("--download-and-vendor-in", metavar="dep1,dep2,...",
                    help="Comma separated list of maven artifact names to download " +
                         "and vendor in instead of using them from the system.")
parser.add_argument("--use-mvn", default="mvn-local", metavar="mvm-executable-name",
                    help="Use specified mvn executable. Default is mvn-local, " +
                         "which should be a symlink to xmvn. If you have neither, " +
                         "plain mvn also works but will download more junk.")
args = parser.parse_args()

script_dir = os.path.dirname(os.path.realpath(__file__))
out_dir = args.outdir

if(out_dir == None):
	print("error: must specify output directory with --outdir")
	sys.exit(1)

vendored_libs_dir = out_dir+"/vendored_deps"

deps_to_vendor = args.download_and_vendor_in.split(",") if args.download_and_vendor_in else []
mvn_executable = args.use_mvn

for dep in deps:
	if dep in deps_to_vendor:
		deps_vendor.append(dep);
	else:
		deps_system.append(dep);

if deps_system:
	# TODO: don't want -r for compilation actually?
	p = subprocess.run(["xmvn5-resolve", "-rc"] + deps_system, capture_output=True, text=True)
	deps_system_classpath = p.stdout.strip()
	if not deps_system_classpath:
		print("xmvn5-resolve returned an error, exiting:\n")
		print(p.stderr)
		sys.exit(1)

if deps_vendor:
	for dep in deps_vendor:
		subprocess.run([mvn_executable, "-Duser.home="+MVN_TMP_DIR, "dependency:copy", "-DoutputDirectory="+vendored_libs_dir, "-Dartifact="+dep+":LATEST"])
	for jarfile in os.listdir(vendored_libs_dir):
		deps_vendored_classpath += ":"+vendored_libs_dir+"/"+jarfile # TODO: shouldn't put : before first member

# ensure <outdir>/ exists
os.makedirs(out_dir, exist_ok=True)

# prepare wrapper
wrapper_template = open(script_dir+"/jni_upcall_gen.in").read();

install_classpath = ""
define_javadir = "" # don't insert a definition unless needed
define_vendored_deps_dir = "" # ditto

if deps_system:
	for path in deps_system_classpath.split(":"):
		if install_classpath: # no path separator before first path
			install_classpath += ":\\\n"
		if path.startswith("/usr/share/java"): # make the common case look cleaner
			install_classpath += "${javadir}" + path.removeprefix("/usr/share/java")
			define_javadir = "\njavadir=/usr/share/java # path to distro-packaged jars\n"
		else:
			install_classpath += path

if deps_vendor:
	define_vendored_deps_dir = "vendored_deps_dir=${libdir}/vendored_deps/ # path to vendored jars\n"
	for jarfile in os.listdir(vendored_libs_dir):
		if install_classpath: # no path separator before first path
			install_classpath += ":\\\n"
		install_classpath += "${vendored_deps_dir}/" + jarfile

wrapper_final = wrapper_template.format(define_vendored_deps_dir=define_vendored_deps_dir, define_javadir=define_javadir, install_classpath=install_classpath)

wrapper_file_path = out_dir + "/jni_upcall_gen"
wrapper_file = open(wrapper_file_path, mode="w")
wrapper_file.write(wrapper_final)
wrapper_file.close()
os.chmod(wrapper_file_path, 0o755)

# compile the tool
subprocess.run(["javac", "-d", out_dir, "-cp", deps_system_classpath+deps_vendored_classpath] + srcs, cwd=script_dir+"/src/")
