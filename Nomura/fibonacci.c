#include "mulprec.h"
#include <time.h>



int main(int argc, char **argv){
    
    srandom(time(NULL));
    struct NUMBER a,b,c;
    setInt(&a,1);
    setInt(&b,0);
    setInt(&c,0);
    for(int i=0;i<=100000;i++){
        add(&a,&b,&c);
        copyNumber(&a,&b);
        copyNumber(&c,&a);
    }
    dispNumberZeroSuppress(&c);
    return 0;
}