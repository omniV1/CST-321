# I/O Software Layers in Operating Systems

## Overview
This document provides an overview of the various Input/Output (I/O) software layers found in a typical operating system, with a focus on the Linux operating system.

## User-Level Libraries

At the highest level, user-level libraries provide an interface between user applications and the kernel I/O subsystems. These libraries encapsulate system call interfaces, offering a more convenient and accessible way to perform I/O operations.

- **Example in Linux**: The GNU C Library (`glibc`) provides standard functions such as `printf` for output and `scanf` for input, alongside file operations like `fopen`, `fwrite`, and `fread`.

## Kernel-Level Modules

Kernel modules, particularly device drivers, act as the middlemen between the hardware devices and the operating system. They translate the generic I/O interfaces provided by the kernel to the specific instructions that the hardware devices can understand.

- **Example in Linux**: Device drivers in Linux, like the `ext4` driver for handling file system operations or the `e1000` driver for Intel Ethernet cards, are typically loaded as kernel modules.

## Interrupt Handlers

Interrupt handlers are low-level routines that respond to hardware interrupts, which are signals sent by the devices to indicate that they require CPU attention.

- **Example in Linux**: When a key is pressed, the keyboard hardware generates an interrupt that is handled by an interrupt handler within the Linux kernel, allowing the system to process the keypress event.

## Operating System Device-Independent I/O Software

This layer abstracts the hardware specifics, providing a unified interface for I/O operations across various devices. It ensures that user-level applications can perform I/O operations without needing to consider the hardware details.

- **Example in Linux**: The Virtual File System (VFS) is Linux's implementation that provides a uniform interface for file systems, whether they are on a local disk, network, or a removable drive.

## Operating System User-Space I/O Software

These components facilitate the interaction between user-space applications and the kernel's I/O mechanisms. They allow programs to use kernel services without engaging in kernel mode's complexities and permissions.

- **Example in Linux**: The system call interface in Linux is used by user-space programs to perform controlled I/O operations like opening files, reading from sockets, or writing to devices.

## Kernel I/O Subsystem

The kernel I/O subsystem includes services such as scheduling, which determines the sequence of I/O operations; buffering, which stores data temporarily during transfer; and caching, which keeps frequently accessed data ready for quick use.

- **Example in Linux**: Linux employs several I/O schedulers, like CFQ (Completely Fair Queuing) and NOOP (No Operation), that manage the order in which I/O requests are processed to optimize throughput and minimize latency.

Each layer plays a vital role in managing I/O operations within a computer system.

## Hardware Interrupt Handling Summary
////////////////////////

INTERRUPT.PNG HERE

//////////////////////

Interrupts are critical for an operating system's responsiveness and efficiency.

### Interrupt Trigger
- **Scenario**: A hardware device, such as a keyboard or network adapter, triggers an interrupt to communicate with the CPU. This could be due to user actions like a key press or incoming network data.
- **Action**: The device sends an interrupt signal directly to the CPU, signaling a pause in current processes to address the interrupt.

### Recognition
- **Mechanism**: The operating system identifies the interrupt's source and nature using the Interrupt Request Line (IRQ). This helps prioritize the interrupts, ensuring critical ones are attended to promptly.

### Acknowledgment
- **Communication**: The operating system acknowledges the interrupt, often signaling back to the hardware device. This acknowledgment usually occurs through designated memory addresses or I/O ports, informing the device that its request is being processed.

### Interrupt Service Routine (ISR)
- **Procedure**: The CPU invokes the appropriate ISR, a pre-defined function within the operating system kernel designed for the specific interrupt. The ISR's role can vary from reading buffer data to initiating hardware operations.

### Execution
- **Process**: The ISR executes the necessary steps to handle the interrupt. This can involve data transfer, event signaling, or direct hardware interaction to adjust its state or operation.

### Cleanup
- **Finalization**: Post-ISR execution involves cleaning up, such as resetting status flags, clearing buffers, or updating system logs. This step ensures the system is ready for further operations.

### Task Resumption
- **Continuation**: The system resumes the task it was performing before the interruption. Depending on the OS's scheduling policies, it might return to the interrupted task or move to a more urgent one.

This process minimizes system disruption and maintains stability for the user.

## Keyboard and Mouse Input I/O Devices Operation

///////////////////////

BLOCK PNG HERE

///////////////////////


## keyboard Input Device Operation

When a user presses a key on a keyboard, it initiates a complex interaction between the keyboard's physical hardware and the computer's operating system, resulting in the pressed key being recognized and acted upon by application software.

- **Physical Key Press**: The user's action depresses a specific key.
- **Hardware Interface**: The keyboard's circuitry detects the key press and generates an electrical signal.
- **Device Controller**: This embedded processor interprets the electrical signal, converting it into a digital code representing the pressed key.
- **I/O Registers**: The digital code is temporarily stored in these registers within the controller.
- **Interrupt Request (IRQ)**: The device controller sends an IRQ to the CPU, indicating that there is keyboard input to be processed.
- **Device Driver**: Within the operating system, a specific keyboard device driver interprets the digital code based on the keyboard layout and encoding standard (e.g., ASCII).
- **Operating System**: The OS integrates this input into its event queue, allowing the software to respond to the key press.
- **Application Software**: Finally, the application active at the time of the key press responds to the input, whether it be typing in a text editor or executing a command in a software program.

## Mouse Input Device Operation

The operation of a mouse as an input device follows a similar path, translating physical movements and clicks into actions on a computer.

- **Movement and Clicks**: The user moves the mouse or clicks its buttons.
- **Sensors and Buttons**: Optical sensors detect movement, and mechanical sensors detect button presses, generating electronic signals.
- **Hardware Interface**: These signals are sent to the mouse's device controller.
- **Device Controller**: Processes the signals, translating them into digital data indicating movement direction, speed, and button clicks.
- **I/O Registers**: This data is temporarily stored in the device's registers.
- **Interrupt Request (IRQ)**: The mouse controller sends an IRQ to the CPU, signaling that input data is ready for processing.
- **Device Driver**: The operating system's mouse device driver interprets the input data, converting movements into cursor position changes and clicks into selection or interaction events.
- **Operating System**: Integrates the mouse input into the system, updating the cursor position or responding to clicks according to the current context or open applications.
- **User Interface**: The effects of the mouse input are reflected on the screen, allowing the user to interact with the graphical user interface (GUI) seamlessly.

In both cases, the keyboard and mouse utilize a combination of physical interactions (key presses, movements, clicks) and software processing (through device controllers, drivers, and the operating system) to provide input methods for the user. These operations ensure that even that actions, like moving a cursor or pressing a key, are translated into digital signals that the computer can understand and respond to.

# References

Baeldung. (2023). Mouse Events and Input Event Interface in Linux. Available at: https://www.baeldung.com/linux/mouse-events-input-event-interface [Accessed 24 Mar. 2024].


Reha, M. (2024). Topic 5 Assignment Guide: Getting Started. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/158247 [Accessed 24 Mar. 2024].

Reha, M. (2024). Topic 5 Book Lectures. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/158247 [Accessed 24 Mar. 2024].

Reha, M. (2024). Topic 5 Ground Lectures. Available at: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472998 [Accessed 24 Mar. 2024].
