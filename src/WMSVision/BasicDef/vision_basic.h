#ifndef VISION_BASIC_H
#define VISION_BASIC_H

#include "wms_vision_basic.h"
class vision_basic
{
public:
    vision_basic();
};



typedef  struct  Stru_Image{
    wms_Vision_Image_core * img;
     int ctr;
}wms_Vision_Image;

// 数组
typedef  struct  Stru_array_float{
    float * data;
    int nums;
}sdk_Vision_array_float;

//-------------------------------------------
typedef
struct stru_ptr {
    int ctr;
    void *p;
}ptr;

#define T ptr*

//typedef struct T *T;

// p is a heap-allocated pointer.
// passing a reference to a stack-allocated
// variable will cause an error when
// the ptr tries to free p.
//
// Return a reference-counted pointer
// initialized to point at p.
T new_p(void *p);

// Increase the reference count
// of p and return a pointer to p.
T cp(T p);

// Decrease the reference count
// of p. If the reference count
// has reached 0, free the contained
// pointer
void del(T p);

// Same as del, except that *f
// is called on the contained pointer
// before it is freed
void delFunc(T p, void (*f)(void*));

// Return the contained pointer.
void* Ptr(T p);


//--------------------------------------------------







#endif // VISION_BASIC_H
