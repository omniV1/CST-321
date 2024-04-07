/**Owen Lindsey
 * CST-321
 * 3/03/2024
 * This code was done with the help of:
 *
 * Black-Shaffer, D. (2024). Virtual Memory: 11 TLB Example. Youtube. https://www.youtube.com/watch?v=95QpHJX55bM
 *
 * Programiz. (2024). Bitwise Operators in C.https://www.programiz.com/c-programming/bitwise-operators
 *
 * Reha, M. , (2024). Activity 4 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473096
 *
 * Reha, M. (2024). Topic 4 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472997
 *
 * Ryan's Tutorials. (2024). Binary Tutorial - Binary Conversions. https://ryanstutorials.net/binary-tutorial/binary-conversions.php
*/

#include <stdio.h>
#include <stdbool.h>

void printBinary(char* bits);
void clearBinaryBits(char* bits);
void convertPrintBinary(int number, char* bits);
void decimalToBinary(int number, char* bits);

int main() {
    int number;
    char bits[33] = { // LSB at index 0 and MSB at index 31
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
