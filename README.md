# Simple Helper Memory Hexdump (shmhex)
I've had it with the gdb debugger! Using it is too cumbersome and slow. From now on I will simply hexdump everything when I need to debug my code. To that end, I have created this simple tool for hexduming memory directly from within an application.

### ???:
The code in this repository (obviously) comes with no guarantee of it's quality, usefulness, or a guarantee of any other kind. Use at your own peril.

### How to use:
Firstly: the function definitions are contained in the header file, so I recommend against including this in any public-facing code.
I am not a security expert and am not certain about the security implications of doing something like this, but I believe it makes certain kinds of attacks a whole lot easier.
It's a debug tool so it's not meant for that kind of thing anyway. You should do something along the lines of:

     #ifdef DEBUG
     #include "shmhex.h"
     #endif

The primary use-case is covered by the `shmhex_shmhexdump` function. The function declaration looks like this:

     void shmhex_shmhexdump(char* buffer, size_t buffer_size, uint8* ptr, size_t size);

buffer - buffer where the output will be written

Note: the when the buffer is filled, a null charracter is appended at the end,
making the output is a valid null terminated string.

buffer_size - (in bytes) pretty self-explanatory

ptr - pointer to the memory which you want to dump

size - size (in bytes) of the memory dumpy

Once the buffer is filled with the dump, you can pass it to the appropriate logging funcion, or render it to the screen, or whatever.

The output comes in the format:

     Hexdump at memory address 0x[address]: (\n)
     bb bb bb bb bb bb bb ... (\n)(\0)

With bb being the hexadecimal representation of each byte.

The repo comes with two more useful functions: `shmhex_shmexify_byte` and
`shmhex_shmhexify_address`. These functions convert their respective inputs to
a hexadecimal representation.

     void shmhex_shmexify_byte(char* buffer, buffer_size, uint8 data);
     void shmhex_shmhexify_address(char* buffer, size_t buffer_size, void* address);

Both functions dump the result into their respective buffer, the byte function needing
a buffer of at least 3 bytes, and the address function needing 17 in 64-bit architecture
(two for each byte, and one for the null terminator).

Note: neither function puts a 0x in front of their output.

Mmm shmhexy
