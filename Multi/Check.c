#include "Multiple-Precision.h"
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>





int TruePI(struct NUMBER pi);//返り値に桁



int main(int argc, char *argv[])
{
    
    struct timeval tv;
    double start,end;
    gettimeofday(&tv,NULL);
    start = tv.tv_sec + tv.tv_usec * 1e-6;


    /*
    int keta_num = 100;//求めたい桁数(偶数限定)
   

   struct NUMBER pi_temp;//円周率
   struct NUMBER pi;//円周率

   struct NUMBER one;//定数の設定
   struct NUMBER one_m;//-1
   struct NUMBER two;
   struct NUMBER three;
   struct NUMBER six;
   struct NUMBER RootThree;
   struct NUMBER NeedNum;//求めたい桁数
   struct NUMBER six_M_RootThree;//6√3

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

    clearByZero(&RootThree);
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
    setInt(&six,6);
    NeedNum.n[keta_num * 2] = 1; //求めたい桁数を設定(√3の計算のために2倍してます)
    setInt(&a,100000); //ループ回数を指定
    //srandom((unsigned)time(NULL));

    RootNutonRapson(&three,&RootThree,NeedNum);//ルート3を求める
    multiple(&six,&RootThree,&six_M_RootThree);//6√3を求める

    NeedNum.n[keta_num * 2] = 0;
    NeedNum.n[keta_num] = 1; //求めたい桁数を設定
    
     
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
    if(isZero(&temp2) == 0){
        break;
        }
    }
    
    
    printf("six_M_RootThree = ");
    DispNumber(&six_M_RootThree);
    printf("\n");

    printf("pi_temp         = ");
    DispNumber(&pi_temp);
    printf("\n");


    multiple(&six_M_RootThree,&pi_temp,&pi);
    
    printf("pi              = ");
    DispNumber(&pi);
    printf("\n");

    printf("上から%d桁まで一致\n",TruePI(pi));

*/
    

  
    srand((unsigned)time(NULL));
    struct NUMBER a,b,c,d;
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    clearByZero(&d);
    //int keta_num = 10;//求めたい桁数(偶数限定)
    struct NUMBER NeedNum;//求めたい桁数
    clearByZero(&NeedNum);
    NeedNum.n[0] = 10000; //求めたい桁数を設定
    
    
    //setInt(&a,854986428640463);
    //setInt(&b,583896384892894);

    
    setInt(&a,1);
    printf("%d\n",inverse3(a,&b,NeedNum));
    
    //RootNutonRapson(&a,&c,b);
    //divide(a,b,&c,&d);
    //sub(&a,&b,&c);
    DispNumber(&a);
    printf("\n");
    DispNumber(&b);
    printf("\n");
    DispNumber(&c);
    printf("\n");
    DispNumber(&d);
    printf("\n");
    

    //printf("上から%d桁まで一致\n",TruePI(a));
     /* */


  
  

   


    


   
    
    gettimeofday(&tv,NULL);
    end = tv.tv_sec + tv.tv_usec * 1e-6;

    printf("所要時間 = %f\n",end - start);

 return 0;
}

int TruePI(struct NUMBER pi){
    FILE *fp;
    fp = fopen("pi.txt","r");

    if(fp == NULL){
        printf("ファイルが開けません\n");
        return -1;
    }

    int j = 0;
    for(int i = KETA - 1; i >= 0; i--){
       if(pi.n[i] != 0){
          j = i;
          break;
       }
      
    }
    
    int keeta = 0;
    char c = 'o';
    for(int i = j; i >= 0; i--){
        c = fgetc(fp);
       if( c != pi.n[i] + '0'){
           break;
       }
       keeta++;
    }


    fclose(fp);
    return keeta;
}