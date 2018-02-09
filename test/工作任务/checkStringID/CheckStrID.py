#!/usr/bin/python
#coding:utf-8
#coding:gbk

import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re

checkPath = sys.argv[0]
StrIdsPath = sys.argv[1]
print checkPath
print StrIdsPath 


#	
#MSG_04_02_01_RES_00         19
#MSG_MM_00_02_00_54_RES_00   25
#STR_MM_07_33_12_RES_04      22
#STR_MM_17_01_02_RES_138
#MSG_MSG_MM_00_02_00_46_RES_00
#MSG_07_23_12_RES_00






def writeStrID(str):
	fd = open("wuxing.txt", "a+")
	fd.writelines(str)
	fd.close()
	

def StrIds() :
	i = 0;
	fpr = open(StrIdsPath, 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	print total_rows;
	
	for read_row in range(0, total_rows) :		
		line = fpr.readline()
		n = line.find('"STR_')
		m = line.find('"MSG_')
		q = line.find('/*')
		if (q < 0) :
			if (n >= 0) :
				line_n = line[n+1:-4]
				print line_n;
				writeStrID(line_n)
				writeStrID("\n")
				i+= 1;
			if (m >= 0) :
				line_m = line[m+1:-4]
				print str;
				writeStrID(line_m)
				writeStrID("\n")
				i+= 1;
				
	print i;			
	print total_rows;			
				
				
				
				
				
				
				
				
				
				
StrIds();
		
				
				
				