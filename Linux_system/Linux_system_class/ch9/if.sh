#!/bin/bash

a=2
b=4
if [ $a -eq 2 ] && [ $b -eq 3 ] ; then 
  echo "1"
elif  [ $a -eq 12 ] || [ $b -eq 41 ] ; then
   echo "2"
else 
   echo "3"
fi
