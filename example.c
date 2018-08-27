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