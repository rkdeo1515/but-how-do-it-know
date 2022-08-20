#include <stdio.h>


//// 반복문 2개 프린트문 한개로 프로그램을 완성하도록 수정하시오.



void printHorizontalBar()
{
    printf("--------------------"
           "--------------------"
           "--------------------"
           "--------------------\n");
}

void printColumn(int a, int b)
{
    //     "12345678901234567890"
    //     " 0 * 0 = 00        |"
    //      1 23 346 78 91011
    char vbar = '|';
    char op[4] = " * ";
    char eq[4] = " = ";

    // 1+2+3+2+3+8+1 = 20
    printf("%1c%2d%3s%-2d%3s%-8d%1c",
           vbar, a, op, b, eq, a * b, vbar);
	
    printf("%1c%2d%3s%-2d%3s%-8d%1c",
           ' ', a+1, op, b, eq, (a+1) * b, vbar);
    printf("%1c%2d%3s%-2d%3s%-8d%1c",
           ' ', a+2, op, b, eq, (a+2) * b, vbar);
    printf("%1c%2d%3s%-2d%3s%-8d%1c",
           ' ', a+3, op, b, eq, (a+3) * b, vbar);
    putchar('\n');
}
void printForm(int a, int b)
{
    char vbar = '|';
    char op[4] = " * ";
    char eq[4] = " = ";
    printf("%1c%2d%3s%-2d%3s%-8d%1c",
           ' ', a, op, b, eq, a * b, vbar);
}

int printMultiplicationTableWithGrid()
{
    int cnt = 0;
    int i = 0, j = 0;

    printHorizontalBar();
    for (i = 2; i < 10; i += 4)
    {
        for (j = 2; j < 10; j++)
        {
            cnt++;
            printColumn(i, j);
        }
        printHorizontalBar();
    }
    return cnt;
}

int printMultiplicationTable()
{
    int cnt = 0;
    int i = 0;
    for (i = 22; i < 100; i += 1 + (((i % 10) == 9) * 2))
    {
        cnt++;
        printf("%d * %d = %d \n%c", i / 10, i % 10, (i / 10) * (i % 10), (((i % 10) == 9) * '\n'));
    }
    return cnt;
}

int printMultiplicationTableWithGrid_2()
{
    int cnt = 0;
    int i = 0, j = 0;
    int hflag = 1;
    char *s[2] = {
        "--------------------------------------------------------------------------------\n",
        ""};

    for (i = 2; i < 20; i += 1 + (((i % 10) == 9) * 2))
    {
        for (j = 2; j < 6; j++)
        {
            cnt++;
            printf("%s", s[!(hflag ^ (i / 10))]);
            printForm(j + (4 * (i / 10)), i % 10);
            hflag = (i / 10);
        }
        printf("\n");
    }
    printf("%s", s[0]);
    return cnt;
}

int main(int argc, char *argv[])
{
	printf("Loop Count : %d\n\n",printMultiplicationTable());          		// #1 격자 x 구구단 출력 (반복문 1개 사용)
	printf("Loop Count : %d\n\n",printMultiplicationTableWithGrid());		// #2 격자 구구단 출력
   	printf("Loop Count : %d\n\n",printMultiplicationTableWithGrid_2());		// #3 격자 구구단 출력
    return 0;
}

