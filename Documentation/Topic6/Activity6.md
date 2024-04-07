
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

(Screenshot of terminal output)[]

### Script Justification

The script is carefully crafted to showcase fundamental file manipulation commands in a Bash environment. It also reflects the need for a neat organization and version control in a developer's workflow. Creating separate directories for the same set of files and then removing them mimics a scenario where a developer might want to back up their work before making significant changes, or perhaps before attempting a risky operation that could potentially corrupt their files.


## Theory of Operation for Terminal Commands

The series of commands executed in the terminal are standard file and directory operations that are part of the Unix command-line interface.

### Command Explanations

- `ls`, `ls -a`, and `ls -l`:
  These commands list the contents of the home directory. `ls` provides a simple list, `ls -a` includes hidden files (those starting with `.`), and `ls -l` gives detailed information such as permissions, owner, size, and modification date.

- `less` and its options:
  The `less` command is a file viewer that allows backward movement in the file as well as forward movement. `-N` option displays line numbers, `-S` option chops long lines, and `-i` option enables case-insensitive searches within the viewer.

- `more` and its options:
  Similar to `less`, `more` is a file viewer but is older and less feature-rich. The `-d` option gives directions, `-c` clears the screen before displaying file content, and `-s` squeezes multiple blank lines into a single line.

- `file` command:
  The `file` command is used to determine the type of a given file or directory. When run on directories, it usually indicates that they are directories, and when run on files, it provides a description of the file type.

Each of these commands is an essential part of navigating and viewing files in a Unix-like environment, and they provide a powerful interface for managing files and directories from the command line.

(Terminal file command)[]

(Terminal command less)[] 

(Terminal command more)[]

(Terminal ls command home)[] 

## Theory of Operation for test3.sh and test4.sh Scripts

### test3.sh Script

The `test3.sh` script demonstrates basic variable declaration and output in a Bash script.

- A variable `name` is declared to store the my name.
- Another variable `age` is declared to store the my age.
- The `echo` command is used to print the contents of both variables to the screen, providing a simple way to verify that the variables have been set correctly.


### test4.sh Script

The `test4.sh` script showcases the use of special shell variables and the Internal Field Separator (IFS).

- The `IFS` is set to `-`, which will affect how bash splits input into fields.
- `$0` represents the script's filename.
- `$1` and `$2` are the first and second arguments passed to the script.
- `$@` and `$*` both represent all arguments passed to the script, but `"quoted values"` are handled differently by each.
- `$#` is the total number of arguments passed to the script.



## Theory of Operation for Terminal Commands

### which gcc Command

- The `which` command is used to identify the location of executables in the system path.
- Running `which gcc` returns the path to the `gcc` compiler executable, confirming its installation and location on the system.

### man gcc Command

- The `man` command opens manual pages for Unix commands.
- `man gcc` provides access to the comprehensive manual for the `gcc` compiler, detailing its options, syntax, and examples.

(Terminal msc commands)[]



## Theory of Operation for test5.sh Script

### Initial Script Execution

The initial `test5.sh` script includes a simple `echo` command that outputs "Hello World" to the console. When inspecting the file permissions with `ls -l`, it may not be executable by the user depending on the default umask settings. The owner of the file is the user who created it. If the execute bit (`x`) is not set for the user, the script cannot be executed, which is likely the case immediately after creation.

### Changing File Permissions

To make the script executable, the `chmod +x ~/test5.sh` command is used. This command modifies the file's permissions, adding the execute (`x`) permission for the user. The `ls -l` command will then show an updated permission string, likely changing from something like `-rw-r--r--` to `-rwxr-xr-x`, indicating that the user (owner), group, and others can now execute (`x`) the file.

Running the script after changing permissions will successfully execute and output "Hello World" to the terminal. This demonstrates the importance of file permissions in Unix-like operating systems and how they can be modified to control access to file contents.
