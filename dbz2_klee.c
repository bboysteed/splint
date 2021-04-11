#include <assert.h>
#include <klee/klee.h>
int main(){
    int a,b,c,d,e,f,g;
    //a=98;
    //g=10;
    klee_make_symbolic(&a,sizeof(a),"a");
    klee_make_symbolic(&b,sizeof(a),"b");
    if (a>10 && b>99){
        c=-2*b;
        if (a+c>10){
            d=a+88;
            e=7;
                if (d-e>4){
		    if (d+e==0){
		    	//klee_aseert(0);
		    };
                    g=c/(d+e);
                }else{
                    g=a/(c-e);
                };
        }else if(a+c<10){
            d=a+99;
            e=10;
                if (d-e>2){
                    g=c/(a+c-b);
                }else{
                    g=f/(a+e-d);
                };
        }else{
            d=a-8;
            e=100;
                if (d-e>43){
                    g=2*a/(c+f-b);
                }else{
                    g=4*b/(6*c-f+e);
                };
        };

    }else if (a>10&&b<99){
        c=3*b;
        if (a+c>10){
            d=a+88;
            e=7;
                if (d-e>23){
                    g=c/(d+e);
                }else{
                    g=a/(c-e);
                };
        }else if(a+c<10){
            d=a+29;
            e=53;
                if (d-e>34){
                    g=c/(a+c-b);
                }else{
                    g=f/(a+e-d);
                };
        }else{
            d=a-8;
            e=140;
                if (d-e>0){
                    g=2*a/(c+2*f-b);
                }else{
                    g=4*b/(6*c-f+e);
                };
        };
    }else{
        c=b+34;
        if (a+c>140){
            d=a+545;
            e=54;
                if (d-e>0){
                    g=c/(d+e);
                }else{
                    g=a/(c-e);
                };
        }else if(a+c<10){
            d=a+435;
            e=34;
                if (d-e>0){
                    g=c/(a+c-b);
                }else{
                    g=f/(a+e-d);
                };
        }else{
            d=a-8;
            e=134;
                if (d-e>0){
                    g=2*a/(c+f-b);
                }else{
                    g=4*b/(6*c-f+e);
                };
        };

    };
return 0;
}