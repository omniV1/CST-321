#!/bin/bash

# i. Sets the IFS variable to a value of ‘-‘
IFS='-'

# ii. echo "File Name: $0"
echo "File Name: $0"

# iii. echo "First Parameter : $1"
echo "First Parameter : $1"

# iv. echo "Second Parameter : $2"
echo "Second Parameter : $2"

# v. echo "Quoted Values: $@"
echo "Quoted Values: $@"

# vi. echo "Quoted Values: $*"
echo "Quoted Values: $*"

# vii. echo "Total Number of Parameters : $#"
echo "Total Number of Parameters : $#"
