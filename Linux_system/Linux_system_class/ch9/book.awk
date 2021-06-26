
BEGIN {
i=0;
}

$3 > 20.0 {i=$3+i;} 

END {
  printf("totaal price %6.2f\n",i)

}
