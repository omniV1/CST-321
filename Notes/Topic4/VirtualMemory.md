# Virtual Memory in Operating Systems

## Introduction to Virtual Memory

- **History**: In the 1960s, memory management solutions involved splitting programs into sections called overlays.
- **Problems**: Overlays were stored on disk and swapped in and out of memory as needed, which was not efficient for large programs or multitasking.
- **Solution**: The virtual memory system was introduced to address these issues.

## What is Virtual Memory?

- **Definition**: Virtual memory is a feature of operating systems that allows computers to compensate for physical memory shortages.
- **Mechanism**: It translates virtual memory addresses into physical addresses and maps them accordingly.
- **Pages**: Programs are divided into chunks called pages, which are the basic units of data for virtual memory.
- **Storage**: Pages that do not fit in physical memory can be stored on disk.

## What is a Swap File?

- **Swap File**: A file on disk that holds the pages that are not currently held in physical memory.
- **Purpose**: It acts as an overflow area for the physical memory, allowing the system to appear to have more memory than it physically has.

## Virtual Memory Translation

- **Process**: Programs generate virtual addresses, which the Memory Management Unit (MMU) in hardware translates to physical addresses.
- **Components**:
  - **CPU**: Sends virtual addresses to the MMU.
  - **MMU**: Translates virtual addresses to physical addresses.
  - **Memory**: Where the translated addresses are used to access the actual data.
  - **Disk Controller**: Manages reading and writing to disk when pages are swapped in and out.

# Discussion

- **Efficiency**: Virtual memory allows systems to run more efficiently by using disk space as an extension of RAM.
- **Multitasking**: It enables multitasking by allowing more processes to run concurrently than would fit in physical memory alone.
- **Flexibility**: Virtual memory provides a flexible memory management system where the size of a program's memory can be adjusted dynamically.

By integrating virtual memory, modern operating systems can run large applications and support multiple processes effectively, overcoming the limitations of physical memory constraints.

# Virtual Memory Mapping Entities

## Who does the Virtual Memory mapping?

- **Mapping Table**: Known as a Page Table, which is cached with Page Table Entries (PTE).
- **TLB**: Translation Lookaside Buffer (TLB) used to cache PTEs for faster memory access.
- **MMU**: Memory Management Unit (MMU) maps virtual addresses to physical addresses.
- **Process Context Switch**: MMU is re-initialized during each context switch to ensure the correct mapping of the process's virtual memory.


# Virtual Memory Mapping Entities

## Who does the Virtual Memory mapping?

- **Mapping Table**: Known as a Page Table, which is cached with Page Table Entries (PTE).
- **TLB**: Translation Lookaside Buffer (TLB) used to cache PTEs for faster memory access.
- **MMU**: Memory Management Unit (MMU) maps virtual addresses to physical addresses.
- **Process Context Switch**: MMU is re-initialized during each context switch to ensure the correct mapping of the process's virtual memory.

# Virtual Memory Pages

## What is a Virtual Memory Page?

- **Virtual Address Space**: Each process has a separate virtual address space.
- **Page Table**: A structure that maps virtual pages to physical frames.
- **Page Size**: Typically, pages are at least 4KB in size.
- **Address Range**: Explains how addresses are calculated based on page size (e.g., 4K–8K means addresses 4096–8191).


# MMU Translation Mechanism

## How does the MMU Map and Translate virtual addresses?

- **MMU Operation**: Internal operation with pages, translating 16-bit virtual addresses using page tables.
- **Translation**: Splits virtual addresses into Page Number and Page Offset.
- **Faults**: If the needed page is not in memory, a fault is generated to load the page from disk.
- **Physical Address**: Formed from the page number and offset.

# Operating Systems - Paging and Page Tables

## What is a Page Table Entry?

- A Page Table Entry (PTE) contains the mapping from virtual addresses to physical addresses.
- Typical fields in a PTE:
  - `Caching disabled`: Indicates whether caching is disabled for the page.
  - `Modified (Dirty)`: Shows if the page has been written to (modified).
  - `Referenced`: Used to tell if the page has been accessed.
  - `Protection`: Stores access control information (e.g., read/write permissions).
  - `Present/Absent`: Indicates whether the page is currently in physical memory.
  - `Page frame number`: The physical memory address where the page resides.

- **Note**: If the page is not present in physical memory, the `Present/Absent` flag is set to 0, which will trigger a page fault, causing the Operating System (OS) to load the page from the disk.

## Does Paging Need to Be Fast?

- **Answer**: YES!!!
- Reasons why paging must be fast:
  1. Every virtual address must be quickly translated to a corresponding physical address.
  2. The Memory Management Unit (MMU) is implemented in hardware to facilitate fast address translations.
  3. The virtual address space can be large, necessitating quick lookups in the page table.

## How Can We Speed Up Paging?

- Use of a Translation Lookaside Buffer (TLB):
  - The TLB is a cache within the MMU used to store recent Page Table Entries (PTEs).
  - It typically contains between 8 to 256 entries.
  - Caching PTEs in the TLB saves time because the MMU can retrieve the translation from the TLB instead of the main memory.

- Example TLB Entries:

  | Valid | Virtual Page | Modified | Protection | Page Frame |
  |-------|--------------|----------|------------|------------|
  | 1     | 140          | 1        | RW         | 31         |
  | 1     | 20           | 0        | R X        | 38         |
  | 1     | 130          | 1        | RW         | 29         |
  | ...   | ...          | ...      | ...        | ...        |

- `Valid`: Indicates if the entry is valid.
- `Virtual Page`: The virtual page number.
- `Modified`: Indicates if the page has been modified.
- `Protection`: The access permissions of the page (Read-Write `RW`, Read-Execute `R X`, etc.).
- `Page Frame`: The physical frame number where the page resides.
