#include <stdio.h>

void myswap(void **val1, void **val2)
{
    void **val3;
    *val3 = *val1;
    *val1 = *val2;
    *val2 = *val3;
}

int main()
{
    int val1 = 10;
    int val2 = 20;

    printf("size_t:%lu\n", sizeof(size_t));

    printf("%d, %d\n", val1, val2);
    myswap(&(void *){&val1}, &(void *){&val2});
    // myswap((void **)&val1, (void **)&val2);
    printf("%d, %d\n", val1, val2);

    return 0;
}
/*
10, 20
0, 10

10, 20
20, 10
*/