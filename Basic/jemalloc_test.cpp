
#include <stdio.h>
#include <jemalloc/jemalloc.h>
  
void jemalloc_test(int i)
{
        malloc(i*100);
}
 
int main(int argc, char **argv)
{
        int i;
        for(i=0;i<1000;i++)
        {
                jemalloc_test(i);
        }
        malloc_stats_print(NULL,NULL,NULL);
        return 0;
}
