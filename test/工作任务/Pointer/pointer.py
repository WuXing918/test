#!/usr/bin/python
# encoding=utf-8

import os
import sys
import xlwt
import xlrd
import xlutils.copy
import re	
import commands
defaultencoding = 'utf-8'

dir = sys.argv[1]
row_num = 0
func_text = ""

	
# define the stack
# stack is defined

def WriteExecl(line,row, line_num):
	data = xlrd.open_workbook('excelFile.xls')
	wb = xlutils.copy.copy(data)
	workbook = wb.get_sheet(0)  
#    line = line.decode("utf-8")	
#	row = row.decode("utf-8")
#	line_num = line_num.decode("utf-8")
	workbook.write(row, line_num, line) 
	wb.save('excelFile.xls')
	

def ReadcurrentFile(filehasPath,file):
	fpr = open(filehasPath, 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	handle_now = 0 
	global row_num
	global func_text
	L = filehasPath.find('QmlApps/')
	#print filehasPath[L+8:];
	WriteExecl(filehasPath[L+8:], row_num, 0);
	row_num = row_num + 1;
	
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		n = line.find(' ' + os.path.splitext(file)[0] + '::')
		if (n >= 0) :
			func_text = line;
			try :
				WriteExecl(unicode(line[:-1]), row_num, 1);
			except :
				print "*******************************************************"
				print line[:-1]
			row_num = row_num + 1;
			
			#print line;
		else:
			reObj1 = re.compile('\w+\-\>') 
			m = reObj1.findall(line)
			if (len(m)) :
				if (len(m) > 1) :
					# write the pointer
					WriteExecl(m, row_num, 2);
					# write line number
					WriteExecl(read_row, row_num, 3);
					
					L = filehasPath.find('QmlApps/')
					WriteExecl(filehasPath[L+8:], row_num, 0);
					WriteExecl(func_text[:-1], row_num, 1);
					row_num = row_num + 1;
					#print m
				else :
					if (str(m[0]) == "this->") :
						print "pass it"
					else :
						WriteExecl(m[0][:-2], row_num, 2);
						WriteExecl(read_row, row_num, 3);
						L = filehasPath.find('QmlApps/')
						WriteExecl(filehasPath[L+8:], row_num, 0);
						WriteExecl(func_text[:-1], row_num, 1);
						row_num = row_num + 1;
						#print m

def readDir(dir):  
    dirid = os.walk(dir)  
    for rootDir, pathList, fileList in dirid: 
        for file in fileList:
			if ((os.path.splitext(file)[1] == '.cpp') and ((os.path.splitext(file)[0]).find('Test') != 0) and ((os.path.splitext(file)[0]).find('Mock') != 0)):
				# read the .cpp
				print os.path.splitext(file)[0]
				ReadcurrentFile(os.path.join(rootDir, file),file);
			else :
				print os.path.splitext(file)[0]



readDir(dir)