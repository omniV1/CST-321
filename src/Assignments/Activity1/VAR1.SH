#!/bin/sh

#taken from examples in page 10 of activity guide

# Create a variable and export it for this shell as well as other processes
MYVAR=" This is a test "
 export MYVAR;
echo " #########################"
echo " ######## VS1.SH #########"
echo " ##########################"
printenv

# call another script
exec ./var2.sh # Run in same process and wait for it to complete
#exec ./var2.sh $ # Run in samethe background (and not block)
#exec .var2.sh > test.txt
