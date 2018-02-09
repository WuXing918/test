#!/usr/bin/python
#coding:utf-8
#coding:gbk	
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

def writecheckImgIdsafter(str) :
	fd = file("checkImgResult.cpp", 'a+') 
	fd.writelines(str)          
	fd.close()
	 
	 
def checkImgIds(str):
	#global imgids_h
	file_object = open(imgids_h, 'r')
	file_object.seek(0);
	all_the_text = file_object.read()
	if (all_the_text.find(str) < 0) :
		print 'Not Match:' + str
		writecheckImgIdsafter(str+'\n')
	file_object.close() 
 
def writecheckImgIdsBefore(str) :
	fd = file("checkImgIdsBefore.cpp", 'a+')
	fd.writelines(str)          
	fd.close()

def readIMGStrIDBeforenew() :
	fpr = open("IMGStrIDBeforenew.cpp", 'r')
	total_rows = len(fpr.readlines())
	#print(total_rows)
	fpr.seek(0);
	handle_now = 0  
	if (total_rows < 2) :
		return;
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		if (line.find('.h') >= 0) or (line.find('.cpp') >= 0) or (line.find('.qml') >= 0):
			lineafter = line;
			writecheckImgIdsBefore(line)
			writecheckImgIdsafter(line)
		n = line.find('TEX_PNG_BUHIN_')
		if (n >= 0) :
			line = line[n:]
			writecheckImgIdsBefore(line)
			line1 = line.translate(None, "\n")
			checkImgIds(line1)


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
		if (line.find('.h') >= 0) or (line.find('.cpp') >= 0) or (line.find('.qml') >= 0):
			writeIMGStrIDBeforenew(line)
		n = line.find('TEX_PNG_BUHIN_')
		if(n >= 0):
			new_str=DelLastChar(line)
			linenew = new_str.replace(',','\n')
			line_new = linenew.replace('\"','\n')
			writeIMGStrIDBeforenew(line_new)


def writeIMGStrIDBefore(str) :
	f = file("IMGStrIDBefore.cpp", 'a+')
	f.writelines(str)
	f.close()

# 没有路径
def writecheckList(filename, str) :
	 f = file("checkList.cpp", 'a+')
	 f.writelines(str)          
	 f.close()
	 
#读取路径文件（代码中的文件读取）
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
			writecheckList(filename, line)	
			if (line.find('NQLogger.debug') < 0):
				writeIMGStrIDBefore(reObj1.findall(line))
				writeIMGStrIDBefore('\n')

def readDir(dir):  
    dirid = os.walk(dir)  
    for rootDir, pathList, fileList in dirid: 
        for file in fileList:
			if (os.path.splitext(file)[1] == '.cpp') or (os.path.splitext(file)[1] == '.qml') or (os.path.splitext(file)[1] == '.h') :
				# 写文件路径
				writeIMGStrIDBefore(os.path.join(rootDir, file)+'\n')
				readfile(os.path.join(rootDir, file), file)
				readIMGStrIDBefore()
				readIMGStrIDBeforenew()
				commands.getstatusoutput('rm IMGStrIDBefore.cpp')
				commands.getstatusoutput('rm IMGStrIDBeforenew.cpp')
				
readDir(dir)