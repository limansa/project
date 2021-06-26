#!/bin/sh

key=$1
file=config.txt

 [ $# -eq 1 ] || { echo "Usage : $0 <key>"; exit;}

  grep $key $file | cut -f2 -d'='
 

