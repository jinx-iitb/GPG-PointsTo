
int *p,*q,a,b;

void  f(int n){

if(n!=0) { 
   p=q;
   q=&a;
   f(--n);
  }
else p=&b;	
}

int main(){

  f(5);


}