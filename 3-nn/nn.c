#include<stdio.h>
#include<obliv.h>
#include <time.h>
#include"nn.h"
#include"../../obliv-c/test/oblivc/common/util.h"

int main(int argc,char *argv[]){
	ProtocolDesc pd;
	protocolIO io;
	FILE *fp;
	int t=1000;

	int b1,b2,
		bc1[fc1_col],bc2[fc2_col],
		w1[w_len][w_len],w2[w_len][w_len],
		fc1[fc1_row][fc1_col],fc2[fc1_col][fc2_col],
		face[x_row][x_col];
	int fc1_1[fc1_row][fc1_col/3],fc1_2[fc1_row][fc1_col/3];
	int face_length=x_row*x_col;
	int i,j,m,n,k;
/*
  if(argc<4)
  { if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Server location missing\n");
    else fprintf(stderr,"string missing\n");
    fprintf(stderr,"Usage: %s <port> <--|remote_host> <int>\n",argv[0]);
    return 1;
  }*/

/*
const char* remote_host = (strcmp(argv[2],"--")?NULL:argv[2]);
ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);
int currentParty = (remote_host?2:1);
*/

int currentParty = (argv[1][0]=='1')?1:2;

if(currentParty==1){
	//读取w1

 	if((fp=fopen("parameter/value0.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<w_len;i++){
			for(j=0;j<w_len;j++){
				 fscanf(fp,"%d",&w1[i][j]);
				 io.w1[i][j]=w1[i][j];
				 //printf("%d\t",w1[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}
	//读取b1
	if((fp=fopen("parameter/value1.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		 fscanf(fp,"%d",&b1);
		 io.b1=b1;
		 //printf("%d\n",b1);
		 fclose(fp);
	}

	//读取w2
	if((fp=fopen("parameter/value2.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<w_len;i++){
			for(j=0;j<w_len;j++){
				 fscanf(fp,"%d",&w2[i][j]);
				 io.w2[i][j]=w2[i][j];
				 //printf("%d\t",w2[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}
	//读取b2
	if((fp=fopen("parameter/value3.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		 fscanf(fp,"%d",&b2);
		 io.b2=b2;
		 //printf("%d\n",b2);
		 fclose(fp);
	}

	//读取fc1
	if((fp=fopen("parameter/value4.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<fc1_row;i++){
			for(j=0;j<fc1_col;j++){
				 fscanf(fp,"%d",&fc1[i][j]);
				 //io.fc1[i][j]=fc1[i][j];
				 //printf("%d\t",fc1[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}

	//fc1_1,fc1_2,fc1_3
	for(i=0;i<fc1_row;i++){
		for(j=0;j<fc1_col/2;j++){
			io.fc1_1[i][j]=fc1[i][j];
			io.fc1_2[i][j]=fc1[i][j+fc1_col/2];
		}
	}
	//读取bc1
	if((fp=fopen("parameter/value5.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<fc1_col;i++){
			 fscanf(fp,"%d",&bc1[i]);
			 io.bc1[i]=bc1[i];
			 //printf("%d\t",bc1[i]);
		}
		fclose(fp);
	}
	//读取fc2
	if((fp=fopen("parameter/value6.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<fc2_row;i++){
			for(j=0;j<fc2_col;j++){
				 fscanf(fp,"%d",&fc2[i][j]);
				 io.fc2[i][j]=fc2[i][j];
				 //printf("%d\t",fc2[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}
	//读取bc2
	if((fp=fopen("parameter/value7.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<fc2_col;i++){
			 fscanf(fp,"%d",&bc2[i]);
			 io.bc2[i]=bc2[i];
			 //printf("%d\t",bc2[i]);
		}
		fclose(fp);
	}

protocolAcceptTcp2P(&pd,argv[2]);

}
 
if(currentParty==2){

	if((fp=fopen("parameter/face.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<x_row;i++){
			for(j=0;j<x_col;j++){
				 fscanf(fp,"%d",&face[i][j]);
				 io.face[i][j]=face[i][j];
				 //printf("%d\t",face[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}

protocolConnectTcp2P(&pd,argv[3],argv[2]);
}

  clock_t start, end;
  start = clock();
  //sscanf(argv[3],"%f",&io.value);
  //protocolUseStdio(&pd);
  setCurrentParty(&pd,currentParty);
  execYaoProtocol(&pd,nn,&io);
  cleanupProtocol(&pd);
  //fprintf(stderr,"Result: %d\n",io.res);

  for(i=0;i<y_col;i++){
    fprintf(stderr,"%d\t",io.y_conv[i]);
  }
  printf("\n");
  fprintf(stderr,"Result: %d\n",io.res);
  end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,"Elapsed Time: %f\n",cpu_time_used);
  return 0;
}
