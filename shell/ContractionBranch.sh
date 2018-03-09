#! /bin/bash

cd /media/wuxing/Projects/Projects
pwd

for br in $(ls)
do
	cd $br
	echo $br  clean branch...
	repo forall -c git gc
	echo $br cleaned!
	echo
	cd ..
done
echo

cd /home/wuxing/17Cy_Pro
pwd

for br in $(ls)
do
	cd $br
	echo $br  clean branch...
	repo forall -c git gc
	echo $br cleaned!
	echo
	cd ..
done
echo


