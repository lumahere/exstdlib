#define EXSTD_STRINGS
#include "exstd.h"

String _String_constructor(str literal){
    usize inlen = strlen(literal); 
    char* heap = malloc(inlen + _STR_ALLOC_EXTRA);
    char* mdata = memcpy(heap, literal, inlen);
    String res = {inlen, inlen + _STR_ALLOC_EXTRA, mdata, _internal_string_append, _internal_string_extend, _internal_string_drop, _internal_string_get};
    return res;
}

void _String_destructor(String* self){
    self->drop(self);
}

void _internal_string_append(String* self, const char* to_append){
    usize inlen = strlen(to_append);
    if(self->capacity < inlen + self->len + 1){
        self->capacity += self->capacity + inlen + _STR_ALLOC_EXTRA;
        self->data = realloc(self->data, self->capacity);
    }
        memcpy(self->data+self->len, to_append, inlen);
        self->len += inlen;
        self->data[self->capacity] = '\0';
}
void  _internal_string_extend(struct String* self, struct String* other){

    if(self->capacity < other->len + self->len + 1){
        self->capacity += self->capacity + other->len + _STR_ALLOC_EXTRA;
        self->data = realloc(self->data, self->capacity);
        self->data = memcpy(self->data+self->len, other->data, other->len);
        self->len += other->len;
        self->data[self->capacity] = '\0';
    }
}
void  _internal_string_drop(struct String* self){
    free(self->data);
    self->capacity = 0;
    self->len = 0;
}
const char* _internal_string_get(struct String* self){
    return self->data;
}