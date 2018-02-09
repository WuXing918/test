#!/bin/bash

cd /media/wuxing/Projects/Projects
pwd
for br in $(ls)
do
	cd $br
	echo $br Cleaning...
	repo forall -c 'git stash'
	repo forall -c 'git clean -xfd'
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
	echo $br Cleaning...
	repo forall -c 'git stash'
	repo forall -c 'git clean -xfd'
	echo $br cleaned!
	echo
	cd ..
done
echo
