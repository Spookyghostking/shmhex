#ifndef __SHMHEX_H_
#define __SHMHEX_H_
#include<assert.h>
#include<stdint.h>

typedef uint8_t uint8;


void shmhex_shmhexify_byte(char* buffer, size_t buffer_size, uint8 data) {
    assert(buffer_size >= 3);
    buffer[2] = 0;
    uint8 lo_bit = data & 0x0f;
    uint8 ho_bit = (data & 0xf0) >> 4;
    char c0;
    char c1;
    if (lo_bit < 10) {
        c1 = lo_bit + 48;
    } else if (lo_bit >= 10) {
        c1 = lo_bit + 97 - 10;
    }
    if (ho_bit < 10) {
        c0 = ho_bit + 48;
    } else if (ho_bit >= 10) {
        c0 = ho_bit + 97 - 10;
    }
    buffer[0] = c0;
    buffer[1] = c1;
}

void shmhex_shmhexify_address(char* buffer, size_t buffer_size, void* address) {
    size_t address_length = sizeof(address);
    assert(buffer_size >= (address_length * 2) + 1);

    for (size_t bi = 0; bi < address_length; bi++) {
        char* buffer_ptr = buffer + (bi * 2);
        size_t di = address_length - bi - 1;
        uint8* data = (uint8*)&address + di;
        shmhex_shmhexify_byte(buffer_ptr, buffer_size - (bi * 2), *data);
    }
    buffer[address_length * 2] = 0;
}

void shmhex_memcpy(void* dest, void* src, size_t size) {
    uint8* dest_p = (uint8*)dest;
    uint8* src_p = (uint8*)src;
    while (size > 0) {
        dest_p[size - 1] = src_p[size - 1];
        size--;
    }
}

size_t shmhex_strlen(char* string) {
    size_t len = 0;
    while (string[len] != 0)
        len += 1;
    return len;
}

void shmhex_shmhexdump(char* buffer, size_t buffer_size, uint8* ptr, size_t size) {
    char* cursor = buffer;

    char* begin = "Hexdump at memory address 0x";
    size_t begin_len = shmhex_strlen(begin);
    char* intermission = ":\n";
    size_t intermission_len = shmhex_strlen(intermission);

    size_t output_size = begin_len + intermission_len + sizeof(ptr) * 2 + size * 3 + 2;
    assert(buffer_size >= output_size);

    shmhex_memcpy(cursor, begin, begin_len);
    cursor += begin_len;

    shmhex_shmhexify_address(cursor, buffer_size - (buffer - cursor), ptr);
    cursor += sizeof(ptr) * 2;

    shmhex_memcpy(cursor, intermission, intermission_len);
    cursor += intermission_len;

    for (size_t i = 0; i < size; i++) {
        shmhex_shmhexify_byte(cursor, buffer_size - (buffer - cursor), ptr[i]);
        cursor[2] = ' ';
        cursor += 3;
    }
    assert(buffer_size - (buffer - cursor) > 1);
    cursor[0] = '\n';
    cursor[1] = 0;
}
#endif // __SHMHEX_H_
