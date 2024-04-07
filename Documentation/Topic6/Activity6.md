
# CST-321 Assignment - Activity 6
**Student Name:** Owen Lindsey  
**Institution:** Grand Canyon University  
**Course:** CST-321  
**Instructor:** Mark Reha  
**Assignment Title:** CST-321 Activity 6 Guide

## Theory of Operation for test1.sh

The script `test1.sh` performs a series of navigational and file listing operations within the Linux file system using Bash shell commands.

Here's what each part of the script does:

1. `pwd` prints the current working directory to the terminal. It ensures that the user can verify their starting point before the script changes directories.

2. `cd ~` changes the current directory to the home directory of the current user. The tilde (`~`) is a shortcut for the home directory.

3. `cd /c/git/CST-321/src/Topic4` changes the directory from the home directory to a specified child directory. This command assumes that `/c/git/CST-321/src/Topic4` exists within the home directory.

4. `ls *.c` lists all files in the current directory (which should be the child directory after the previous command) that have a `.c` extension. This is commonly used to find source code files for C programs.

5. `cd ~` is used again to return to the home directory after listing the `.c` files. This ensures that the script ends in a known location, which is the user's home directory.

The script provides a demonstration of basic file system navigation and pattern matching using the Bash shell. By echoing the current directory and listing specific files, it shows how shell scripts can automate tasks and provide informative output to the user.

(output)[url of screenshot test1.sh]


## Theory of Operation for test2.sh

The `test2.sh` script manages file and directory operations in the Linux file system, demonstrating how to automate common tasks with a Bash shell script.

### Detailed Operations

1. `cd ~`: This command navigates to the home directory, ensuring the script has a consistent starting point.

2. `mkdir -p mycode`: Creates a new directory called `mycode` in the home directory. The `-p` flag prevents an error if the directory already exists.

3. `cd mycode`: Changes the current directory to `mycode`, where operations on C program files will occur.

4. `cp /c/git/CST-321/src/Topic6/c_programs/*.c .`: Copies all `.c` files from the `c_programs` directory to the current working directory, `mycode`. This path is chosen based on the location where the C programs developed during the course are stored.

5. `cd ..`: Moves the working directory up one level, back to the home directory.

6. `mkdir -p mycode2`: Similar to step 2, this creates a second directory `mycode2`, again using `-p` to ensure idempotency.

7. `cp -r mycode/* mycode2/`: Copies everything from `mycode` to `mycode2`, duplicating the C programs as a backup or for further operations.

8. `mv mycode deadcode`: Renames the `mycode` directory to `deadcode`, demonstrating a simple way to reorganize or archive project directories.

9. `rm -rf deadcode`: Deletes the `deadcode` directory and its contents completely, showcasing how to clean up or remove project directories that are no longer needed.

### Script Justification

The script is carefully crafted to showcase fundamental file manipulation commands in a Bash environment. It also reflects the need for a neat organization and version control in a developer's workflow. Creating separate directories for the same set of files and then removing them mimics a scenario where a developer might want to back up their work before making significant changes, or perhaps before attempting a risky operation that could potentially corrupt their files.



