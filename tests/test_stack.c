//
// Created by sparkai on 22-10-24.
//
#include "stack.h"

int main() {

    stack s;
    stackInit(s, sizeof(int), 0, NULL);

    int ix = 3, iy = 4, iz = 5;
    stackPush(s, &ix);
    stackPush(s, &iy);
    stackPush(s, &iz);
    stackPush(s, REF_INT(6));
    stackPush(s, REF_INT(7));
    stackPush(s, REF_INT(8));

    int popInt;
    for (int i = 0; i < 6; ++i) {
        stackPop(s, &popInt);
        printf("isEmpty=%d, Pop Value: %d\n", stackEmpty(s), popInt);
    }

    stackDestroy(s);

    return 0;
}