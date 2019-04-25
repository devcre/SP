/** System Programming (5) : system(3) **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ret = system("ps -ef | grep erica > erica.txt");

    printf("Return Value of system function : %d \n", ret);

    return 0;
}
