
void f(){

}

void g(){
  f();
}

void h(){
   f();
   g();
}

void m(){
  f();
}

void n(){

}

void o(){

if(1) o();
}

void q();
void p(){
 if(1) q();
}
void q(){
 if(1) p();
}
int main(){
   h();
   f();
   m();
   n();
   o();
   p();
}
