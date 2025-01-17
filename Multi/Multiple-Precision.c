#include <time.h>
#include <stdlib.h>
#include "Multiple-Precision.h"

/*
予め外で初期化をしている前提で関数を組む

*/
//構造体の初期化関数
void clearByZero(struct NUMBER *a){
    for(int i = 0; i < KETA; i++){
        a->n[i] = 0;
    }
    a -> sign  = 1;//符号を正に設定
}

//構造体の表示関数(constをつけることで値を変更できないようにする)
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
    printf("%d",a->n[i]);
  } //各桁の値を表示
  
}

//構造体に乱数をセットする関数 srandomを使えるようにしよう
void SetRnd(struct NUMBER *a, int keta){

if(keta > KETA){
    return;
}//桁数がオーバーしていたらエラーを返す
    a->sign = (random() % 2) ? 1 : -1;//符号をランダムに設定
    for(int i = 0; i  < keta; i++){
        a->n[i] = random() % 10;
    }//各桁の値をランダムに設定

}

//構造体のコピー関数 bにaの値をコピーする
void copyNumber(const struct NUMBER *a, struct NUMBER *b){
    
    for(int i = 0; i < KETA; i++){
        b->n[i] = a->n[i];
        
    }
    b->sign = a->sign;
   
}

//符号を取得する関数
int getSign(const struct NUMBER *a){
    return a->sign;
}

//符号を設定する関数
void setSign(struct NUMBER *a ,int b){
    if(b >= 0){
        a->sign = 1;
    }
    else{
    a->sign = -1;
    }

}

//絶対値を求める関数
void getAbs(const struct NUMBER *a, struct NUMBER *b){
   copyNumber(a,b);
    b->sign = 1;
}

//引数の値を絶対値に変更する関数
void changeAbs(struct NUMBER *a){
    a->sign = 1;
}

//0かどうかを判定する関数 正常終了で0を返す　異常終了で-1を返す
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

//10倍する関数 正常終了で0を返す　異常終了で-1を返す
int mulBy10(const struct NUMBER *a, struct NUMBER *b){
    if(a->n[KETA - 1] != 0){
        return -1;
    }//オーバーフローを判定
    for(int i = 0; i < KETA - 1; i++){
        b->n[i + 1] = a->n[i];
    }
    b->n[0] = 0;
    b->sign = a->sign;
    return 0;//正常終了

    //一応bの初期化も行っているから、わざわざclearByZeroを呼び出す必要はない
}

//10分の1する関数 戻り値に余りを返す
int divBy10(const struct NUMBER *a, struct NUMBER *b){
    for(int i =1; i < KETA; i++){
        b->n[i - 1] = a->n[i];
    }
    b->sign = a->sign;
    return a->n[0];
}

//構造体に整数をセットする関数　正常終了で0を返す　異常終了で-1を返す
int setInt(struct NUMBER *a, int x){
    
    a->sign = (x < 0) ? -1 : 1;
    x = abs(x);
 
    for (int i = 0; i < KETA; i++) {
        a->n[i] = x % 10;
        x /= 10;
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
    int carry =0;
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
        c->n[i] = carry % 10;
        carry /= 10;
    
    }
    }
    else{
        c->sign = 1;
        for(int i =0; i < KETA; i++){
        carry += a->n[i] + b->n[i];
        c->n[i] = carry % 10;
        carry /= 10;
    
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
        clearByZero(c);
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
          c->n[i] = d.n[i] - high + 10 - e.n[i];
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
          c->n[i] = e.n[i] - high + 10 - d.n[i];
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
          c->n[i] = a->n[i] - high + 10 - b->n[i];
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
          c->n[i] = b->n[i] - high + 10 - a->n[i];
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
int simpleMultiple(int a, int b , int *c){
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

//掛け算を行う関数(まだ未完成　4×5以上の計算になるとなぜか－になるバグ発生中)
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
   struct NUMBER d,e;
   clearByZero(&d);
   clearByZero(&e);
   clearByZero(c);
   int h =0,l =0;

   
   if(getSign(a) == -1 && getSign(b) == 1){
       l =2;
    }
    else if(getSign(a) == 1 && getSign(b) == -1){
       l =1;
    }
   //符号の判定


   for(int i =0; i < KETA; i++){
    for(int j = 0; j < KETA; j++){
       d.n[j] += h;
       simpleMultiple(a->n[j],b->n[i],&h);
       d.n[j] += h % 10;
       h /= 10;

    }
    if(h != 0){
        return -1;
    }
    
    for(int k = 0; k < i; k++){
        mulBy10(&d,&e);
        copyNumber(&e,&d);
    }
    add(c,&d,&e);
    copyNumber(&e,c);
    clearByZero(&d);
    clearByZero(&e);
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
    