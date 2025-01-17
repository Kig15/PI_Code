#define KETA 10
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Multiple-Precision.h>

struct  NUMBER
{
    int n[KETA];//各桁の値
    int sign;//符号
    /* data */
};

/*
void ABC(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    a->n[0] = 10;
    b->n[0] = 20;
    c->n[0] = 30;

    printf("a = %d\n", a->n[0]);
    printf("b = %d\n", b->n[0]);
    printf("c = %d\n", c->n[0]);//a,b,cの値が変更されている　ポインタ参照のテスト
}
*/

void clearByZero(struct NUMBER *a){//構造体の初期化関数
    for(int i = 0; i < KETA; i++){
        a->n[i] = 0;
    }
    a -> sign  = 1;//符号を正に設定
}

void DispNumber(const struct NUMBER *a){//構造体の表示関数(constをつけることで値を変更できないようにする)
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

  for(int  i = KETA -1; i >= 0; i--){
    printf("%2d",a->n[i]);
  } //各桁の値を表示
  
}

void SetRnd(struct NUMBER *a, int keta){//構造体に乱数をセットする関数 srandomを使えるようにしよう

if(keta > KETA){
    return;
}//桁数がオーバーしていたらエラーを返す
    a->sign = (random() % 2) ? 1 : -1;//符号をランダムに設定
    for(int i = 0; i  < keta; i++){
        a->n[i] = random() % 10;
    }//各桁の値をランダムに設定

}

void copyNumber(const struct NUMBER *a, struct NUMBER *b){//構造体のコピー関数
    /*
    for(int i = 0; i < KETA; i++){
        b->n[i] = a->n[i];
        
    }
    b->sign = a->sign;
    */
   *b = *a;
}

void getAbs(const struct NUMBER *a, struct NUMBER *b){//絶対値を求める関数
   copyNumber(a,b);
    b->sign = 1;
}

int isZero(const struct NUMBER *a){//0かどうかを判定する関数 正常終了で0を返す　異常終了で-1を返す
    for(int i = 0; i < KETA; i++){
        if(a->n[i] != 0){
            return -1;
        }
    }
    return 0;
}

int mulBy10(const struct NUMBER *a, struct NUMBER *b){//10倍する関数 正常終了で0を返す　異常終了で-1を返す
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

int divBy10(const struct NUMBER *a, struct NUMBER *b){//10分の1する関数 戻り値に余りを返す
    for(int i =1; i < KETA; i++){
        b->n[i - 1] = a->n[i];
    }
    b->sign = a->sign;
    return a->n[0];
}

int main(int argc, char *argv[]){
   struct NUMBER b;
   struct NUMBER c;
   struct NUMBER d;

    srandom((unsigned)time(NULL));

    clearByZero(&b);
    isZero(&b) == 0 ? printf("正常に初期化されました\n") : printf("正常に初期化されませんでした\n");
    clearByZero(&c);
    isZero(&c) == 0 ? printf("正常に初期化されました\n") : printf("正常に初期化されませんでした\n");
    SetRnd(&b, 5);

    for(int i = 0; i < 6; i++){
        (mulBy10(&b, &c) == -1) ? printf("オーバーフローです\n") : printf("正常に10倍されました\n");
        printf("b = ");
        DispNumber(&b);
        printf("\n");

        printf("c = ");
        DispNumber(&c);
        printf("\n\n");

        copyNumber(&c, &b);
        
    }

    clearByZero(&b);
    clearByZero(&c);
    SetRnd(&b, 10);
    int r = 0;
    for(int i = 0; i < 11; i++){
        r = divBy10(&b, &c);
        (r >= 0) ? printf("余り%d\n",r) : printf("正常に1/10されました\n");
        printf("b = ");
        DispNumber(&b);
        printf("\n");

        printf("c = ");
        DispNumber(&c);
        printf("\n\n");

        copyNumber(&c, &b);
        
    }
    return 0;
    
}


