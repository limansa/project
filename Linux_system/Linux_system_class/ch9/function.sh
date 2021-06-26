
  sum () 
          {
             sum=0
             for i in `seq $1 $2`;
                do
			     sum=$(($sum+$i))
                done	
			return $sum
           }
           sum 1 10
		   n=$?
		   echo $n

