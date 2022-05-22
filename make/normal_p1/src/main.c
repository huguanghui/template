#include <stdio.h>

#include "main_api.h"

void test_demo()
{
    printf("[HGH-TEST][%s %d]\n", __FUNCTION__, __LINE__);
    return;
}

int main(int argc, char *argv[])
{
    test_demo();
    return 0;
}
