#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h>

int sqrt_newton(int x);

int main(void){

    int i,r,r1,r2,d;

    srandom((unsigned)time(NULL));

    

        r = 2000000;
        r1 = sqrt_newton(r);
        r2 = (int)sqrt((double)r);
        d = r1 - r2;
        printf("%10d : %6d - %6d = %d\n",r,r1,r2,d);
    

    return 0;

}

int sqrt_newton(int N){

    int x;//現在の平方根の近似値
    int b;//1つ前のｘ
    int c;//2つ前のｘ

    if(N < 0) return -1;
    if((N == 0) || (N == 1)) return N;

    x = N/2;//初期値
    b = x;
    c = x;

    while(1){
        c = b;
        b = x;

    printf("------\n");
    printf("x = %d\n",x);
    printf("b = %d\n",b);
    printf("c = %d\n",c);
    printf("------\n"); 

        x = (x + N/x) / 2;
        if((x == b)) break;//収束判定
        if((x == c)){
            if(b < x) x = b;
            break;
        }//振動判定

    }

    return x;
}

