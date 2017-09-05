#include "FunTLB.h"

int main()
{
    FunTLB m_tlb(8);

    m_tlb.Load(0, 0x111111, K);std::cout << std::endl;
    m_tlb.Load(1, 0x111111, K);std::cout << std::endl;
    m_tlb.Load(0, 0x111111111, M2);std::cout << std::endl;
    m_tlb.Load(1, 0x111111111, M2);std::cout << std::endl;
    m_tlb.Load(0, 0x111112222, M4);std::cout << std::endl;
    m_tlb.Load(1, 0x111112222, M4);std::cout << std::endl;
    m_tlb.Load(0, 0x1111111111, G);std::cout << std::endl;
    m_tlb.Load(1, 0x1111111111, G);std::cout << std::endl;

    m_tlb.Statistics();


    return 0;
}