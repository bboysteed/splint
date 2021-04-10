//#include <stdio.h>
#include <klee/klee.h>
int main()
{
    int n;
    klee_make_symbolic(n,sizeof(n),"num");
    hun = n / 100;
    ten = (n-hun*100) / 10;
    ind = n % 10;
    if(n == hun*hun*hun + ten*ten*ten + ind*ind*ind)  /*各位上的立方和是否与原数n相等*/
    {
        klee_assert(0);
    }
           
    
  //  printf("Hello world\n");
    return 0;
}

