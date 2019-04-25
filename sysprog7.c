/** System Programming (7) : exit(2), atexit(3) **/

#include <stdio.h>
#include <stdlib.h>

void cleanup1(void)
{
    printf("cleanup 1 is called \n");
}

void cleanup2(void)
{
    printf("cleanup 2 is called \n");
}

int main(void)
{
    atexit(cleanup1);	// atexit(3)
    atexit(cleanup2);

    exit(0);		// exit(2)
}
