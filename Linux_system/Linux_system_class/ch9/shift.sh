
show_arg() {
while  [ “$1” != “” ]; do
  echo “$# $1”
  shift
done

}
 
 show_arg $*


exit 0

