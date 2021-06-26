
#!/bin/sh





for i in $(ls *.[ch]) ;do
  
   sed  -f copy.sed $i > tmpfile
   cp tmpfile $i
  
   
   

done
