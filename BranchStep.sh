#!/bin/bash

cd /media/wuxing/Projects/Projects
pwd

for br in $(ls)
do
	cd $br
	echo $br  clean branch...
	repo forall -c git gc
	echo $br cleaned!
    
    echo $br Cleaning...
	repo forall -c 'git stash'
	repo forall -c 'git clean -xfd'
	echo $br cleaned!
    
    echo $br Updating...
	repo sync 
	echo $br updated...
    
	echo
	cd ..
done
echo


