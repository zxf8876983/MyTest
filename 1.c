#include<stdio.h>
#include<stdlib.h>
 
 
#define w_row 784
#define w_col 10
#define b_row 1
#define b_col 10
#define x_row 10
#define x_col 784
#define y_row 10
#define y_col 10

int max(float array[],int a);

 int max(float array[],int n){
  int i;
  int index=0;
  float maxnum=array[0];
  for(i=1;i<n;i++){
    if(maxnum<array[i]){
      maxnum=array[i];
      index=i;
    }
  }
  return(index);
 }


void main()
{
 FILE *fp;
 float w[w_row][w_col];
 float b[b_row][b_col];
 float x[x_row][x_col];
 float y[y_row][y_col];
 int i,j,k;

 if((fp=fopen("W.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<w_row;i++){
    for(j=0;j<w_col;j++){
     fscanf(fp,"%f",&w[i][j]);
    }
   }
 fclose(fp);
}


 if((fp=fopen("b.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<b_row;i++){
    for(j=0;j<b_col;j++){
     fscanf(fp,"%f",&b[i][j]);
    }
   }
 fclose(fp);
}
 

 if((fp=fopen("x.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<x_row;i++){
    for(j=0;j<x_col;j++){
     fscanf(fp,"%f",&x[i][j]);
    }
   }
 fclose(fp);
}
  

 if((fp=fopen("y.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<y_row;i++){
    for(j=0;j<y_col;j++){
     fscanf(fp,"%f",&y[i][j]);
    }
   }
 fclose(fp);
}

float m1[10][10];
//int m2[10][1];
//m1=x*w+b
for(i=0;i<x_row;i++){
   for(j=0;j<w_col;j++){
     float s=0;
     for(k=0;k<x_col;k++){
       s+=x[i][k]*w[k][j];
     }
     m1[i][j]=s+b[0][j];
     //m1[i][j]=s;
     //printf("%f\t",s);
	 printf("%f\t",m1[i][j]);
   }
   printf("\n");
}
/*
for(i=0;i<10;i++){
  for(j=i;j<10;j++){
    float temp=m1[i][j];
    m1[i][j]=m1[j][i];
    m1[j][i]=temp;
  }
}*/

for(i=0;i<10;i++){
  printf("%d\t%d\n",max(m1[i],10),max(y[i],10));
}

for(i=0;i<10;i++){
  for(j=0;j<10;j++){
    printf("%f\t",y[i][j]);
  }
  printf("\n");
}
for(i=0;i<10;i++){
  for(j=0;j<10;j++){
    printf("%f\t",m1[i][j]);
  }
  printf("\n");
}

}
