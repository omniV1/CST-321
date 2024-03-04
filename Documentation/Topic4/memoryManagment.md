##### Owen Lindsey
##### CST-321
##### Memory Management
##### 3/3/2024


# MMU and Address Translation:

### How it works:

The Memory Management Unit (MMU) is essentially a computer's memory coordinator, translating virtual addresses to physical ones, similar to how a librarian organizes books. Through paging, it divides memory into equal sections for orderly storage, and with segmentation, it adjusts sections based on content size for efficient use. This system allows a computer to handle more tasks by smartly managing its memory space, ensuring smooth operation even when the physical memory is at capacity, akin to a librarian managing books in a library to maximize space and accessibility.

```pseudo
Function TranslateVirtualAddressToPhysicalAddress(virtualAddress):
    // Define page size - assuming 4K bytes for simplicity
    pageSize = 4096

    // Extract the page number and offset from the virtual address
    pageNumber = virtualAddress / pageSize
    offset = virtualAddress % pageSize

    // Lookup the page number in the page table to find the corresponding frame number
    // pageTable is a predefined array or structure mapping virtual pages to physical frames
    if pageNumber is in pageTable:
        frameNumber = pageTable[pageNumber]
    else:
        // If the page number is not in the table, a page fault occurs
        return "Page Fault"

    // Calculate the physical address using the frame number and offset
    physicalAddress = (frameNumber * pageSize) + offset

    return physicalAddress

```
This pseudocode outlines the key steps in translating a virtual address to a physical address:

1. Define the Page Size: The size of each page in memory, which is a constant value, like 4KB in this example.

2. Extract Page Number and Offset: Divide the virtual address by the page size to find which page it belongs to and the offset within that page.


4. Handle Page Faults: If the page number doesn't exist in the page table, a page fault occurs, indicating the data needs to be fetched into memory.

5. Calculate Physical Address: Multiply the frame number by the page size and add the offset to get the physical address.

# Page fault handling

### Flow chart
![flowchart](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic4/screenshots/pageHandling.drawio.png)




### Purpose for page fault handling:

Think of computer's memory system as an airport. The Memory Management Unit (MMU) is the air traffic controller, directing data 'planes' to the memory 'runways.' Like an airport can't handle all planes at once due to limited runways, a computer can't load all data simultaneously due to limited memory.

A page fault is like a plane that arrives but can't land because the runway isn't free. The operating system, just like the control tower, decides what to do usually, it moves less urgent data to the hard drive, like instructing a plane to circle and wait, freeing up memory for immediate needs.

This efficient management ensures essential data is available, much like prioritizing flights for landing. It prevents 'collisions' of data and maintains 'traffic,' allowing the computer to operate with minimal delays or crashes.

# Components of Virtual Memory Management system

| Component        | Role                                                                                              | Type         |
|------------------|---------------------------------------------------------------------------------------------------|--------------|
| MMU (Memory Management Unit) | Translates virtual addresses to physical addresses. Handles the 'how' of data accessibility.    | Mechanism    |
| Page Fault Handler           | Activates on page faults to decide the action (fetch from disk or swap out data). Bridges policy and mechanism. | Policy/Mechanism |
| External Pager               | Decides which pages to swap in/out based on algorithms, setting memory management strategy.     | Policy       |

1. Initial Request: When a process requests access to data, the MMU first attempts to translate the virtual address to a physical address.

2. Page Fault Detection: If the requested data is not found in physical memory, the MMU triggers a page fault, alerting the Page Fault Handler.

3. Decision Making: The Page Fault Handler evaluates the situation. If physical memory is full, it consults the External Pager to decide which data to swap out.

4. Swapping: Based on policies set by the External Pager, such as Least Recently Used (LRU) or First In, First Out (FIFO), specific pages are selected for swapping. This process might involve writing a page to disk if it's modified (dirty) and loading the requested page into the freed space.

5. Table Update: After swapping, the Page Fault Handler updates the page table to reflect the new mappings of virtual addresses to physical addresses.

6. Process Resumption: With the requested data now in physical memory and the page table updated, the MMU can successfully translate the virtual address, allowing the process to access the data and continue its execution.

This cycle ensures that even with limited physical memory, the system can efficiently manage multiple processes, providing them with the necessary data by intelligently deciding which data resides in memory and which can be temporarily moved to disk.

# page table using a C array

### Flowchart

![Flowchart](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic4/screenshots/mmu.drawio.png)

1. Start: The process begins, corresponding to the initial state of the program execution.

2. Input VA: The user is prompted to input a virtual address, as per the program requirement to accept a hexadecimal virtual memory address.

3. Extract Page Offset from VA Using AND operation with mask 0xFFF: This step applies a bitmask to extract the page offset from the virtual address. In a 4KB page size system, the last 12 bits of the address (hence the mask 0xFFF) represent the offset within the page.

4. Is VA within physical memory range?: Here, the flowchart checks whether the virtual address is within the range of the physical memory, which would be between 0x00000000 and 0x0007FFFF for a 512KB physical memory size.

5. Look up PTE using Page Number: The page number part of the virtual address (obtained after masking out the offset) is used as an index to look up the Page Table Entry (PTE) in the page table.

6. Is PTE Valid?: A decision point that checks if the page is currently loaded in physical memory, which corresponds to the "valid" bit in the PTE.

7. Calculate PA using Physical Page Number and Page Offset: If the PTE is valid, the physical address is calculated by combining the frame number from the PTE with the page offset.

8. Output Physical Address: The program displays the calculated physical address, satisfying the requirement to show the resultant physical memory address as a hexadecimal number.

9. Handle page fault: If the PTE is not valid, which means the page is not in physical memory, the flowchart indicates a page fault. This would generally trigger a process to load the page from secondary storage (disk), but for your program's purpose, this step could simply indicate that the page is "Currently on Disk."

10. End: The process concludes, which would correspond to the end of the address translation or after handling the page fault.

### Code implementation
```c
unsigned int promptForPageSize() {
    unsigned int pageSizeChoice;
    printf("Enter page size (1 for 4K, 2 for 8K): ");
    scanf("%u", &pageSizeChoice);
    return pageSizeChoice == 1 ? 4095 : 8191; // Adjusted to match the prompt's requirement
}

void displayPageSize(unsigned int pageSize) {
    printf("Page Size: %u\n", pageSize);
    printf("Hexadecimal: 0x%X\n", pageSize);

    // Display binary
    printf("Binary: ");
    for (int i = 15; i >= 0; i--) {
        printf("%u", (pageSize >> i) & 1);
    }
    printf("\n");
}

void initializePageTable(unsigned int pageSize) {
    // Calculate the number of frames available in physical memory based on the page size
    unsigned int totalFrames = PA_SIZE / pageSize;

    // Initialize all page table entries
    for (int i = 0; i < PAGE_TABLE_ENTRIES; i++) {
        if (i < totalFrames) {
            // For entries that map to a valid frame in physical memory
            pageTable[i].frameNumber = i; // Assign frame number (simplified direct mapping for example)
            pageTable[i].valid = 1; // Mark as valid
        } else {
            // For entries beyond available physical memory frames
            pageTable[i].frameNumber = 0; // Assign a default frame number
            pageTable[i].valid = 0; // Mark as invalid, indicating "on disk" or not present in physical memory
        }
    }
}

void convertAndDisplayAddress(unsigned int pageSize) {
    char virtualAddressHex[10];
    unsigned int virtualAddress;

    printf("Enter virtual memory address (hexadecimal): ");
    scanf("%s", virtualAddressHex);
    virtualAddress = (unsigned int)strtol(virtualAddressHex, NULL, 16);

    unsigned int physicalAddress = virtualToPhysicalAddress(virtualAddress, pageSize);
    if (physicalAddress != (unsigned int)-1) { // Check if address conversion was successful
        printf("Physical Address (Hexadecimal): 0x%X\n", physicalAddress);
    } else {
        printf("Result: Currently on Disk.\n");
    }
}

unsigned int virtualToPhysicalAddress(unsigned int virtualAddress, unsigned int pageSize) {

    unsigned int pageNumber = virtualAddress >> 12; // Get the page number from VA
    if (pageTable[pageNumber].valid) { // Check if the page is valid
        unsigned int frameNumber = pageTable[pageNumber].frameNumber;
        unsigned int pageOffset = virtualAddress & 0xFFF; // Mask out the bottom 12 bits for the offset
        return (frameNumber << 12) | pageOffset; // Combine frame number and offset for PA
    }
    return (unsigned int)-1; // Indicate that the address is not in physical memory
}

```
### Program Functionality Overview

#### 1. Page Size Selection Prompt
- **Operation**: Users are asked to select between two page sizes: 4K (4095 bytes) or 8K (8191 bytes).
- **User Interaction**: Selection is made by entering `1` for a 4K page or `2` for an 8K page.
- **Significance**: This step allows users to define the granularity of memory management for scenarios where page size impacts memory allocation efficiency.

#### 2. Binary and Hexadecimal Representation of Page Size
- **Operation**: The selected page size is shown to the user in both binary and hexadecimal formats.
- **Technical Approach**: The program uses bitwise operations to convert the page size to binary and utilizes format specifiers for hexadecimal.
- **Significance**: Demonstrating the page size in multiple formats provides the data representation methods used within computers for memory management.

#### 3. Page Table Simulation
- **Operation**: The program shows the functionality of a page table by mapping virtual addresses to physical addresses or indicating that data is "on disk."
- **Technical Approach**: It operates within a virtual memory space of 1M bytes against a physical memory limit of 512K bytes, mimicking page table behavior.
- **Significance**: This abstraction models the core functionality of a memory management unit (MMU), offering a view of how virtual to physical address translation occurs within an operating system.

#### 4. Virtual Address Input and Conversion
- **Operation**: Users input a virtual memory address in hexadecimal format, which the program then checks for direct mapping or disk storage.
- **Technical Approach**: The program checks whether the input address falls within the physical memory boundaries, directly mapping it if possible, or show it as "on disk".
- **Significance**: This step emulates the MMU's crucial task of address translation, highlighting the use cases between virtual and physical memory spaces and the handling of memory that exceeds physical storage capabilities.
### 5. Validation with Different Addresses

![screenshot of output](https://github.com/omniV1/CST-321/blob/main/Documentation/Topic4/screenshots/memoryManagment.png)

# Program Output Analysis

The output showcases the execution of a C program designed to emulate the Memory Management Unit (MMU) functionality. Below is an analysis of the program's behavior based on the provided output:

## Test Cases with 4K Page Size

### Case 1: Virtual Address `0x500`
- **Page Size**: 4095 (4K)
- **Hexadecimal Page Size**: 0xFFF
- **Binary Representation**: `0000111111111111`
- **Input Virtual Address**: `0x500`
- **Physical Address**: `0x500`

The virtual address `0x500` falls within the physical memory range, and the program correctly maps it to the same physical address, indicating direct mapping.

### Case 2: Virtual Address `0xFFF`
- **Input Virtual Address**: `0xFFF`
- **Physical Address**: `0xFFF`

Similar to the previous case, the virtual address `0xFFF` is within the range and is directly mapped to an identical physical address.

### Case 3: Virtual Address `0x80000`
- **Input Virtual Address**: `0x80000`
- **Output**: "Currently on Disk."

This virtual address exceeds the physical memory limit. The program correctly identifies that it cannot be mapped to physical memory and is, therefore, "on disk."

### Case 4: Virtual Address `0x7FFFFE`
- **Input Virtual Address**: `0x7FFFFE`
- **Output**: "Currently on Disk."

Despite being close to the physical memory limit, this virtual address is beyond the range and is accurately identified as "on disk."

## Test Cases with 8K Page Size

### Case 1: Virtual Address `0x12345`
- **Page Size**: 8191 (8K)
- **Hexadecimal Page Size**: `0x1FFF`
- **Binary Representation**: `0001111111111111`
- **Input Virtual Address**: `0x12345`
- **Physical Address**: `0x12345`

For an 8K page size, the address `0x12345` is directly mapped, indicating correct address translation.

### Case 2: Virtual Address `0xABCD`
- **Input Virtual Address**: `0xABCD`
- **Output**: "Currently on Disk."

The address `0xABCD` does not fit into the available physical memory range for an 8K page size, and the program correctly reports it as "on disk."

In summary, the program's output reflects the appropriate responses for each test case, demonstrating the correct implementation of virtual to physical address translation, direct mapping, and handling of addresses that do not fit into the physical memory space.

## Conclusion

The MMU emulation program has demonstrated a basic mechanism for translating virtual addresses to physical addresses and handling page faults. Through this program, key concepts of memory management and the role of the MMU within an operating system were explored. 

# screen cast video of application
https://www.loom.com/share/d0253aad08e04282b095c0059a088f9a

# Resources
Tanenbaum, A. S., & Bos, H. (2021). Memory management. In Modern operating systems (5th ed., pp. 193-198)

Reha, M. (2024). Topic 4 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472997

Reha, M. (2024). Topic 4 VA to PA translation algorithm: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/2508842771

Reha, M. (2024). Advice for Getting Started on Assignment 4 Memory Management Research: https://halo.gcu.edu/resource/2d8f9d40-0886-4d3b-8753-33c9f43f59ee
