#include "FunTLB.h"

FunTLB::FunTLB(unsigned int core_num)
: core_num(core_num)
{

	for(unsigned int i = 0; i < core_num; i++)
	{
		m_l1i_ptr[i] = new L1ITLB(2*i);
		m_l1d_ptr[i] = new L1DTLB(2*i+1);
		m_l2_ptr[i] = new L2TLB(i);

		m_l1i_ptr[i]->SetL2Ptr(m_l2_ptr[i]);
		m_l1d_ptr[i]->SetL2Ptr(m_l2_ptr[i]);
	}

}

FunTLB::~FunTLB()
{
	for(unsigned int i = 0; i < core_num; i++)
	{
		delete m_l1i_ptr[i];
		delete m_l1d_ptr[i];
		delete m_l2_ptr[i];
	}
}

void
FunTLB::Load(unsigned int l1_id, uint64_t addr,  PageType type)
{
	addr = addr >> 6 << 6;

	if(l1_id%2 == 0)
	{
		m_l1i_ptr[l1_id/2]->Load(addr, type);
	}
	else
	{
		m_l1d_ptr[l1_id/2]->Load(addr, type);
	}
}

void
FunTLB::Statistics()
{
	for(unsigned int i = 0; i < core_num; i++)
	{
		m_l1i_ptr[i]->Statistics();
		m_l1d_ptr[i]->Statistics();
		m_l2_ptr[i]->Statistics();
	}
}
