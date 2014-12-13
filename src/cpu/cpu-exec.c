#include "nemu.h"

#include "ui/ui.h"
#include "ui/breakpoint.h"
#include "ui/watchpoint.h"

#include <setjmp.h>

// The start address of 'loader' is at 0x100000
// The start address of 'user program' is at 0x800000
#define LOADER_START 0x100000
extern uint8_t loader [];
extern uint32_t loader_len;
void load_prog();
void init_dram();
void init_cache();
void init_cache_L2();
void restart() 
{
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;
	cpu.ebp = 0x00000000;
	cpu.esp = 0x08000000;
	cpu.eflags = 0x00000002;

	cpu.CR0_PE = 0;

	init_dram();
	init_cache();
	init_cache_L2();
}



jmp_buf jbuf;	/* Make it easy to perform exception handling */
extern int quiet;

int exec(swaddr_t);

char assembly[40];
static void print_bin_instr(swaddr_t, int);

void cpu_exec(volatile uint32_t n) 
{
	volatile uint32_t n_temp = n;

	setjmp(jbuf);
	for(; n > 0; --n) 
  	{
		swaddr_t eip_temp = cpu.eip;
if (cpu.eip == 0x10000d) assert(0);
		int instr_len = exec(cpu.eip);
 	 	if(n_temp != -1 || (enable_debug && !quiet)) 
		{
			// print the instruction executed
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		} 
		cpu.eip += instr_len;

		switch (bp_state) 
		{
			case OFF: 
				break;

			case TRIG:
				--cpu.eip;
				uint8_t instr = search_bp(cpu.eip);
				swaddr_write(cpu.eip, 1, instr);
	     		printf("Breakpoint at 0x%08X\n", cpu.eip);
		
				bp_state = RESET;
						
				return; 

			case RESET:
				swaddr_write(eip_temp, 1, INT3_CODE);
				bp_state = OFF;
				break;
		} 
			
		if (WP_STATE) 
		{ 
			bool changed = test_wp();
			if (changed) { nemu_state = STOP; return; }
		}

		switch(nemu_state)
		{
			case END:
				return;

			case RUNNING:
				if (n == 1)  { nemu_state = STOP;  return;  }
		}
	}
}

static void print_bin_instr(swaddr_t eip, int len) 
{
	printf("  0x%.8x:   ", eip);

	int i;
	for(i = 0; i < len; i ++) 
		printf("%02x ", swaddr_read(eip + i, 1));

	printf("%*.s", 50 - (12 + 3 * len), "");
}
