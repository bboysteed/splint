#include <stdio.h>

int main(){
    int a,b,c,d,e,f,g;
    printf("a:");
    scanf("%d",&a);
    printf("b:");
    scanf("%d",&b);
    if (a>10 && b>99){
        c=-2*b;
        if (a+c>10){
            d=a+88;
            e=7;
                if (d-e>4){
		    if (d+e==0){
		    	printf(":::1\n");
		    	return 0;
		    };
                    g=c/(d+e);
                }else{
		    if (c-e==0){
                        printf("\n");
                        return 0;
                    };
                    g=a/(c-e);
                };
        }else if(a+c<10){
            d=a+99;
            e=10;
                if (d-e>2){
		    if (a+c-b==0){
                        printf(":::3");
                        return 0;
                    };
                    g=c/(a+c-b);
                }else{
		    if (a+e-d==0){
                        printf(":::4\n");
                        return 0;
                    };
                    g=f/(a+e-d);
                };
        }else{
            d=a-8;
            e=100;
                if (d-e>43){
		    if (c+f-b==0){
                        printf(":::5");
                        return 0;
                    };
                    g=2*a/(c+f-b);
                }else{
		    if (6*c-f+e==0){
                        printf(":::6\n");
                        return 0;
                    };
                    g=4*b/(6*c-f+e);
                };
        };

    }else if (a>10&&b<99){
        c=3*b;
        if (a+c>10){
            d=a+88;
            e=7;
                if (d-e>23){
		   if (d+e==0){
                        printf(":::7\n");
                        return 0;
                    };
                    g=c/(d+e);
                }else{
                    if (c-e==0){
                        printf(":::8\n");
                        return 0;
                    };
			g=a/(c-e);

                };
        }else if(a+c<10){
            d=a+29;
            e=53;
                if (d-e>34){
			if (a+c-b==0){
                        printf(":::9\n");
                        return 0;
                    };
                    g=c/(a+c-b);
                }else{
			if (a+e-d==0){
                        printf(":::10\n");
                        return 0;
                    };
                    g=f/(a+e-d);
                };
        }else{
            d=a-8;
            e=140;
                if (d-e>0){
			if (c+2*f-b==0){
				printf(":::11\n");
				return 0;
			};
                    g=2*a/(c+2*f-b);
                }else{
			if (6*c-f+e==0){
                        printf(":::12\n");
                        return 0;
                    };
                    g=4*b/(6*c-f+e);
                };
        };
    }else{
        c=b+34;
        if (a+c>140){
            d=a+545;
            e=54;
                if (d-e>0){
			if (d+e==0){
                        printf(":::13\n");
                        return 0;
                    };
                    g=c/(d+e);
                }else{
			if (c-e==0){
                        printf(":::14\n");
                        return 0;
                    };
                    g=a/(c-e);
                };
        }else if(a+c<10){
            d=a+435;
            e=34;
                if (d-e>0){
			if (a+c-b==0){
                        printf(":::15\n");
                        return 0;
                    };
                    g=c/(a+c-b);
                }else{
			if (a+e-d==0){
                        printf(":::16\n");
                    };
                    g=f/(a+e-d);
                };
        }else{
            d=a-8;
            e=134;
                if (d-e>0){
			if (c+f-b==0){
                        printf(":::17\n");
                        return 0;
                    };
                    g=2*a/(c+f-b);
                }else{
			if (6*c-f+e==0){
                        printf(":::18\n");
                        return 0;
                    };
                    g=4*b/(6*c-f+e);
                };
        };

    };




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
   // if (n2==0){
     //   printf("assss");
   // };
    return n1/n2;
}
