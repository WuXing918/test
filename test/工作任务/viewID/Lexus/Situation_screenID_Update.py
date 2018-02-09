#!/usr/bin/python
#coding:utf-8
#coding:gbk	

import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 
import re
MapOverlay = sys.argv[1]
ViewInfo_DCU = sys.argv[2]
def wrtitethree(i, ScreenList_ScreenID, type_creenID, StatusBarInfo, FocusControlMode, CdRatioPattern, Clock, SubViewIcon) :
	ExeclID = xlrd.open_workbook('screen_3_25Lexus.xls')
	HmiReturnResult = copy(ExeclID)   
	ExeclWrite = HmiReturnResult.get_sheet(0)
	ExeclWrite.write(i, 10, ScreenList_ScreenID)
	ExeclWrite.write(i, 11, type_creenID)
	
	ExeclWrite.write(i, 13, StatusBarInfo)
	ExeclWrite.write(i, 15, FocusControlMode)
	ExeclWrite.write(i, 17, CdRatioPattern)
	ExeclWrite.write(i, 19, Clock)
	ExeclWrite.write(i, 21, SubViewIcon)
	
	HmiReturnResult.save('screen_3_25Lexus.xls')




def findViewIDMap(i, ScreenID):
	data = xlrd.open_workbook(MapOverlay)
	table = data.sheet_by_index(2) 
	nrows = table.nrows
	print "-----start------"
	print nrows
	print "screen = ", ScreenID;
	for j in range(11, nrows) :
		ScreenList_ScreenID = table.cell(j,0).value
		print ScreenList_ScreenID;
		type_creenID = table.cell(j,3).value
		
		StatusBarInfo = table.cell(j,6).value
		FocusControlMode = table.cell(j,12).value
		CdRatioPattern = table.cell(j,17).value
		Clock = table.cell(j,10).value
		SubViewIcon = table.cell(j,9).value
		if(cmp(len(ScreenList_ScreenID),len(ScreenID)) == 0):
			n = ScreenList_ScreenID.find(ScreenID)
			if (n >= 0) :
				print "ScreenNo", ScreenList_ScreenID, type_creenID
				wrtitethree(i, ScreenList_ScreenID, type_creenID, StatusBarInfo, FocusControlMode, CdRatioPattern, Clock, SubViewIcon);
				return;
	print "------end-------"



def readscreen():
	data = xlrd.open_workbook(ViewInfo_DCU)
	table = data.sheet_by_index(0) 
	nrows = table.nrows
	print nrows
	for i in range(2, nrows) :
		ScreenID = table.cell(i,19).value
		print ScreenID;
		findViewIDMap(i, ScreenID);
	
	
	
#findViewIDMap("view");	
readscreen();






