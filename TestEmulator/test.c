#include <stdio.h>
#include <stdlib.h>
#include "i8080.h"

int main() {

    struct i8080 *cpu = malloc(sizeof(struct i8080));

    #define MEMSIZE 244
    cpu->memory = malloc(sizeof(char) * MEMSIZE);
    cpu->memsize = MEMSIZE;

    i8080_reset(cpu);

    printf("B: %d\n", cpu->B);
    printf("A: %d\n", cpu->A);
    printf("C: %d\n", i8080_get_flag(cpu, FLAG_C));
    printf("AC: %d\n", i8080_get_flag(cpu, FLAG_A));

    i8080_write_byte(cpu, 0, 0x04);
    i8080_write_byte(cpu, 1, 0x80);
    for (int i=2; i<242; i++) {
        i8080_write_byte(cpu, i, 0x04);
    }

    i8080_write_byte(cpu, 242, 0x90);
    i8080_write_byte(cpu, 243, 0x76);
    for (int i=0; i<244; i++) {
        i8080_step(cpu);
    }
    

    printf("B: %d\n", cpu->B);
    printf("A: %d\n", cpu->A);
    printf("C: %d\n", i8080_get_flag(cpu, FLAG_C));
    printf("AC: %d\n", i8080_get_flag(cpu, FLAG_A));


    return 0;
}