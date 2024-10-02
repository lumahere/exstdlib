#ifndef EXSTD_STDLIB
#define EXSTD_STDLIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int usize;
typedef const char* str;

#if defined EXSTD_FULL || defined EXSTD_STRINGS
typedef struct String
{
    usize len;
    usize capacity;
    char* data;    
    //func pointers

    void (*append)(struct String* self, const char* to_append);
    // this copies the extend string
    void (*extend)(struct String* self, struct String* other);
    void (*drop)(struct String* self);
    const char* (*get)(struct String* self);
    
} String;


#define STR(literal) mk_heap_string(literal)

#define _STR_ALLOC_EXTRA 10
String mk_heap_string(str literal);
void _internal_string_append(String* self, const char* to_append);
void  _internal_string_extend(struct String* self, struct String* other);
void  _internal_string_drop(struct String* self);
const char* _internal_string_get(struct String* self);
#endif //EXSTD_STRINGS


#if defined EXSTD_FULL || defined EXSTD_ALLOC
// ##### Works the same way as c++'s new. Redirected to malloc
#define NEW(type, init_value) h_allocninit(sizeof(type), (type[]){init_value})
// ##### Works the same way as c++'s delete. Redirected to free
#define DELETE(var) free(var);

// ### Works almost like zig's defer but also like python's with statement
// it works using a scope and at the end of the scope, the function passed into DEFER will get executed
// you can use this to automatically clean up a resource after scope ends
// ## Example.
// ```c    
//    void* some_resource = NEW(Resource);
//    DEFER(DELETE(some_resource)){
//        work_with_resource(&some_resource);
//        process(&some_resource); 
//    } /*--> some_resource is deallocated here;*/
//    ```
#define DEFER(cleanup_func) for(int _done__ = 0; !_done__; (cleanup_func), _done__ = 1)

    void* h_allocninit(usize size, const void* init_val);

#endif

//WARNING! EXPERIMENTAL!//WARNING! EXPERIMENTAL!//WARNING! EXPERIMENTAL!//WARNING! EXPERIMENTAL!//
#if defined EXSTD_FULL || EXSTD_CLASS

    /* #### EXSTD CLASS 
     ##### a small class implementation for C, very Basic.
     ## EXAMPLE
    
    ``` 
        CLASS(Point,
            int x;
            int y;
        )

        CONSTRUCTOR(Point)(int x, int y){
            return (Point){x,y};
        }

        int main(){
            Point a = INSTANTIATE(Point, 2, 2);
            let smthing = a.x + a.y;
        }
    ```
     */
    #define CLASS(name, members) typedef struct name {members} name; \
        struct name _##name##_constructor(); \
        void _##name##_destructor();
    
    // ### REQUIRED IN EVERY CLASS (even empty)
    // ##### Define a constructor for the struct, constructors have to return the built class
    // ## Example.
    // ```
    //  CONSTRUCTOR(Vector)(int a, int b){
    //      return (Vector){a,b};
    //}
    //```
    #define CONSTRUCTOR(name) struct name _##name##_constructor
        
    #define DESTRUCTOR(name) void _##name##_destructor(struct name* self)
    #define INSTANTIATE(class, Args...) _##class##_constructor(Args)
    // ##### Dont call DESTROY if DESTRUCTOR for its class isn't defined
    #define DESTROY(class, var) _##class##_destructor(var)
    #define DERIVE(base, new_class, new_members) typedef struct new_class {struct base mBaseClass; new_members} new_class;

    //TODO: Make a DERIVED constructor possible also it's Destructor; rethink the whole idea of classes
#endif

#if defined EXSTD_FULL || defined EXSTD_IO
#if !defined EXSTD_FULL && !defined EXSTD_STRINGS   
    #error please define EXSTD_STRINGS to use EXSTD_IO
#endif



#endif

#endif