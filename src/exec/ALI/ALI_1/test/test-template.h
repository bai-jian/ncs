#include "exec/helper.h"

#include "exec/template-start.h"

#include "cpu/modrm.h"
#include "exec/set_eflags/set_eflags.h"

make_helper( concat(test_r2rm_, SUFFIX) )
{
	ModR_M m;  m.val = instr_fetch(eip+1, 1);
	if (m.mod != 3)
	{
		swaddr_t  mem_i;	uint32_t len = read_ModR_M(eip+1, &mem_i);
		DATA_TYPE mem_v = MEM_R(mem_i);
		uint8_t   reg_i = m.reg;
		DATA_TYPE reg_v = REG(reg_i);

		DATA_TYPE value = mem_v & reg_v;

		cpu.CF = cpu.OF = 0;
		concat(set_SF_, SUFFIX) (value);
		concat(set_ZF_, SUFFIX) (value);
		concat(set_PF_, SUFFIX) (value);

		print_asm("test" str(SUFFIX) " %%%s, %s", REG_NAME(reg_i), ModR_M_asm);

		return 1 + len;
	}
	else
	{   
		uint8_t   s_reg_i = m.reg;
		DATA_TYPE s_reg_v = REG(s_reg_i);
		uint8_t   d_reg_i = m.R_M;
		DATA_TYPE d_reg_v = REG(d_reg_i);

		DATA_TYPE value = s_reg_v & d_reg_v;

		cpu.CF = cpu.OF = 0;
		concat(set_SF_, SUFFIX) (value);
		concat(set_ZF_, SUFFIX) (value);
		concat(set_PF_, SUFFIX) (value);

		print_asm("test" str(SUFFIX) " %%%s, %%%s", REG_NAME(s_reg_i), REG_NAME(d_reg_i));
		return 1 + 1;
	}
}

#include "exec/template-end.h"
