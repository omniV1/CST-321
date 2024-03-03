#### Owen Lindsey

#### CST-321

#### Activity 4 - Number Conversion and Bitwise Operations

---

# Number Conversion and Bitwise Operations in C

## Theory of operations

| Components                   | Description                                                                                          |
|------------------------------|------------------------------------------------------------------------------------------------------|
| **Initialization**           | The program initializes an array `bits` to represent binary digits and sets a flag `ok` to control user input within a valid range. |
| **User Input**               | Prompts the user for a number between 0 and 1000, ensuring input is within bounds for the conversion process. |
| **Binary Conversion**        | Converts the user input to binary by calling `convertPrintBinary` which in turn uses `decimalToBinary` to fill the `bits` array with the corresponding binary digits. |
| **Hexadecimal Conversion**   | Utilizes standard I/O library functions to convert and display the number in hexadecimal format. |
| **Bitwise Manipulation**     | Performs bitwise operations by shifting the input number, masking certain bits, and combining the result using bitwise OR with a fixed pattern. |
| **Result Display**           | Outputs the manipulated number in decimal, binary, and hexadecimal formats, demonstrating different representations of the same data. |

## Code:

```c
int main() {
    int number;
    char bits[32] = { // LSB at index 0 and MSB at index 31
                      '0','0','0','0','0','0','0','0',
                      '0','0','0','0','0','0','0','0',
                      '0','0','0','0','0','0','0','0',
                      '0','0','0','0','0','0','0','0',
                      '\0' // Null terminator for the string
                    };
    bool ok = false; // Flag to check if the input is within the valid range

    // Prompt user for a number within the range
    while(!ok) {
        printf("\nDisplay a number between 0 and 1000: ");
        scanf("%u", &number);
        if(number > 1000) {
            printf("This number needs to be between 0 and 1000!\n");
        } else {
            ok = true; // Valid input, break out of the loop
        }
    }

    // Display the number in binary
    printf("The number in binary is: ");
    convertPrintBinary(number, bits);

    // Display the number as a 32-bit hexadecimal number
    printf("The number in hexadecimal is: 0x%08X\n", number);

    // Shift the number left by 10, mask the lower 10 bits to 0, OR with 0x3FF
      int result = (number << 10) & (~0x3FF) | 0x03FF;

    // Display the result in decimal, binary, and hexadecimal
    printf("The result in decimal is: %u\n", result);
    printf("The result in hexadecimal is: 0x%08X\n", result);
    printf("The result in binary is: ");
    convertPrintBinary(result, bits);

    return 0; // Successful execution
}

// Function definitions below

/**
 * Print the binary representation of a number stored in an array of char.
 * The binary representation is stored in reverse order, with the least significant bit (LSB) at index 0.
 *
 * @param bits A char array containing the binary representation of a number.
 */
void printBinary(char* bits) {
    // Loop from the most significant bit (MSB) to the least significant bit (LSB)
    // and print each bit.
    for(int x = 31; x >= 0; --x) {
        printf("%c", bits[x]);
    }
    // After printing all bits, print a newline character for better readability.
    printf("\n");
}

/**
 * Resets all bits in the array to '0'.
 *
 * @param bits A char array representing binary bits to be cleared.
 */
void clearBinaryBits(char* bits) {
    // Set each bit in the array to '0' indicating the binary zero.
    for(int i = 0; i < 32; i++) {
        bits[i] = '0';
    }
}

/**
 * Converts an integer to binary and prints its binary representation.
 * It uses other utility functions to clear any previous data, convert the number,
 * and then print it.
 *
 * @param number The decimal number to convert to binary.
 * @param bits The char array where the binary representation will be stored.
 */
void convertPrintBinary(int number, char* bits) {
    // First clear the binary bits array to ensure it doesn't contain old data.
    clearBinaryBits(bits);
    // Convert the decimal number to binary and store the result in bits array.
    decimalToBinary(number, bits);
    // Print the binary representation stored in bits array.
    printBinary(bits);
}

/**
 * Converts a decimal number to its binary representation and stores it in a char array.
 * The binary representation is stored in reverse order, from LSB to MSB in the array.
 *
 * @param number The decimal number to convert to binary.
 * @param bits The char array where the binary representation will be stored.
 */
void decimalToBinary(int number, char* bits) {
    int index = 0; // Start from the beginning of the array.
    // Continue to divide the number by 2 to get each binary bit.
    while(number != 0) {
        int remainder = number % 2; // Get the remainder (0 or 1).
        bits[index] = remainder > 0 ? '1' : '0'; // Assign the corresponding bit as '0' or '1'.
        number /= 2; // Divide the number by 2 for the next iteration.
        index++; // Move to the next position in the array.
    }
    // Fill the rest of the array with '0' to complete the 32-bit binary representation.
    for(int i = index; i < 32; i++) {
        bits[i] = '0';
    }
}

```
## Key Functions and System Calls

| Function/System Call    | Description                                                                                   |
|-------------------------|-----------------------------------------------------------------------------------------------|
| `convertPrintBinary()`  | Orchestrates the conversion of a decimal number to binary and then prints it.                |
| `decimalToBinary()`     | Performs the actual conversion from decimal to binary.                                        |
| `printBinary()`         | Handles the printing of the binary array in a human-readable format.                          |
| `clearBinaryBits()`     | Resets the binary array to all zeros to prepare for a new conversion.                         |

## Function Descriptions:

- `convertPrintBinary()`: This function coordinates several steps: clearing any previous binary representation, converting the new decimal input to binary, and then displaying this binary data. By encapsulating these operations, it simplifies the main program flow and emphasizes modularity.

- `decimalToBinary()`: The core algorithm for converting decimal numbers to binary is encapsulated within this function. It iteratively divides the decimal number, capturing the remainder as binary digits, and stores them in an array.

- `printBinary()`: this function takes the binary data stored in an array and prints it from the most significant bit to the least significant bit. This reverse-order printing is crucial for presenting the binary data in a format that's intuitive for us to read.

- `clearBinaryBits()`: Before each conversion process, it's essential to reset the binary representation to ensure no residual data from previous operations affects the current calculation. This function zeroes out the binary array, preparing it for a fresh conversion.

These functions work together to create a program that converts decimal numbers to binary, displaying them alongside their hexadecimal representation and demonstrating basic bitwise operations.


# Research question A: TLB Miss

 To cause a TLB (Translation Lookaside Buffer) miss on purpose, we will try to access parts of memory in such a way that the computer's quick memory lookup (the TLB) doesn't already have a shortcut for where to find it. Here's a simple breakdown of how we plan to do this with our loop and the variables `M` (step size) and `N` (array size).

- **Page Size**: This is like a block of memory. Our block size is 4KB, which is pretty standard.
- **TLB Entries**: Think of this as slots in our quick memory lookup. We have 64 slots available.
- **Size of an `int`**: We're assuming each integer takes up 4 bytes of space.


### Step Size (`M`)

- **Goal**: We want to jump far enough in our memory block so that each time we do, we're landing on a new block.
- **How**: Since a block is 4KB and an `int` is 4 bytes, jumping 1024 `int`s (or `4096 / 4`) means we're always moving to the next block of memory.

### Array Size (`N`)

- **Goal**: We want to make sure we're using more memory blocks than our quick lookup can handle, to ensure it can't keep up.
- **How**: We use 65 blocks of memory because our TLB can only keep track of 64. This way, we're always one step ahead, causing a miss.

## Conclusion

- **For a single loop**: We set `M` to 1024 so every jump is to a new memory block, and `N` to `65 * 1024` to ensure we use more blocks than the TLB can track.
- **If we repeat the loop**: The computer might try to catch up by remembering some of our steps (caching), which could make our plan to always cause a TLB miss less effective over time. But initially, we're making the computer work harder to find each piece of data.


# Research Question b: Program Fit and Page Size

### The program's requirement is broken down into three segments:

- **Text Segment**: This is where our program's executable code resides, requiring 32,768 bytes.
- **Data Segment**: It holds global and static variables, amounting to 16,386 bytes.
- **Stack Segment**: Utilized for local variables and function calls, it needs 15,870 bytes.


### Code:
```c
#include <stdio.h>

#define TEXT_SIZE 32768   // Text segment size in bytes
#define DATA_SIZE 16386   // Data segment size in bytes
#define STACK_SIZE 15870  // Stack segment size in bytes
#define PAGE_SIZE_4KB 4096    // 4KB page size in bytes
#define PAGE_SIZE_512B 512    // 512B page size in bytes

// A function to figure out how many pages each segment will need
void calculate_pages(int page_size, const char* page_size_name) {
    // Doing some math to divide each segment by the page size
    // If there's any leftover, that means we need an extra page
    int text_pages = TEXT_SIZE / page_size + (TEXT_SIZE % page_size ? 1 : 0);
    int data_pages = DATA_SIZE / page_size + (DATA_SIZE % page_size ? 1 : 0);
    int stack_pages = STACK_SIZE / page_size + (STACK_SIZE % page_size ? 1 : 0);
    int total_pages = text_pages + data_pages + stack_pages;

    // Print out how many pages we need for each part
    printf("Using %s pages, the program needs:\n", page_size_name);
    printf("Text: %d pages, Data: %d pages, Stack: %d pages, Total: %d pages\n\n",
           text_pages, data_pages, stack_pages, total_pages);
}
}

```
### Output

```
owen@linux:~/CST-321/src/Topic4/src$ ./researchb_binary
Program segments: Text=32768 bytes, Data=16386 bytes, Stack=15870 bytes

Using 4KB pages, the program requires:
Text: 8 pages, Data: 5 pages, Stack: 4 pages, Total: 17 pages

Using 512B pages, the program requires:
Text: 64 pages, Data: 33 pages, Stack: 31 pages, Total: 128 pages



```
## Analysis of Page Sizes

- **4KB Pages**: Opting for these larger pages tends to simplify the overall memory management process since fewer pages are needed. This efficiency, however, may introduce internal fragmentation. What this means is that we might end up with allocated memory pages not being fully used, akin to having empty spaces in a mostly filled storage box.

- **512B Pages**: On the flip side, utilizing smaller pages increases the total number required. This granularity allows for a more precise allocation of memory, potentially minimizing wasted space. The downside? It significantly ramps up the management overhead. It's like organizing a large collection of small items individually rather than in bulk - it requires more effort but can result in neater organization.

## Fitting Within the Address Space

The code's output provides clear insights into whether our program can fit within the system's address space:

- **For 4KB Pages**: The program requires a total of 17 pages. In the grand scheme of modern computing systems, this is relatively modest, suggesting that the program should comfortably fit within the typical address spaces provided by most systems today.

- **For 512B Pages**: Here, the program precisely fits into an address space of 65,536 bytes, using up every available bit of space with no room to spare. This scenario underscores a tight but exact allocation, showcasing the precision possible with smaller pages but also highlighting the lack of flexibility.

## Key Takeaways

When we're faced with the decision between using 4KB and 512B pages, we're essentially balancing between two ends of a spectrum: allocation efficiency and management overhead. Larger pages make our lives easier by simplifying memory management but can lead to less efficient use of space. Otherwise, smaller pages can maximize our use of the available address space but at the cost of increased complexity in memory management.

Understanding how to navigate this balance is important for any software developer looking to optimize memory usage. It's an example of the trade-offs that we often have to consider in software development, demonstrating that the best choice often depends on the specific requirements and constraints of the project at hand.

# Resources
Black-Shaffer, D. (2024). Virtual Memory: 11 TLB Example. Youtube. https://www.youtube.com/watch?v=95QpHJX55bM

Programiz. (2024). Bitwise Operators in C.https://www.programiz.com/c-programming/bitwise-operators

Reha, M. , (2024). Activity 4 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473096

Reha, M. (2024). Topic 4 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472997

Ryan's Tutorials. (2024). Binary Tutorial - Binary Conversions. https://ryanstutorials.net/binary-tutorial/binary-conversions.php
