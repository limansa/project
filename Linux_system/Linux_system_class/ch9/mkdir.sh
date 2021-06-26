#/bin/bash

function MKDIR() {

 COUNTER=1
 today=$(date +%Y%m%d)
while [  $COUNTER -le 10 ]
do
  
   dirname="$HOME/testdir_${today}_${COUNTER}"
   mkdir $dirname
   let COUNTER=COUNTER+1 
done

}

  MKDIR
