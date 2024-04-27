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



![Terminal commands](
https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/commandsInTerminal.png
) 


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

![Terminal GREP operation](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/GREPinTerminal.png) 


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

![Terminal OpenSSL operation](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/Openssl_1.png) 

![Terminal OpenSSL operation](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/openssl2.png) 

![Terminal OpenSSL operation](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/openssl3.png) 

#### `e.`) Theory of Operation for OpenSSL commands

| Command                                               | Description                                                               | Detailed Operation                                                                                                                                                                                                                           |
|-------------------------------------------------------|---------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `openssl enc -aes-256-cbc -salt -in test.txt -out test.enc` | Encrypts `test.txt` using AES-256-CBC with a salt.                       | **AES-256-CBC**: Symmetric key encryption algorithm with Cipher Block Chaining. The `-salt` option enhances security by adding randomness. Takes `test.txt` as plaintext input, outputs encrypted data to `test.enc`. Requires a password to derive the encryption key. |
| `openssl enc -d -aes-256-cbc -in test.enc -out test.dec`    | Decrypts `test.enc` using the same AES-256-CBC algorithm.                | The `-d` flag switches to decryption. It reads encrypted data from `test.enc` and converts it back to plaintext, outputting to `test.dec`. The same password used during encryption is needed for successful decryption.                         |
| `openssl enc -aes-256-cbc -salt -a -in test.txt -out test.enc` | Encrypts `test.txt` and encodes the output in Base64.                    | Performs AES-256-CBC encryption with a salt and uses the `-a` option to encode the encrypted data in Base64 format. This ensures the data remains intact during transport in text-based systems. Requires a password for encryption.             |
| `openssl enc -d -aes-256-cbc -a -in test.enc -out test.dec`    | Decrypts `test.enc` and decodes from Base64 using the same algorithm.    | Combines decryption with Base64 decoding. The `-a` flag indicates that the input file (`test.enc`) is Base64 encoded. Decrypts and converts the data back to plaintext, outputting to `test.dec`. The same password is required for decryption. |

#### `m.`) Research on MD5 Hash 
 - i. What is steganography?
                
` Steganography` is the practice of hiding secret data within an ordinary file or message to avoid detection. Unlike cryptography, which obscures the content of a message, steganography hides the existence of the message itself. It can be used to embed hidden information in digital images, audio files, videos, or other types of digital media, where alterations to the binary data are imperceptible to human senses.


- ii. How could an MD5 hash be used to prevent steganography
              
 An `MD5 hash` can be used to monitor the integrity of files and detect unauthorized changes, which could include the insertion of steganographic content. By generating and storing an MD5 hash of the original file, a system can periodically re-hash the stored media and compare it against the original hash. Any alteration to the file, including the embedding of hidden data via steganography, will change the hash value, thereby indicating tampering or modification. However, it's important to note that MD5 is not collision-resistant, which limits its effectiveness against sophisticated attacks where the hash might be preserved despite changes to the data.


#### `n.`) Screenshot of MD5 Hash 
![MD5 Hash](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/MD5Hash.png) 

## Working with Networks

### 2) netstat network utility on Terminal 

#### `i.`) Screenshot of terminal output 

![Terminal netstat operation](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/network1.png) 

![Terminal netstat operation](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/network2.png) 

#### `j.`) Theory of Operation on netsat utility 

| Command | Description | Theory of Operation |
|---------|-------------|--------------------|
| `sudo apt install net-tools` | Installs the net-tools package which contains essential networking utilities including `netstat`. | This command uses the Advanced Packaging Tool (APT) to install the net-tools package. It is essential for managing networking on older Linux systems and provides utilities like `ifconfig` and `netstat` which are used for network interface configuration and network statistics monitoring respectively. |
| `hostname` | Displays the system's network name. | This command is used to get or set the hostname of the system. The hostname is important for network communication, allowing a user-readable label that can be resolved to an IP address via DNS. |
| `ifconfig -a` | Lists all network interfaces, including those that are down. | `ifconfig` (interface configuration) is used to configure, manage, and display the properties of network interfaces such as IP addresses and netmasks. The `-a` option ensures that all currently available interfaces are listed, regardless of their state. |
| `netstat -a` | Lists all network connections and listening ports. | `netstat` (network statistics) is a powerful tool that displays network connections for TCP, routing tables, interface statistics, masquerade connections, and multicast memberships. The `-a` option shows both listening and non-listening sockets. |
| `netstat -at` | Lists TCP connections. | This command filters the output of `netstat` to show only TCP connections. TCP (Transmission Control Protocol) is crucial for establishing reliable connections between hosts. |
| `netstat -tnl` | Displays listening TCP connections, showing only network address and port number. | The `-tnl` options combine to show TCP connections (`-t`), suppress the resolution of hostnames (`-n`), and display only listening sockets (`-l`). This is useful for quickly assessing which services are accepting incoming connections. |
| `sudo netstat -ltpe` | Lists listening ports along with service names and more detailed information like process ID and user ID. | The `-ltpe` options extend the `netstat` output to include the program name (`-p`), show listening sockets (`-l`), disable hostname resolution (`-n`), and display the user ID (`-e`). This is invaluable for administrators to identify which applications are listening on which ports. |
| `netstat -i` | Displays network interfaces with statistics. | This command lists the network interfaces along with statistics such as the number of packets and bytes received and sent. This information is key for monitoring network activity and diagnosing issues. |

## Ethical Hacking 

### 1)  Tutorials point research
  `i`. What are some types of hacking?
  
 1. **Social Engineering**: An attack vector that relies on human interaction and often involves manipulating people into breaking normal security procedures to gain unauthorized access to systems, networks, or physical locations, or for financial gain. Examples include:
   
   - Dumpster diving to retrieve sensitive information thrown away by a company.
   - Befriending employees to extract confidential information.
   - Impersonating an employee or a legitimate user to gain physical or system access.
  


1. **Phishing Attacks**: A form of social engineering where attackers send fraudulent emails that seem to come from reputable sources to steal sensitive data like credit card numbers and login credentials.



2. **TCP/IP Hijacking**: An active session attack where an attacker takes over a TCP session between two machines without the need of a password mainly by exploiting the session's data packets. This could involve:
   - Using the Man-in-the-Middle (MITM) technique to intercept and inject malicious data into the session.
   - Employing tools like Shijack or Hunt to actively hijack the session.



3. **Reconnaissance**: Involves gathering information about the target before launching an attack. This can be:
   - **Passive**: Gathering data without directly interacting with the target system to avoid detection.
   - **Active**: Directly interacting with the system to gather information which may alert the target about the potential attack.
  

  `ii`. What tools are available
  
1. **Wireshark**: A network protocol analyzer that lets you capture and interactively browse the traffic running on a computer network.
2. **Shijack**: A tool mentioned specifically for TCP/IP session hijacking, used to take over a session by manipulating sequence numbers in packet headers.
3. **Hunt**: Another tool for TCP/IP hijacking, capable of sniffing networks and intercepting traffic to perform man-in-the-middle and session hijacking attacks.
4. **Ethercap**: Commonly used for man-in-the-middle attacks on LANs, capable of intercepting and modifying traffic on a network segment.
  
 `iii`. What are some different attacks?
1. **Social Engineering Attacks**: Includes dumpster diving, phishing, pretexting, and tailgating where attackers exploit human psychology.

2. **TCP/IP Hijacking**: Where an attacker takes control of a pre-established communication session between two computers.

3. **Phishing**: A specific type of social engineering where attackers send fraudulent emails or set up fake websites to trick victims into providing sensitive information.


`iV`. What other possible tools would you need to do this job?
  
1. **Metasploit**: A framework for developing and executing exploit code against a remote target machine.
   
2. **Nmap**: A network scanning tool used to discover hosts and services on a computer network by sending packets and analyzing the responses.
   
3. **Burp Suite**: An integrated platform for performing security testing of web applications.
   
4. **Kali Linux**: A Debian-derived Linux distribution designed for digital forensics and penetration testing, which includes numerous tools for hacking and security testing.            

`v`.  What additional training or resources would you need to do this job??

1. **Certified Ethical Hacker (CEH)**: A professional certification provided by the EC-Council that teaches the fundamentals of ethical hacking and penetration testing.
   
2. **Offensive Security Certified Professional (OSCP)**: An ethical hacking certification that focuses on hands-on offensive information security skills.

3. **Security conferences and workshops**: Events like DEF CON and Black Hat provide a platform for learning about the latest security research, trends, and tools.
   
4. **Online Courses and Tutorials**: Platforms like Coursera, Udemy, and Cybrary offer courses ranging from beginner to advanced levels in ethical hacking and cybersecurity.
   
5. **Practice Labs and Ranges**: Online platforms like Hack The Box or TryHackMe offer virtual labs and challenges for hands-on hacking practice.


### 2) Trusted Computing Base 
`i`. What is the trusted computing base?

The **trusted computing base (TCB)** is the core component of a computing system that is crucial for enforcing its security. The TCB comprises all the hardware, firmware, and software components that are critical to the security of the system. Essentially, it includes those elements that handle the enforcement of security policies and thereby manage the security of the entire computing system. Components outside the TCB have limited privileges and cannot perform actions that might compromise the system's security. The TCB is fundamental because any vulnerabilities or bugs within this base can jeopardize the security properties of the whole system.

  
`ii`. Why is this important?

The TCB is critically important for several reasons:

1. **Security Assurance**: The integrity and security of a computing system largely depend on the TCB. By focusing security efforts on a small, manageable set of components, it is possible to more thoroughly ensure the system is secure against attacks.

2. **System Integrity**: The TCB maintains the system's integrity by ensuring that all security mechanisms within the computer operate correctly. This includes maintaining the correctness of security protocols, the protection of security mechanisms from tampering, and the accurate execution of security policies.

3. **Minimization of Risk**: By isolating the security-critical components into a TCB, the system can be designed to minimize the risk of security breaches. Components outside the TCB cannot perform actions that significantly compromise the system, limiting the potential damage from less secure parts of the system.

4. **Enabling Secure Operations**: The TCB allows for secure operations on a computer system by ensuring that only authorized code and processes can access sensitive information or perform critical functions. This is crucial for environments where high security is necessary.

5. **Facilitation of Security Evaluations**: With a defined TCB, security evaluations, such as those done under the Common Criteria security process, can be more focused and thorough. Evaluators can concentrate their efforts on the most critical parts of the system, which simplifies the process and enhances the reliability of the evaluation.

6. **Economic and Practical Feasibility**: The necessity to keep the TCB as small as possible is economically and practically important. Smaller TCBs simplify the task of securing and verifying the system, which can reduce the costs and time required for security audits and reviews. This is especially significant in systems that require high assurance, such as military or critical infrastructure systems.

## Research Questions

### Overview on Authentication Schemes 

#### `a.`) 

| Authentication Scheme | Description | Example Use |
|-----------------------|-------------|-------------|
| Passwords             | The most common form of authentication, requiring a user to know and enter a secret string of characters. | Used by nearly all operating systems and online platforms for initial login authentication. |
| Physical Objects      | Authentication using a physical device such as a security token, smart card, or USB key. | Bank ATMs use a physical card and PIN for account access. |
| Biometrics            | Uses unique biological traits of individuals for verification, such as fingerprints, facial recognition, or iris scans. | Smartphones like iPhones use Face ID or Touch ID for device unlocking and payments. |
| Challenge-Response    | A method where the user proves knowledge of a secret without revealing it, by answering a challenge. | Used in some secure VPN connections and remote server access. |
| One-Time Passwords (OTP) | Passwords that are valid for only one login session or transaction, often generated by a hardware token or software application. | Frequently used for two-factor authentication but can serve as a single-factor in systems like a bank's OTP token for transactions. |
| Behavioral Biometrics | Analyzes patterns in human activity like keystrokes dynamics or mouse movements. | Used for continuous authentication on sensitive systems. |


### Overview on Multi-Factor Authentication Schemes 


#### `b.`) 

| Authentication Scheme        | Description |
|------------------------------|-------------|
| Two-Factor Authentication (2FA) | Combines two different types of authentication methods, typically something the user knows (password) and something the user has (security token or mobile app OTP). Common in both consumer and corporate settings to protect user accounts. |
| Three-Factor Authentication | Involves three distinct authentication methods, often combining something the user knows (password), something the user has (security token), and something the user is (biometric verification). Used in high-security environments like government or military systems. |
| Adaptive Authentication      | Uses a variety of factors to authenticate a user based on the current context, such as location, device, time, and behavior. The system might ask for additional proof of identity if the login attempt is made from a new location or device. |

### More Detail

1. `Two-Factor Authentication (2FA):` This is the most commonly implemented form of MFA. It requires users to provide two different types of authentication. For example, after entering a password, a user might also need to enter a code received via SMS or generated by an app on their mobile device. This method is widely used due to its strong security and relatively straightforward implementation.

2. `Three-Factor Authentication:` For environments where security needs are higher, three-factor authentication adds another layer of security. This typically includes something the user knows (a password), something the user has (a hardware token or a phone app), and something the user is (biometric data, such as a fingerprint or retina scan). This method is less common due to higher costs and more complex implementation but is critical in areas requiring stringent security measures.

3. `Adaptive Authentication:` This dynamic approach adjusts the authentication requirements based on the risk associated with a particular login attempt. Factors considered may include the user’s location, the device being used, the time of the login, and even behavior patterns. If the system detects an anomaly (e.g., a login from a foreign country), it might prompt for additional authentication factors. This method is increasingly popular among organizations that manage a large user base across various security contexts.




## References

Moon, S. (2023, January 4). 10 basic examples of linux netstat command - check ports and connections. BinaryTides. https://www.binarytides.com/linux-netstat-command-examples/ 

NA. (2024). Buffer overflow. Buffer Overflow | OWASP Foundation. https://owasp.org/www-community/vulnerabilities/Buffer_Overflow 

NA. (2024). Ethical hacking - TCP/IP hijacking. Tutorialspoint. https://www.tutorialspoint.com/ethical_hacking/ethical_hacking_tcp_ip_hijacking.htm 

NA. (2024). More than a password: CISA. Cybersecurity and Infrastructure Security Agency CISA. (n.d.). https://www.cisa.gov/MFA 

NA. (2024). Ubuntu documentation. User accounts. https://help.ubuntu.com/stable/ubuntu-help/user-accounts.html.en 

NA. (2024). Logging cheat sheet¶. Logging - OWASP Cheat Sheet Series. https://cheatsheetseries.owasp.org/cheatsheets/Logging_Cheat_Sheet.html 

Rosenblatt, S. (2015). The biggest cyberthreat to companies could come from the inside. CNET. https://www.cnet.com/news/privacy/the-biggest-cyber-threat-to-companies-could-come-from-the-inside/ 
