#!/usr/bin/python


def readfile():
    fin = open("screen.log", 'r')
    for eachLine in fin: 
        eachLine=eachLine.strip('\n')       
        num = eachLine.rfind('/') 
        print eachLine[num+1:]

        #match(eachLine)

readfile()
