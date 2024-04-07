#include <stdio.h>

#define TEXT_SIZE 32768   // Text segment size in bytes
#define DATA_SIZE 16386   // Data segment size in bytes
#define STACK_SIZE 15870  // Stack segment size in bytes
#define PAGE_SIZE_4KB 4096    // 4KB page size in bytes
#define PAGE_SIZE_512B 512    // 512B page size in bytes

void calculate_pages(int page_size, const char* page_size_name) {
    int text_pages = TEXT_SIZE / page_size + (TEXT_SIZE % page_size ? 1 : 0);
    int data_pages = DATA_SIZE / page_size + (DATA_SIZE % page_size ? 1 : 0);
    int stack_pages = STACK_SIZE / page_size + (STACK_SIZE % page_size ? 1 : 0);
    int total_pages = text_pages + data_pages + stack_pages;

    printf("Using %s pages, the program requires:\n", page_size_name);
    printf("Text: %d pages, Data: %d pages, Stack: %d pages, Total: %d pages\n\n",
           text_pages, data_pages, stack_pages, total_pages);
}

int main() {
    printf("Program segments: Text=%d bytes, Data=%d bytes, Stack=%d bytes\n\n", TEXT_SIZE, DATA_SIZE, STACK_SIZE);

    // Calculate and display the number of pages required for 4KB page size
    calculate_pages(PAGE_SIZE_4KB, "4KB");

    // Calculate and display the number of pages required for 512B page size
    calculate_pages(PAGE_SIZE_512B, "512B");

    return 0;
}
