#!/usr/bin/python
#coding:utf-8
#coding:gbk	
import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re

dir = sys.argv[1]
StrIds = sys.argv[2] 
Result = sys.argv[3]

os.system("echo /dev/null > output.txt");

def statement(str) :
	f = file(Result, 'a+')
	f.writelines(str)
	f.close()
	
	
def checkout(line):
	print line;
	os.system(line);
	
	
def ReadStrResID():
	fpr = open(StrIds, 'r')
	total_rows = len(fpr.readlines())
	print(total_rows)
	fpr.seek(0);
	
	handle_now = 0  
	if (total_rows == 0) :
		print "StrRes is 0 !"
		return;
	for read_row in range(handle_now, total_rows) :		
		line = fpr.readline()
		line1 = line[0:22]
		print line1;
		#print '----------------'
		#line1 = line.translate(None, "\n");
		#print line1;
		print "----------------"
		str = "grep " + "\"" + line1 + "\"" + " -nr " + dir + " >> " + Result
		checkout(str);
		print "--------------------------------------------------------------"
		statement("----------------------------------------------------------\n")
		

ReadStrResID();