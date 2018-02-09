#!/usr/bin/python
#coding:utf-8
#coding:gbk	

import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re
ScreenControl = sys.argv[1]
ViewInfo_DCU = sys.argv[2]


def wrtitethree(i, ViewID, ScreenID, SmartDestination, DestSetting, ScreenControl_ScreenID) :
	ExeclID = xlrd.open_workbook('screenControl.xls','W')
	HmiReturnResult = copy(ExeclID)
	ExeclWrite = HmiReturnResult.get_sheet(0)
	ExeclWrite.write(i, 5, ViewID)
	ExeclWrite.write(i, 6, ScreenID)
	ExeclWrite.write(i, 7, ScreenControl_ScreenID)
	ExeclWrite.write(i, 8, SmartDestination)
	ExeclWrite.write(i, 9, DestSetting)
	HmiReturnResult.save('screenControl.xls')


def findViewIDMap(i, ScreenID, ViewID, SmartDestination):
	data = xlrd.open_workbook(ScreenControl)
	table = data.sheet_by_index(1) 
	nrows = table.nrows
	print "-----start------"
	print nrows
	print "screen = ", ScreenID;
	for j in range(11, nrows) :
		ScreenControl_ScreenID = table.cell(j,1).value
		#print ScreenControl_ScreenID;
		DestSetting = table.cell(j,34).value

		if(cmp(len(ScreenControl_ScreenID),len(ScreenID)) == 0):
			n = ScreenControl_ScreenID.find(ScreenID)
			if (n >= 0) :
				print "ScreenNo", ScreenControl_ScreenID, DestSetting
				wrtitethree(i, ViewID, ScreenID, SmartDestination, DestSetting, ScreenControl_ScreenID);
				return;



def readscreen():
	data = xlrd.open_workbook(ViewInfo_DCU)
	table = data.sheet_by_index(0) 
	nrows = table.nrows
	print nrows
	for i in range(2, nrows) :
		ScreenID = table.cell(i,19).value
		ViewID = table.cell(i,0).value
		SmartDestination = table.cell(i,21).value
		#print ScreenID;
		findViewIDMap(i, ScreenID, ViewID, SmartDestination)
	
	
	
readscreen();
