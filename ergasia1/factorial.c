#include<stdio.h>
#define N 4

//Factorial Calculation
 
int main(){
   int fact = 1;
   
   if (N == 0){
      fact = 1;
   }else{
      for(int i = 1; i <= N; i++){
         fact = fact * i;
      }
   }

   printf("The factorial of %d is %d", N, fact);
}
