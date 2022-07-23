/* Automatically generated file; DO NOT EDIT!! */

#define STANDALONE
#include <wine/test.h>

extern void func_protocol(void);
extern void func_sock(void);

const struct test winetest_testlist[] =
{
    { "protocol", func_protocol },
#ifndef _M_AMD64 // hangs
    { "sock", func_sock },
#endif
    { 0, 0 }
};
