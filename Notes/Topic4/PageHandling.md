# What is a Page Fault?

A **Page Fault** is a type of interrupt, also known as a trap, which is raised by the CPU when a program accesses a memory page that is mapped into the virtual address space but not loaded into the physical memory.

The hardware component responsible for detecting a page fault is the **Memory Management Unit (MMU)**.

The **Page Fault Handler**, which is part of the operating system's kernel, manages these events and loads the required page into physical memory.

### How does Copy-On-Write work in our `fork()` API?



# What is a Page Fault Handler?

A Page Fault occurs under the following circumstances:

- There is no **Page Table Entry (PTE)** for the accessed page.
- The **Page Table Entry (PTE)** prohibits access due to the page not being present or an access rights conflict.

When a page is not present in physical memory, the present/absent bit is set to 0, causing a fault and prompting the OS to load the page from the disk.


# What happens in the Page Fault Handler? 

1. The **MMU** triggers a trap to the kernel, which saves the program counter.
2. An assembly routine saves the general registers and other state information.
3. The system identifies the required **virtual page**.
4. The **virtual address** causing the fault is checked for validity and protection consistency.
5. If the **Page Frame** is dirty, it's scheduled for disk transfer, and the process is suspended.
6. Once clean, the OS locates the disk address of the page and schedules its loading into physical memory.
7. After loading, the **Page Table** is updated, and the frame is marked as normal.
8. The faulting instruction is reset to its initial state.
9. The OS reschedules the faulting process and returns to the assembly routine.
10. The assembly routine restores the saved state and resumes user space execution.

### What is Page Replacement?
- **Purpose**: Determine which memory pages to swap out to disk.
- **Demand Paging**: Loads a page into RAM only when requested.
- **Preemptive Paging**: Preloads pages predicted to be needed soon.
- **Anticipatory Paging**: Loads requested page and consecutive pages on a page fault, like CPU pre-fetch.

### Example Page Swapping to a Backing Store
- Illustrates page swapping process between main memory and disk.
- Demonstrates paging to a static swap area and dynamic backing up of pages.

### Summary of Page Replacement Algorithms
- **Optimal**: Theoretical best but not implementable; a benchmark.
- **NRU (Not Recently Used)**: Crude approximation of LRU.
- **FIFO (First-In, First-Out)**: Can discard important pages.
- **Second Chance**: Improves on FIFO.
- **Clock**: Practical implementation.
- **LRU (Least Recently Used)**: Excellent, difficult to implement accurately.
- **NFU (Not Frequently Used)**: Crude LRU approximation.
- **Aging**: Efficient, good LRU approximation.
- **Working Set**: Somewhat costly to implement.
- **WSClock**: Efficient and effective algorithm.

### Flags in a Page Table Entry
- **Caching Disabled**
- **Modified (Dirty Bit)**
- **Present/Absent**
- **Referenced**
- **Protection**
- **Referenced Bit**: Set when a page is accessed.
- **Modified Bit**: Set when a page is written to.

### Aging Page Replacement Algorithm
- Uses a **Reference Counter** per page.
- Shifts counter right, adds the Reference bit on the left.
- Evicts the page with the lowest Reference Counter value.
- Demonstrates the algorithm with R-bits and Counters over time.

## WSClock Page Replacement Algorithm
- All pages are kept in a circular list.
- The "clock hand" advances around the ring, and each entry contains "time of last use".
- On a page fault, the following logic is applied:
  - If Reference Bit = 1: Page is in use and not evicted. The Referenced Bit is cleared if it will be set again soon, and the "time of last use" is updated.
  - If Reference Bit = 0:
    - If the age of the page is less than T, it's in the working set. The hand advances without eviction.
    - If the age of the page is greater than T:
      - If the page is clean, reclaim the frame without writing to disk.
      - If the page is dirty, schedule a write for the page and evict it.

## WSClock Algorithm Operation Examples
- Examples show the operation of the WSClock algorithm when R = 1 and R = 0.
- The diagrams likely illustrate how the algorithm advances the hand and decides whether to evict a page based on its Reference Bit and "time of last use".

## Detailed Explanation of Shared Pages in Operating Systems

In the context of operating systems (OS), **shared pages** refer to a memory management technique that allows multiple processes to access the same physical memory pages. This approach is particularly useful for multi-process or multi-threaded environments where different processes might need to access the same code or data.

### Purpose of Shared Pages

- **Efficient Memory Use**: Shared pages reduce the overall memory footprint of running applications by avoiding duplicate copies of the same content in physical memory.
- **Faster Process Creation**: When a new process is created, the OS can map the shared pages into the process's address space instead of copying the data, which can significantly speed up the process creation time.

## How Shared Pages Work

1. **Memory Mapping**:
   - The operating system maintains a page table to keep track of all memory pages, including shared pages.
   - When a process is created or a new library is loaded, the OS maps the shared pages into the process's virtual address space.
   
2. **Copy-on-Write (CoW)**:
   - Sometimes, shared pages use a mechanism called Copy-on-Write. With CoW, if a process tries to write to a shared page, the OS creates a private copy of that page for the process. This ensures that other processes are not affected by the changes.

3. **Shared Libraries and Mappings**:
   - Shared libraries, like the C standard library (libc), are common examples of shared pages. These libraries are mapped into the address space of applications that use them.
   - Shared mappings are also used for inter-process communication (IPC), where two or more processes share a segment of memory to exchange data without involving disk I/O or network communication.

### Advantages of Shared Pages

- **Reduced Memory Consumption**: Multiple processes can use the same library or data without increasing the physical memory usage.
- **Improved Cache Utilization**: Since the same physical page is used, the data in shared pages benefits from being cached once for all accessing processes, improving cache utilization.
- **Lower Context Switching Overhead**: Shared pages reduce the need to load or unload page tables during context switches between processes that share the same memory.

### Security and Synchronization

- **Access Control**: The OS ensures that shared pages are typically read-only to prevent a process from modifying them. If write access is required, it is strictly controlled and monitored.
- **Synchronization Mechanisms**: When shared pages are used for IPC, synchronization mechanisms like semaphores or mutexes are often required to coordinate the access to shared pages.

## Detailed Explanation of Segmentation in Operating Systems

Segmentation is a memory management technique in which the memory is divided into different segments of variable size, each segment being a different length. This technique is designed to provide a more flexible and user-oriented approach to memory management.

### How Segmentation Works

1. **Logical Division**:
   - Memory is divided into logical segments that correspond to the different modules of a program, such as the main function, utility functions, data structures, etc.

2. **Segment Table**:
   - Each program has a segment table that stores the base address of each segment in physical memory and the length of the segment.
   - The segment table is indexed by segment numbers, which are assigned to segments in a way that is meaningful to the user.

3. **Addressing**:
   - Addresses in a segmented memory system are specified by a two-part address: the segment number and the offset within that segment.
   - For example, an address might be specified as `segment 2, offset 14`, which refers to the 14th memory location in the 2nd segment.

4. **Protection and Sharing**:
   - Each segment can have its own set of access controls, allowing for protection mechanisms at the segment level.
   - Segments can be shared between processes, where a single segment is accessible by multiple processes for inter-process communication or shared libraries.

### Advantages of Segmentation

- **Simplicity for Users**: Segments can correspond to natural divisions within a user's program, such as functions, data arrays, etc.
- **Protection**: Each segment can have its own protection settings (read/write/execute), which can be enforced by the hardware, making it more secure.
- **Sharing**: Segments can be shared among processes, allowing for efficient inter-process communication and avoiding duplication of common code.

### Real-World Examples

- **Compilers**: A compiler might create separate segments for the header files, library functions, and helper functions, making it easier to manage and link the compiled code.
- **Operating System Kernels**: The kernel's code, data, and stack might be in separate segments, providing a clear structure to the kernel and improving security.
- **Multitasking Environments**: In a multitasking environment, the stack for each task might be in a separate segment, simplifying task switching and state management.

## Real-World Encounter: Segmentation vs. Shared Pages

When discussing memory management in operating systems, segmentation and shared pages are two concepts that deal with how a system manages and allocates memory to processes. Below is a table that compares and contrasts these two concepts based on various attributes in a real-world context:

| Attribute            | Segmentation                                                            | Shared Pages                                                         |
|----------------------|-------------------------------------------------------------------------|----------------------------------------------------------------------|
| **Basic Concept**    | Divides memory into variable-sized units based on logical program sections. | Allows multiple processes to use the same page in memory.            |
| **Use Case**         | Typically used for organizing a program's modules into logical units.   | Used for allowing efficient memory usage by sharing common code/data.|
| **Real-World Example** | A text editor program might be segmented into code for the UI, file I/O, and spell checking. | An operating system where multiple running instances of a text editor share the same code pages but have separate data pages. |
| **Advantages**       | Matches the logical structure of programs; can provide a more intuitive approach to memory management. | Saves memory by avoiding duplication; allows for efficient inter-process communication. |
| **Disadvantages**    | Can lead to external fragmentation due to variable segment sizes.       | Requires careful management to ensure synchronization and consistency. |
| **Protection**       | Offers the ability to set different access rights per segment (read, write, execute). | Shared pages typically have read-only access to avoid conflicts.       |
| **Flexibility**      | High flexibility due to variable segment sizes.                         | Less flexible as pages are of fixed size.                             |
| **Memory Utilization**| Can be less efficient due to fragmentation.                            | More efficient as it reduces the number of duplicate pages.           |
| **Implementation**   | Requires a segment table with base and limit for each segment.          | Requires a page table with an entry for each shared page.             |
| **Suitability**      | More suitable for systems where programs have distinct logical units.   | More suitable for systems running multiple instances of the same program or using shared libraries. |
