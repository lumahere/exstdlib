# CEXTLIB Extended C Library
An attempt to expand the C std library with maybe easier to use interface. probably useless. 

## EXAMPLE
```c
    #define EXSTD_FULL
    #include "exstd.h"

    CLASS(Point, 
        int x;
        int y;
    );
    
    CONSTRUCTOR(Point)(int x, int y){
        return (Point){x,y};
    }

    int main(){
        Point a = INSTANTIATE(Point, 5, 5);
        int* res = NEW(int, 6);

        DEFER(DELETE(res)){
            printf("%d %d -> %d\n", a.x, a.y, *res);
        }

        return 0;

    }

```