#include "Multiple-Precision.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    
   

   struct NUMBER pi_temp;//円周率
   struct NUMBER pi;//円周率

   struct NUMBER one;//定数の設定
   struct NUMBER one_m;//-1
   struct NUMBER two;
   struct NUMBER three;
   struct NUMBER six;
   struct NUMBER NeedNum;//求めたい桁数

   struct NUMBER a;//計算用の構造体
   struct NUMBER b;
   struct NUMBER c;
   struct NUMBER d;
   struct NUMBER e;
   struct NUMBER f;
   struct NUMBER g;
   struct NUMBER h;
   struct NUMBER n;//Σのn
   struct NUMBER n_mOne;//Σのn-1

    clearByZero(&pi);
    clearByZero(&pi_temp);

    clearByZero(&one);
    clearByZero(&one_m);
    clearByZero(&two);
    clearByZero(&three);
    clearByZero(&six);
    clearByZero(&NeedNum);

    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    clearByZero(&d);
    clearByZero(&e);
    clearByZero(&f);
    clearByZero(&g);
    clearByZero(&h);
    
    clearByZero(&n);
    clearByZero(&n_mOne);

    setInt(&one,1);
    setInt(&one_m,-1);
    setInt(&two,2);
    setInt(&three,3);
    setInt(&six,1);
    NeedNum.n[7] = 1;
    setInt(&a,100);
    //srandom((unsigned)time(NULL));

    
     
 while(numComp(&n,&a) == -1){
   
   
    

    divide(n,two,&b,&c);//cが１なら奇数　cが０なら偶数

    
    
    if(numComp(&c,&one) == 0){
        struct NUMBER temp;
        clearByZero(&temp);
        copyNumber(&one_m,&temp);
        multiple(&NeedNum,&temp,&d);
    }
    else{
        
        struct NUMBER temp;
        clearByZero(&temp);
       copyNumber(&one,&temp);
       multiple(&NeedNum,&temp,&d);
       
         
    }//dが分子の値(求めたい桁数倍されてます)

   printf("----------\n");
   printf("d = ");
   DispNumber(&d);
   printf("\n");

    multiple(&n,&two,&b);
    add(&b,&one,&e);//eが(2n+1)

   printf("e = ");
   DispNumber(&e);
   printf("\n");
    

    if(numComp(&n,&one) == 0 ||numComp(&n,&one) == 1 ){
        copyNumber(&n,&f);

        struct NUMBER temp;
        clearByZero(&temp);
        setInt(&temp,3);

        while(isZero(&f) == -1){
       
             multiple(&three,&temp,&g);
             copyNumber(&g,&temp);

             oneDecrement(&f);

        }
    }
    else{
        

    copyNumber(&three,&g);
    }//gは3^n+1

   printf("g = ");
   DispNumber(&g);
   printf("\n");
    
    

    struct NUMBER temp1;
    clearByZero(&temp1);
    multiple(&e,&g,&temp1);

    printf("temp1 = ");
    DispNumber(&temp1);
    printf("\n");

    struct NUMBER temp2;
    clearByZero(&temp2);
    struct NUMBER temp3;
    clearByZero(&temp3);
    divide(d,temp1,&temp2,&temp3);
   
   printf("temp2 = ");
   DispNumber(&temp2);
   printf("\n");

    add(&temp2,&h,&pi_temp);
    copyNumber(&pi_temp,&h);
    
   printf("h = ");
   DispNumber(&h);
   printf("\n");



   DispNumber(&n);
   oneIncrement(&n);
   
    printf("\n");
    }
    

    multiple(&six,&pi_temp,&pi);
    DispNumber(&pi);

/**/
    


/*
    struct NUMBER a,b,c,d;
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    clearByZero(&d);



   
   // setInt(&b,3);

for(int i = 3; i < 100; i++){
 clearByZero(&a);
    setInt(&a,i);
    int ans = isPrime(a);
    switch (ans)
    {
    case 1:
        printf("--素数です--\n");
        break;
    case 0:
        printf("合成数です\n");
        break;
    case -1:
        printf("エラーです\n");
        break;
    
    default:
        printf("エラーです\n");
        break;
    }

     DispNumber(&a); 
    printf("\n");
}
  
    //SetRnd(&b,2);
    //divide(a,b,&c,&d);
    //sub(&a,&b,&c);
   
   
    DispNumber(&b);
    printf("\n");
    DispNumber(&c);
    printf("\n");
    DispNumber(&d);
    printf("\n");
    */


  
  

   


    


   
    


 return 0;
}
