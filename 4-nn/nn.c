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
	int h_fc1[fc1_col];
	int fc1_1[fc1_row][fc1_col/2],fc1_2[fc1_row][fc1_col/2];
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
				 //io.face[i][j]=face[i][j];
				 //printf("%d\t",face[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}


	if((fp=fopen("parameter/value0.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<w_len;i++){
			for(j=0;j<w_len;j++){
				 fscanf(fp,"%d",&w1[i][j]);
				 //io.w1[i][j]=w1[i][j];
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
		 //io.b1=b1;
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
				 //io.w2[i][j]=w2[i][j];
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
		 //io.b2=b2;
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

	//fc1_1,fc1_2
	for(i=0;i<fc1_row;i++){
		for(j=0;j<fc1_col/2;j++){
			fc1_1[i][j]=fc1[i][j];
			fc1_2[i][j]=fc1[i][j+fc1_col/2];
		}
	}
	//读取bc1
	if((fp=fopen("parameter/value5.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<fc1_col;i++){
			 fscanf(fp,"%d",&bc1[i]);
			 //io.bc1[i]=bc1[i];
			 //printf("%d\t",bc1[i]);
		}
		fclose(fp);
	}

	int W1[x_row+4][x_col+4]={0};
	int h_conv1[x_row][x_col]={0};
	//填充
	for(i=0;i<x_row;i++){
		for(j=0;j<x_col;j++){
			 W1[i+2][j+2]=face[i][j];
			 //printf("%d\t",W1[i+2][j+2]);
		}
		//printf("\n");
	}
	/*	
	for(i=0;i<x_row+4;i++){
		for(j=0;j<x_col+4;j++){
			 //W1[i+2][j+2]=face[i][j];
			 printf("%d\t",W1[i][j]);
		}
		printf("\n");
	}
	*/

	//conv2d_1
	for(i=2;i<x_row+2;i++){
		for(j=2;j<x_col+2;j++){
			k=0;
			for(m=0;m<5;m++){
				for(n=0;n<5;n++){
			 		k+=w1[m][n]*W1[i-2+m][j-2+n]; //x*w
				}
			}
			h_conv1[i-2][j-2]=k/t+b1;                 //x*w+b
			if(h_conv1[i-2][j-2]<0) h_conv1[i-2][j-2]=0;  //relu
			//printf("%d\t",h_conv1[i][j]);
		}
		//printf("\n");
	}


	/*
	for(i=0;i<x_row;i++){
		for(j=0;j<x_col;j++){
			 printf("%d\t",h_conv1[i][j]);
		}
		printf("\n");
	}
	*/

	
	//maxpool_1
	int h_pool1[x_row_pool1][x_col_pool1];
	for(i=0;i<x_row-1;i+=2){
		for(j=0;j<x_col-1;j+=2){
			k=h_conv1[i][j];
			//printf("%d\n",k);
			for(m=0;m<2;m++){
				for(n=0;n<2;n++){
					if(h_conv1[i+m][j+n]>k){
						k=h_conv1[i+m][j+n];}				
				}			
			}
			h_pool1[i/2][j/2]=k;	
			//printf("%d\t",h_pool1[i/2][j/2]);	
		}
		//printf("\n");
	}

//---------------------------------------------------------
//---------------------------------------------------------

	int W2[x_row_pool1+4][x_col_pool1+4]={0};
	int h_conv2[x_row_pool1][x_col_pool1]={0};
	//填充
	for(i=0;i<x_row_pool1;i++){
		for(j=0;j<x_col_pool1;j++){
			 W2[i+2][j+2]=h_pool1[i][j];
			 //printf("%d\t",W1[i+2][j+2]);
		}
		//printf("\n");
	}

	//conv2d_2
	for(i=2;i<x_row_pool1+2;i++){
		for(j=2;j<x_col_pool1+2;j++){
			k=0;
			for(m=0;m<5;m++){
				for(n=0;n<5;n++){
			 		k+=w2[m][n]*W2[i-2+m][j-2+n]; //x*w
				}
			}
			h_conv2[i-2][j-2]=k/t+b2;                 //x*w+b
			if(h_conv2[i-2][j-2]<0) h_conv2[i-2][j-2]=0;  //relu
			//printf("%d\t",h_conv2[i-2][j-2]);
		}
		//printf("\n");
	}

	//maxpool_2
	int h_pool2[x_row_pool2][x_col_pool2];
	for(i=0;i<x_row_pool1-1;i+=2){
		for(j=0;j<x_col_pool1-1;j+=2){
			k=h_conv2[i][j];
			//printf("%d\n",k);
			for(m=0;m<2;m++){
				for(n=0;n<2;n++){
					if(h_conv2[i+m][j+n]>k){
						k=h_conv2[i+m][j+n];}				
				}			
			}
			h_pool2[i/2][j/2]=k;	
			//printf("%d\t",h_pool2[i/2][j/2]);	
		}
		//printf("\n");
	}
//------------------------------------------------------------------
//------------------------------------------------------------------
 	int h_pool2_flat[fc1_row];
	for(i=0;i<x_row_pool2;i++){
		for(j=0;j<x_col_pool2;j++){
			h_pool2_flat[i*x_col_pool2+j]=h_pool2[i][j];
			//printf("%d\t",h_pool2_flat[i*x_row_pool2+j]);
		}
		//printf("\n");
	}


	for(i=0;i<fc1_col/2;i++){
		for(j=0;j<fc1_row;j++){
			h_fc1[i]+=h_pool2_flat[j]*fc1_1[j][i];
			h_fc1[i+fc1_col/2]+=h_pool2_flat[j]*fc1_2[j][i];
		}
		h_fc1[i]=h_fc1[i]/t+bc1[i];
		h_fc1[i+fc1_col/2]=h_fc1[i+fc1_col/2]/t+bc1[i+fc1_col/2];
		if(h_fc1[i]<0) h_fc1[i]=0;
		if(h_fc1[i+fc1_col/2]<0) h_fc1[i+fc1_col/2]=0;                //relu
		//printf("%d\t",h_fc1[i]);
	}

	for(i=0;i<fc1_col;i++){
		 io.h_fc1[i]=h_fc1[i];
		 //printf("%d\t",h_fc1[i]);
	}
	//printf("\n");


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

  if(currentParty==2){
	  for(i=0;i<y_col;i++){
		fprintf(stderr,"%d\t",io.y_conv[i]);
		if((i+1)%8==0) printf("\n");
	  }
	  printf("\n\n");
	  if(io.res==0) printf("你是编号为0的人");
	  printf("\n");
  	  //fprintf(stderr,"Result: %d\n",io.res);
  }
  end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,"Elapsed Time: %f\n",cpu_time_used);
  return 0;
}
