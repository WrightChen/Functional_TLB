#ifndef _L2CACHE_H_
#define _L2CACHE_H_

#define L2_SET_NUM 512

#include <iostream>
#include <array>
#include "TLBEntry.h"
#include "Lru.h"

using namespace std;

class L2TLB
{
    public:
        L2TLB(unsigned int id);
        bool Load(uint64_t addr);
        void Store(uint64_t addr);

        void Statistics(){
            
            if(m_load_counter != 0)
            cout << "[L2_" << m_id << "][Statistics]" << endl 
                 << "[Load][Total] " << dec << m_load_counter << endl
                 << "[Load][Hit] " << dec << m_load_hit << endl
                 << "[Load][Hit Rate] " << double(m_load_hit) / double(m_load_counter) * 100 << "%" << endl
                 << endl;
            
        }

    private:
		unsigned int						m_id;

        unsigned int                        m_load_counter;
        unsigned int                        m_load_hit;

        array<L2Entry, 32>                  m_l2;

        Lru                                 m_lru;

};

#endif