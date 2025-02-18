#include <time.h>
#include <stdlib.h>
#include "Multiple-Precision.h"

/*


*/
//構造体の初期化関数 基数変換済み
void clearByZero(struct NUMBER *a){
    for(int i = 0; i < KETA; i++){
        a->n[i] = 0;
    }
    a -> sign  = 1;//符号を正に設定
}

//構造体の表示関数(constをつけることで値を変更できないようにする)  基数変換済み
void DispNumber(const struct NUMBER *a){
 int j =0;
    switch (a->sign)
    {
    case 1:
        printf("+"); 
        break;
    case -1:
        printf("-");
        break;
    
    default:
     printf("+"); 
        break;
    }//符号の表示

    for(int i = KETA -1; i >= 0; i--){
        if(a->n[i] != 0){
            j = i;
            break;
        }
    }//0サプ実装

  for(int  i = j; i >= 0; i--){
    printf("%09lld",a->n[i]);
  } //各桁の値を表示
  
}

//構造体に乱数をセットする関数 srandomを使えるようにしよう 基数変換済み
void SetRnd(struct NUMBER *a, int keta){

if(keta > KETA * 9){
    return;
}//桁数がオーバーしていたらエラーを返す
    a->sign = (random() % 2) ? 1 : -1;//符号をランダムに設定
    int keta_kisuu = keta / 9;//桁数を9で割った商
    int keta_amari = 1;//桁数を9で割った余り
    for(int i = 0; i  < keta_kisuu; i++){
        a->n[i] = random() % KISUU;//999,999,999までの数をランダムに設定
    }//各桁の値をランダムに設定

    for(int i = 0; i < keta % 9; i++){
        keta_amari *= 10;
    }

    a->n[keta_kisuu] = random() % keta_amari;//余りの桁数をランダムに設定

}

//構造体のコピー関数 bにaの値をコピーする 基数変換済み
void copyNumber(const struct NUMBER *a, struct NUMBER *b){
    clearByZero(b);
    
    for(int i = 0; i < KETA; i++){
        b->n[i] = a->n[i];
        
    }
    b->sign = a->sign;
   
}

//符号を取得する関数 基数変換済み
int getSign(const struct NUMBER *a){
    return a->sign;
}

//符号を設定する関数 基数変換済み
void setSign(struct NUMBER *a ,int b){
    if(b >= 0){
        a->sign = 1;
    }
    else{
    a->sign = -1;
    }

}

//絶対値を求める関数   基数変換済み
void getAbs(const struct NUMBER *a, struct NUMBER *b){
   copyNumber(a,b);
    b->sign = 1;
}

//引数の値を絶対値に変更する関数  基数変換済み
void changeAbs(struct NUMBER *a){
    a->sign = 1;
}

//0かどうかを判定する関数 正常終了で0を返す　異常終了で-1を返す 基数変換済み
int isZero(const struct NUMBER *a){
    if(a->sign == -1){
        return -1;
    }

    for(int i = 0; i < KETA; i++){
        if(a->n[i] != 0){
            return -1;
        }
    }
    return 0;
}

//10倍する関数 正常終了で0を返す　異常終了で-1を返す 基数変換済み(10億進数としてみてるため、値を10倍するのではなく、桁をずらすだけ)
int mulBy10(const struct NUMBER *a, struct NUMBER *b){
    clearByZero(b);
    if(a->n[KETA - 1] > 0){
        return -1;
    }//オーバーフローを判定

    for(int i = 0; i < KETA - 1; i++){
        b->n[i+1] = a->n[i];
    }

    b->n[0] = 0;
    b->sign = a->sign;
    return 0;//正常終了

    //一応bの初期化も行っているから、わざわざclearByZeroを呼び出す必要はない
}

//10分の1する関数 戻り値に余りを返す   基数変換済み(10億進数としてみてるため、値を10分の1するのではなく、桁をずらすだけ)
long long divBy10(const struct NUMBER *a, struct NUMBER *b){
    clearByZero(b);
    for(int i =1; i < KETA; i++){
        b->n[i - 1] = a->n[i];
    }
    b->sign = a->sign;
    return a->n[0];
}

//構造体に整数をセットする関数　正常終了で0を返す　異常終了で-1を返す 基数変換済み
int setInt(struct NUMBER *a, long long x){
    clearByZero(a);
    
    a->sign = (x < 0) ? -1 : 1;
    x = llabs(x);
 
    for (int i = 0; i < KETA; i++) {
        a->n[i] = x % KISUU;
        x /= KISUU;
        if(x == 0){
            break;
        }
    }
    
    return (x == 0) ? 0 : -1;
    
}

//大小比較を行う関数 a==b 0 , a > b 1 , a < b -1
int numComp(struct NUMBER *a, struct NUMBER *b){
    if(a->sign > b->sign){
        return 1;
    }
    else if(a->sign < b -> sign){
        return -1;
    }
    else if(a->sign == 1 && b->sign == 1)
    {
        for(int i = KETA -1; i >= 0; i--){
            if(a->n[i] > b->n[i]){
                return 1;
            }
            else if(a->n[i] < b->n[i]){
                return -1;
            }
        }
    }
    else if(a->sign == -1 && b->sign == -1){
        for(int i = KETA -1; i >= 0; i--){
            if(a->n[i] > b->n[i]){
                return -1;
            }
            else if(a->n[i] < b->n[i]){
                return 1;
            }
        }
    }
  
    return 0;
}

//足し算を行う関数 正常１を返す　異常-1を返す
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    long long carry =0;
    clearByZero(c);
    if((a->sign ==1) && (b->sign ==-1)){
        struct NUMBER d;
       clearByZero(&d);
        getAbs(b,&d);
       return sub(a,&d,c);
        
    }
    if((a->sign == -1) && (b -> sign ==1)){
        struct NUMBER d;
       clearByZero(&d);
        getAbs(a,&d);
       return sub(b,&d,c);
        
    }
    if(a->sign == -1 && b->sign == -1){
       

        c->sign = -1;
        for(int i =0; i < KETA; i++){
        carry += a->n[i] + b->n[i];
        c->n[i] = carry % KISUU;
        carry /= KISUU;
    
    }
    }
    else{
        

        c->sign = 1;
        for(int i =0; i < KETA; i++){
        carry += a->n[i] + b->n[i];
        c->n[i] = carry % KISUU;
        carry /= KISUU;
    
    }
    }
   
    if(carry != 0){
        return -1;
    }
    return 0;
}

//インクリメントを行う関数
int increment(struct NUMBER *a, struct NUMBER *b){
    struct NUMBER one;
    int r;

    setInt(&one,1);
    r = add(a,&one,b);
    return r;

}

//1引数のみでインクリメントを行う関数
int oneIncrement(struct NUMBER *a){
    struct NUMBER one,b;
    int r;

    clearByZero(&b);
    clearByZero(&one);
    setInt(&one,1);
    r = add(a,&one,&b);
    copyNumber(&b,a);
    return r;
}

int decrement(struct NUMBER *a, struct NUMBER *b){
    struct NUMBER one;
    int r;

    setInt(&one,1);
    r = sub(a,&one,b);
    return r;

}

//1引数のみでデクリメントを行う関数
int oneDecrement(struct NUMBER *a){
    struct NUMBER one,b;
    int r;

    clearByZero(&b);
    clearByZero(&one);
    setInt(&one,1);
    r = sub(a,&one,&b);
    copyNumber(&b,a);
    return r;
}

//引き算を行う関数 正常１を返す　異常-1を返す
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int high = 0;//桁借りのフラグ 0:借りなし 1:借りあり
    int l;//lは0 X * Y, 1 X * (-Y), 2 (-X) * Y, 3 (-X) * (-Y)
    clearByZero(c);
    if(numComp(a,b) == 0){
        
        return 1;
    }//a == bの時は0を返す

     if(getSign(a) == -1 && getSign(b) == -1){
       l =3;
    }
    else if(getSign(a) == -1 && getSign(b) == 1){
       l =2;
    }
    else if(getSign(a) == 1 && getSign(b) == -1){
       l =1;
    }
    else if(getSign(a) == 1 && getSign(b) == 1){
       l =0;
    }//符号の判定
    
    if(l == 2){
        struct NUMBER d;
        clearByZero(&d);
        getAbs(a,&d);
        int temp =  add(&d,b,c);
        c->sign = -1;
        return temp;

    }
    else if(l == 1){
        struct NUMBER d;
        clearByZero(&d);
        getAbs(b,&d);
        return add(a,&d,c);
    }
    else if(l == 3){
        struct NUMBER d,e;
        clearByZero(&d);
        clearByZero(&e);
       if(numComp(a,b) == -1){
        c->sign = -1;
        getAbs(a,&d);
        getAbs(b,&e);

        for(int i = 0; i < KETA; i++){
       if((d.n[i] - high) > e.n[i]){
          c->n[i] = d.n[i] - high - e.n[i];
          high = 0;
       }
       else if((d.n[i] -high) < e.n[i]){
          c->n[i] = d.n[i] - high + KISUU - e.n[i];
          high = 1;
       }
       else{//(a->n[i] - high) == b->n[i]の時
           c->n[i] = 0;
           high = 0;
       }

     
     }
    }//a > bの時

    else if(numComp(a,b) == 1){
        c->sign = 1;
        getAbs(a,&d);
        getAbs(b,&e);

       for(int i = 0; i < KETA; i++){
       if((e.n[i] - high) > d.n[i]){
          c->n[i] = e.n[i] - high - d.n[i];
          high = 0;
       }
       else if((e.n[i] - high) < d.n[i]){
        
          c->n[i] = e.n[i] - high + KISUU - d.n[i];
          high = 1;
       }
       else{
              c->n[i] = 0;
              high = 0;
       }
     }
     
    }//a < bの時
    }
    else{

    if(numComp(a,b) == 1){
        c->sign = 1;

        for(int i = 0; i < KETA; i++){
       if((a->n[i] - high) > b->n[i]){
          c->n[i] = a->n[i] - high - b->n[i];
          high = 0;
       }
       else if((a->n[i] -high) < b->n[i]){
          c->n[i] = a->n[i] - high + KISUU - b->n[i];
          high = 1;
       }
       else{//(a->n[i] - high) == b->n[i]の時
           c->n[i] = 0;
           high = 0;
       }

     
    }
    }//a > bの時
    else if(numComp(a,b) == -1){
        c->sign = -1;

       for(int i = 0; i < KETA; i++){
       if((b->n[i] - high) > a->n[i]){
          c->n[i] = b->n[i] - high - a->n[i];
          high = 0;
       }
       else if((b->n[i] - high) < a->n[i]){
          c->n[i] = b->n[i] - high + KISUU - a->n[i];
          high = 1;
       }
       else{
              c->n[i] = 0;
              high = 0;
       }
     }
     
    }//a < bの時
    }
   
   if(high == 1){
       return -1;
   }
   return 1;

   
}

//簡単な掛け算を行う関数
int simpleMultiple(long long a, long long b , long long *c){
   int i =b;
   *c = 0;
  /*
    while(1){
    if(i== 0){
        break;
    }
    *c += a;
    i--;
   }
   */

   for(i = b; i > 0; i--){
       
          *c += a;
          
   }
   return 0;
    
  
}

//掛け算を行う関数()
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
  
   clearByZero(c);
   long long h =0;
   int l =0;

   
   if(getSign(a) == -1 && getSign(b) == 1){
       l =2;
    }
    else if(getSign(a) == 1 && getSign(b) == -1){
       l =1;
    }
   //符号の判定

   int a_keta = 0;
   int b_keta = 0;

   for(int i = KETA - 2; i >= 0; i--){
       if(a->n[i] != 0){
            if(a_keta == 0){
                a_keta = i;
            }
          
       }

       if(b->n[i] != 0){
            if(b_keta == 0){
                b_keta = i;
            }
           
       }

       if(a_keta != 0 && b_keta != 0){
           break;
        }

      
   }//0サプ実装

   


   for(int i =0; i <= b_keta + 1; i++){
   
    for(int j = 0; j <= a_keta+ 1; j++){
       

       

       if(a->n[j] == 0 || b->n[i] == 0){
           h = 0;
           continue;
       }
       //simpleMultiple(a->n[j],b->n[i],&h); <--ゴミ
       h = a->n[j] * b->n[i];
       c->n[j + i] += h % KISUU;
       c->n[j + i + 1] += h / KISUU;

       c->n[j + i + 1] += c->n[j + i] / KISUU;
       c->n[j + i] %= KISUU;
       

    }
    if(h != 0){
        return -1;
    }
    
    //for(int k = 0; k < i; k++){
    //  mulBy10(&d,&e);
    //  copyNumber(&e,&d);
    //}
    
    //mulByN(d,&e,i * 9);
    //copyNumber(&e,&d);

    //add(c,&e,&d);
    //copyNumber(&d,c);
   
   }//掛け算の処理　コメント一行で説明できるようなものではない

   if(l){
       setSign(c,-1);
       }//答えの符号を設定
    return 0;
}

//簡単な割り算を行う関数 0正常終了　-1異常終了
int sinmpleDivide(int x, int y, int *z,int*w){
   int k = 0, l = 0;//kは商      lは0 X * Y, 1 X * (-Y), 2 (-X) * Y, 3 (-X) * (-Y)

 if(y == 0 || x == 0){
       return -1;//0除算エラー
   }

   if(x < 0 && y < 0){
   l = 3;
   }
   else if(x < 0 && y > 0){
    l = 2;
   }
   else if(x > 0 && y < 0){
    l = 1;
   }
   else if(x > 0 && y > 0){
    l = 0;
   }//符号の判定

   x = abs(x);
   y = abs(y);//絶対値を取得

   while(1)
   {
    if(x < y){
        break;
    }
    x -= y;
    k++;
   }//割り算の処理

  
   switch(l){//商と余りの符号を判定
       case 0:
         *z = k;//商
        *w = x;//余り
             break;
       case 1:
        *z = -k;//商
        *w = x;//余り
             break;
       case 2:
         *z = -k;//商
         *w = -x;//余り
            break;
       case 3:
         *z = k;//商
         *w = -x;//余り
             break;
       }

    return 0;
}

//a / b 割り算を行う関数(未検証なためMainで検証してくれ) 0正常終了　-1異常終了
int divide(struct NUMBER a, struct NUMBER b, struct NUMBER *c, struct NUMBER *d){
    struct NUMBER k,g; 
    int l;//lは0 X * Y, 1 X * (-Y), 2 (-X) * Y, 3 (-X) * (-Y)
    clearByZero(&k);
    clearByZero(&g);
    clearByZero(c);
    clearByZero(d);
   
   
    
    if(isZero(&b) == 0){
        return -1;
    }//0除算エラー
    if(isZero(&a) == 0){
        return 0;
    }//0除算エラー


    if(getSign(&a) == -1 && getSign(&b) == -1){
       l =3;
    }
    else if(getSign(&a) == -1 && getSign(&b) == 1){
       l =2;
    }
    else if(getSign(&a) == 1 && getSign(&b) == -1){
       l =1;
    }
    else if(getSign(&a) == 1 && getSign(&b) == 1){
       l =0;
    }//符号の判定

   

    changeAbs(&a);
    changeAbs(&b);//絶対値を取得

   
/*
    while(1)
   {
    if(numComp(&a,&b) == -1){
        break;
    }

    sub(&a,&b,&g);
  //  printf("g = ");
   // DispNumber(&g);
    //printf("\n");
    copyNumber(&g,&a);
    oneIncrement(&k);
   }//割り算の処理
 */

struct NUMBER f,e,temp;
//clearByZero(&f);
//clearByZero(&e);
//clearByZero(&temp);


int keta_a = 0;
int keta_f = 0;
//while(1){
while(1){
    if(numComp(&a,&b) == -1){
        break;
    }
    copyNumber(&b,&f);
    setInt(&e,1);

     /*
    printf("-----------------\n");
    printf("a = ");
    DispNumber(&a);
    printf("\n");
    printf("f = ");
    DispNumber(&f);
    printf("\n");
    printf("e = ");
    DispNumber(&e);
    printf("\n");
   
   */


    while(numComp(&a,&f) == 1){//a > dの時
        keta_a = isKETA(a);
        keta_f = isKETA(f);

        if(keta_a == keta_f){
            break;
        }

        mulByN(f,&temp,keta_a - keta_f);
        copyNumber(&temp,&f);
        if(numComp(&a,&f) == 1 || numComp(&a,&f) == 0){
            mulByN(e,&temp,keta_a - keta_f);
            copyNumber(&temp,&e);
            break;
        }
        else{
            divByN(f,&temp,1);
            copyNumber(&temp,&f);
            mulByN(e,&temp,keta_a - keta_f - 1);
            copyNumber(&temp,&e);
            break;
        }
       

        
        //printf("aaa\n");
    }

    if(numComp(&a,&f) == 0){//a = dの時
        setInt(&a,0);
        add(&k,&e,&temp);
        copyNumber(&temp,&k);
        //printf("bbb\n");
    }
    else{//a < dの時
       
        
        sub(&a,&f,&temp);
    /*
          printf("a = ");
    DispNumber(&a);
    printf("\n");
      printf("f = ");
    DispNumber(&f);
    printf("\n");
      printf("a = ");
    DispNumber(&temp);
    printf("\n");
    */
        copyNumber(&temp,&a);
        add(&k,&e,&temp);
        copyNumber(&temp,&k);
        //printf("ccc\n");
    }

    
    // printf("-----------------\n");
    

 
}//割り算の処理 まとめて引くことによる高速化
   
    
switch(l){//商と余りの符号を判定
       case 0:
        
         copyNumber(&k,c);//商
         copyNumber(&a,d);//余り
             break;
       case 1:
       if(isZero(&k)){
          setSign(&k,-1);
       }
        copyNumber(&k,c);//商
        copyNumber(&a,d);//余り
             break;
       case 2:
         if(isZero(&k)){
          setSign(&k,-1);
       }
        copyNumber(&k,c);//商
        setSign(&a,-1);
        copyNumber(&a,d);//余り
            break;
       case 3:
         copyNumber(&k,c);//商
         setSign(&a,-1);
         copyNumber(&a,d);//余り
             break;
       }
 return 0;
}

int isPrime(struct NUMBER a){//素数判定を行う関数　素数なら1 合成数なら0 a<=1で-1
    struct NUMBER one;
    clearByZero(&one);
    setInt(&one,1);
    if(numComp(&a,&one) == -1 || numComp(&a,&one) == 0){
        return -1;
    }//a<=1の時は-1を返す


    struct NUMBER temp,temp2,ans,amari;
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&ans);
    clearByZero(&amari);
    setInt(&temp2,2);
    copyNumber(&a,&temp);

     while(numComp(&a,&temp2) == 1){
      
            divide(temp,temp2,&ans,&amari);
           if(isZero(&amari) == 0){
               return 0;
               }//割り切れた時は合成数

           
            oneIncrement(&temp2);
        }

    return 1;


}

int RootNutonRapson(struct NUMBER *N, struct NUMBER *d,struct NUMBER keta){//ニュートンラプソン法で平方根の逆数を求める関数 正常終了1 異常終了-1 NeedNumは二倍にするから、あらかじめ二倍にしておかなくてもよい
    struct NUMBER x;//現在の平方根の近似値
    struct NUMBER b;//1つ前のｘ
    struct NUMBER h;//1 - N * x^2
   
    struct NUMBER temp,temp1,temp2,temp3,temp4,one,three,four,eight,eight_inv,keta2,N_copy;
    
    int keta_temp = isKETA(keta);
    mulByN(keta,&keta2,keta_temp - 1);

    clearByZero(d);
    
    mulByN(*N,&N_copy,keta_temp - 1);//N だけど足すようなので10^keta倍してる //100

    int N_keta = isKETA(*N);
   
    setInt(&temp,2);
    mulByN(temp,&x,keta_temp - 2 - N_keta);//0.2 //100
   
    

    
   
    //定数の設定
    
    setInt(&one,1);//1
    mulByN(one,&one,keta_temp - 1);//1 だけど足すようなので10^keta倍してる //100
    setInt(&three,3);//3   //1
    setInt(&four,4);//4    //4
    setInt(&temp,8);
    inverse3(temp,&temp1,keta);// 1/8 * 10^keta
    copyNumber(&temp1,&eight_inv);//1/8 だけど足すようなので10^keta倍してる //100
    mulByN(temp,&eight,keta_temp - 1);//8　だけど足すようなので10^keta倍してる //100
   
    

   /*
    printf("one       = ");
    DispNumber(&one);
    printf("\n");
    printf("three     = ");
    DispNumber(&three);
    printf("\n");
    printf("four      = ");
    DispNumber(&four);
    printf("\n");
    printf("eight     = ");
    DispNumber(&eight);
    printf("\n");
    printf("eight_inv = ");
    DispNumber(&eight_inv);
    printf("\n");
    printf("keta      = ");
    DispNumber(&keta);
    printf("\n");
    printf("keta2     = ");
    DispNumber(&keta2);
    printf("\n");
    */

     int roopNum = 0;
    while(1){
        roopNum++;


        copyNumber(&x,&b);

        //h = 1 - N * x^2　を求める
        copyNumber(&b,&temp4);
        multiple(N,&b,&temp);
        multiple(&temp,&b,&temp1); // N*x^2  //100 00 keta = 100でも最大コレ　今後はこれで表記
        divByN(temp1,&temp,keta_temp - 1);//N * x^2  //100
        sub(&one,&temp,&h);//1 - N * x^2  //100

       
        //x = x / 8 *(8 + 3*h * 3* h^2) を求める
        multiple(&three,&h,&temp);//3 * h  //100
        multiple(&temp,&h,&temp1);//3 * h^2  //100 00
        divByN(temp1,&temp2,keta_temp - 1);//3 * h^2  //100
       
       
       
        multiple(&four,&h,&temp3);//4 * h  //100

       
        add(&temp2,&temp3,&temp4);//3 * h^2 + 4 * h  //100 


        add(&eight,&temp4,&temp2);//8 + 3 * h^2 + 4 * h  //100
       
        
        

        multiple(&eight_inv,&b,&temp3);//1/8 * x  //100 00
        divByN(temp3,&temp4,keta_temp - 1);//1/8 * x  //100
       

        multiple(&temp2,&temp4,&temp3);//(8 + 3 * h^2 + 4 * h) * 1/8 * x  //100 00
        divByN(temp3,&x,keta_temp - 1);//(8 + 3 * h^2 + 4 * h) * 1/8 * x  //100

        

          
            if(isKETA(h) < 3){
                break;
            }//収束判定

           



    }

    

    




    copyNumber(&x,d);
    printf("6√3ループ回数 = %d\n",roopNum);
    fflush(stdout);

    return 1;
   
/*
    //copyNumber(&temp,&keta);
   
    //int keta_temp2 = isKETA(keta2);
   // printf("keta = %d\n",keta_temp2);
    

    if(numComp(N,&x) == -1)return -1;//N < 0の時はエラーを返す
    if(isZero(N) == 0) copyNumber(N,d);//N = 0の時は0を返す
    setInt(&x,1);
    if(numComp(N,&x) == 0){ 
         multiple(N,&keta,d);
        return 1;
        }//N = 1の時は1を返す
    if(isKETA(keta) < 3) return -1;//桁数が3未満の時はエラーを返す　丸め誤差が下二桁だから

    
    //clearByZero(&temp);
    //clearByZero(&temp1);
    setInt(&two,2);

    //multiple(N,&keta,&N_copy);//桁は3とかじゃなくて　10000みたいに表します

    //divide(N_copy,two,&temp,&temp1);
    inverse3(two,&two_inv,keta2);      //100 00
    //inverse3(two,&temp1,keta);      
    multiple(N,&two_inv,&x);          //100 00
    //divByN(temp2,&x,keta_temp2 - 1);

    //copyNumber(&temp,&x);
    copyNumber(&x,&b);
    //copyNumber(&x,&c);
    //clearByZero(d);
  
  
   int roopNum = 0;
   int judgeBreak =0;
   while(1){
        roopNum++;
        judgeBreak++;
        
        copyNumber(&b,&c);
        copyNumber(&x,&b);
       
      

        //divide(N_copy,x,&temp,&temp1);

        inverse3(x,&temp,keta2);   //100 00
        
       
        multiple(N,&temp,&temp1); //100 00
        //divByN(temp1,&temp,keta_temp2 - 1);

        add(&x,&temp1,&temp); //100 00

        
        //multiple(&temp,&two_inv,&temp2); //100 00 00 00
        //divByN(temp2,&x,keta_temp2 - 1);
       
        divBy2(temp,&x); //100 00

       //divide(temp1,two,&x,&temp);
        if(judgeBreak >= 10){
            judgeBreak = 0;
            sub(&b,&x,&temp1);
            if(isKETA(temp1) < 3){
                break;
            }//収束判定
            sub(&c,&x,&temp1);
            if(isKETA(temp1) < 3){
                if(numComp(&b,&x) == -1) copyNumber(&b,&x);
                break;
            }//振動判定（要検証、これでいいのかは不明　無限ループが起こったらここを疑って）
        }

    }
    //divByN(x,d,(((keta_temp- 1) / 2)));//----------------後の改善案、結局求まった桁の1/3捨てるんならもうxの値がketa_tempの桁数になったらいいのでは----------------
    copyNumber(&x,d);
    printf("6√3ループ回数 = %d\n",roopNum);
    fflush(stdout);
    return 1;
*/


}

int isKETA(const struct NUMBER a){//桁数を求める関数
   int Keta =0;
   int j = 0;
   long long temp = 0;  
   for(int i = KETA -1; i >= 0; i--){
        if(a.n[i] != 0){
            j = i;
            break;
        }
    }//0サプで最大の桁のとこを求めるlog10
    temp = a.n[j];
    for(int i = 0; i < 9; i++){
        temp /= 10;
        Keta++;
        if(temp == 0){
            break;
        }
        
    }
    //一番上の桁の桁数を求める
    Keta += (9 * j);//それに9をかけて、それ以外の桁数を求める

   
   return Keta;

}
    
/**/
int inverse3(struct NUMBER a, struct NUMBER *b,struct NUMBER keta){ //3次収束の式で逆数を求める式  正常終了で0を返す　異常終了で-1を返す　　生の値を入れて、ketaで補正するため、ここでketaで補正した値を入れると、正確な値が出ない
    struct NUMBER x;//現在の平方根の近似値
    struct NUMBER y;//1つ前のｘ
    struct NUMBER h;//作業用の値
    //struct NUMBER g;//収束判定用の値

    struct NUMBER temp;
    struct NUMBER temp1;
    struct NUMBER temp2;

    

    if(isZero(&a) == 0) return -1;//a = 0の時はエラーを返す
    

    int keta_num = isKETA(keta);
    if(keta_num < 3) return -1;//桁数が3未満の時はエラーを返す　丸め誤差が下二桁だから
    int keta_a = isKETA(a);
    int sign = getSign(&a);
    

    setInt(&temp,1);
    if(numComp(&a,&temp) == 0){//a = 1の時
        setInt(b,1);
        setSign(b,1);
        return 0;
    }
     setInt(&temp,-1);
    if(numComp(&a,&temp) == 0){//a = -1の時
        setInt(b,1);
        setSign(b,-1);
        return 0;
    }

    //clearByZero(&x);
    //clearByZero(&y);
    //clearByZero(&h);
    //clearByZero(&g);
    //clearByZero(&temp);
    clearByZero(b);

    int temp_int = keta_num - keta_a;
    if(temp_int > 0){
        setInt(&x,1);
        temp_int -= 1;
        int aaa = temp_int / 9;
        int bbb = temp_int % 9;
        int ccc = 1;
        for(int i = 0; i < bbb; i++){
            ccc *= 10;
        }
        x.n[aaa] =ccc * 2;
        //mulByN(x,&temp,temp_int);
        //copyNumber(&temp,&x);
        //setInt(&temp1,2);
        //multiple(&x,&temp1,&temp);
        //copyNumber(&temp,&x);
        //x = 0.2 * 10^(-keta_a) * 10^(keta_num) の初期値を求める処理

       while(1){
           
            copyNumber(&x,&y);//y = x
            

            multiple(&a,&y,&temp);
            sub(&keta,&temp,&h);//h = (1.0 * keta) - a * y
            

            multiple(&h,&h,&temp);
            divByN(temp,&temp1,keta_num -1 );

            /*
            printf("h * h = ");
            DispNumber(&temp1);
            printf("\n");
            */

            add(&h,&temp1,&temp);
            add(&keta,&temp,&temp1);
            multiple(&y,&temp1,&temp2);
            divByN(temp2,&x,keta_num - 1);
            //copyNumber(&temp,&x);//x = y * (1.0 * keta + h + h * h)の計算
            

           // copyNumber(&h,&g);
           // setSign(&g,1);   //g = fabs(h)
             
            
            
            sub(&y,&x,&temp1);
            if(isKETA(temp1) < 3){
                break;
            }//収束判定
        }
        copyNumber(&x,b);
        setSign(b,sign);

        return 0;


    }
    else{//(temp) < 0
    setInt(b,0);
    setSign(b,1);
    return -1;

    }



}


int mulByN(struct NUMBER a, struct NUMBER *b, int n){//aの中の値を10^nでかける関数 正常終了で0を返す　異常終了で-1を返す
    int slide = n / 9;
    int amari = n % 9;

    if(n == 0){
        copyNumber(&a,b);
        return 0;
    }

    
    if(amari != 0){
    while(slide > 0){
        mulBy10(&a,b);
        copyNumber(b,&a);
        slide--;
        
    }//どうあがいても消される桁を消す(ちょっとおもいかも)

    /*
    printf("a = \n");
    DispNumber(&a);
    printf("\n");
    */

   long long ten = 1,ten2 =1;
    clearByZero(b);

    for(int i =0; i < (9 - amari); i++){
        ten *= 10;
    }//10^(9-あまり)を求める
    for(int i =0; i < amari; i++){
        ten2 *= 10;
    }//10^あまりを求める

     //printf("ten = %lld\n",ten);

    for(int i =0; i < KETA-1; i++){
        if(a.n[i] != 0){
            b->n[i] += (a.n[i] % ten) * ten2;
            b->n[i + 1] += a.n[i] / ten;
             
        }
    }
    b->n[KETA-1] += (a.n[KETA-1] % ten) * ten2;

   setSign(b,getSign(&a));

   }
   else{//amari == 0

    while(slide > 0){
        mulBy10(&a,b);
        copyNumber(b,&a);
        slide--;
    }//どうあがいても消される桁を消す(ちょっとおもいかも)


   }

    return 0;

}

int divByN(struct NUMBER a, struct NUMBER *b, int n){//aの中の値を10^nで割る関数 正常終了で0を返す　異常終了で-1を返す
   int slide = n / 9;
   int amari = n % 9;

    if(n == 0){
        copyNumber(&a,b);
        return 0;
    }

    

   if(amari != 0){
    while(slide > 0){
        divBy10(&a,b);
        copyNumber(b,&a);
        slide--;
    }//どうあがいても消される桁を消す(ちょっとおもいかも)
/*
    printf("a = \n");
    DispNumber(&a);
    printf("\n");
*/

    long long ten = 1,ten2 =1;
    clearByZero(b);

    for(int i =0; i < (9 - amari); i++){
        ten *= 10;
    }//10^(9-あまり)を求める
    for(int i =0; i < amari; i++){
        ten2 *= 10;
    }//10^あまりを求める
    
    //printf("ten = %lld\n",ten);

    for(int i =0; i < KETA-1; i++){
        if(a.n[i] != 0){
            b->n[i] += a.n[i] / ten2;
        }
        if(a.n[i+1] != 0){
                b->n[i] += (a.n[i+1] % ten2) * ten;
       }
    }
     b->n[KETA-1] += a.n[KETA-1] / ten2;

   

   }
   else{//amari == 0

    while(slide > 0){
        divBy10(&a,b);
        copyNumber(b,&a);
        slide--;
    }//どうあがいても消される桁を消す(ちょっとおもいかも)

   }

    return 0;
}

int divBy2(struct NUMBER a, struct NUMBER *b){//aの中の値を2で割る関数 余りを返す
    long long Temp =0;//一時保存
    int mod2 = 0;//2で割った時の余り ほぼCarry
    clearByZero(b);

    int j =0;
    for(int i = KETA -1; i >= 0; i--){
        if(a.n[i] != 0){
            j = i;
            break;
        }
    }//0サプ実装

    for(int i = j; i >= 0; i--){
      //printf("a.n[%d] = %lld\n",i,a.n[i]);
      Temp = (a.n[i] + (mod2 * KISUU)) / 2;
      //printf("Temp   = %lld\n",Temp);
      mod2 = a.n[i] % 2;
      //printf("mod2 = %d\n",mod2);
      b->n[i] = Temp;
     
    }
    return mod2;

}