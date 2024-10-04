#define EXSTD_FULL
#include "exstd.h"

CLASS(Res, 
    int x;
    int y;
);

CONSTRUCTOR(Res)(int x, int y){
    return(Res){x,y};
}

DESTRUCTOR(Res){
    printf("Res is destroyed with value: %d %d\n", self->x, self->y);
}
int main(){
    i32* mamam = NEW(i32, 5);
}