

 [ $# -eq 1 ] || { echo "usage: $0 <if>"; exit; }
 
  ifconfig $1 | grep "inet addr" | cut -f 2 -d':'  | cut -f 1 -d' '
