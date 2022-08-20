#include <stdio.h>


//// 반복문 2개 프린트문 한개로 프로그램을 완성하도록 수정하시오.
/*
 * -> 이미 이전 코드에서  printMultiplicationTableWithGrid_2()는
 *    for 2개와 1개의 printf 문을 사용하였던 코드 이며, 
 *    보기 불편하실까봐 실제 실행되는 코드 이외의 것들은 지우고, 
 *    함수는 하나로 합쳤습니다.
 */

#define VBAR '|'
#define OP " * "
#define EQ " = "

int printMultiplicationTableWithGrid_2()
{
    int cnt = 0;
    int i = 0, j = 0;
    int a,b,c;
    int hflag = 1;
    char *hbar[2] = {
        "--------------------------------------------------------------------------------\n",
        ""};

    for (i = 2; i < 20; i += 1 + (((i % 10) == 9) * 2))
    {
        for (j = 2; j < 6; j++)
        {
            cnt++;
            a = j + (4 * (i / 10));
            b = i % 10;
            c = a * b;
            printf("%s%1c%2d%3s%-2d%3s%-8d%1c",
                 hbar[!(hflag ^ (i / 10))],
                 ' ', a, OP, b, EQ, c, VBAR);
            hflag = (i / 10);
        }
        putchar('\n');
    }
    puts(hbar[0]);
    return cnt;
}

int main(int argc, char *argv[])
{
   	printMultiplicationTableWithGrid_2();
    return 0;
}

