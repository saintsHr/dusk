#include "dusk/interrupts/isr.h"
#include "dusk/kernel.h"

#include <stdint.h>

void isr_handler(struct isr_registers* regs) {
	if (regs->exception >= 32) return;

	switch (regs->exception) {
    	case 0:  kpanic("[Exception] Divide Error."); 				   break;
		case 1:  kpanic("[Exception] Debug Exception."); 			   break;
		case 2:  kpanic("[Exception] NMI Interrupt."); 				   break;
		case 3:  kpanic("[Exception] Breakpoint."); 				   break;
		case 4:  kpanic("[Exception] Overflow."); 					   break;
		case 5:  kpanic("[Exception] BOUND Range Exceeded."); 		   break;
		case 6:  kpanic("[Exception] Invalid Opcode."); 			   break;
		case 7:  kpanic("[Exception] Device Not Available."); 		   break;
		case 8:  kpanic("[Exception] Double Fault."); 				   break;
		case 9:  kpanic("[Exception] Coprocessor Segment Overrun.");   break;
		case 10: kpanic("[Exception] Invalid TSS."); 				   break;
		case 11: kpanic("[Exception] Segment Not Present."); 		   break;
		case 12: kpanic("[Exception] Stack-Segment Fault."); 		   break;
		case 13: kpanic("[Exception] General Protection."); 		   break;
		case 14: kpanic("[Exception] Page Fault."); 				   break;
		case 15: kpanic("[Exception] Intel Reserved.");                break;
		case 16: kpanic("[Exception] x87 FPU Floating-Point Error.");  break;
		case 17: kpanic("[Exception] Alignment Check.");               break;
		case 18: kpanic("[Exception] Machine Check.");                 break;
		case 19: kpanic("[Exception] SIMD Floating-Point Exception."); break;
		case 20: kpanic("[Exception] Virtualization Exception.");      break;
		case 21: kpanic("[Exception] Control Protection Exception.");  break;

		default: kpanic("[Exception] Unknown."); break;
    }
}