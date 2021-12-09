import glob
import os
from subprocess import run, PIPE
import time


def dump_cpp_output(result: str, filepath: str):
	with open(filepath, "w") as out_file:
		out_file.write(result)


def exec(cpp_file: str, destination_dir: str):
	exe_name = cpp_file.replace(".cpp", ".exe")
	out_name = os.path.join(destination_dir, os.path.basename(cpp_file)).replace(".cpp", ".out")
	print(f"Output file name: {out_name}")
	
	if "musicstream" in cpp_file:
		aux_cpp = f"MusicStream.cpp Song.cpp Album.cpp Artist.cpp Playlist.cpp Profile.cpp"
	else:
		aux_cpp = ""
	cmd = f"g++ {cpp_file} {aux_cpp} -ansi -Wall -pedantic-errors -O0 -o {exe_name}"
	os.system(cmd)
	try:
		result = run([exe_name], stdout=PIPE, stderr=PIPE, universal_newlines=True)
	except FileNotFoundError:
		print("File not found")
	else:
		dump_cpp_output(result.stdout, out_name)
		os.remove(exe_name)

	


if __name__ == '__main__':
	wd = os.path.abspath(os.path.dirname(__file__))
	mains_dir = os.path.join(wd, "mains")
	output_dir = os.path.join(wd, "actual_outputs")
	file_list = glob.glob(mains_dir + "/*")

	for file in file_list:
		exec(file, output_dir)