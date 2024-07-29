#include<stdio.h>

#include "shmhex.h"

void* malloc(size_t size);


int main(void) {
    int array[8] = {0};
    array[0] = 222222;
    array[1] = 0;
    array[2] = (1 << 24) - 1;
    array[3] = 22;
    array[4] = 22;
    array[5] = 22;
    array[6] = 22;
    array[7] = 22;
    char buffer[2048];
    shmhex_shmhexdump(buffer, 2048, (uint8*)array, 8*sizeof(*array));
    printf("%s", buffer);
    return 0;
}
