# Check if an argument was provided 

if [ -z "$1" ]; then 

echo "No input file provided."
echo "Usage: ./compile.sh <filename_without _extension>"
exit 1

fi

PROGRAM_NAME=$1

# COMPILE THE C PROGRAM_NAME
gcc $PROGRAM_NAME.c -o $PROGRAM_NAME
GCC_RETURN_CODE=$?


# CHECK IF WORKS
if [ $GCC_RETURN_CODE -eq 0 ]; then

echo "IT WORKS..RUNNING>>>"
./$PROGRAM_NAME
else

echo "It doesnt work...return code: $GCC_RETURN_CODE."
exit $GCC_RETURN_CODE

fi
