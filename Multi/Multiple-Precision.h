#define KETA 35
#define KISUU 1000000000
#include <stdio.h>
/*
2025 01 20 基数変換を始める
これ以降のコミットは全て基数変換済である

基数は999,999,999までの数を扱う
つまり1,000,000,000進数

*/


struct  NUMBER
{
    long long n[KETA];//各桁の値
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

void clearByZero(struct NUMBER *a);//構造体の初期化関数

void DispNumber(const struct NUMBER *a);//構造体の表示関数(constをつけることで値を変更できないようにする)

void SetRnd(struct NUMBER *a, int keta);//構造体に乱数をセットする関数 srandomを使えるようにしよう

void copyNumber(const struct NUMBER *a, struct NUMBER *b);//構造体のコピーを行う関数

int getSign(const struct NUMBER *a);//符号を取得する関数

void setSign(struct NUMBER *a,int b);//符号を設定する関数

void getAbs(const struct NUMBER *a, struct NUMBER *b);//絶対値を求める関数

void changeAbs(struct NUMBER *a);//引数の値を絶対値に変更する関数

int isZero(const struct NUMBER *a);//0かどうかを判定する関数 正常終了で0を返す　異常終了で-1を返す
   
int mulBy10(const struct NUMBER *a, struct NUMBER *b);//10倍する関数 正常終了で0を返す　異常終了で-1を返す

long long divBy10(const struct NUMBER *a, struct NUMBER *b);//10分の1する関数 戻り値に余りを返す

extern int setInt(struct NUMBER *a, long long x);//構造体に整数をセットする関数　正常終了で0を返す　異常終了で-1を返す

int numComp(struct NUMBER *a, struct NUMBER *b);//大小比較を行う関数

int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//足し算を行う関数

int increment(struct NUMBER *a, struct NUMBER *b);//インクリメントを行う関数

int oneIncrement(struct NUMBER *a);//1引数のみでインクリメントを行う関数

int decrement(struct NUMBER *a, struct NUMBER *b);//デクリメントを行う関数

int oneDecrement(struct NUMBER *a);//1引数のみでデクリメントを行う関数

int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//引き算を行う関数

int simpleMultiple(long long a, long long b , long long *c);//簡単な掛け算を行う関数

int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);//掛け算を行う関数

int sinmpleDivide(int x, int y, int *z,int*w);//簡単な割り算を行う関数

int divide(struct NUMBER a, struct NUMBER b, struct NUMBER *c, struct NUMBER *d);//割り算を行う関数

int isPrime(struct NUMBER a);//素数判定を行う関数

int RootNutonRapson(struct NUMBER *a, struct NUMBER *b,struct NUMBER keta);//ニュートンラプソン法を行う関数

int isKETA(const struct NUMBER a);//桁数を求める関数

int inverse3(struct NUMBER a, struct NUMBER *b,struct NUMBER keta);//3次収束の式で逆数を求める関数

int mulByN(struct NUMBER a, struct NUMBER *b, int n);//aの中の値を10^nで掛ける関数

int divByN(struct NUMBER a, struct NUMBER *b, int n);//aの中の値を10^nで割る関数

int divide_in(struct NUMBER a, struct NUMBER b, struct NUMBER *c, struct NUMBER *d);//逆数で割り算を行う関数
