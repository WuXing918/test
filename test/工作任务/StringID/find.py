#!/usr/bin/python
import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re	
import commands
			
commands.getstatusoutput('rm *.cpp*')

dir = sys.argv[1]
imgids_h = sys.argv[2] + 'ImgIds.h'
print dir

def DelLastChar(str):
	str_list=list(str)
	str_list.pop()
	return "".join(str_list)

def writeIMGStrIDBeforenew(str) :
	f = file("IMGStrIDBeforenew.cpp", 'a+')
	f.writelines(str)
	f.close()

def readIMGStrIDBefore() :
	fpr = open("IMGStrIDBefore.cpp", 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	handle_now = 0  
	disconnect_num = 0  
	
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		new_str=DelLastChar(line)
		linenew = new_str.replace(',','\n')
		line_new = linenew.replace('\"','\n')
		writedata(line_new)


def writedata(str) :
	f = file("IMGStrIDBefore.cpp", 'a+')
	f.writelines(str)
	f.close()

def writedata1(filename, str) :
	 f = file("checkList.cpp", 'a+')
	 f.writelines(str)          
	 f.close()

def readfile(filename, file) :
	# read file the total line
	fpr = open(filename, 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	handle_now = 0  
	disconnect_num = 0  
	reObj1 = re.compile(r'(TEX_PNG_BUHIN_.*?[,|"])')
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		n = line.find('TEX_PNG_BUHIN_')
		if (n >= 0) :
			writedata1(filename, line)	
			if (line.find('NQLogger.debug') < 0):
				writedata(reObj1.findall(line))
				writedata('\n')

def readDir(dir):  
    dirid = os.walk(dir)  
    for rootDir, pathList, fileList in dirid: 
        for file in fileList:
			if (os.path.splitext(file)[1] == '.cpp') or (os.path.splitext(file)[1] == '.qml') or (os.path.splitext(file)[1] == '.h') :
				commands.getstatusoutput('rm IMGStrIDBefore.cpp')
				writedata(os.path.join(rootDir, file)+'\n')
				readfile(os.path.join(rootDir, file), file)
				readIMGStrIDBefore()
				#readIMGStrID()		
					

print 'Start'

readDir(dir)

print 'Done'

