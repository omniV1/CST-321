#!/bin/bash

echo "Starting script..."

# i. Change directory to your home directory.
echo "Changing to home directory..."
cd ~
echo "Now in $(pwd)"

# ii. Create a child directory called mycode.
echo "Creating directory 'mycode'..."
mkdir -p mycode
echo "'mycode' directory created."

# iii. Change to the mycode directory.
echo "Changing to 'mycode' directory..."
cd mycode
echo "Now in $(pwd)"

# iv. Copy all files that end with .c from the specified course directory to the mycode directory.
echo "Copying .c files from course directory to 'mycode'..."
cp /c/git/CST-321/src/Topic6/c_programs/*.c .
echo "Copy complete. Files in 'mycode':"
ls

# v. Navigate up a directory.
echo "Navigating up a directory..."
cd ..
echo "Now in $(pwd)"

# vi. Create a new child directory called mycode2.
echo "Creating directory 'mycode2'..."
mkdir -p mycode2
echo "'mycode2' directory created."

# vii. Copy all files from the mycode directory to the mycode2 directory.
echo "Copying files from 'mycode' to 'mycode2'..."
cp -r mycode/* mycode2/
echo "Files in 'mycode2':"
ls mycode2

# viii. Rename the mycode directory to deadcode.
echo "Renaming 'mycode' to 'deadcode'..."
mv mycode deadcode
echo "Rename complete."

# ix. Remove the deadcode directory and all its files.
echo "Removing 'deadcode' directory and its contents..."
rm -rf deadcode
echo "'deadcode' directory removed."

echo "Script execution complete."
