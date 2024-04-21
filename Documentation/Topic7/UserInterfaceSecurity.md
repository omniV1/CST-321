# CST-321 Assignment - User Interface and Security 
**Student Name:** Owen Lindsey  
**Institution:** Grand Canyon University  
**Course:** CST-321  
**Instructor:** Mark Reha  


## Login Interface Design Choices

The Login Interface is designed to ensure a secure yet user-friendly authentication process. It incorporates a two-step verification process, combining something the user knows (their password) and something the user has (access to an authentication app). 

### Authentication Scheme and Security Factors
- **Single-Factor Authentication**: Initial login requires a username and password, which provides the first layer of security.
- **Two-Factor Authentication**: On successful entry of username and password, the user is prompted to enter a code from an authenticator app, providing a second security factor.

### Security Policies
- Passwords are hashed and encrypted to protect against unauthorized access.
- The account is locked after three unsuccessful login attempts to prevent brute force attacks.
- The 2FA code expires quickly to mitigate the risk of interception or reuse.

![Login Flowchart](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/loginInterfaceFlowchart.drawio.png)

![Login webframe](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/loginInterface.drawio.png)


## Functional Requirements and Security Policies

| Functional Requirement                 | Security Policy                              |
|----------------------------------------|----------------------------------------------|
| Username (8-10 alphanumeric characters) | AES-256 encryption for stored usernames      |
| Password (10-15 mixed characters)      | SHA-256 hashing for password transmission    |
| Biometric data for 2FA                 | Biometric data encrypted at rest             |
| Automatic lock after 4 failed attempts | Account lockout policy for security          |
| Password change every 90 days          | Mandatory password rotation policy           |
| No password reuse for 10 generations   | History-based password policy enforcement    |
| 2FA code entry                         | Use of TOTP for 2FA to ensure one-time use   |


## System Help Interface Design Choices

The System Help Interface is crafted to provide users with easy access to support documents while ensuring that sensitive information is protected. It balances the need for open access to information with the need to secure and control access to more sensitive system details.

### Authentication Scheme and Security Factors
- **Single-Factor Authentication**: Users can browse general help topics without signing in.
- **Two-Factor Authentication**: Accessing sensitive topics requires additional verification, linking with the user's verified email.

### Security Policies
- Sensitive help topics are behind an additional verification wall to ensure that only authorized users can access them.
- User inactivity leads to an automatic sign-out, protecting the session.

![System Help Flowchart](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/SysHelpFlowchart.drawio.png)

![System Help webframe](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/SystemHelp.drawio.png)


## Functional Requirements and Security Policies

| Functional Requirement                 | Security Policy                                   |
|----------------------------------------|---------------------------------------------------|
| Keyword-based search for help topics   | Search results filtering and secure data retrieval |
| Access to sensitive help topics        | Email verification for additional security         |
| Automatic sign-out after inactivity    | Session protection policy                          |



## Process Management Interface Design Choices

The Process Management Interface allows users to effectively monitor and control system processes. This interface is designed with admin users in mind, requiring robust security measures for process manipulation.

### Authentication Scheme and Security Factors
- **Single-Factor Authentication**: Actions on non-critical processes require an access key or token.
- **Two-Factor Authentication**: For critical system processes, additional biometric verification is prompted.

### Security Policies
- Sensitive process actions are logged for auditing purposes and are subject to strict access control.
- Biometric data used for verification is stored and transmitted with strong encryption protocols.

![process Flowchart](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/processFlowchart.drawio.png)

![process webframe](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic7/screenshots/ProcessManager.drawio.png
)

## Functional Requirements and Security Policies

| Functional Requirement                   | Security Policy                                 |
|------------------------------------------|-------------------------------------------------|
| List and control of system processes     | Encrypted storage and secure API for process management |
| Biometric verification for critical actions | Use of secure biometric verification methods    |
| Action logging for auditing              | Comprehensive logging and monitoring policy    |
| Restriction of sensitive actions to admin users | Access control policies for sensitive actions |


### Resources

Authentication cheat sheet. Authentication - OWASP Cheat Sheet Series. (n.d.). https://cheatsheetseries.owasp.org/cheatsheets/Authentication_Cheat_Sheet.html 

Reha, M. (2024). Operating System Fundamentals Topic 7. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473003

Reha, M. (2024). Topic 7 Assignment Getting Started.  Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473082

Ultimate Flowchart Guide 2024: Definition, examples, symbols, etc.. Ultimate Flowchart Guide 2024: Definition, Examples, Symbols, etc. (n.d.). https://www.zenflowchart.com/flowchart 
