#!/usr/bin/python3
# -*- coding: utf8 -*-

import os
import re
import getopt, sys
import subprocess

def main(module,runs,compiler):
	compiler = compiler.replace('+','');

	print("executing unit tests …", end=" ", flush=True)
	try:
		subprocess.call('./check_{}'.format(module), stdout=subprocess.PIPE)
	except Exception as e:
		raise e

	print(" passed.")

	print("executing {} runs:".format(runs))
	matches = {}
	for i in range (0, runs):
		print(str(i), end=" ", flush=True)
		cmd = './bench_{} 2> /dev/null'.format(module, i)
		string = os.popen(cmd).read()
		strMeasurement = r'^({}_\w*)\s*\d* ns\s*(\d*)'.format(module)
		rMeasurement = re.compile(strMeasurement, re.M)
		res = re.findall(rMeasurement, string)
		for mes in res:
			if mes[0] in matches:
				matches[mes[0]] += [mes[1]]
			else:
				matches[mes[0]] = [mes[1]]

	print('… done.')

	print(matches)
	for key in matches:
		matches[key].sort()

	mins = {key: m[0] for key, m in matches.items()}
	print(mins)

	texfile_path = module + ".tex"
	subprocess.call(['sed','-i','/{}/d'.format(compiler),texfile_path],stdout=subprocess.PIPE)

	texfile = open(texfile_path, 'a')
	texfile.write('% CXX!?\n')
	texfile.write('\\newcommand{{\\{}Z{}Zruns}}{{{}}}\n'.format(compiler,module, runs))

	# mangle names
	for key, mini in mins.items():
		cmd = "\\newcommand{{\\{}Z{}}}{{{}}}\n".format(compiler, key.replace('_','Z'), mini)
		texfile.write(cmd)

	texfile.close()
	

if __name__ == '__main__':
	# main("hash",3,"GCC")
	import argparse

	parser = argparse.ArgumentParser(description='Drive the benchmarks.')
	parser.add_argument('-m', dest='module', help='the module to execute', type=str)
	parser.add_argument('-r', dest='runs', help='number of runs', type=int)
	parser.add_argument('-c', dest='compiler', help='the used compiler', type=str)

	args = parser.parse_args()
	main(args.module, args.runs, args.compiler)
