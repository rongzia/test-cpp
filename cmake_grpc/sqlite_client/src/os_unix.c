//
// Created by rrzhang on 19-7-4.
//

#include <string.h>
#include "sqlite3.h"


extern char* ClientRPCInit();

static int unixOpen(
        sqlite3_vfs *pVfs,           /* The VFS for which this is the xOpen method */
        const char *zPath,           /* Pathname of file to be opened */
        sqlite3_file *pFile,         /* The file descriptor to be filled in */
        int flags,                   /* Input flags to control the opening */
        int *pOutFlags               /* Output flags returned to SQLite core */
){

//package para
//

}

int sqlite3_os_ini(void){
    char *p = ClientRPCInit();

    int* rc = (int*)(p);
    return *rc;
}


