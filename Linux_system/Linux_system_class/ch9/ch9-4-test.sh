#!/bin/bash

echo $$
function sum {
	total="0"
	
	for i in $(seq $1 $2 ); do
		let total+=i
	done
	
	echo sum result: "$total"
}

OPTIONS="sum quit"

select opt in $OPTIONS; do
##---if else version---##
#	if [ "$opt" = "sum" ]; then
#		echo Input two numbers:
#		read T1 T2
#		sum $T1 $T2
#	elif [ "$opt" = "quit" ]; then
#		exit 0
#	else
#		clear
#	fi
##---------------------##

##---case version---##
	case "$opt" in
	"sum" )
		echo Input two numbers:
		read T1 T2
		sum $T1 $T2;;
	"quit" ) exit 0;;
	* ) clear;;
	esac
##------------------##
done
