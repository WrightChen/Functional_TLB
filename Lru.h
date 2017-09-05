#ifndef _LRU_H_
#define _LRU_H_

#include <stdint.h>
#include <iostream>

struct Lru
{
    public:
        void updlru4(bool m_lru[], uint8_t m_loc);
        void updlru6(bool m_lru[], uint8_t m_loc);
        void updlru16(bool m_lru[], uint8_t m_loc);

        uint8_t getlru4(bool m_lru[]);
        uint8_t getlru6(bool m_lru[]);
        uint8_t getlru16(bool m_lru[]);
};

#endif