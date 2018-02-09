#/bin/bash


echo $1

name=$(find $1 -name "*.qml")
#echo $name
ls -l $name | awk '{print $5 " " $9}' 
