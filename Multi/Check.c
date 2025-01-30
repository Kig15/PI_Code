#include "Multiple-Precision.h"
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>





int TruePI(struct NUMBER pi);//返り値に桁
void ProgressBar(int keta_num,int progress[10]);//進捗状況を表示するための関数



int main(int argc, char *argv[])
{
    
    struct timeval tv;
    double start,end;
    gettimeofday(&tv,NULL);
    start = tv.tv_sec + tv.tv_usec * 1e-6;


   
    int keta_num =111;//求めたい桁数　仮に100桁求めたかったら0を100個になるようにしろ（例：101）　あと0は偶数個にしろ
   

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
   struct NUMBER temp,temp1;

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
    setInt(&g,1);
    clearByZero(&h);
    
    clearByZero(&n);
    clearByZero(&n_mOne);

    setInt(&one,1);
    setInt(&one_m,-1);
    setInt(&two,2);
    setInt(&three,3);
    setInt(&six,18);
    NeedNum.n[keta_num] = 1000; //求めたい桁数を設定()

    //long long a_int = 100000;//ループ回数を指定
    //srandom((unsigned)time(NULL));

    

    RootNutonRapson(&three,&temp,NeedNum);// 1/√3 を求める
    multiple(&six,&temp,&six_M_RootThree);//6√3を求める

    int NeedNUM_KETA = isKETA(NeedNum);
    

    //copyNumber(&NeedNum,&d);//dが分子の値
    int d_sign = 1;
    long long n_int = 0;//Σのnの値
    int ans_keta =0; //(2n+1) * 3^n+1の逆数の桁数
    int progress[10] ={NeedNUM_KETA / 10,NeedNUM_KETA * 2 / 10 ,NeedNUM_KETA * 3 /10,NeedNUM_KETA * 4 /10,NeedNUM_KETA * 5 /10,NeedNUM_KETA * 6 /10,NeedNUM_KETA * 7 /10,NeedNUM_KETA * 8 /10,NeedNUM_KETA * 9 /10,NeedNUM_KETA };//進捗状況を表示するための配列
    
   
     //################################################## シャープの公式  #################################################################
    while(1){
   
   
    //setSign(&d,d_sign);
     

    
    setInt(&e,(2 * n_int) + 1);//eが(2n+1)  2n+1は10億ループとかしてもオーバーフローしないからlong longでいい
    
    multiple(&g,&three,&temp);
    copyNumber(&temp,&g);//gは3^n+1

    multiple(&e,&g,&temp);//(2n+1) * 3^n+1

    inverse3(temp,&temp1,NeedNum);//(2n+1) * 3^n+1の逆数を求める

    setSign(&temp1,d_sign);//(2n+1) * 3^n+1の逆数に符号をつける

    add(&temp1,&pi_temp,&temp);//(2n+1) * 3^n+1の逆数を足す Σだから

    copyNumber(&temp,&pi_temp);//pi_tempに足した値をコピー

  
    if(d_sign == 1){
        d_sign = -1;
    }
    else{//d_sign == -1
        d_sign = 1;
    }
  

     n_int++;
     ans_keta = isKETA(temp1);

    ProgressBar(ans_keta,progress);
    fflush(stdout);
    //邪魔なら消して
    
    if(ans_keta < 3){
        break;
    }

  
   
  
   
}
printf("\n");
    
   

    multiple(&six_M_RootThree,&pi_temp,&temp);
    divByN(temp,&pi,NeedNUM_KETA - 1);
    
    
    printf("求めたい桁数 = %d\n",NeedNUM_KETA);

    printf("6√3 = ");
    DispNumber(&six_M_RootThree);
    printf("\n");
    printf("π   = ");
    DispNumber(&pi);
    printf("\n");
    

    printf("上から%d桁まで一致\n",TruePI(pi));
    printf("ループ回数 = %lld\n",n_int);

 /**/
    
 /*
  
    srand((unsigned)time(NULL));
    struct NUMBER a,b,c,d;
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    clearByZero(&d);
    //int keta_num = 10;//求めたい桁数(偶数限定)
    struct NUMBER NeedNum;//求めたい桁数
    clearByZero(&NeedNum);
    NeedNum.n[111] = 10; //求めたい桁数を設定
    
    
    //setInt(&a,854986428640463);
    //setInt(&b,583896384892894);

    
    SetRnd(&a,30 );
    SetRnd(&b,40);
    

   
    multiple(&a,&b,&c);
    //printf("%d\n",inverse3(a,&b,NeedNum));
    
    //RootNutonRapson(&a,&c,b);
    //divide(a,b,&c,&d);
    //sub(&a,&b,&c);

    //multiple(&a,&NeedNum,&c);
    //multiple(&d,&NeedNum,&c);
    //multiple(&c,&NeedNum,&d);
   
    //printf("%d\n",isKETA(NeedNum));
    DispNumber(&a);
    printf("\n");
    DispNumber(&b);
    printf("\n");
    DispNumber(&c);
    printf("\n");
    DispNumber(&d);
    printf("\n");
    

    //printf("上から%d桁まで一致\n",TruePI(a));
    */


  
  

   


    


   
    //
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

   int keta_num = isKETA(pi);
   int a = keta_num / 9;//基数で割った商
   int b = keta_num % 9;//基数で割った余り
   int c = 0; //0サプ用
   for(int i = KETA -1; i >= 0; i--){
        if(pi.n[i] != 0){
            c = i;
            break;
        }
    }//0サプ実装
    int true_keeta = 0;//正しかった桁数

    int temp =0,temp1=0;
    char temp_c = '0';



    if((a > 0) && (b > 0)){//aが0より大きくbが0より大きい
        temp = pi.n[a];
        int ten = 1;
        for(int i = 1; i < b; i++){
            ten *= 10;
        }
       
        for(int i = 1; i <= b; i++){
            if(i != b){
                 temp1 = temp / ten;
            }
            else{
                temp1 = temp;
            }
            temp_c = fgetc(fp);
            if(temp_c != temp1 + '0'){
                fclose(fp);
                return true_keeta;
            }
            true_keeta++;
            temp %= ten;
            ten /= 10;

        }

        for(int i = c-1; i >= 0; i--){
            temp = pi.n[i];
            ten = 100000000;
           
            for(int j = 1; j <= 9; j++){
                 if(j != 9){
                    temp1 = temp / ten;
                 }
                 else{
                    temp1 = temp;
                }
               
                temp_c = fgetc(fp);
                if(temp_c != temp1 + '0'){
                    fclose(fp);
                    return true_keeta;
                }
                true_keeta++;
                temp %= ten;
                ten /= 10;
               
            }
        }
        
    }
    else if((a > 0) && (b == 0)){//aが0より大きくbが0
        int ten = 1;
         for(int i = c; i >= 0; i--){
            temp = pi.n[i];
            ten = 100000000;
             for(int j = 1; j <= 9; j++){
                   if(j != 9){
                         temp1 = temp / ten;
                    }
                    else{
                        temp1 = temp;
                    }
                  temp_c = fgetc(fp);
                  if(temp_c != temp1 + '0'){
                        fclose(fp);
                        return true_keeta;
                    }
                 true_keeta++;
                 temp %= ten;
                 ten /= 10;
                }
            }   

    }
    else{//aが0
       temp = pi.n[a];
        int ten = 1;
        for(int i = 1; i < b; i++){
            ten *= 10;
        }
        for(int i = 1; i <= b; i++){
            if(i != b){
                 temp1 = temp / ten;
            }
            else{
                temp1 = temp;
            }
            temp_c = fgetc(fp);
            if(temp_c != temp1 + '0'){
                fclose(fp);
                return true_keeta;
            }
            true_keeta++;
            temp %= ten;
            ten /= 10;

        }
    }



    fclose(fp);
    return true_keeta;
}

void ProgressBar(int keta_num,int progress[10]){
     printf("\r[");
    for(int i = 9; i >= 1; i--){
       
        if(keta_num <= progress[i]){
            printf("#");
           
        }
        else{
            printf("-");
        }
    }
    printf("]");
    
}