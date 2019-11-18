

#ifndef SQLITE_SERVER_OS_RPC_C
#define SQLITE_SERVER_OS_RPC_C

#include <stdlib.h>
#include <string.h>


extern int sqlite3_os_init(void);

char* RPC_Init()
{
    int rc = sqlite3_os_init();

    char* p = (char*)&rc;
    return p;
}

#endif


