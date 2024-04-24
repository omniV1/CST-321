# CST–321 Security Activity on Buffer Overflow
**Student Name:** Owen Lindsey  
**Institution:** Grand Canyon University  
**Course:** CST-321  
**Instructor:** Mark Reha  

## Basic System Security 


### a) Administration Services to Secure a Workplace Methods

| Component | Detail | Implications and Operations |
|-----------|--------|-----------------------------|
| User Administration | Involves creating, managing, and deleting user accounts. | Ensures only authorized users can access the system. Involves setting appropriate permissions and privileges for each user. Requires regular audits of user accounts for any anomalies or inactive users. |
| Access Controls | Determines how users are granted access to systems and data. | Implements policies like least privilege and need-to-know to limit access to essential services and information. Can include role-based access control (RBAC) systems to streamline permissions based on job roles. |
| Activity Monitoring | Tracks user activities across the system. | Involves logging and analyzing user actions to detect unauthorized or suspicious behavior. Tools like Security Information and Event Management (SIEM) can automate this process. |
| Regular Auditing | Periodic checks on the access control implementations. | Ensures ongoing compliance with security policies and procedures. Involves conducting periodic access reviews, permission audits, and verifying alignment with security policies. |


### b) Buffer Overflow Prevention 

| Technique | Explanation | Implementation Strategy |
|-----------|-------------|-------------------------|
| Programming Defensively | Writing code that anticipates and mitigates security vulnerabilities. | Includes practices like validating input length before processing and avoiding dangerous functions known to cause vulnerabilities. |
| Safe Functions | Utilizing functions that inherently manage memory safely. | Prefer using functions that perform bounds checking, such as `strncpy()` over `strcpy()` in C/C++, or using high-level languages like Python or Java that manage memory automatically. |
| Canaries | Special variables placed on the stack to detect buffer overflows. | When a buffer overflow occurs, the canary value is altered. The system checks the canary before using a buffer to ensure it hasn't been compromised. |
| Compiler Protections | Inbuilt security features within compilers. | Modern compilers offer options like StackGuard or Address Space Layout Randomization (ASLR) to protect against buffer overflows. Enabling these options can prevent exploitation even if a vulnerability exists. |
| Code Analysis Tools | Software tools that can detect potential buffer overflow vulnerabilities in code. | Static and dynamic analysis tools can be employed during the development lifecycle to identify and rectify risky code constructs that could lead to buffer overflows. |


## Applying Basic Security 

### 2) Commands for terminal 

####  - `j.`) Terminal Commands 



![Terminal commands]() 


#### - `k.`) Theory of Operations for commands 
| Command      | Description | Detailed Operation |
|--------------|-------------|--------------------|
| `useradd`    | Creates a new user account on the system. | This command updates the `/etc/passwd`, `/etc/shadow`, `/etc/group`, and `/etc/gshadow` files with the new user information. It also creates a home directory for the new user and copies initial configuration files. |
| `usermod`    | Modifies an existing user account. | It can change many aspects of a user account, including username, home directory, shell, and group affiliations, reflecting these changes across the system's user and group configuration files. |
| `passwd`     | Updates a user's password. | This command modifies the encrypted password in the `/etc/shadow` file. It's used for setting or changing user passwords, including enforcing password policies. |
| `groupadd`   | Adds a new group to the system. | When a new group is created, `groupadd` updates the `/etc/group` and `/etc/gshadow` files with information about the new group, including group name and group ID (GID). |
| `userdel`    | Deletes a user account from the system. | This command removes the user's details from `/etc/passwd`, `/etc/shadow`, `/etc/group`, and other system files. It can also remove the user's home directory and mail spool. |
| `groupmod`   | Modifies an existing group. | Not mentioned in the original list, but `groupmod` is used to change group name or GID. Similar to `usermod`, it ensures that references to the group in the system's configuration files are updated. |
| `gpasswd`    | Administers `/etc/group` and `/etc/gshadow`. | This command allows for the administration of group passwords and members, supplementing the functionality of `groupadd` and `groupmod`. |


### 3) Using GREP in bash 

#### - `b.`) Screenshot of the Terminal console output 

![Terminal GREP operation]() 


#### - `c.`) Theory of Operation for GREP 
| Aspect              | Description |
|---------------------|-------------|
| **Command**         | `grep "session opened"` |
| **Purpose**         | To filter the output from `awk` to only show log entries that specifically indicate a user session has been opened. |
| **Operation**       | `grep` examines each line of input for the pattern "session opened" and prints only the lines where this exact pattern is found. |
| **Case Sensitivity**| The search is case-sensitive, meaning it will only match "session opened" with that exact casing. For a case-insensitive search, the `-i` flag would be used. |
| **Regular Expressions** | Although `grep` can handle complex patterns with regular expressions, this usage is a simple string match. |
| **Efficiency and Selectivity** | This use of `grep` is efficient because it filters out non-relevant data, focusing on important security events—user login attempts. |
| **Usage in Security** | Extracting specific patterns with `grep` from log files is crucial for security analysis, allowing for the identification of potential breaches and monitoring of anomalous user activities. |

### 4) Harding Linux servers 

#### `a.`) What are some areas and services that possibly need to be hardened?
 
 | Area/Service        | Reason for Hardening                                         | Example Actions                                    |
|---------------------|--------------------------------------------------------------|----------------------------------------------------|
| **SSH Access**      | SSH is a common entry point for attackers. Securing it is critical to prevent unauthorized access. | Disabling root login, using key-based authentication. |
| **User Authentication** | Ensuring only authorized users can access the system and its resources is fundamental to system security. | Implementing two-factor authentication, strong password policies. |
| **File System Permissions** | Incorrect permissions can expose sensitive data or allow malicious activities. | Setting correct ownership and permissions on files and directories. |
| **Application Security** | Applications can have vulnerabilities that may be exploited. | Keeping software up-to-date, using application firewalls, and following the principle of least privilege. |


#### `b.`) What configuration files would possibly need to be hardened?

| Configuration File | Purpose | Hardening Measures |
|--------------------|---------|--------------------|
| `/etc/ssh/sshd_config` | Configures the SSH daemon | Disable root login, specify allowed users, enforce the use of SSH keys. |
| `/etc/passwd` | Contains user account information | Ensure no users have UID 0 besides root, check for integrity and no unauthorized accounts. |
| `/etc/shadow` | Contains hashed password information | Ensure it is only readable by the root user to protect password hashes. |
| `/etc/group` | Defines groups to which users belong | Review group memberships and privileges, ensure proper group ownerships. |


#### `c.`) What Linux commands would you need to know to do this job?
| Command      | Usage |
|--------------|-------|
| `chmod`      | Modify file access rights |
| `chown`      | Change file ownership |
| `usermod`    | Modify a user's system account |
| `passwd`     | Update a user's password |
| `systemctl`  | Manage system services (start/stop services, enable/disable at boot) |


#### `d.`) What other possible tools would you need to do this job?
| Tool              | Usage |
|-------------------|-------|
| **SELinux**       | Enforce access control policies that limit executable files and system processes |
| **iptables**      | Configure firewalls to filter traffic, block unwanted access, and manage network traffic |
| **Nessus**        | Perform vulnerability scans and assess the security of the system by identifying known vulnerabilities |
| **OpenVAS**       | Free vulnerability scanner for detecting security issues in software and systems |



#### `e.`) What additional training or resources would you need to do this job?
| Training/Resources             | Description |
|--------------------------------|-------------|
| **Network Security Courses**   | Educational courses to learn about the latest in network security protocols and threat mitigation strategies |
| **Ethical Hacking Training**   | Training programs to learn the techniques of ethical hacking, which can be applied to system hardening |
| **Linux Administration**       | In-depth knowledge of Linux systems for effective system administration and security |
| **Security Updates**           | Staying informed about the latest security vulnerabilities and the corresponding updates or patches |
| **Certifications (e.g., CISSP, CEH)** | Professional security certifications that validate expertise and knowledge in the field of system security |



## Working with OpenSSL

### 2) Commands on terminal

#### `i.`) Screenshot of terminal console output

![Terminal OpenSSL operation]() 

#### `e.`) Theory of Operation for OpenSSL commands

| Command                                               | Description                                                               | Detailed Operation                                                                                                                                                                                                                           |
|-------------------------------------------------------|---------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `openssl enc -aes-256-cbc -salt -in test.txt -out test.enc` | Encrypts `test.txt` using AES-256-CBC with a salt.                       | **AES-256-CBC**: Symmetric key encryption algorithm with Cipher Block Chaining. The `-salt` option enhances security by adding randomness. Takes `test.txt` as plaintext input, outputs encrypted data to `test.enc`. Requires a password to derive the encryption key. |
| `openssl enc -d -aes-256-cbc -in test.enc -out test.dec`    | Decrypts `test.enc` using the same AES-256-CBC algorithm.                | The `-d` flag switches to decryption. It reads encrypted data from `test.enc` and converts it back to plaintext, outputting to `test.dec`. The same password used during encryption is needed for successful decryption.                         |
| `openssl enc -aes-256-cbc -salt -a -in test.txt -out test.enc` | Encrypts `test.txt` and encodes the output in Base64.                    | Performs AES-256-CBC encryption with a salt and uses the `-a` option to encode the encrypted data in Base64 format. This ensures the data remains intact during transport in text-based systems. Requires a password for encryption.             |
| `openssl enc -d -aes-256-cbc -a -in test.enc -out test.dec`    | Decrypts `test.enc` and decodes from Base64 using the same algorithm.    | Combines decryption with Base64 decoding. The `-a` flag indicates that the input file (`test.enc`) is Base64 encoded. Decrypts and converts the data back to plaintext, outputting to `test.dec`. The same password is required for decryption. |

#### `m.`) Research on MD5 Hash 
            - i. What is steganography?
                
                Steganography is the practice of hiding secret data within an ordinary file or message to avoid detection. Unlike cryptography, which obscures the content of a message, steganography hides the existence of the message itself. It can be used to embed hidden information in digital images, audio files, videos, or other types of digital media, where alterations to the binary data are imperceptible to human senses.


            - ii. How could an MD5 hash be used to prevent steganography
              
                An MD5 hash can be used to monitor the integrity of files and detect unauthorized changes, which could include the insertion of steganographic content. By generating and storing an MD5 hash of the original file, a system can periodically re-hash the stored media and compare it against the original hash. Any alteration to the file, including the embedding of hidden data via steganography, will change the hash value, thereby indicating tampering or modification. However, it's important to note that MD5 is not collision-resistant, which limits its effectiveness against sophisticated attacks where the hash might be preserved despite changes to the data.


#### `n.`) Screenshot of MD5 Hash 
![MD5 Hash]() 

## Working with Networks

### 2) netstat network utility on Terminal 

#### `i.`) Screenshot of terminal output 

![Terminal netstat operation]() 

#### `j.`) Theory of Operation on netsat utility 

## Ethical Hacking 

### 1)  Tutorials point research
            - i. What are some types of hacking?
            .
  
            - ii. What tools are available
            .
  
            - iii. What are some different attacks?
            .


            - iV. What other possible tools would you need to do this job?
            .

            - v.  What additional training or resources would you need to do this job??
            . 


### 2) Trusted Computing Base 
            - i. What is the trusted computing base?
            .
  
            - ii. Why is this important?
            .


## Research Questions

#### `a.`) 



#### `b.`) 



