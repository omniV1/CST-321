/**
* Owen Lindsey
* Cst-321
* 03/03/2024
* This code was done with the help of:
*
* Tanenbaum, A. S., & Bos, H. (2021). Memory management. In Modern operating systems (5th ed., pp. 193-198)
*
* Reha, M. (2024). Topic 4 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472997
*
* Reha, M. (2024). Topic 4 VA to PA translation algorithm: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/2508842771
*
* Reha, M. (2024). Advice for Getting Started on Assignment 4 Memory Management Research: https://halo.gcu.edu/resource/2d8f9d40-0886-4d3b-8753-33c9f43f59ee
**/
#include <stdio.h>
#include <stdlib.h>

// Define constants for the sizes of virtual and physical address spaces
#define VA_SIZE 0xFFFFF // Virtual Address Space: 1MB (20-bit address space)
#define PA_SIZE 0x7FFFF // Physical Address Space: 512KB (19-bit address space)

// Define the number of page table entries based on the virtual address space
#define PAGE_TABLE_ENTRIES 256 // This size may vary based on the actual page table logic

// Structure definition for a Page Table Entry (PTE)
typedef struct {
    unsigned int frameNumber : 19; // Frame number in physical address (PA), 19 bits
    unsigned int valid : 1;        // Valid bit to indicate if the frame is present in memory
} PTE;

// Global array representing the page table
PTE pageTable[PAGE_TABLE_ENTRIES];

// Function prototypes
unsigned int promptForPageSize();
void displayPageSize(unsigned int pageSize);
void initializePageTable(unsigned int pageSize);
void convertAndDisplayAddress(unsigned int pageSize);
unsigned int virtualToPhysicalAddress(unsigned int virtualAddress, unsigned int pageSize);

// Main function of the program
int main() {
    // Prompt user for page size and display it
    unsigned int pageSize = promptForPageSize();
    displayPageSize(pageSize);

    // Initialize page table entries based on page size
    initializePageTable(pageSize);

    // Convert user input virtual address to physical address and display
    convertAndDisplayAddress(pageSize);
    return 0;
}

// Prompt the user for a page size and return the corresponding size in bytes
unsigned int promptForPageSize() {
    unsigned int pageSizeChoice;
    printf("Enter page size (1 for 4K, 2 for 8K): ");
    scanf("%u", &pageSizeChoice);
    // Return either 4095 for 4K or 8191 for 8K based on the user's choice
    return pageSizeChoice == 1 ? 4095 : 8191;
}

// Display the page size in binary and hexadecimal formats
void displayPageSize(unsigned int pageSize) {
    printf("Page Size: %u\n", pageSize);
    printf("Hexadecimal: 0x%X\n", pageSize);

    // Display the binary representation of the page size
    printf("Binary: ");
    for (int i = 15; i >= 0; i--) {
        printf("%u", (pageSize >> i) & 1);
    }
    printf("\n");
}

// Initialize the page table with frame numbers and valid bits
void initializePageTable(unsigned int pageSize) {
    // Calculate the number of frames available in physical memory based on the page size
    unsigned int totalFrames = PA_SIZE / pageSize;

    // Initialize page table entries
    for (int i = 0; i < PAGE_TABLE_ENTRIES; i++) {
        // If the entry corresponds to a valid frame in physical memory, mark it as valid
        if (i < totalFrames) {
            pageTable[i].frameNumber = i; // Example direct mapping for simplicity
            pageTable[i].valid = 1;       // Mark the entry as valid
        } else {
            // For entries beyond the available frames, mark them as invalid
            pageTable[i].frameNumber = 0; // Default frame number
            pageTable[i].valid = 0;       // Mark the entry as invalid, indicating it's "on disk"
        }
    }
}

// Prompt the user for a virtual memory address, convert it, and display the physical address
void convertAndDisplayAddress(unsigned int pageSize) {
    char virtualAddressHex[10];
    unsigned int virtualAddress;

    printf("Enter virtual memory address (hexadecimal): ");
    scanf("%s", virtualAddressHex);
    virtualAddress = (unsigned int)strtol(virtualAddressHex, NULL, 16);

    // Convert the virtual address to a physical address using the page table
    unsigned int physicalAddress = virtualToPhysicalAddress(virtualAddress, pageSize);
    if (physicalAddress != (unsigned int)-1) {
        printf("Physical Address (Hexadecimal): 0x%X\n", physicalAddress);
    } else {
        // If the physical address is -1, it indicates the address is "Currently on Disk"
        printf("Result: Currently on Disk.\n");
    }
}

// Convert a virtual address to a physical address using the page table
unsigned int virtualToPhysicalAddress(unsigned int virtualAddress, unsigned int pageSize) {
    // Determine the maximum valid page number based on physical address space size
    unsigned int maxValidPageNumber = PA_SIZE / pageSize;

    // Extract the page number from the virtual address
    unsigned int pageNumber = virtualAddress >> 12; // 12-bit shift corresponds to a 4KB page size
    // If the page is present in the page table, calculate the physical address
    unsigned int pageNumber = virtualAddress / pageSize;
    unsigned int pageOffset = virtualAddress % pageSize;  // Extract the page offset

    // Check if the page number exceeds the maximum valid page number
    if (pageNumber >= maxValidPageNumber) {
        // If the page number is too high, it means the data is not in physical memory
        return (unsigned int)-1; // Indicate that the address is "Currently on Disk"
    }

    // Check if the page is present in the page table and valid
    if (pageTable[pageNumber].valid) {
        // Retrieve the frame number from the page table entry
        unsigned int frameNumber = pageTable[pageNumber].frameNumber
        unsigned int frameNumber = pageTable[pageNumber].frameNumber;
        // Calculate the physical address by combining the frame number and page offset
        return (frameNumber * pageSize) + pageOffset;
    } else {
        // If the page is not valid, it's a page fault or "Currently on Disk"
        return (unsigned int)-1;
    }
}
