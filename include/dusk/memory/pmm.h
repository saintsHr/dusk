#pragma once

#include "dusk/multiboot.h"
#include <stdint.h>

void pmm_init(const struct multiboot_info* mbi);

void* pmm_alloc_page(void);
void pmm_free_page(void* addr);