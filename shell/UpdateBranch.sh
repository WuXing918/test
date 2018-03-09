#! /bin/bash

cd /media/wuxing/Projects/Projects
pwd
for br in $(ls)
do
	cd $br
	echo $br Updating...
	repo sync 
	echo $br updated...
	echo
	cd ..
done
echo

cd /home/wuxing/17Cy_Pro
pwd
 
for br in $(ls)
do
	cd $br
	echo $br Updating...
	repo sync 
	echo $br updated...
	echo
	cd ..
done
echo


