//
// Created by rrzhang on 2019/10/23.
//

#include <iostream>
#include <cstdlib>
using namespace std;

#define UNIV_PAGE_SIZE_DEF (1 << 14)
ulong srv_page_size = UNIV_PAGE_SIZE_DEF;
#define UNIV_PAGE_SIZE ((ulint)srv_page_size)
#define BUFFER_BLOCK_SIZE ((ulint)(UNIV_PAGE_SIZE * 1.3))

#define INNOBASE_CACHE_LINE_SIZE 64
#define byte unsigned char
typedef unsigned long int ulint;
typedef ulint lock_word_t;

struct Block {
    /** Default constructor */
    Block() : m_ptr(), m_in_use() {}

    byte *m_ptr;

    byte pad[INNOBASE_CACHE_LINE_SIZE - sizeof(ulint)];
    lock_word_t m_in_use;
};

void *ut_align(const void *ptr, /*!< in: pointer */
               ulint align_no)  /*!< in: align by this number */
{
    return ((void *)((((ulint)ptr) + align_no - 1) & ~(align_no - 1)));
}

int main(){

    Block *block;

    cout<<"size of struct Block : "<< sizeof(Block)<<endl;
    cout<<"size of struct *block : "<< sizeof(*block)<<endl;
    cout<<"size of struct ulint : "<< sizeof(ulint)<<endl;

    byte *ptr;
    ptr = static_cast<byte *>(malloc(sizeof(*block) + BUFFER_BLOCK_SIZE));
    cout<<"size of struct ptr : "<< sizeof(*block) + BUFFER_BLOCK_SIZE<<endl;
    block = new (ptr) Block();
    block->m_ptr = static_cast<byte *>(ptr + sizeof(*block));
    block->m_in_use = 1;
    cout<<"block->m_in_use : "<<(ulint)ptr[64]<<endl;

    byte *compressed_page;
    compressed_page = static_cast<byte *>(ut_align(block->m_ptr, 512));

    cout<<"location of compressed_page : "<<compressed_page-block->m_ptr<<endl;

    return 0;
}
