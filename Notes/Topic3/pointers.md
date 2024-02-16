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

```plain text
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
```plain text
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
**Output:**
```plain text
Address of var[0] = [address]
Value of var[0] = 10
Address of var[1] = [address + 4 bytes]
Value of var[1] = 100
Address of var[2] = [address + 8 bytes]
Value of var[2] = 200
```
### Theory of operations
| Code Expression | Description |
|-----------------|-------------|
| `ptr = var` | Initializes the pointer `ptr` to point to the first element of the array `var`. |
| `*ptr` | Dereferences the pointer `ptr`, accessing the value at the address it points to. |
| `ptr++` | Increments the pointer by the size of the data type it points to, which is typically 4 bytes for an `int` on many systems, hence moving to the next array element. |
| `Gap between array elements` | There is a 4-byte (32-bits) gap between the array elements because the size of an `int` in this example is 4 bytes, and array elements are stored contiguously in memory. |

### Decrementing a Pointer

**Code example:**


```c
#include <stdio.h>
#define MAX 5

int main() {
    int var[MAX] = {10, 20, 30, 40, 50};
    int* ptr;

    // Set ptr to point to the last element of var
    ptr = &var[MAX-1];
    printf("Initial address of ptr: %p\n", ptr);

    // Decrement ptr and print the address
    ptr--;
    printf("Address after ptr--: %p\n", ptr);

    // Decrement ptr and print the address again
    ptr--;
    printf("Address after another ptr--: %p\n", ptr);

    return 0;
}
```
**Output:**
```plain text
Initial address of ptr: 0x7ffde9a9d870
Address after ptr--: 0x7ffde9a9d86c
Address after another ptr--: 0x7ffde9a9d868
```
### Theory of Operations
| Operation | Explanation |
|-----------|-------------|
| `ptr = &var[MAX-1]` | Sets the pointer `ptr` to point to the last element of the array `var`. |
| `ptr--` | Decrements the pointer, moving it to the previous element in the array. |
| Address decrement | The printed addresses decrease because the pointer moves backwards through the array. |

### Passing Pointers to Functions
```c
#include <stdio.h>
#include <time.h>

void getSeconds(unsigned long *par);

int main() {
    unsigned long sec;
    getSeconds(&sec);
    printf("Number of seconds: %lu\n", sec);
    return 0;
}

void getSeconds(unsigned long *par) {
    /* get the current number of seconds */
    *par = time(NULL);
    return;
}
```
**Output:**
``` Plain text
Number of seconds: 1615823342
```
### Theory of Operations

| Concept          | Description |
|------------------|-------------|
| `unsigned long *par` | A pointer parameter in `getSeconds()` allowing the function to modify the value of the variable passed by the caller. |
| `*par` statement | Dereferences the pointer `par` to access or modify the value of the variable it points to. In the `getSeconds()` function, it sets this variable to the current number of seconds. |

### Code Updates

- Initialize the sec variable to 0.

- Print the value of sec to console in main() before the call to getSeconds().

- Print the value of par to the console in getSeconds() before the call to time().

**code example:**
```c
#include <stdio.h>
#include <time.h>

void getSeconds(unsigned long *par);

int main() {
    unsigned long sec;
    getSeconds(&sec);
    printf("Number of seconds: %lu\n", sec);
    return 0;
}

void getSeconds(unsigned long *par) {
    /* get the current number of seconds */
    *par = time(NULL);
    return;
}

void getSeconds(unsigned long *par) {
printf("The value of par is : %d/n", *par);

// get the current number of seconds
*par = time( NULL );
return;
}
```
**Output:**
```Plain text
The value of seconds before is : 0
The value of par is :
Number of seconds: 1163151651

```

### Theory of Operations
| Code Statement                | Description                                                  |
| ----------------------------- | ------------------------------------------------------------ |
| `unsigned long *par` in `getSeconds` | A pointer parameter allowing the function to modify the value of the variable passed by the caller. |
| `*par = time(NULL)`          | Sets the value at the memory location pointed to by `par` to the current number of seconds. |
| `printf` in `getSeconds`     | Potentially prints an uninitialized value of `par` before it's set, which might be 0. |
| `printf` in `main`           | Prints the updated value of `sec` as the number of seconds since the Unix epoch. |
