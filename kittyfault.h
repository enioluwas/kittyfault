#ifndef __KITTY_FAULT__
#define __KITTY_FAULT__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#ifdef __linux__
#include <execinfo.h>
#endif

#ifdef __linux__
#define KIITY_FORMAT_POSIX \
"           A___A\n\
     ____ / o o \\ *meow*\n\
___/~____   ='= / Segmentation fault at address %p\n\
  (______)__m_m_) Stack trace is below. *purr*\n\
----------------------------------------------------------\n"
#define MAX_BACKTRACE 2048

#elif _WIN32
#define KIITY_FORMAT_WIN \
"           A___A\n\
     ____ / o o \\ *meow*\n\
___/~____   ='= / Segmentation fault caught!\n\
  (______)__m_m_) Run with a debugger to find the cause. *purr*\n\
---------------------------------------------------------------\n"
#endif 

#ifdef _WIN32
static void kittyfault_handler_win(int sig)
{
    fputs(KIITY_FORMAT_WIN, stderr);
    _Exit(EXIT_FAILURE);
}

#elif __linux__
static void kittyfault_handler_posix(int sig, siginfo_t* si, void* args)
{
    fprintf(stderr, KIITY_FORMAT_POSIX, si->si_addr);

    void* backtrace_buff[MAX_BACKTRACE];
    int nframes = backtrace(backtrace_buff, MAX_BACKTRACE);
    char** symbols = backtrace_symbols(backtrace_buff, nframes);
    if (!symbols)
    {
        fprintf(stderr, "kittyfault error: failed to aquire backtrace symbols\n");
        _Exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nframes; ++i)
    {
        fprintf(stderr, "%s\n", symbols[i]);
    }

    _Exit(EXIT_FAILURE);
}
#endif

__attribute__((constructor))
static void kitty_init()
{
    #ifdef _WIN32
    signal(SIGSEGV, kittyfault_handler_win);
    #elif __linux__
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = kittyfault_handler_posix;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
    #endif
}

#endif /*__KITTY_FAULT__*/