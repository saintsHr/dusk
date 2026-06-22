align 8

gdt_start:

; null segment
gdt_null:
	dq 0x0000000000000000

; kernel code segment (ring 0)
gdt_kcode:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00

; kernel data segment (ring 0)
gdt_kdata:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

; user code segment (ring 3)
gdt_ucode:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 11111010b
	db 11001111b
	db 0x00

; user data segment (ring 3)
gdt_udata:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 11110010b
	db 11001111b
	db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start