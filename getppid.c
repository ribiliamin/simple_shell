#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Parent PID: %d\n", getppid());
    return 0;
}

