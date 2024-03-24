#!/bin/bash

# Script to display numbers 1 through 10 using a while loop

counter=1

while [ $counter -le 10 ]; do
  echo "Number $counter"
  ((counter++))
done
