#include "L2TLB.h"


L2TLB::L2TLB(unsigned int id)
: m_id(id)
, m_load_counter(0)
, m_load_hit(0)
{
    
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

bool 
L2TLB::Load(uint64_t addr)
{
    unsigned int t_num, t_loc;
    uint64_t t_tag;

    ++m_load_counter;

    cout << "[L2][Load] " << "Address = " << addr << endl;

    t_tag = addr >> 17;
    t_num = (addr & L2_OFFSET) >> 12;
    
    cout << "[L2][Load] " << "Set_num = " << t_num << endl;

    if(m_l2[t_num].way.find(t_tag) != m_l2[t_num].way.end()){
        ++m_load_hit;

        t_loc = m_l2[t_num].way[t_tag];
        m_l2[t_num].way.erase(t_tag);
        m_l2[t_num].lrurec[t_loc] = 0;
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

void 
L2TLB::Store(uint64_t addr)
{
    unsigned int t_num, t_loc, i;
    uint64_t t_tag, t_addr, t_evict; 
    t_loc = 0xffff;

    cout << "[L2][Store] " << "Address = " << addr << endl;

    t_tag = addr >> 17;
    t_num = (addr & L2_OFFSET) >> 12;
    
    cout << "[L2][Store] " << "Set_num = " << t_num << endl;

    if(m_l2[t_num].way.find(t_tag) == m_l2[t_num].way.end()){
        if(m_l2[t_num].way.size() < 16){
            for(i = 0; i < 16; ++i)
                if(m_l2[t_num].lrurec[i] == 0){
                    t_loc = i;
                    break;
                }
            
            m_lru.updlru16(m_l2[t_num].lru, t_loc);
            m_l2[t_num].way.insert({t_tag, t_loc});
            m_l2[t_num].lrurec[t_loc] = addr;

        }
        else{
            t_loc = m_lru.getlru16(m_l2[t_num].lru);
            t_addr = m_l2[t_num].lrurec[t_loc];
            t_evict = t_addr >> 17;

            m_l2[t_num].way.erase(t_evict);
            m_l2[t_num].way.insert({t_tag, t_loc});
            m_l2[t_num].lrurec[t_loc] = addr;

        }
    }
    else{
        cout << "L1TLB Data shouldn't exist in L2TLB." << endl;
    }
}
