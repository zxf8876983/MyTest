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

int max(int array[],int n);

 int max(int array[],int n){
  int i;
  int index=0;
  int maxnum=array[0];
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
 int t=10000;
 float W[w_row][w_col];
 float B[b_row][b_col];
 float X[x_row][x_col];
 float Y[y_row][y_col];
 
 int w[w_row][w_col];
 int b[b_row][b_col];
 int x[x_row][x_col];
 int y[y_row][y_col];
 
 int i,j,k;

 if((fp=fopen("parameter/W.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<w_row;i++){
    for(j=0;j<w_col;j++){
     fscanf(fp,"%f",&W[i][j]);
     w[i][j]=(int)(W[i][j]*t);
    }
   }
 fclose(fp);
}


 if((fp=fopen("parameter/b.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<b_row;i++){
    for(j=0;j<b_col;j++){
     fscanf(fp,"%f",&B[i][j]);
     b[i][j]=(int)(B[i][j]*t);
     //printf("%d\t",b[i][j]);
    }
   }
 fclose(fp);
}
 

 if((fp=fopen("parameter/x.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<x_row;i++){
    for(j=0;j<x_col;j++){
     fscanf(fp,"%f",&X[i][j]);
     x[i][j]=(int)(X[i][j]*t);
    }
   }
 fclose(fp);
}
  

 if((fp=fopen("parameter/y.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<y_row;i++){
    for(j=0;j<y_col;j++){
     fscanf(fp,"%f",&Y[i][j]);
     y[i][j]=(int)(Y[i][j]*t);
    }
   }
 fclose(fp);
}

//float m1[10][10];
int m1[10][10];
//int m2[10][1];
//m1=x*w+b
for(i=0;i<x_row;i++){
   for(j=0;j<w_col;j++){
     long s=0;
     for(k=0;k<x_col;k++){
       s+=(x[i][k]*w[k][j]);
       printf("%ld\t",s);
     }
     m1[i][j]=s/t+b[0][j];
     //m1[i][j]=s;
     //printf("%f\t",s);
	 printf("%d\t",m1[i][j]);
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
    //printf("%f\t",y[i][j]);
    printf("%d\t",y[i][j]);
  }
  printf("\n");
}
for(i=0;i<10;i++){
  for(j=0;j<10;j++){
    //printf("%f\t",m1[i][j]);
    printf("%d\t",m1[i][j]);
  }
  printf("\n");
}

}
