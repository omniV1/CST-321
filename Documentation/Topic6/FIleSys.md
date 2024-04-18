
# CST-321 Assignment - File System and Compilation Flow
**Student Name:** Owen Lindsey  
**Institution:** Grand Canyon University  
**Course:** CST-321  
**Instructor:** Mark Reha  
**Assignment Title:** File System and Compilation Process Analysis  




## Exercise 1: Linux File System Exploration

### Purpose of Directories
| Directory | Purpose |
|-----------|---------|
| `/  `      | The root directory is the top level directory of the filesystem hierarchy. It contains all other directories and files. |
| `/bin `     | Contains essential binary executables that need to be available in single user mode and to bring the system up or repair it. |
| `/dev`      | Holds device files that represent hardware components or other special files that represent system and network interfaces. |
|` /etc `     | Configuration files for the system. Most system-wide configuration files are located here. |
| `/lib `     | Contains shared library images that the executable programs in /bin and /sbin depend on to function. |
|` /boot `    | Contains the boot loader files, including the Linux kernel. Used for booting the system. |
| `/home `    | Home directories for all users to store their personal files. Each user has a directory within /home. |
| `/mnt`      | Temporary mount point where sysadmins can mount filesystems manually. |
|` /proc  `   | A virtual filesystem providing process and kernel information as files. In essence, it does not contain 'real' files but runtime system information. |
|` /tmp  `    | A temporary storage directory where files are kept until the next reboot. Used by system and applications for temporary file storage. |
|` /usr  `    | Secondary hierarchy for user data; contains the majority of (multi-)user utilities and applications. |
|` /var   `   | Variable files—files whose content is expected to continually change during normal operation of the system—such as logs, spool files, and temporary e-mail files. |
| `/sbin `    | Contains binary executables used for system administration (i.e., maintenance and/or repair of the system) in addition to those in /bin. |


## Exercise 2: Home Directory Structure

| Directory          | Purpose                                                                                       |
|--------------------|-----------------------------------------------------------------------------------------------|
| `Desktop`          | Contains files and shortcuts that appear on the desktop environment for quick access.         |
| `Documents`        | A place for storing personal documents such as text files, spreadsheets, etc.                 |
| `Downloads`        | The default location for files downloaded from the internet.                                  |
| `Music`            | Intended for storing music files like MP3s or other audio formats.                           |
| `Pictures`         | Used for storing digital photographs, images, and graphics.                                   |
| `Videos`           | A place for storing video files, commonly accessed by media players.                          |
| `Templates`        | Holds document templates for creating new documents in GNOME-based applications.              |
| `Public`           | Meant for files that the user wishes to share with others on the same computer or network.    |
| `snap`             | Stores snap application data, managed by the snapd service.                                   |
| `eclipse`          | Likely contains the Eclipse IDE itself.                                                       |
| `eclipse-workspace`| Where Eclipse project files and workspace configurations are saved.                           |
| `nohup.out`        | A file that captures output from processes run with `nohup` command, not a directory.         |
| `CST-321`          | Directory for the CST-321 course's cloned Git repository, contains course-related project files.|
| `owen`             | A personal directory for the user 'owen', for specific files or personal projects.   |

## Exercise 3: Flowchart for Simulated C Compiler Process

In this exercise, the flowchart will illustrate a simulated process of compiling a C program using a series of Linux system I/O calls. Each step in the flowchart will correspond to a specific I/O operation, starting from reading the input C program, compiling it into tokens, and writing these tokens to a file, to finally linking these tokens with a library to create an executable file. This process will demonstrate a thorough understanding of file operations such as creating, opening, reading from, writing to, and closing files, as well as directory management within a Linux environment.

![Flowchart](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic6/screenshots/Filesys.drawio.png)

### Justifications for Decisions
- **Opening Files:**
  We use `open()` instead of `fopen()` due to its lower-level access to file descriptors, providing finer control over I/O operations, which is required for some system calls like `read()` and `write()`.
  
- **Reading and Writing:**
  The `read()` and `write()` system calls are used in a loop to handle files in chunks, ensuring that we can process files larger than the available memory.

- **Looping Logic:**
  Loops are implemented for reading the source file and for the linking process. This allows the program to handle each line of code and each object file individually, adhering to the single responsibility principle.

- **Error Handling:**
  At each step, we include decision nodes to check for errors, such as failed file reads or writes, which is critical for robustness in real-world applications.

- **Temporary Directory (`tmp`):**
  A temporary directory is used for intermediate files to avoid cluttering the user's workspace and to ease cleanup after compilation.

- **Checksum Implementation:**
  A checksum is computed and added to the final executable to ensure data integrity.



 # Resources:

Reha, M. (2024). Operating System Fundamentals Topic 6. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472999

Reha, M. (2024). Topic 6 Assignment Getting Started. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473081
 
Linux Operating System. (n.d.). File System Calls. Available at: https://linasm.sourceforge.net/docs/syscalls/filesystem.php

Muiruri, J. (n.d.). How to Use the I/O System Calls open, close, read, and write. Available at: https://medium.com/@muirujackson/how-to-use-the-i-o-system-calls-open-close-read-and-write-f6f80dc61e2a 

WIT Solapur - Professional Learning Community. (2019). System Calls for the File System : Part 1. YouTube. Available at: https://www.youtube.com/watch?v=tmp7dGJuyLQ 

WIT Solapur - Professional Learning Community. (2019). System Calls for the File System : Part 2. YouTube. Available at: https://www.youtube.com/watch?v=jsozu-FXKRQ

WIT Solapur - Professional Learning Community. (2019). System Calls for the File System : Part 3. YouTube. Available at: https://www.youtube.com/watch?v=gUM_KSs6zHI

