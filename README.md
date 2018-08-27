# kittyfault

Replace your SIGSEGV handler with a cute little kitty cat. Unofficial fork from [dogfault](https://notabug.org/VictorSCushman/dogfault/src/master).

Tired of seeing the vanilla `Segmentation fault (core dumped)` message? Simply drop [kittyfault.h](https://github.com/enioluwa23/kittyfault/blob/master/kittyfault.h) into your program's folder and include it. You will be met with an adorable little feline delivering the otherwise morbid news.

## Usage

Load `kittyfault.h` as an installed library and compile with the `-I.` flag or `-I<kittyfault-directory-path>`.

To enable stack trace detection (*Nix only), programs compiled against a specific ANSI C standard must specify the POSIX standard using `-D_POSIX_C_SOURCE=199309L` (199309 or greater) or by compiling with `--std=<gnu std version>` instead of `--std=<std version>`.

Furthermore, to enable function name detection *Nix environments must compile with the `-rdynamic` flag.

Otherwise, this header is compatible with both `WIN32` (MinGW, etc) and *Nix environments.

Compatible with both `gcc` and `clang`.

## Example

```c
/* example.c */
#include <kittyfault.h>

void foo();
void bar();

int main()
{
    foo();

    puts("I shouldn't be printed\n");
    return EXIT_SUCCESS;
}

void foo()
{
    bar();
    puts("I shouldn't be printed either\n");
}

void bar()
{
    const char *s = NULL;
    printf("%c\n", s[0]); // standard segfault
}
```

### POSIX Output

```text
$ gcc example.c -I. -rdynamic
$ ./a.out
           A___A
     ____ / o o \ *meow*
___/~____   ='= / Segmentation fault at address (nil)
  (______)__m_m_) Stack trace is below. *purr*
----------------------------------------------------------
./a.out() [0x400b7c]
/lib/x86_64-linux-gnu/libc.so.6(+0x354b0) [0x7fdc2c2654b0]
./a.out(bar+0x14) [0x400d09]
./a.out(foo+0xe) [0x400ce8]
./a.out(main+0xe) [0x400cc9]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0) [0x7fdc2c250830]
./a.out(_start+0x29) [0x400a49]
```

### WIN32 Output

```text
> gcc -g example.c -I.
> a.exe
           A___A
     ____ / o o \ *meow*
___/~____   ='= / Segmentation fault caught!
  (______)__m_m_) Run with a debugger to find the cause. *purr*
---------------------------------------------------------------
```

## License

[MIT](https://github.com/enioluwa23/kittyfault/blob/master/LICENSE)