#!/usr/bin/python
import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
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
 
def readIMGStrID() :
	fpr = open("IMGStrIDBefore.cpp", 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	
	handle_now = 0  
	if (total_rows < 2) :
		return;
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		if (line.find('.h') >= 0) or (line.find('.cpp') >= 0) or (line.find('.qml') >= 0):
			writecheckImgIdsBefore(line)
			writecheckImgIdsafter(line)
		n = line.find('TEX_PNG_BUHIN_')
		if (n >= 0) :
			line = line[n:]
			#print line4
			writecheckImgIdsBefore(line6)
			line7 = line6.translate(None, "\n")
			#writecheckImgIdsBefore(line6)
			checkImgIds(line7)
			#print line.translate(None, punctuation)

 
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
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		n = line.find('TEX_PNG_BUHIN_')
		if (n >= 0) :
			writedata1(filename, line)
			if (line.find('//') != 0) and (line.find('NQLogger.debug') < 0):
				line = line[n:]
				linenew = line.replace(',','\n')		
				writedata(linenew)
				

def readDir(dir):  
    dirid = os.walk(dir)  
    for rootDir, pathList, fileList in dirid: 
        for file in fileList:
			if (os.path.splitext(file)[1] == '.cpp') or (os.path.splitext(file)[1] == '.qml') or (os.path.splitext(file)[1] == '.h') :
				writedata(os.path.join(rootDir, file)+'\n')
				readfile(os.path.join(rootDir, file), file)
				readIMGStrID()		
				commands.getstatusoutput('rm IMGStrIDBefore.cpp')	

print 'Start'

readDir(dir)

print 'Done'

