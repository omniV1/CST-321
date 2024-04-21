
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



![output](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/test1.sh.png)




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



![Screenshot of test2.sh](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/test2.sh.png)




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



![less](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/less-command.png)

![more -d](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/more-d.png)

![command more](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/more.png)

![Terminal ls home](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/ls-home.png) 


## Theory of Operation for test3.sh and test4.sh Scripts

### test3.sh Script

The `test3.sh` script demonstrates basic variable declaration and output in a Bash script.

- A variable `name` is declared to store the my name.
- Another variable `age` is declared to store the my age.
- The `echo` command is used to print the contents of both variables to the screen, providing a simple way to verify that the variables have been set correctly.

![test3.sh](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/test3.sh.png)

(test3.sh)[]


### test4.sh Script

The `test4.sh` script showcases the use of special shell variables and the Internal Field Separator (IFS).

- The `IFS` is set to `-`, which will affect how bash splits input into fields.
- `$0` represents the script's filename.
- `$1` and `$2` are the first and second arguments passed to the script.
- `$@` and `$*` both represent all arguments passed to the script, but `"quoted values"` are handled differently by each.
- `$#` is the total number of arguments passed to the script.

![test4.sh](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/test4.sh.png)


## Theory of Operation for Terminal Commands

### which gcc Command

- The `which` command is used to identify the location of executables in the system path.
- Running `which gcc` returns the path to the `gcc` compiler executable, confirming its installation and location on the system.

### man gcc Command

- The `man` command opens manual pages for Unix commands.
- `man gcc` provides access to the comprehensive manual for the `gcc` compiler, detailing its options, syntax, and examples.




## Theory of Operation for test5.sh Script - Permissions

### Initial Script Execution

The initial `test5.sh` script includes a simple `echo` command that outputs "Hello World" to the console. When inspecting the file permissions with `ls -l`, it may not be executable by the user depending on the default umask settings. The owner of the file is the user who created it. If the execute bit (`x`) is not set for the user, the script cannot be executed, which is likely the case immediately after creation.

### Changing File Permissions

To make the script executable, the `chmod +x ~/test5.sh` command is used. This command modifies the file's permissions, adding the execute (`x`) permission for the user. The `ls -l` command will then show an updated permission string, likely changing from something like `-rw-r--r--` to `-rwxr-xr-x`, indicating that the user (owner), group, and others can now execute (`x`) the file.

Running the script after changing permissions will successfully execute and output "Hello World" to the terminal. This demonstrates the importance of file permissions in Unix-like operating systems and how they can be modified to control access to file contents.


![test5.sh screenshot](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/test5.sh.png)


## Theory of Operation for Redirection and Piping Commands

### Redirection

- The `ls -l > myfiles.txt` command lists directory contents in long format and redirects the output from the standard output to the file `myfiles.txt`. Instead of displaying the list in the terminal, it saves it to the file.


![myfiles.txt screenshot](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/myfiles.txt.png)


### Sorting Text in a File

- To sort names alphabetically, the `sort < names.txt` command is used. It takes the content of `names.txt` as input and sorts the lines, displaying the sorted output in the terminal.

![names before](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/names-before.png)


![names after](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/names-after.png) 

### Using Pipes with `less`

- The `ls -l | less` command combination uses a pipe (`|`) to send the output of the `ls -l` command to `less`, allowing the user to view the content in a scrollable format.
  
- Another command piped into `less` can be `cat myfiles.txt | less`, which displays the contents of `myfiles.txt` in a scrollable format using `less`.

These operations demonstrate how the shell can redirect output from one command to a file or another command, which is a powerful feature for combining commands and managing output in Unix-like operating systems.


![less-pipe-command](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/less-pipe-command.png)


![less-pipe-output](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/less-pipe-output.png)


## Theory of Operation for Head and Tail Commands

The `head` and `tail` commands are used to display the beginning and the end of files, respectively.

- `head`: This command outputs the first ten lines of a file by default. It's useful for quickly inspecting the start of log files or any text files where the initial content is of interest. Running `head syslog` in the `/var/log` directory displays the most recent system log entries, which are often the most relevant for checking the status or recent events on the system.

- `tail`: Conversely, `tail` shows the last ten lines of a file. For log files, which are appended to over time, this command is commonly used to see the latest entries. Executing `tail syslog` provides a snapshot of the most recent activities logged by the system.

In cases where the user does not have sufficient permissions to read the log files, `sudo` can be prefixed to the commands to run them with elevated privileges, allowing for unrestricted access to the files.

## Theory of Operation for the Logs Application

The Logs application provides a graphical user interface (GUI) for viewing system log files. It simplifies the process of inspecting logs by categorizing them and allowing users to filter and search for specific entries. This approach is more user-friendly, especially for those who are less comfortable using command-line tools. The application typically defaults to showing the `syslog`, or it can be navigated to via the interface. The benefit of using the Logs application is its ease of use and the ability to visualize the log data in a more organized and interactive manner.

![head&tails](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/head%26tails.png)

## Theory of Operation for Disk Utility Commands

### fdisk -l Command

The `sudo fdisk -l` command lists all the disk partitions along with detailed information such as disk size, number of sectors, bytes per sector, and partition types. The output shows various `/dev/loopX` devices, which are typically associated with loop devices that represent ISO files or disk images mounted in the filesystem. It also lists physical disk devices like `/dev/sda` and `/dev/sdb`, which are the actual hard drives or SSDs. The `sudo` prefix is necessary because viewing disk partition details requires administrative privileges.

![fdisk](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/fdisk.png)

### df Command

Running the `df` command displays information about the file system disk space usage. It lists each mounted filesystem, total blocks, used and available space, and the mount points. In the provided output, filesystems like `tmpfs`, `/dev/sda3`, and mounts for EFI system partitions and shared folders are displayed, providing insight into storage distribution and usage across the system.

### du Command

The `du` (disk usage) command is used to estimate file and directory space usage. The command `du` without options shows the number of kilobytes used by the current directory, which in this case, is 100 kilobytes. When run with the `-h` option (`du -h`), it provides a human-readable format, which shows the size in a more comprehensible format (100K).

<<<<<<< HEAD

(df&du)[]

=======
![du&df](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/df%26du.png)


## Disk Usage Analyzer - Analyzing the Home Folder

### Selecting and Analyzing the Home Folder

Upon running the Disk Usage Analyzer, I selected my Home Folder to be analyzed. This tool quickly scanned the contents of the folder, including all subdirectories and files. It presented a detailed overview of disk usage in a visual format, including graphs and a list of items sorted by the space they occupy.

### Interpretation of Results

The results displayed by the Disk Usage Analyzer gave insights into which files and folders were using the most disk space. This can be particularly helpful for identifying large, unnecessary files or for general housekeeping to free up disk space. The graphical representation makes it easy to spot at a glance where space is being used, which is more intuitive than interpreting raw numbers from the command line.

The application showed various directories like Documents, Downloads, Pictures, and others within the Home Folder, along with their respective sizes. This breakdown allows for efficient management of disk space by providing the user with actionable information on where they can clean up files if needed.

### Advantages of Disk Usage Analyzer

Using the Disk Usage Analyzer has several advantages:

- **User-Friendly**: Provides a graphical interface that is more approachable for users not familiar with command-line tools.
- **Efficient**: Quickly scans and presents data, saving time compared to manual inspection.
- **Detailed Breakdown**: Offers a granular view of disk usage by file and directory.
- **Visualization**: Graphs and charts help in understanding data usage patterns easily.

This GUI-based approach complements the traditional command-line disk utilities, making disk management more accessible to all user levels.

![Disk usage analyzer](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/DiskUsageAnalyzer.png)

## Research Question 1: 

| Feature             | FAT-16                     | FAT-32                           | NFS                                  | Unix File Systems (e.g., EXT4)       |
|---------------------|----------------------------|----------------------------------|--------------------------------------|--------------------------------------|
| **Developed by**    | Microsoft                  | Microsoft                        | Sun Microsystems                     | Various (EXT4 primarily by Linux)    |
| **Max File Size**   | 2-4 GB                     | 4 GB                             | Limited by server's file system      | Up to 16 TB (EXT4)                   |
| **Max Volume Size** | 2-4 GB (16 GB with certain OS) | 2 TB (commonly), 8 TB (max)           | Not applicable (network protocol)    | Up to 1 EB (EXT4)                    |
| **File System Type**| Disk file system           | Disk file system                 | Network file system protocol         | Disk file system                     |
| **Use Case**        | Older or smaller storage devices | Larger storage than FAT-16, wide compatibility | Accessing files over a network        | Modern Linux installations, robustness |
| **Advantages**      | Simplicity, wide compatibility | Improved capacity over FAT-16, compatibility | Distributed file access, no local disk space used | Journaling, performance, large file and volume support |
| **Disadvantages**   | Limited size, lacks modern features | 4 GB file size limit, not suited for new, large drives | Dependent on network, performance can vary | Not native to Windows, less common outside Linux |


## Research Question 2: 



| Feature / Distro     | Linux Mint                     | Pop!_OS                         | Zorin OS                         | Ubuntu Desktop                 |
|----------------------|--------------------------------|---------------------------------|----------------------------------|-------------------------------|
| Base                 | Ubuntu                         | Ubuntu                          | Ubuntu                           | Debian (upstream for Ubuntu)  |
| Desktop Environment  | Cinnamon, MATE, Xfce           | GNOME (Customized)              | GNOME with Zorin Appearance      | GNOME                         |
| User Interface       | Traditional, similar to Windows| Modern, streamlined             | Windows-like, customizable       | Modern, streamlined           |
| Performance          | Optimized for stability        | Optimized for System76 hardware | Balanced for performance         | Balanced for performance      |
| Software Management  | APT, Synaptic, Software Manager| APT, Pop!_Shop                  | APT, Software Store              | APT, Snap, Ubuntu Software    |
| Unique Selling Point | Familiarity and comfort        | Integration with System76 hardware, gaming focus | Ease of transition from Windows  | Leading open-source platform  |
| System Restoration   | Timeshift backup tool          | Recovery partition              | No default tool, relies on backups | No default tool, relies on backups |
| Pre-installed Apps   | Mint-specific tools            | Pop!_OS specific tools, NVIDIA support | Zorin-specific apps and tools     | Standard GNOME apps           |
| Target Audience      | Beginners, Windows converts    | Power users, developers         | Windows converts, new Linux users | General Linux audience        |
| Support Lifecycle    | Based on Ubuntu LTS            | Based on Ubuntu LTS             | Based on Ubuntu LTS              | 5 years for LTS, 9 months for regular releases |



<<<<<<< HEAD
# Resources

=======
# References 

Child, D. (n.d.). Linux Command Line Cheat Sheet. Available at: https://cheatography.com/davechild/cheat-sheets/linux-command-line/

Reha, M. (2024). Operating System Fundamentals Topic 6. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472999

Reha, M. (2024). Topic 6 Assignment Getting Started.  Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473081

Tanenbaum, A. S., & Bos, H. (2022). Chapter 4. In Modern Operating Systems (5th ed.). Pearson.
>>>>>>> 04eda0a786f9431d3be14af9e27d754aed4a23f5
