#include <stdio.h>
#include <math.h>
#include <time.h>

int seek_prime_numbers(int start, int end)
{
    int i, j, tmp;
    start = (start < 2) ? 2 : start;

    for (i = start; i < end; i++)
    {
        tmp = 0;
        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
                tmp++;
        }
        if (tmp == 0)
            printf("%d, ", i);
    }
    putchar('\n');
}

void seek_prime_numbers_sqrt(int start, int end)
{
    int i, j, tmp;
    start = (start < 2) ? 2 : start;

    for (i = start; i < end; i++)
    {
        tmp = 0;
        for (j = 2; j < sqrt(i); j++)
        {
            if (i % j == 0)
                tmp++;
        }
        if (tmp == 0)
            printf("%d, ", i);
    }
    putchar('\n');
}

void seek_prime_numbers_div(int start, int end)
{
    int i, j, tmp;
    start = (start < 2) ? 2 : start;

    for (i = start; i < end; i++)
    {
        tmp = 0;
        for (j = 2; j < i / j; j++)
        {
            if (i % j == 0)
                tmp++;
        }
        if (tmp == 0)
            printf("%d, ", i);
    }
    putchar('\n');
}

#define MODE 1
int main(int argc, char *argv[])
{

    /*
        Comparison of function execution speed
        1st : seek_prime_numbers_sqrt
        2nd : seek_prime_numbers_div
        3rd : seek_prime_numbers
    */
    int i = 0;
    int t = 0;
    clock_t start = 0, end = 0;

#if MODE == 0
    start = clock();
    seek_prime_numbers(10000, 30000);
    end = clock();
#elif MODE == 1
    start = clock();
    seek_prime_numbers_sqrt(20000, 100000);
    end = clock();
#elif MODE == 2
    start = clock();
    seek_prime_numbers_div(20000, 100000);
    end = clock();
#endif
    t = end - start;
    printf("time: %dms\n", t);

    return 0;
}