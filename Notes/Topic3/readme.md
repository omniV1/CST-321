# Topic 3 Coding and Discussion on using Pointers in C


### What does the & Operator do in C?

- Known as the **address-of Operator**.

- When used **in-front** of a variable, you're telling the program to use the **memory address of the variable** instead of its value.

### What does the %x in printf specify?

- the argument is an **unsigned hexadecimal integer**.

- it converts the **numerical value** of the variable to its **equivalent hexadecimal representation**.

- It is used in examples involving **memory** because memory addresses are typically **represented as hexadecimal**.

- **Fun Fact**: you can use the _Scientific or Programmer mode_ in the Windows Calculator application to convert between hexadecimal and decimal. Just select the _Programmer' view_, input your hexadecimal value, and the calculator will display the decimal equivalent.

**Code example:**
```c
int main() {
    int var1;
    var1 = 0;

    printf("The size of int var1: %lu", sizeof(var1));
    printf("Address of var1 variable: %p\n", &var1);
    printf("Number of var1 variable: %x\n", var1);
    printf("Number of var1 variable: %X\n", var1);

    return 0;
}

```
**Output:**

```plaintext
Size = sizeof var1 = 4
Address = &var1 = 0x7ffee25c8b58
Number of var1 variable: 0
Number of var1 variable: 0
```
### Theory of operations for the above code:

| Concept               | Description                                                                                      |
|-----------------------|--------------------------------------------------------------------------------------------------|
| `sizeof()` Method     | Returns the size of a variable or type in bytes. For a C compiler, `int` is typically 4 bytes.   |
| `64-bit Operating System` | Can address more memory compared to 32-bit systems using 64-bit addresses.                    |
| `Data Bus Width`        | Modern Intel processors have a 64-bit (8 bytes) wide data bus.                                   |
| `sizeof(var1)`        | Would return the size of an `int` type, typically 4 bytes.                                       |
| `sizeof(&var1)`       | Would return the size of a pointer, typically 8 bytes on a 64-bit system.                        |

### What are Pointers?
- Pointers are **variables** that store **memory addresses**.

### How to Use Pointers?
- Pointers can be used to **access and manipulate data** stored in memory addresses which they point to.

### NULL Pointers
-**NULL pointer** is a pointer that does not point to any valid memory address.

### Code Example:

```c
#include <stdio.h>

int main() {
    int var; // actual variable declaration
    int *ip; // pointer variable declaration

    var = 20; // actual variable initialization
    ip = &var; // store address of var in pointer variable

    printf("Address of var variable: %p\n", ip);
    printf("Address stored in pointer variable: %p\n", ip);
    printf("Access the value using the pointer: %d\n", *ip);
    printf("Value of *ip variable: %d\n", *ip);

    return 0;
}
```
**Output**:
```plaintext
Address of var variable: 0x7ffee25cb858
Address stored in pointer variable: 0x7ffee25cb858
Access the value using the pointer: 20
Value of *ip variable: 20
```
## Discussion of code above

### Why did the address of the var variable and the ip variable end up being the same address?

- The ip variable was declared as a pointer to an int and assigned the address of var, hence they share the same address.

### Does the ip variable "point" to the same var variable and its value?

- Yes, ip points to the address of var, and using the dereference operator *, ip can access and provide the value stored in var.

### Incrementing a Pointer Example

**Code Example:**

```c
#include <stdio.h>

const int MAX = 3;

int main() {
    int var[] = {10, 100, 200};
    int i, *ptr;

    /* let us have array address in pointer */
    ptr = var;
    for (i = 0; i < MAX; i++) {
        printf("Address of var[%d] = %p\n", i, ptr);
        printf("Value of var[%d] = %d\n", i, *ptr);

        /* move to the next location */
        ptr++;
    }
    return 0;
}
```
