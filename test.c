#define EXSTD_FULL
#include "exstd.h"

CLASS(Res, 
    int x;
    int y;
    CLASS_METHOD(int, get_vars);
);

DECLARE_CLASS_METHOD(int, Res, get_vars){
    return 2;
}

CONSTRUCTOR(Res, int a, int b){
    self->x = a;
    self->y = b; 
    BIND_CLASS_METHOD(Res, get_vars);
}

DESTRUCTOR(Res){
    printf("Res is destroyed with value: %d %d\n", self->x, self->y);
}
int main(){
    i32* mamam = NEW(i32, 5);
    Res a = INSTANTIATE(Res, 2 ,3);
    printf("%d\n", a.get_vars() );
    DESTROY(Res, &a);
}