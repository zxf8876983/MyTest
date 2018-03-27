#include<stdio.h>
#include<obliv.h>
#include <time.h>
#include"nn.h"
#include"../../obliv-c/test/oblivc/common/util.h"

int main(int argc,char *argv[])
{
  ProtocolDesc pd;
  protocolIO io;
  FILE *fp;
  float w[w_row][w_col];
  float b[b_row][b_col];
  float x[x_row][x_col];
  int i,j,k;
  int t=10000;
/*
  if(argc<4)
  { if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Server location missing\n");
    else fprintf(stderr,"string missing\n");
    fprintf(stderr,"Usage: %s <port> <--|remote_host> <int>\n",argv[0]);
    return 1;
  }*/

/*
const char* remote_host = (strcmp(argv[2],"--")?argv[2]:NULL);
ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);
int currentParty = (remote_host?2:1);
*/
int currentParty = (argv[1][0]=='1')?1:2;

if(currentParty==1){

 if((fp=fopen("parameter/W.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<w_row;i++){
    for(j=0;j<w_col;j++){
     fscanf(fp,"%f",&w[i][j]);
     io.w[i][j]=(int)(w[i][j]*t);
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
     fscanf(fp,"%f",&b[i][j]);
     io.b[i][j]=(int)(b[i][j]*t);
     //printf("%d\t",b[i][j]);
    }
   }
 fclose(fp);
}
protocolAcceptTcp2P(&pd,argv[2]);
}
 
if(currentParty==2){

 if((fp=fopen("parameter/x.txt","r"))==NULL)
 { 
  printf(" can't open");
  exit(0);
 }else{
   for(i=0;i<x_row;i++){
    for(j=0;j<x_col;j++){
     fscanf(fp,"%f",&x[i][j]);
     io.x[i][j]=(int)(x[i][j]*t);
    }
   }
 fclose(fp);
}
protocolConnectTcp2P(&pd,argv[3],argv[2]);
}

  clock_t start, end;
  start = clock();
  //sscanf(argv[3],"%f",&io.value);
  setCurrentParty(&pd,currentParty);
  execYaoProtocol(&pd,nn,&io);
  cleanupProtocol(&pd);
  for(i=0;i<10;i++){
    fprintf(stderr,"Result: %d\n",io.res[i]);
  }
  end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,"Elapsed Time: %f\n",cpu_time_used);
  return 0;
}
