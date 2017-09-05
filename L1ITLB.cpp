#include "L1ITLB.h"

L1ITLB::L1ITLB(unsigned int id)
: m_id(id)
, m_k_counter(0)
, m_k_hit(0)
, m_2m_counter(0)
, m_2m_hit(0)
, m_4m_counter(0)
, m_4m_hit(0)
, m_g_counter(0)
, m_g_hit(0)
{
    uint8_t i;

    for(i = 0; i < 4; ++i)
        m_l1g[i] = 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/

void 
L1ITLB::Load(uint64_t addr, PageType type)
{
    unsigned int t_num, t_loc, i;
    uint64_t t_tag, t_addr, t_evict;
    t_loc = 0xffff;

    cout << "[L1ITLB][Load] " << "Address = " << addr << endl;

    switch(type){
        case K :
            ++m_k_counter;
            t_tag = addr >> 16;
            t_num = (addr & K_OFFSET) >> 12;

            if(m_l1ik[t_num].way.find(t_tag) == m_l1ik[t_num].way.end()){
                if(m_l1ik[t_num].way.size() < 6){
                    for(i = 0; i < 6; ++i)
                        if(m_l1ik[t_num].lrurec[i] == 0){
                            t_loc = i;
                            break;
                        }
                    
                    m_lru.updlru6(m_l1ik[t_num].lru, t_loc);
                    m_l1ik[t_num].way.insert({t_tag, t_loc});
                    m_l1ik[t_num].lrurec[t_loc] = addr;

                    m_l2_ptr->Load(addr);
                }
                else{
                    t_loc = m_lru.getlru6(m_l1ik[t_num].lru);
                    t_addr = m_l1ik[t_num].lrurec[t_loc];
                    t_evict = t_addr >> 16;

                    m_l1ik[t_num].way.erase(t_evict);
                    m_l1ik[t_num].way.insert({t_tag, t_loc});
                    m_l1ik[t_num].lrurec[t_loc] = addr;

                    m_l2_ptr->Load(addr);
                }
            }
            else{
                ++m_k_hit;
                t_loc = m_l1ik[t_num].way[t_tag];
                m_lru.updlru6(m_l1ik[t_num].lru, t_loc);
            }
            break;
        case M2 :
            ++m_2m_counter;
            t_tag = addr >> 24;
            t_num = (addr & M2_OFFSET) >> 21;

            if(m_l1m[t_num].way.find(t_tag) == m_l1m[t_num].way.end()){
                if(m_l1m[t_num].way.size() < 4){
                    for(i = 0; i < 4; ++i)
                        if(m_l1m[t_num].lrurec[i] == 0){
                            t_loc = i;
                            break;
                        }
                    
                    m_lru.updlru4(m_l1m[t_num].lru, t_loc);
                    m_l1m[t_num].way.insert({t_tag, t_loc});
                    m_l1m[t_num].lrurec[t_loc] = addr;
                }
                else{
                    t_loc = m_lru.getlru4(m_l1m[t_num].lru);
                    t_addr = m_l1m[t_num].lrurec[t_loc];
                    t_evict = t_addr >> 24;

                    m_l1m[t_num].way.erase(t_evict);
                    m_l1m[t_num].way.insert({t_tag, t_loc});
                    m_l1m[t_num].lrurec[t_loc] = addr;
                }
            }
            else{
                ++m_2m_hit;
                t_loc = m_l1m[t_num].way[t_tag];
                m_lru.updlru4(m_l1m[t_num].lru, t_loc);
            }
            break;
        case M4 :
            ++m_4m_counter;
            t_tag = addr >> 25;
            t_num = (addr & M4_OFFSET) >> 22;

            if(m_l1m[t_num].way.find(t_tag) == m_l1m[t_num].way.end()){
                if(m_l1m[t_num].way.size() < 4){
                    for(i = 0; i < 4; ++i)
                        if(m_l1m[t_num].lrurec[i] == 0){
                            t_loc = i;
                            break;
                        }
                    
                    m_lru.updlru4(m_l1m[t_num].lru, t_loc);
                    m_l1m[t_num].way.insert({t_tag, t_loc});
                    m_l1m[t_num].lrurec[t_loc] = addr;
                }
                else{
                    t_loc = m_lru.getlru4(m_l1m[t_num].lru);
                    t_addr = m_l1m[t_num].lrurec[t_loc];
                    t_evict = t_addr >> 25;

                    m_l1m[t_num].way.erase(t_evict);
                    m_l1m[t_num].way.insert({t_tag, t_loc});
                    m_l1m[t_num].lrurec[t_loc] = addr;
                }
            }
            else{
                ++m_4m_hit;
                t_loc = m_l1m[t_num].way[t_tag];
                m_lru.updlru4(m_l1m[t_num].lru, t_loc);
            }
            break;
        case G :
            ++m_g_counter;
            t_tag = addr >> 31;
            t_num = (addr & G_OFFSET) >> 29;

            if(m_l1g[t_num] != t_tag){
                m_l1g[t_num] = t_tag;
            }
            else{
                ++m_g_hit;
            }
            break;
        
        default :
            cout << "Error Page Type!" << endl;
    }
    

}

