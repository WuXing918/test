#!/usr/bin/python

import re		
imgids_h = '../../../17Cy_Master/board/dcu/m2n/Resource/res/include/' + 'ImgIds.h'

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
	fpr = open("IMGStrIDBeforenew.cpp", 'r')
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
 
			writecheckImgIdsBefore(line)
			line1 = line.translate(None, "\n")
			 
			checkImgIds(line1)
			#print line.translate(None, punctuation)






def DelLastChar(str):
	str_list=list(str)
	str_list.pop()
	return "".join(str_list)


def writedata(str) :
	f = file("IMGStrIDBeforenew.cpp", 'a+')
	f.writelines(str)
	f.close()


def readfile() :
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
		
readfile()

#
#




























