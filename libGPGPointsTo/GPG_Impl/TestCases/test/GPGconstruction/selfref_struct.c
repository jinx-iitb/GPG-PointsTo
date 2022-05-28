
//Example collected from geeksforgeeks
#include <stdio.h> 
#include <stdlib.h>

struct node { 
    int data1; 
    char data2; 
    struct node* prev;
    struct node* next; 
}; 

 struct node ob1; // Node1 

 struct node ob2; // Node2 
  
 struct node *ob3;

 struct node *ob6;

 int a[5];

 struct node ob[10];

 int *p;

void f(int **r){

}

int main() 
{ 
    int *q;   
   struct node ob5;
  //  p=&a[0];

  //  q=&a[0];


    f(&q);

    // Initialization 
    //ob1.link = NULL; 
    ob1.data1 = 10; 
    ob1.data2 = 20; 
  
   
    // Initialization 
    //ob2.link = NULL; 
    ob2.data1 = 30; 
    ob2.data2 = 40; 
  
    // Linking ob1 and ob2 
   // ob1.link = &ob2; 
  
    ob3=&ob1;

   // ob1.link->link = &ob5;

    ob3->next = &ob2;

    ob3->next->prev = &ob1;

     ob6 = (struct node *) malloc(sizeof(struct node)*10);

//    ob3->link->link->link = &ob2;

   // a[2]=3;

     //ob[5].link = &ob2;

   // p[3]=10;

   // q[4]=10;

    // Accessing data members of  ob2 using ob1 
   // printf("%d", ob1.link->data1); 
   // printf("\n%d", ob1.link->data2); 
    return 0; 
} 
