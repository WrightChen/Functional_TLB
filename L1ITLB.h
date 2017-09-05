#ifndef _L1ITLB_H_
#define _L1ITLB_H_

#include <iostream>
#include <array>
#include "TLBEntry.h"
#include "Lru.h"

#include "L2TLB.h"

using namespace std;

class L1ITLB
{
    public:
        L1ITLB(unsigned int id);
        void Load(uint64_t addr, PageType type);


        void SetL2Ptr(L2TLB* l2_ptr){
            m_l2_ptr = l2_ptr;
        }

        void Statistics(){

            if(m_k_counter != 0)
            cout << "[L1_" << m_id << "][Statistics]" << endl 
                 << "[4K][Total] " << dec << m_k_counter << endl
                 << "[4K][Hit] " << dec << m_k_hit << endl
                 << "[4K][Hit Rate] " << double(m_k_hit) / double(m_k_counter) * 100 << "%" << endl
                 << endl;
                
            if(m_2m_counter != 0)
            cout << "[L1_" << m_id << "][Statistics]" << endl 
                 << "[2M][Total] " << dec << m_2m_counter << endl
                 << "[2M][Hit] " << dec << m_2m_hit << endl
                 << "[2M][Hit Rate] " << double(m_2m_hit) / double(m_2m_counter) * 100 << "%" << endl
                 << endl;
            
            if(m_4m_counter != 0)
            cout << "[L1_" << m_id << "][Statistics]" << endl 
                 << "[4M][Total] " << dec << m_4m_counter << endl
                 << "[4M][Hit] " << dec << m_4m_hit << endl
                 << "[4M][Hit Rate] " << double(m_4m_hit) / double(m_4m_counter) * 100 << "%" << endl
                 << endl;

            if(m_g_counter != 0)
            cout << "[L1_" << m_id << "][Statistics]" << endl 
                 << "[1G][Total] " << dec << m_g_counter << endl
                 << "[1G][Hit] " << dec << m_g_hit << endl
                 << "[1G][Hit Rate] " << double(m_g_hit) / double(m_g_counter) * 100 << "%" << endl
                 << endl;
        }


    private:
		unsigned int						m_id;

        unsigned int                        m_k_counter;
        unsigned int                        m_k_hit;
        unsigned int                        m_2m_counter;
        unsigned int                        m_2m_hit;
        unsigned int                        m_4m_counter;
        unsigned int                        m_4m_hit;
        unsigned int                        m_g_counter;
        unsigned int                        m_g_hit;

        array<IKEntry, 16>                  m_l1ik;
        array<MEntry, 8>                    m_l1m;
        array<uint64_t, 4>                  m_l1g;

        Lru                                 m_lru;
        L2TLB*                              m_l2_ptr;

};

#endif