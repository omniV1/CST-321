# CST–321 Security Activity on Buffer Overflow
**Student Name:** Owen Lindsey  
**Institution:** Grand Canyon University  
**Course:** CST-321  
**Instructor:** Mark Reha  

## 1) Research on Buffer Overflow

### a) What is a Buffer Overflow?

A buffer overflow occurs when a program attempts to write more data to a fixed-length block of memory, or buffer, than it is allocated to hold. Due to the lack of bounds checking in C for array or buffer-based operations, writing excess data to a buffer can overwrite adjacent memory locations. This mismanagement of memory can alter the execution flow of a program, potentially leading to crashes, unauthorized access, data corruption, or execution of malicious code.

### b) Diagram of a Buffer Overflow

![buffer overflow diagram](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/bufferoverflow.drawio.png)

## Stack State: Before and After Buffer Overflow Attack

### Function Before Attack
This section of the stack is unchanged and represents the original state:
- **Local Variable**: Unaffected and occupies the top of the stack.
- **Buffer**: Intended space for data storage.
- **Frame Pointer**: Points to the start of the current stack frame (not visible in the after-attack view because we assume it has been overwritten).
- **Return Address**: Points to the next instruction after the function returns (this will be targeted by the overflow).
- **Function Parameters**: Passed to the function and located at the bottom of the stack frame.

### Function After Attack
This section shows the stack after it has been compromised:
- **Local Variable**: Remains unaffected at the top.
- **Overflow Data**: Exceeds the intended buffer space and begins to overwrite adjacent memory.
- **Overwritten Data**: This area has been corrupted by the overflow data, affecting what was originally the frame pointer and potentially other parts of the stack.
- **Return Address**: Has been altered by the overflow data; it now points to a different memory location.
- **Data Written Past Buffer Boundary**: This part of the diagram highlights the critical overflow that leads to the attack vector.
- **Malicious Code**: The new destination for the corrupted return address, leading to the execution of an attacker’s payload.

### Stack Growth
- The downward arrow between the two stack states clearly indicates the direction in which the stack grows.

### Attack Execution Path
- An arrow from the Return Address in the After Attack section to Malicious Code visualizes the path that the CPU’s instruction pointer will follow due to the altered return address.


### c) Issues and Harm Caused by Buffer Overflows

Buffer overflows can have significant repercussions, such as:

- **System Crashes**: Overflows can lead to runtime errors that crash applications.
- **Security Breaches**: By overwriting memory, attackers can execute arbitrary code, potentially gaining unauthorized access.
- **Data Corruption**: Overflow can overwrite valid data, leading to unpredictable behavior or loss of information.
- **Privilege Escalation**: If the overflow occurs in a privileged process, it could grant an attacker elevated system access.

In C programs, buffer overflows are feasible because the language does not automatically check that data written to buffers does not exceed their size, unlike some other languages that enforce such checks.

### d) Techniques to Prevent and Counter Buffer Overflows

#### Prevention Techniques:

- **Bounds Checking**: Implement manual checks for buffer sizes during data operations.
- **Safe Functions**: Utilize safe library functions designed to prevent overflows.
- **Compiler Checks**: Employ compiler options and protections, like stack canaries, to detect overflows.

#### Countermeasures:

- **ASLR (Address Space Layout Randomization)**: Randomizes addresses of processes and system files in memory.
- **DEP (Data Execution Prevention)**: Marks areas of memory as non-executable to prevent execution of part of a memory overflow.
- **Stack Canaries**: Uses special guard variables to detect and block buffer overflow attacks.

#### Defensive Mechanisms in Operating Systems:

Operating systems incorporate features like ASLR and DEP to thwart buffer overflow exploits. They also regularly update and patch vulnerabilities, use strict permission models, and monitor for unusual activities associated with such exploits.

## 2) Research on Zero-Day Exploit

### a) What is a Zero-Day Exploit?

A zero-day exploit is a cyber attack that takes place on the same day a vulnerability is discovered in software, before the developers have released a patch to fix it. These exploits are highly effective because they take advantage of software holes that the wider public, including the developers themselves, are unaware of at the time of the attack. This makes zero-day exploits extremely dangerous, as they do not have known fixes or mitigations when they are executed, allowing attackers to bypass security protections, gain unauthorized access, and inflict significant harm.

### b) Ethical Issues Arising from Zero-Day Exploits and a Christian Worldview Perspective


#### **Discussion:**

From a Christian worldview, the ethical issues surrounding zero-day exploits revolve around the concepts of stewardship, honesty, and the moral responsibility to protect others from harm. In the realm of cybersecurity, exploiting a zero-day vulnerability means utilizing knowledge of a flaw for personal gain or to harm others, rather than disclosing this knowledge to the software developer that could remediate it.

**Stewardship:** Christianity promotes the idea of stewardship, where individuals are entrusted with resources and responsibilities (Genesis 1:28). In the context of zero-day exploits, this can be interpreted as the responsibility of security researchers and hackers to use their skills to protect resources—here, the security and privacy of users—rather than to exploit them.

**Honesty:** Proverbs 12:22 states that "The LORD detests lying lips, but he delights in people who are trustworthy." Applying this to zero-day exploits, the ethical action according to Christian teachings would be to disclose vulnerabilities to the creators responsibly, allowing them to correct the issue and protect users.

**Moral Responsibility:** The parable of the Good Samaritan (Luke 10:30-37) illustrates the Christian duty to help those who are suffering. In cybersecurity, this parable encourages individuals aware of zero-day vulnerabilities to help others by mitigating potential harms through responsible disclosure.

**Benefit to Society:**
Understanding and integrating the Christian ethical perspective on zero-day exploits can benefit society by:
- **Promoting Greater Security:** Encouraging the ethical disclosure of vulnerabilities to improve overall cybersecurity.
- **Preventing Harm:** Reducing the instances of attacks and breaches that exploit undisclosed vulnerabilities.
- **Cultivating Trust:** Building stronger community trust in digital systems and those who maintain and secure them.


## Research on Kali Linux

### a) What is Kali Linux and its Usage?

Kali Linux is a Debian-based Linux distribution designed for digital forensics and penetration testing. It is maintained and funded by Offensive Security Ltd. Kali contains several hundred tools targeted towards various information security tasks, such as Penetration Testing, Security Research, Computer Forensics, and Reverse Engineering. Kali Linux is a crucial tool for security professionals and IT administrators, providing a comprehensive environment to test network security and perform vulnerability scans and attacks to understand system weaknesses. It is used extensively in cybersecurity training to teach security techniques and the use of some of the most sophisticated, powerful, and versatile security tools available.

### b) Standard Tools Included in Kali Linux Distribution

The following table lists 10 standard tools included in the Kali Linux distribution, explaining their functions and their usage in cybersecurity training:

| Tool            | Function                                              | Use in Cyber Security Training                         |
|-----------------|-------------------------------------------------------|--------------------------------------------------------|
| **Nmap**        | Network scanner used to discover hosts and services   | Teaches network mapping and vulnerability identification|
| **Wireshark**   | Network protocol analyzer                             | Used for capturing and analyzing traffic                |
| **Metasploit**  | Framework for developing and executing exploit code   | Facilitates penetration testing with custom exploits    |
| **John the Ripper** | Password cracker                                  | Used for testing password strength and cracking passwords |
| **Aircrack-ng** | Suite for assessing WiFi network security             | Teaches about WiFi vulnerabilities and how to exploit them |
| **Burp Suite**  | Web application security testing                     | Used to assess web application vulnerabilities          |
| **Hydra**       | Network logon cracker                                 | Used to teach brute force attacks against network services |
| **SQLmap**      | Automated SQL injection and database takeover tool    | Used for detecting and exploiting SQL injection flaws   |
| **OWASP ZAP**   (Zed Attack Proxy) | Web application penetration testing tool | Teaches automated and manual vulnerability testing of web apps |
| **Nikto**       | Web server scanner                                    | Used to scan web servers for malicious files and outdated software |

### c) Ethical Issues Related to Kali Linux from a Christian Worldview


#### **Discussion:**

From a Christian worldview, using Kali Linux responsibly aligns with the stewardship entrusted to cybersecurity professionals (Genesis 1:28). The potential for misuse, however, presents significant ethical dilemmas; for instance, tools like Kali can be used maliciously to exploit rather than secure systems. Such actions would be deceitful, violating the Biblical command against lying and stealing (Exodus 20:15, Proverbs 12:22).

**Ethical Conduct:** The Christian ethical framework emphasizes integrity and the moral obligation to protect and not harm (Proverbs 22:1). Security professionals are to use their knowledge and tools to defend and secure, not to attack and steal. This includes practicing 'white-hat' hacking, which involves seeking permission before engaging with another's system and always with the intent of improving security.

**Benefiting Others:** Knowledge of tools like Kali Linux can significantly benefit society by enhancing the security of technological systems. From securing personal data to protecting national infrastructure, the proper use of Kali Linux supports the common good, reflecting the Christian mandate to love and serve others (John 15:12).

## Password Validator Script

A Bash script has been created to check and validate the strength of passwords provided as command-line arguments. The script evaluates the password based on length, numeric character inclusion, and the presence of special characters.

### Password Validator Script (`password_validator.sh`)



```BASH

#!/bin/bash

# Check if the correct number of arguments were provided
if [ "$#" -ne 3 ]; then
    echo "Error: You must enter exactly 3 command line arguments: the filename, the group name, and the operation flag."
    exit 1
fi

filename=$1
group=$2
operation=$3

# Check if the input file exists and is not empty
if [ ! -s "$filename" ]; then
    echo "Error: File does not exist or is empty."
    exit 1
fi

# Check if the group exists, if not, create it
if ! getent group "$group" > /dev/null 2>&1; then
    sudo groupadd "$group"
    echo "Group '$group' created."
fi

# Function to add users from the file
add_users() {
    while IFS=' ' read -r userid password; do
        if [ -z "$userid" ] || [ -z "$password" ]; then
            echo "Skipping blank line."
            continue
        fi

        echo "Adding user '$userid'..."
        sudo useradd -m -p "$password" -G "$group" "$userid"
        if [ "$?" -eq 0 ]; then
            echo "User '$userid' added successfully."
        else
            echo "Failed to add user '$userid'."
        fi
    done < "$filename"
}

# Function to remove users from the file
remove_users() {
    while IFS=' ' read -r userid password; do
        if [ -z "$userid" ]; then
            echo "Skipping blank line."
            continue
        fi

        echo "Removing user '$userid'..."
        sudo userdel -r "$userid"
        if [ "$?" -eq 0 ]; then
            echo "User '$userid' removed successfully."
        else
            echo "Failed to remove user '$userid'."
        fi
    done < "$filename"
}

# Determine the operation to perform
case "$operation" in
    -a)
        add_users
        ;;
    -r)
        remove_users
        ;;
    *)
        echo "Invalid operation flag. Use '-a' to add or '-r' to remove."
        exit 1
        ;;
esac
```
![password_validator](
https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/password_validator.png)


## User Management Script

The user management script handles the addition and removal of users from a Linux system. It takes a file with user information, a group name, and an operation flag as arguments.

### User Management Script (manage_users.sh)

```BASH
#!/bin/bash

# Script to add or remove users from a Linux system

# Validating the correct number of arguments
if [ "$#" -ne 3 ]; then
    echo "Error: Incorrect number of arguments."
    exit 1
fi

# Arguments
filename=$1
group=$2
operation=$3

# Process the input file
if [ ! -s "$filename" ]; then
    echo "Error: User file is empty or does not exist."
    exit 1
fi

# Check and add group if necessary
if ! getent group "$group" &>/dev/null; then
    sudo groupadd "$group"
    echo "Group '$group' has been created."
fi

# Add or remove users based on the operation flag
case "$operation" in
    -a)
        add_users
        ;;
    -r)
        remove_users
        ;;
    *)
        echo "Error: Invalid operation flag."
        exit 1
        ;;
esac

```
![Manage users](
https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/Manage_users.png
)



### Resources 

Bitten Tech. (2017). What is BUFFER OVERFLOW? | Overflow of input | Programming errors explained [Video]. YouTube. https://www.youtube.com/watch?v=mTrTwg03N9M

Cyber Security Entertainment. (2017). Zero Day Exploit explained under 2 mins [Video]. YouTube. https://www.youtube.com/watch?v=PNgIJXodwic

Kim, D., Fisher, D., & McCalman, D. (2009). Modernism, Christianity, and Business Ethics: A Worldview Perspective. Journal of Business Ethics, 90(1), 115–121. https://doi-org.lopes.idm.oclc.org/10.1007/s10551-009-0031-2

Monteclaro, A. J. (2023). What is virtualization security? how to keep your virtualized infrastructure secure. ServerWatch. https://www.serverwatch.com/virtualization/virtualization-security/ 

Reha, M. (2024). Operating System Fundamentals Topic 7. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473003

Reha, M. (2024). Topic 7 Assignment Getting Started.  Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473082

Lynch, E. on O. B. J., & Lynch, J. (2016). Is debian the gold standard for linux security?. InfoWorld. https://www.infoworld.com/article/3118898/is-debian-the-gold-standard-for-linux-security.html 

