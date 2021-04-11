# splint cppcheck klee
check code division by zero work


#### 前提说明：
    - 故障定位是指在能够正常运行但会发生故障的软件中定位故障，而不是一堆堆砌的、没有关联的函数集合来定位bug

- `splint`
    - 必须是没有语法错误的文件
    - 输出案例
    
```bash
    $ splint origin_dyz2.c
    Splint 3.1.2a --- May 25 2020
    
    division_by_zero_2.c: (in function main)
    origin_dyz2.c:6:5: Return value (type int) ignored: scanf("%d", &a)
      Result returned by function call is not used. If this is intended, can cast
      result to (void) to eliminate message. (Use -retvalint to inhibit warning)
    origin_dyz2.c:8:5: Return value (type int) ignored: scanf("%d", &b)
    origin_dyz2.c:41:23: Variable f used before definition
      An rvalue is used that may not be initialized to a value on some execution
      path. (Use -usedef to inhibit warning)
    origin_dyz2.c:47:13: Variable f used before definition
    origin_dyz2.c:53:15: Variable f used before definition
    origin_dyz2.c:94:23: Variable f used before definition
    origin_dyz2.c:100:12: Variable f used before definition
    origin_dyz2.c:106:12: Variable f used before definition
    origin_dyz2.c:144:23: Variable f used before definition
    origin_dyz2.c:150:10: Variable f used before definition
    origin_dyz2.c:156:12: Variable f used before definition
    division_by_zero_2.c: (in function add)
    origin_dyz2.c:173:12: Unreachable code: return n1 + n2;
      This code will never be reached on any possible execution. (Use -unreachable
      to inhibit warning)
    origin_dyz2.c:190:5: Function div inconsistently declared to return int
      A function, variable or constant is redefined with a different type. (Use
      -incondefs to inhibit warning)
       load file standard.lcd: Specification of div: div_t
    
    Finished checking --- 13 code warnings
    
```

- `cppcheck `

  - 必须语法没有错误

  - 输出案例

```bash
$ cppcheck origin_byz1.c
Checking origin_byz1.c ...
origin_byz1.c:25:39: error: Uninitialized variable: c [uninitvar]
    printf("%d,%d,%d,%d,%d,%d,%d",a,b,c,d,e,f,g);
                                      ^
origin_byz1.c:25:41: error: Uninitialized variable: d [uninitvar]
    printf("%d,%d,%d,%d,%d,%d,%d",a,b,c,d,e,f,g);
                                        ^
origin_byz1.c:20:19: error: Uninitialized variable: f [uninitvar]
        a = div(a,f);
                  ^
origin_byz1.c:22:12: error: Uninitialized variable: c [uninitvar]
        f+=c;
           ^
origin_byz1.c:25:45: error: Uninitialized variable: f [uninitvar]
    printf("%d,%d,%d,%d,%d,%d,%d",a,b,c,d,e,f,g);
                                            ^
origin_byz1.c:54:9: error: Uninitialized variable: n2 [uninitvar]
    if (n2==0){
        ^
origin_byz1.c:20:19: note: Calling function 'div', 2nd argument 'f' value is <Uninit>
        a = div(a,f);
                  ^
origin_byz1.c:54:9: note: Uninitialized variable: n2
    if (n2==0){
        ^
origin_byz1.c:57:15: error: Uninitialized variable: n2 [uninitvar]
    return n1/n2;
              ^
origin_byz1.c:20:19: note: Calling function 'div', 2nd argument 'f' value is <Uninit>
        a = div(a,f);
                  ^
origin_byz1.c:57:15: note: Uninitialized variable: n2
    return n1/n2;

```

- `klee` 
  - 必须编译成llvm码
  - 案例

```c
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

```

### 改写成klee的符号化：

```c
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

```

#### 运行情况：

```bash
klee@8cf25c342a4f:~/mpb_test4$ ktest-tool klee-last/test0000         
test000001.ktest    test000007.ktest    test000012.kquery   test000019.div.err
test000002.ktest    test000008.div.err  test000012.ktest    test000019.kquery
test000003.div.err  test000008.kquery   test000013.ktest    test000019.ktest
test000003.kquery   test000008.ktest    test000014.ktest    test000020.ktest
test000003.ktest    test000009.ktest    test000015.ktest    test000021.ktest
test000004.ktest    test000010.ktest    test000016.ktest    test000022.ktest
test000005.ktest    test000011.ktest    test000017.ktest    test000023.ktest
test000006.ktest    test000012.div.err  test000018.ktest    test000024.ktest

```

可以看出标出了除0错误

#### 重播

```bash
klee@8cf25c342a4f:~/mpb_test4$ ktest-tool klee-last/test000019.ktest 
ktest file : 'klee-last/test000019.ktest'
args       : ['div2.bc']
num objects: 3
object 0: name: 'model_version'
object 0: size: 4
object 0: data: b'\x01\x00\x00\x00'
object 0: hex : 0x01000000
object 0: int : 1
object 0: uint: 1
object 0: text: ....
object 1: name: 'a'
object 1: size: 4
object 1: data: b'\x00\x00\x00@'
object 1: hex : 0x00000040
object 1: int : 1073741824
object 1: uint: 1073741824
object 1: text: ...@
object 2: name: 'b'
object 2: size: 4
object 2: data: b'\x00\x00\x00\xe0'
object 2: hex : 0x000000e0
object 2: int : -536870912
object 2: uint: 3758096384
object 2: text: ....

```

#### 运行源程序查看在哪里发生除0错误

```bash
klee@8cf25c342a4f:~/mpb_test4$ ./or_div2 
a:1073741824
b:-536870912
:::9
```

可以看出在`9`处发生了除零。