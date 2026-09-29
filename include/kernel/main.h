#ifndef DUSK_KERNEL_MAIN_H
#define DUSK_KERNEL_MAIN_H

__attribute__((noreturn))
void kernel_main(void);

__attribute__((noreturn))
void kernel_panic(const char* msg);

#endif
