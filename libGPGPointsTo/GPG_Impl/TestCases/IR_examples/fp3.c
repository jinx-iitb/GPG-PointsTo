#include <stdio.h>
int *x, *y, a, b;
int (*f_ptr)();
int h(){
  x = &b;
  return 0;  
}
int f(){
    x = &a;
    y = &b;
    return 0;
}
int g(){
    if(a > 10)
	    f_ptr = &f;
    else
        f_ptr = &h;	    
    return 0;
}
int main()
{
    x = &b;
    y = &a;
    g();
    (*f_ptr)();
    return 0;
}
