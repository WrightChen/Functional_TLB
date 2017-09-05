#ifndef _FUNCTION_TLB_H_
#define _FUNCTION_TLB_H_

#define CORE_NUM 8

#include <iostream>
#include <stdint.h>
#include <assert.h>

#include "L1ITLB.h"
#include "L1DTLB.h"
#include "L2TLB.h"

class FunTLB
{
	public:
		FunTLB(unsigned int core_num);
		~FunTLB();

		void Load(unsigned int l1_id, uint64_t addr, PageType type);
		void Statistics();
		
	private:
		L1ITLB*					m_l1i_ptr[CORE_NUM];
		L1DTLB*					m_l1d_ptr[CORE_NUM];
		L2TLB*					m_l2_ptr[CORE_NUM];
		unsigned int 				core_num;

};

#endif
