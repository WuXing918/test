#!/bin/bash


for br in $(cat wuxing.log)
do
      ls  -Rlh  | grep ${br}.qml | awk -F " " '{print $9,$5}' 
done
echo



