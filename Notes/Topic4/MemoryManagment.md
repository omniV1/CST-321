# Intro to Memory Management

### Running Processess with no Memory Abstraction

1. User program and operating system in RAM.

2. Operating system in Rom, user program starting at memory address 0.

3. Device drivers in ROM, user program and operating system in RAM.

These descriptions are reminiscent of the very early days of computing, where operating systems were rudimentary and memory management was very simple. This could mimic the era of batch processing systems or early single-user systems without multitasking capabilities.

# Memory Management in Operating Systems

## The Relocation Problem

- **Issue**: When two programs are loaded back-to-back in memory without any abstraction, they can't run if the memory addresses they need are already in use.
- **Example**: Two programs, each of 16-KB size, cannot be loaded one after the other if the memory is already occupied, leading to the relocation problem.

## Base and Limit Registers

- **Solution**: Introduction of Base and Limit Registers to solve the relocation problem.
- **Base Register**: Holds the starting memory address where a process is loaded.
- **Limit Register**: Contains the size of the process.
- **Functionality**: CPU uses the Base register to calculate actual memory addresses during execution and checks with the Limit register to prevent the process from accessing memory outside its allocated space.

## Swapping

- **Concept**: Swapping is an early form of multitasking that involves loading and running entire processes in memory for a while before swapping them out to disk.
- **Purpose**: This process ensures that the CPU is always busy with some process, enhancing CPU utilization by swapping out processes that are waiting for their next turn to use the CPU.

## Early Memory Management Algorithms

- **Strategies**:
  - **First Fit**: Allocate the first hole that is big enough.
  - **Next Fit**: Like first fit but starts searching from the location of the last placement.
  - **Best Fit**: Allocate the smallest hole that is big enough; must search the entire list unless ordered by size.
  - **Worst Fit**: Allocate the largest hole; must also search the entire list.
  - **Quick Fit**: Maintain separate lists for commonly used sizes.

## Discussion Question

- **Question**: Why do we need a better Memory Management System?
- **Implication**: The early memory management strategies have limitations and do not efficiently address the needs of modern computing systems.

# Need for Advanced Memory Management Systems

- **Scalability**: Early techniques are not scalable for the complex needs of modern applications.
- **Efficiency**: Improved methods are required for efficient utilization of CPU and memory resources.
- **Multitasking**: Modern systems run multiple applications simultaneously, requiring dynamic memory allocation.
- **Security**: Advanced memory management can provide better isolation and protection between processes.
- **Flexibility**: Techniques like virtual memory, paging, and segmentation allow for more flexibility in memory usage.

By understanding these concepts and their evolution, you can appreciate the complexity and importance of memory management in contemporary operating systems.
