trap 'echo dont hang up' 1
echo $$

while true
do
      echo "try to hang up" 
  sleep 1
done

