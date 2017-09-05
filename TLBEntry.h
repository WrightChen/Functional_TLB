#ifndef _TLBENTRY_H_
#define _TLBENTRY_H_

#include <map>
#include <stdint.h>

#define K_OFFSET            ((1UL<<16)-1)
#define M2_OFFSET           ((1UL<<24)-1)
#define M4_OFFSET           ((1UL<<25)-1)
#define G_OFFSET            ((1UL<<31)-1)
#define L2_OFFSET           ((1UL<<17)-1)

enum PageType{G = 3, M4 = 2, M2 = 1, K = 0};

struct IKEntry
{
    public:
        std::map<uint64_t, uint8_t> way;
        uint64_t lrurec[6] = {0, 0, 0, 0, 0, 0};
        bool lru[5] = {0, 0, 0, 0, 0};
};

struct DKEntry
{
    public:
        std::map<uint64_t, uint8_t> way;
        uint64_t lrurec[4] = {0, 0, 0, 0};
        bool lru[3] = {0, 0, 0};
};

struct Buffer
{
    public:
        std::map<uint64_t, uint8_t> way;
        uint64_t lrurec[2] = {0, 0};
        bool lru = 0;
};

struct MEntry
{
    public:
        std::map<uint64_t, uint8_t> way;
        uint64_t lrurec[4] = {0, 0, 0, 0};
        bool lru[3] = {0, 0, 0};
};

struct L2Entry
{
    public:
        std::map<uint64_t, uint8_t> way;
        uint64_t lrurec[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        bool lru[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

};


#endif