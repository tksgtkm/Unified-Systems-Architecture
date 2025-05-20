#include <stdio.h>
#include <stdlib.h>

int ntz(unsigned x) {
    int n;

    if (x == 0)
      return 32;

    n = 1;
    if ((x & 0x0000FFFF) == 0) {
        n = n + 16;
        x = x >> 16;
    }
    if ((x & 0x000000FF) == 0) {
        n = n + 8;
        x = x >> 8;
    }
    if ((x & 0x0000000F) == 0) {
        n = n + 4;
        x = x >> 4;
    }
    if ((x & 0x00000003) == 0) {
        n = n + 2;
        x = x >> 2;
    }

    return n - (x & 1);
}

int nlz(unsigned x) {
    int n;

    if (x == 0)
      return 32;

    n = 0;
    if (x <= 0x0000FFFF) {
        n = n + 16;
        x = x << 16;
    }
    if (x <= 0x00FFFFFF) {
        n = n + 8;
        x = x << 8;
    }
    if (x <= 0x0FFFFFFF) {
        n = n + 4;
        x = x << 4;
    }
    if (x <= 0x3FFFFFFF) {
        n = n + 2;
        x = x << 2;
    }
    if (x <= 0x7FFFFFFF) {
        n = n + 1;
    }
    return n;
}

int pop(unsigned x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = x + (x << 8);
    x = x + (x << 16);
    return x >> 24;
}