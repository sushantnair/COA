#include <stdio.h>
int q = 0,m = 0, c = 0, q1 = 0, m1 = 0, com[10] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Q[10] = {0}, anumcp[10] = {0}, M[10] = {0};
int OCQ[10] = {0}, TCM[10] = {0}, pro[10] = {0}, res[10] = {0};
//q is the Multiplier, m is the multiplicand, c is the carry; 
void binary(){
     q1 = q;
     m1 = m;
     int r, r2, i, temp;
     for (i = 0; i < 10; i++){
           Q[i] = q1 % 2;
           anumcp[i] = q1 % 2;
           q1 = q1 / 2;
           M[i] = m1 % 2;
           m1 = m1 / 2;
           if(M[i] == 0){
                TCM[i] = 1;
           }
           if(Q[i] == 0){
                OCQ[i] =1;
           }
     }
   //part for two's complementing
   c = 0;
   for ( i = 0; i < 10; i++){
           res[i] = com[i]+ TCM[i] + c;
           if(res[i] >= 2){
                c = 1;
           }
           else
                c = 0;
           res[i] = res[i] % 2;
     }
   for (i = 9; i >= 0; i--){
     bcomp[i] = res[i];
   }
   //in case of negative inputs
   if (q < 0){
      c = 0;
     for (i = 9; i >= 0; i--){
           res[i] = 0;
     }
     for ( i = 0; i < 10; i++){
           res[i] = com[i] + OCQ[i] + c;
           if (res[i] >= 2){
                c = 1;
           }
           else
                c = 0;
           res[i] = res[i]%2;
     }
     for (i = 9; i >= 0; i--){
           Q[i] = res[i];
           anumcp[i] = res[i];
     }
 
   }
   if(m < 0){
     for (i = 0; i < 10; i++){
           temp = M[i];
           M[i] = TCM[i];
           TCMi] = temp;
     }
   }
}
void add(int num[]){
    int i;
    c = 0;
    for ( i = 0; i < 10; i++){
           res[i] = pro[i] + num[i] + c;
           if (res[i] >= 2){
                c = 1;
           }
           else{
                c = 0;
           } 
           res[i] = res[i]%2;
     }
     for (i = 9; i >= 0; i--){
         pro[i] = res[i];
         printf("%d",pro[i]);
     }
   printf(":");
   for (i = 9; i >= 0; i--){
           printf("%d", anumcp[i]);
     }
}
void arshift(){//for arithmetic shift right
    int temp = pro[9], temp2 = pro[0], i;
    for (i = 1; i < 10  ; i++){//shift the MSB of product
       pro[i-1] = pro[i];
    }
    pro[9] = temp;
    for (i = 1; i < 10  ; i++){//shift the LSB of product
        anumcp[i-1] = anumcp[i];
    }
    anumcp[9] = temp2;
    printf("\nAR-SHIFT: ");//display together
    for (i = 9; i >= 0; i--){
        printf("%d",pro[i]);
    }
    printf(":");
    for(i = 9; i >= 0; i--){
        printf("%d", anumcp[i]);
    }
}
 
void main(){
   int i, q_ = 0;
   printf("\nEnter two numbers, each less than 511, to multiply using Booth's Algorithm: ");
   //simulating for two numbers each below 16
   do{
        printf("\nEnter Multiplier Q: ");
        scanf("%d",&q);
        printf("Enter Multiplicand M: ");
        scanf("%d", &m);
     }while(q >=511 || m >=511);
 
    printf("\nExpected product = %d", q * m);
    binary();
    printf("\n\nBinary Equivalents are: ");
    printf("\nQ = ");
    for (i = 9; i >= 0; i--){
        printf("%d", Q[i]);
    }
    printf("\nM = ");
    for (i = 9; i >= 0; i--){
        printf("%d", M[i]);
    }
    printf("\n2's complement of M = ");//2's Complement of B => B is the Multiplicand as A = A - M => A = A + 2C(M)
    for (i = 9; i >= 0; i--){
        printf("%d", TCM[i]);
    }
    printf("\n\n");
    for (i = 0;i < 10; i++){
           if (Q[i] == q_){//just shift for 00 or 11
               printf("\n-->");
               arshift();
               q_ = Q[i];
           }
           else if(Q[i] == 1 && q_ == 0){//subtract and shift for 10
              printf("\n-->");
              printf("\nSUB B: ");
              add(TCM);//add two's complement to implement subtraction
              arshift();
              q_ = Q[i];
           }
           else{//add ans shift for 01
              printf("\n-->");
              printf("\nADD B: ");
              add(M);
              arshift();
              q_ = Q[i];
           }
     }
 
     printf("\nProduct is = ");
     for (i = 9; i >= 0; i--){
           printf("%d", pro[i]);
     }
     for (i = 9; i >= 0; i--){
           printf("%d", anumcp[i]);
     }
}
