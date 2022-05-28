
 int *p,x,y,z;
int main(){
	
    p=&x;

    if(y)
     p=&y;
    else
     x=20;

    p=&z;

}