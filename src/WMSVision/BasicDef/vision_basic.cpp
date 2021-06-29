#include "vision_basic.h"
#include <stdio.h>
#include <stdlib.h>
vision_basic::vision_basic(){
}

#include "wms_vision_basic.h"
//----------------------------------------------------
wms_Vision_Image*  newImg(wms_Vision_Image_core *p) {
    wms_Vision_Image * newa = (wms_Vision_Image *) malloc(sizeof(wms_Vision_Image));
    newa->ctr = 1;
    newa->img  = p;
    return newa;
}

void *PtrImg(wms_Vision_Image * p) {
    return p->img;
}

wms_Vision_Image  *cpImg(wms_Vision_Image * p) {
    p->ctr++;
    return p;
}

wms_Vision_Image  *cloneImg(wms_Vision_Image * p)
{
   wms_Vision_Image * newa = newImg(   p->img );
   return  newa;
}

int   delImg(wms_Vision_Image * p) {
    if (p->ctr == 1) {
        free(p->img);
        free(p);
    } else {
        p->ctr--;
    }
    return   p->ctr  ;
}

//----------------------------------------------------
ptr*  new_p(void *p) {
    ptr * newa = ( ptr*  )malloc(sizeof(ptr));
    newa->ctr = 1;
    newa->p = p;
    return newa;
}

ptr  *cp(ptr * p) {
    p->ctr++;
    return p;
}

void del(ptr * p) {
    if (p->ctr == 1) {
        free(p->p);
        free(p);
    } else {
        p->ctr--;
    }
}

void delFunc(ptr * p, void (*f)(void*)) {
    if (p->ctr == 1) {
        f(p->p);
        free(p->p);
        free(p);
    } else {
        p->ctr--;
    }
}

void *Ptr(ptr * p) {
    return p->p;
}
//----------------------------------------------------




