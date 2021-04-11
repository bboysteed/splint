#include <stdio.h>

int main(){
    int g,a,b,c,d,e,f;
    a=98;
    g=10;
    if (a>10){
        b=87;
        e=add(a,b);
    }else if (g==10){
        c=77;
    }else{
        d=67;
        f=div(d,a);

    };


    if (e>=100){
        a = div(a,f);
    }else{
        f+=c;
        b = div(e,f);
    };
    printf("%d,%d,%d,%d,%d,%d,%d",a,b,c,d,e,f,g);
    
    

return 0;
}
int add(int n1,int n2){
    return n1+n2;
    return n1+n2;


}

int minus(int n1 ,int n2){
    return n1-n2;

}


int plus(int n1, int n2){
    return n1*n2;

}


int div(int n1,int n2){
    //if n2==0{
    //klee_assert(0);
    //};
    if (n2==0){
        printf("assss");
    };
    return n1/n2;
}
