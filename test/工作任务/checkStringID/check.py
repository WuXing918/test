#!/usr/bin/python
#coding:utf-8
#coding:gbk

import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re

Result = sys.argv[1]
dir = sys.argv[2]
def statement(line) :
	fpr = open("nihao.txt", 'a+')
	fpr.writelines('-----------------------------------------------------------------\n');
	fpr.writelines(line)
	fpr.close()


def checkout(str,line):
	print line;
	os.system(str);

def checkoutStr():
	fpr = open("wuxing.txt", 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	print total_rows;
	
	for read_row in range(0, total_rows) :	
		line = fpr.readline()
		line_n = line[:-1];
		print '------------------------------------------------------------'
		print line_n;
		statement(line);
		str = "grep " + "\"" + line_n + "\"" + " -nr " + dir + " >> " + Result
		checkout(str,line);
		print '------------------------------------------------------------'
	
	
checkoutStr();