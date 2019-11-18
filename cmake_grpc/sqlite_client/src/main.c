//
// Created by rrzhang on 19-7-4.
//

#include <stdio.h>
#include <stdlib.h>

struct stct {
    int a;
};
typedef struct stct stct;

int TestFun();
int TestFun() {
    stct* stct1 = malloc(sizeof(int));
}

extern const char* ClientRPCInit();

void main() {
    printf("%d\n", ClientRPCInit());
}