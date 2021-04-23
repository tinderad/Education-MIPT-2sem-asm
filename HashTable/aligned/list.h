#ifndef __LIST__
#define __LIST__

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "math.h"
#include "assert.h"
#include "coloring.h"
#include "config.h"
#include "string.h"
#include <stdexcept>
#include "x86intrin.h"
#include "SIMD_strcmp.cpp"

//static int   Neutral();
static char* Neutral();

struct ListElement
{
    ListElement* next_     = 0;
    ListElement* prev_     = 0;
    const __m128i*  key_      = nullptr;
    size_t       n_blocks_ = 0;
    Type value_;

    ListElement(const __m128i* key = nullptr, Type value = Neutral(), ListElement* next = nullptr, ListElement* prev = nullptr, size_t n_blocks = 0);
    ListElement(const ListElement& that)              = delete;
    ListElement& operator= (const ListElement& that)  = delete;

    void print();
};

struct HashTableList
{   
    ListElement* tail = 0;
    size_t size = 0;
    ListElement* head = 0;
    volatile size_t test = 0;
    public:

    enum LIST_CODES
    {
        #define CODE(codename) codename,
        LIST_OK = 0,        
        #include "listcodes.h"
        #undef CODE
    };

    HashTableList();
    HashTableList (const HashTableList& that)            = delete;
    //HashTableList& operator= (const HashTableList& that) = delete;

    LIST_CODES append(ListElement* new_element);
    int print(bool quiet = true);
    const char* getCodename(LIST_CODES code);
    LIST_CODES validate();

    ListElement* getElement(const __m128i* key, size_t n_blocks);
    Type getValue(const __m128i* key, size_t n_blocks);
    void setValue(const __m128i* key, size_t n_blocks, Type value);

};

#endif