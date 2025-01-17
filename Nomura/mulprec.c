#include <stdio.h>
#include <stdlib.h>
#include "mulprec.h"

/* 
    多倍長変数の値をゼロクリアして符号を正にする 
*/
void clearByZero(struct NUMBER *a){
    for(int i=0;i<KETA;i++){
        a->n[i] ^= a->n[i];
    }
    setSign(a,PLUS);
}

/*
    多倍長変数の値を表示する
*/
void dispNumber(const struct NUMBER *a){
    printf("%c", (getSign(a)==PLUS) ? '+' : '-');
    for(int i=KETA-1;i>=0;i--){
        printf("%2d",a->n[i]);
    }
}

/*
    多倍長変数の値をゼロサプレスで表示する
*/
void dispNumberZeroSuppress(const struct NUMBER *a){
    printf("%c", (getSign(a)==PLUS) ? '+' : '-');
    int i = KETA-1;
    while(a->n[i]==0 && i>0) i--;
    while(i>=0){
        printf("%d",a->n[i]);
        i--;
    }
}

/*
    指定した桁数だけ乱数で埋める
*/
void setRnd(struct NUMBER *a, int k){
    clearByZero(a);
    int is_zero = TRUE;
    if(k>KETA){k = KETA;}
    for(int i=0;i<k;i++){
        a->n[i] = (int)(((double)random()/((double)RAND_MAX+1.0))*177)%10;
        //a->n[i] = random()%10;
        if(a->n[i]!=0){
            is_zero = FALSE;
        }
    }
    if(is_zero==TRUE){
        setSign(a,PLUS);
    }else{
        setSign(a, random()%2 ? PLUS : MINUS);
    }
}

/*
    aをbにコピーする
*/
void copyNumber(const struct NUMBER *a, struct NUMBER *b){
    for(int i=0;i<KETA;i++){
        b->n[i] = a->n[i];
    }
    setSign(b,getSign(a));
}

/*
    aの絶対値をbに返す
*/
void getAbs(const struct NUMBER *a, struct NUMBER *b){
    copyNumber(a,b);
    setSign(b,PLUS);
}

/*
    aが0か判別する

    戻り値
        0  ... a==0
        -1 ... a!=0
*/
int isZero(const struct NUMBER *a){
    for(int i=0;i<KETA;i++){
        if(a->n[i]!=0){
            return -1;
        }
    }
    return 0;
}

/*
    aを10倍にしてbに返す

    戻り値
        0  ... 正常終了
        -1 ... オバーフロー
*/
int mulBy10(const struct NUMBER *a, struct NUMBER * b){
    setSign(b,getSign(a));
    for(int i=0;i<KETA-1;i++){
        b->n[i+1] = a->n[i];
    }
    b->n[0] = 0;
    if(a->n[KETA-1]==0){
        return 0;
    }else{
        return -1;
    }
}

/*
    aを1/10倍にしてbに返す

    戻り値
        aを10で割った余り
*/
int divBy10(const struct NUMBER *a, struct NUMBER * b){
    //b->sign = a->sign;
    setSign(b,getSign(a));
    for(int i=0;i<KETA-1;i++){
        b->n[i] = a->n[i+1];
    }
    b->n[KETA-1] = 0;
    return getSign(a)*a->n[0];
}

/*
    多倍長変数aにint型変数xの値を設定する

    戻り値
        0  ... 正常終了
        -1 ... xの値がaに設定しきれなかった
*/
int setInt(struct NUMBER *a, int x){
    clearByZero(a);
    if(x<0){
        a->sign = MINUS;    //  setSign()ではaが0なら強制的に+にされてしまうので
    }
    for(int i=0;i<KETA;i++){
        a->n[i] = getSign(a)*(x%10);
        x-=x%10;
        x/=10;
        if(x==0){break;}
    }
    if(x==0){
        return 0;
    }else{
        return -1;
    }
}

/*
    多倍長変数aの符号を
    s=1なら正に、s=-1なら負に設定して0を返す
    それ以外はエラーとして-1を返す
*/
int setSign(struct NUMBER *a, int s){
    if(s==1 || isZero(a)==0){
        a->sign = PLUS;
    }else if(s==-1){
        a->sign = MINUS;
    }else{
        return -1;
    }
    return 0;
}

/*
    aが0か正なら+1を, 負なら-1を返す
*/
int getSign(const struct NUMBER *a){
    if(a->sign==PLUS){
        return 1;
    }else if(a->sign==MINUS){
        return -1;
    }
}

/*
    2つの多倍長変数a,bの大小を比較する

    戻り値
        0  ... a == b
        1  ... a > b
        -1 ... a < b
*/
int numComp(struct NUMBER *a, struct NUMBER *b){
    if(getSign(a)==PLUS && getSign(b)==MINUS){
        return 1;
    }else if(getSign(a)==MINUS && getSign(b)==PLUS){
        return -1;
    }else if(getSign(a)==PLUS && getSign(b)==PLUS){
        for(int i=KETA-1;i>=0;i--){
            if(a->n[i] > b->n[i]){
                return 1;
            }else if(a->n[i] < b->n[i]){
                return -1;
            }
        }
        return 0;
    }else if(getSign(a)==MINUS && getSign(b)==MINUS){
        for(int i=KETA-1;i>=0;i--){
            if(a->n[i] > b->n[i]){
                return -1;
            }else if(a->n[i] < b->n[i]){
                return 1;
            }
        }
        return 0;
    }
}

/*
    aとbを交換する
*/
void swap(struct NUMBER *a, struct NUMBER *b){
    struct NUMBER c;
    copyNumber(a,&c);
    copyNumber(b,a);
    copyNumber(&c,b);
}

/*
    c <-- a + b

    戻り値
        0  ... 正常終了
        -1 ... オーバーフロー   
*/
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int carry = 0;
    clearByZero(c);
    for(int i=0;i<KETA;i++){
        carry += a->n[i] + b->n[i];
        c->n[i] = carry%10;
        carry /= 10;
    }
    if(carry>=1){
        return -1;
    }
    return 0;
}

/*
    c <-- a - b

    戻り値
        0  ... 正常終了
        -1 ... オーバーフロー   
*/
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    int h = 0;
    if(numComp(a,b)==1 || numComp(a,b)==0){
        for(int i=0;i<KETA;i++){
            a->n[i] -= h;
            if(a->n[i] >= b->n[i]){
                c->n[i] = a->n[i] - b->n[i];
                h = 0;
            }else if(a->n[i] < b->n[i]){
                c->n[i] = 10 + a->n[i] - b->n[i];
                h = 1;
            }
        }
    }else if(numComp(a,b)==-1){
        sub(a,b,c);
        setSign(c,MINUS);
        return -1;
    }
    return 0;
}