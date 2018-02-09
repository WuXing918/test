#!/usr/bin/python

import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import commands
			
commands.getstatusoutput('rm *.cpp*')
print 
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
	if (all_the_text.find(str) >= 0) :
		print "ok!"
	else :
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
	print(total_rows)
	fpr.seek(0);
	
	handle_now = 0  
	
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		n = line.find('TEX_PNG_BUHIN_')
		if (n >= 0) :
			line = line[n:]
			line1 = line.translate(None, "\"")
			line2 = line1.translate(None, ";")
			line3 = line2.translate(None, ")")
			line4 = line3.translate(None, "]")
			line5 = line4.translate(None, " ")
			line6 = line5.translate(None, "}")
			
			#print line4
			writecheckImgIdsBefore(line6)
			line7 = line6.translate(None, "\n")
			#writecheckImgIdsBefore(line6)
			checkImgIds(line7)
			#print line.translate(None, punctuation)

		
def writedata(filename, str) :
	 f = file("IMGStrIDBefore.cpp", 'a+')
	 f.writelines(str)          
	 f.close()

def writedata1(filename, str) :
	 f = file("checkList.cpp", 'a+')
	 f.writelines(filename+'\n')
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
		if (line.find('//') != 0) :
			n = line.find('TEX_PNG_BUHIN_')
			if (n >= 0) :
				line = line[n:]
				linenew = line.replace(',','\n')
						
				writedata(filename, linenew)
				writedata1(filename, linenew)

# 
def readDir(dir):  
    dirid = os.walk(dir)  
    for rootDir, pathList, fileList in dirid: 
        for file in fileList:
			if (os.path.splitext(file)[1] == '.cpp')|(os.path.splitext(file)[1] == '.qml') :
				 
				readfile(os.path.join(rootDir, file), file)
				
readDir(dir)
readIMGStrID()