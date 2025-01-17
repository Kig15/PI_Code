#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA (21000)
#define PLUS (1)
#define MINUS (-1)
#define TRUE (1)
#define FALSE (-1)

//  多倍長変数
struct NUMBER{
    int n[KETA];    //  各桁の値
    int sign;      //   符号変数  -1:-, 1:0or+
};

void clearByZero(struct NUMBER *);
void dispNumber(const struct NUMBER *);
void dispNumberZeroSuppress(const struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(const struct NUMBER *, struct NUMBER *);
void getAbs(const struct NUMBER *, struct NUMBER *);
int isZero(const struct NUMBER *);
int mulBy10(const struct NUMBER *, struct NUMBER *);
int divBy10(const struct NUMBER *, struct NUMBER *);
int setInt(struct NUMBER *, int);
int setSign(struct NUMBER *, int);
int getSign(const struct NUMBER *);
int numComp(struct NUMBER *, struct NUMBER *);
void swap(struct NUMBER *, struct NUMBER *);
int add(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int sub(struct NUMBER *, struct NUMBER *, struct NUMBER *);