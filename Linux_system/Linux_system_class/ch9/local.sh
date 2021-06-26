#!/bin/bash
n=10
func ()
{
  local n
  let n=n-1
  echo "inner n=$n"
}

echo "1:outer n=$n"
n=$(($n+1))

func
echo "2:outer n=$n"

