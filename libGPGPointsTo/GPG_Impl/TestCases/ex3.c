#include <stdio.h>

int *a, *b, *c;

struct abc{
int *d;
int *e;
};

int f(struct abc *st){
int* temp = st->d;
st->d = b;
st->e = temp;
//f(st);
return 0;
}

int main(){
    int *p;
    int x = 5;
    int y = 6;
    struct abc st;
    st.d = &x;
    st.e = &y;
    f(&st);
    p = &x;
    *p = 6;
    printf("%p %d", p, *p);
    return 1;
}
