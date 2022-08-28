#include <stdio.h>
#include "list.h"

void print_list_info(List *list)
{
    puts("--------------------");
    printf("size : %d\n", list_size(list));
    if (!list_size(list))
    {
        printf("list is empty\n");
    }
    else
    {

        printf("head : %p, %d\n", list_head(list), list_head(list)->data);
        printf("tail : %p, %d\n", list_tail(list), list_tail(list)->data);
    }
    puts("--------------------");

    return;
}

int main()
{
    long tmp;
    List mylist;
    // int _;
    printf("List initialized..\n");
    list_init(&mylist, NULL);
    print_list_info(&mylist);

    printf("insert next data..\n");
    list_ins_next(&mylist, NULL, (const void *)97);
    print_list_info(&mylist);

    printf("insert next data..\n");
    list_ins_next(&mylist, NULL, (const void *)98);
    print_list_info(&mylist);

    printf("insert next data..\n");
    list_ins_next(&mylist, NULL, (const void *)99);
    print_list_info(&mylist);

    printf("remove next data..\n");
    list_rem_next(&mylist, NULL, (void **)&tmp);
    printf("rdata: %d\n", tmp);
    print_list_info(&mylist);

    printf("List destroied..\n");
    list_destroy(&mylist);
    print_list_info(&mylist);

    return 0;
}