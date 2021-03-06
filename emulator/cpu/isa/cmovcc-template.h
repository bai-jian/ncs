#include "template-start.h"
#include "modrm.h"
#include "cpu/reg.h"

make_helper( concat(cmove_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if (cpu.ZF)  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmove"str(SUFFIX)" %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	}
	else
	{
		if (cpu.ZF)  REG(m.reg) = REG(m.R_M);
		print_asm("cmove"str(SUFFIX)" %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}
make_helper( concat(cmovne_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if (!cpu.ZF)  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmovne"str(SUFFIX)"   %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	} 
	else
	{ 
		if (!cpu.ZF)  REG(m.reg) = REG(m.R_M);
		print_asm("cmovne"str(SUFFIX)"   %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}
make_helper( concat(cmovbe_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if ( cpu.CF || cpu.ZF )  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmovbe"str(SUFFIX)"   %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	}
	else
	{
		if ( cpu.CF || cpu.ZF )  REG(m.reg) = REG(m.R_M);
		print_asm("cmovbe"str(SUFFIX)"   %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}
make_helper( concat(cmova_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if ( !cpu.CF && !cpu.ZF)  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmova"str(SUFFIX)" %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	}
	else
	{
		if ( !cpu.CF && !cpu.ZF)  REG(m.reg) = REG(m.R_M);
		print_asm("comva"str(SUFFIX)" %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}
make_helper( concat(cmovs_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if ( cpu.SF )  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmovs"str(SUFFIX)"    %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	}
	else
	{
		if ( cpu.SF )  REG(m.reg) = REG(m.R_M);
		print_asm("cmovs"str(SUFFIX)"    %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}
make_helper( concat(cmovns_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if ( !cpu.SF )  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmovns"str(SUFFIX)"   %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	}
	else
	{
		if ( !cpu.SF )  REG(m.reg) = REG(m.R_M);
		print_asm("cmovns"str(SUFFIX)"   %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}
make_helper( concat(cmovge_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip + 1, 1);
	if (m.mod != 3)
	{
		swaddr_t mem_a;  uint8_t len = read_ModR_M(eip + 1, &mem_a);
		if ( cpu.SF == cpu.OF )  REG(m.reg) = MEM_R(mem_a);
		print_asm("cmovs"str(SUFFIX)" %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return 1 + len;
	}
	else
	{
		if ( cpu.SF == cpu.OF )  REG(m.reg) = REG(m.R_M);
		print_asm("cmovs"str(SUFFIX)" %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1 + 1;
	}
}


#include "template-end.h"
