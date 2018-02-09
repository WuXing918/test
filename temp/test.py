#!/usr/bin/python
import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 

def readscreen():
	data = xlrd.open_workbook("ViewInfo_DCU.xlsx")
	table = data.sheet_by_index(0) 
	nrows = table.nrows
	print nrows
	for i in range(3, nrows) :
		ScreenID = table.cell(i,0).value
		print ScreenID;

readscreen();
