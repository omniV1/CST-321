#!/bin/bash

# Script to print and search names from a file

if [ $# -lt 2 ]; then
  echo "Usage: $0 <filename> <name_to_search>"
  exit 1
fi

filename=$1
name_to_search=$2
found=0

echo "Sorted names from $filename:"
while read name; do
  echo $name
  if [[ $name == $name_to_search ]]; then
    found=1
    break # once we find the name, we can exit the loop
  fi
done < <(sort $filename) # process substitution to avoid a subshell

if [ $found -eq 1 ]; then
  echo "Name '$name_to_search' found in file."
else
  echo "Name '$name_to_search' not found in file."
fi
