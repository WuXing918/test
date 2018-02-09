#!/usr/bin/python
#-*- coding: UTF-8 -*- 
import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy
ViewInfo_DCU = sys.argv[1]
ScreenList = sys.argv[2]
HmiReturnResult = sys.argv[3]
print ViewInfo_DCU;
print ScreenList;

def writeResult(i, ScreenID, ReturnID, HMIID, ScreenList_ScreenID):
    global HmiReturnResult;
    ExeclID = xlrd.open_workbook(HmiReturnResult)
    HmiReturn = copy(ExeclID)   
    ExeclWrite = HmiReturn.get_sheet(0)
    print '@@@@@@@@'
    print i , ScreenID
    print '@@@@@@@@'
    ExeclWrite.write(i, 1,  HMIID)
    ExeclWrite.write(i, 2,  ReturnID)
    ExeclWrite.write(i, 3,  ScreenID)	
    ExeclWrite.write(i, 4,  ScreenList_ScreenID)		
    HmiReturn.save(HmiReturnResult) 

def compare(i, ScreenID):
	data = xlrd.open_workbook(ScreenList)
	table = data.sheet_by_index(1) 
	nrows = table.nrows
	for j in range(7, nrows)  :
		ScreenList_ScreenID = table.cell(j,6).value 
		print "screenList = ",ScreenList_ScreenID; 
		if(cmp(len(ScreenList_ScreenID),len(ScreenID)) == 0):
			n = ScreenList_ScreenID.find(ScreenID) 
			if (n >= 0) :
				ReturnID = table.cell(j,86).value
				HMIID = table.cell(j,87).value
				print "-------------------"
				print i
				print ScreenID
				print ScreenList_ScreenID
				print ReturnID
				print HMIID
				print "-------------------"
				writeResult(i, ScreenID, ReturnID, HMIID, ScreenList_ScreenID)
				break; 
				
	if((j+1) >= nrows):
		print "===================="
		print i
		print ScreenID
		print "===================="
		#writeResult(i, "", "")
		#writeResult(i, ScreenID, "", "", "")
		
def readViewInfo():
	data = xlrd.open_workbook(ViewInfo_DCU)
	table = data.sheet_by_index(7) 
	nrows = table.nrows
	print nrows
	for i in range(8, nrows)  : 
		ScreenID = table.cell(i,4).value
		#print ScreenID;
		compare(i, ScreenID)
		

readViewInfo()

















