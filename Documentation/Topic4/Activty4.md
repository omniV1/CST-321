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
| `printf()`              | Outputs formatted data to stdout, used for prompting the user and displaying results.         |
| `scanf()`               | Reads formatted input from stdin, used to get the user's number.                             |
| `convertPrintBinary()`  | Orchestrates the conversion of a decimal number to binary and then prints it.                |
| `decimalToBinary()`     | Performs the actual conversion from decimal to binary.                                        |
| `printBinary()`         | Handles the printing of the binary array in a human-readable format.                          |
| `clearBinaryBits()`     | Resets the binary array to all zeros to prepare for a new conversion.                         |

## Detailed Descriptions:

- `printf()`: This standard output function is crucial for interacting with the user. It provides feedback and results, making the program's operations transparent and understandable. Whether it's prompting the user for input or displaying the final output in various formats, `printf()` ensures that information is communicated effectively.

- `scanf()`: Serving as the primary means of receiving input from the user, `scanf()` is essential for capturing the number that will undergo conversion and manipulation. It ensures that the program can process user-specific data, making the operations dynamic and interactive.

- `convertPrintBinary()`: This function is at the heart of the program's binary conversion and display process. It coordinates several steps: clearing any previous binary representation, converting the new decimal input to binary, and then displaying this binary data. By encapsulating these operations, it simplifies the main program flow and emphasizes modularity.

- `decimalToBinary()`: The core algorithm for converting decimal numbers to binary is encapsulated within this function. It iteratively divides the decimal number, capturing the remainder as binary digits, and stores them in an array. This methodical approach ensures accurate conversion from decimal to binary representation.

- `printBinary()`: Focused on output, this function takes the binary data stored in an array and prints it from the most significant bit to the least significant bit. This reverse-order printing is crucial for presenting the binary data in a format that's intuitive for humans to read, aligning with conventional binary notation.

- `clearBinaryBits()`: Before each conversion process, it's essential to reset the binary representation to ensure no residual data from previous operations affects the current calculation. This function zeroes out the binary array, preparing it for a fresh conversion and ensuring the program's output remains accurate and reliable for each user input.

These functions work together to create a user-friendly program that converts decimal numbers to binary, displaying them alongside their hexadecimal representation and demonstrating basic bitwise operations. Through clear separation of concerns and encapsulation of specific tasks, the program remains modular, maintainable, and easy to understand.
