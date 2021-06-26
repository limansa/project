#!/bin/shfunction sum {
  sum=0
    
   [ ! $# -eq 2 ] && { echo Usage:$0 num1 num2; exit; }
      
  a=$1
  b=$2

  while [ $a -le $b ] ; do 
    
     sum=`expr $sum + $a`
     a=`expr $a + 1`
  done  

 }  
  
  sum 1 
  echo $sum

 


