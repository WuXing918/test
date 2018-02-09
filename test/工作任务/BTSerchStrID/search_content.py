#!/usr/bin/python
#coding:utf-8
#coding:gbk	
import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re
Searchpath = sys.argv[1]
StrIdsPath = sys.argv[2]
i = 0
num = 0
filterType = ['gif','png','bmp','jpg','jpeg','rar','zip',
            'ico','apk','ipa','doc','docx','xls','jar',
            'xlsx','ppt','pptx','pdf','gz','pyc','class',
			'dat']

def writeStrID(str):
    global m
    fd = open("Result.txt", "a+")
    print str 	
    fd.writelines(str);
    fd.writelines('\n');
    fd.close()
			
def search(path=None,cont=None):
    if not path or not cont:
        print('path or searchString is empty')
        return	
	global num
    _loopFolder(path,cont)
    if num == 0 :
        print cont,("%s file find" % num);
        
	
	
def _loopFolder(path,cont):
    arr = path.split('/')
    if not arr[-1].startswith('.'): #不检查隐藏文件夹
        if os.path.isdir(path):
            folderList = os.listdir(path)
            for x in folderList:
                _loopFolder(path+"/"+x,cont)
        elif os.path.isfile(path):
            _verifyContent(path,cont)
 
def _verifyContent(path,cont):
    if path.split('.')[-1].lower() in filterType:
        return
    global num
    fh = open(path,'r')
    fhContent = fh.readlines()
    fh.close()
    for index,x in enumerate(fhContent):
        if cont in x:
            num += 1
            #print("%s    %s" % (path,index+1))
            break
    return




# find the the StrID of StrIds.h file    so  many
def StrIds() :
	global i;
	fpr = open(StrIdsPath, 'r')
	total_rows = len(fpr.readlines())
	fpr.seek(0);
	#print total_rows;
	
	for read_row in range(0, total_rows) :		
		line = fpr.readline()
		n = line.find('"STR_')
		m = line.find('"MSG_')
		q = line.find('/*')
		global num
		if (q < 0) :
			if (n >= 0) :
				line_n = line[n+1:-4]
				i+= 1;
				#print line_n;
				num = 0;
				search(Searchpath, line_n)
			if (m >= 0) :
				i+= 1;
				line_m = line[m+1:-4]
				#print line_m;
				num = 0;
				search(Searchpath, line_m)
				
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("invalid parameters")
    else:
        StrIds();	