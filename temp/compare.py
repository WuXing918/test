#!/usr/bin/python

import os
import sys
import xlrd
import xlwt
from xlutils.copy import copy 

def readscreen(eachLine):
	data = xlrd.open_workbook("ViewInfo_DCU.xlsx")
	table = data.sheet_by_index(0) 
	nrows = table.nrows
	for i in range(3, nrows) :
		ScreenID = table.cell(i,0).value
		num = ScreenID.find(eachLine);
        if num > 0:
            print eachLine

	

def readfile():
    fin = open("fenge.log", 'r')
    for eachLine in fin: 
        eachLine=eachLine.strip('\n')       
        #print eachLine
        readscreen(eachLine)

readfile()
