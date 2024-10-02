// CS354 SP22 Project 4 Sample Tester
// Authored by Ruixuan Tu

#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(114514);
    Mem_Dump();

    char *p[512] = { 0x0 };
    for (int i = 1; i < 463; i++) {
        if ((p[i] = Mem_Alloc(i)) == NULL) {
            printf("Allocation failed\n");
            exit(0);
        }
        if ((long)p[i] % 16 != 0) {
            printf("Allocation not aligned\n");
            exit(0);
        }
        Mem_Dump();
    }
    Mem_Dump();

    for (int i = 463; i < 512; i++) {
        if ((p[i] = Mem_Alloc(i)) != NULL) {
            printf("Allocation success unexpectedly\n");
            exit(0);
        }
        Mem_Dump();
    }
    Mem_Dump();


    for (int i = 462; i >= 1; i--) {
        if (Mem_Free(p[i]) == -1) {
            printf("Free failed\n");
            exit(0);
        }
        Mem_Dump();
    }
    Mem_Dump();

    for (int i = 512; i > 462; i--) {
        if (Mem_Free(p[i]) != -1) {
            printf("Free success unexpectedly\n");
            exit(0);
        }
        Mem_Dump();
    }
    Mem_Dump();

    Free_Memory_Allocator();
    return 0;
}
