#!/bin/bash

# Script to print all files in the current directory

for file in $(ls); do
  echo "File: $file"
done
