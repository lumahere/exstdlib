#define EXSTD_FULL
#include "exstd.h"

CLASS(Res, 
    String* a;
    int b;)

CONSTRUCTOR(Res)(int a, int b){
    String* bs = NEW(String, STR("Hello"));
    return (Res){bs,b};    
}

DESTRUCTOR(Res){
    self->a->drop(self->a);
}

int main(){
    Res a = INSTANTIATE(Res, 2, 3);
    DEFER(DESTROY(Res, &a)){
        printf("%s\n",a.a->get(a.a));
    }
}