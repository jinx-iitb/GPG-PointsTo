int *x ,*y, a, b;
void f()
{
    x = &b;
    y = &a;
}
void g()
{
    x = &b;
}
int main()
{
    void (*f_ptr)();
    f_ptr = f;
    x = &a;
    y = &b;
    (*f_ptr)();
    f_ptr = g;
    (*f_ptr)();
    return 0;
}