




 #!/bin/bash 
    sum=0
    COUNTER=20
    until [  $COUNTER -lt 10 ]; do
	 echo COUNTER $COUNTER 
	 let COUNTER-=1
	  sum=$(($sum+$COUNTER))
    done
	echo $sum

