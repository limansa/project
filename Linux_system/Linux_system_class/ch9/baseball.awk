
BEGIN {
i=0;
max=0;
line=0;
}

$1 == "A"  {i=$4+i} 
$4 > max { max=$4;line=$0; }
END {
  printf("Total HomeRuns of player A is  %6.2f\n",i)
  printf("the maximum HomeRuns of player is==>%s\n",line)

}
