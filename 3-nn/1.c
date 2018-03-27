#include<stdio.h>
#include<stdlib.h>
 
 
#define w_len 5
#define fc1_row 168
#define fc1_col 70
#define fc2_row 70
#define fc2_col 41
#define x_row 56
#define x_col 48
#define x_row_pool1 28
#define x_col_pool1 24
#define x_row_pool2 14
#define x_col_pool2 12
#define y_row 1
#define y_col 41

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



void main(){

	FILE *fp;
	int t=1000;
	int b1,b2,
		bc1[fc1_col],bc2[fc2_col],
		w1[w_len][w_len],w2[w_len][w_len],
		fc2[fc1_col][fc2_col],face[x_row][x_col];
	int fc1[fc1_row][fc1_col];
	int fc1_1[fc1_row][fc1_col/2],fc1_2[fc1_row][fc1_col/2];
	int face_length=x_row*x_col;
	int i,j,m,n,k;
	//读取w1
	if((fp=fopen("parameter/value0.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<w_len;i++){
			for(j=0;j<w_len;j++){
				 fscanf(fp,"%d",&w1[i][j]);
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
				 //printf("%d\t",fc1[i][j]);
			}
			//printf("\n");
		}
		fclose(fp);
	}

	//fc1_1,fc1_2,fc1_3
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
			 //printf("%d\t",bc1[i]);
		}
	}
	//读取fc2
	if((fp=fopen("parameter/value6.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<fc2_row;i++){
			for(j=0;j<fc2_col;j++){
				 fscanf(fp,"%d",&fc2[i][j]);
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
			 //printf("%d\t",bc2[i]);
		}
	}
	//face
	if((fp=fopen("parameter/face.txt","r"))==NULL){ 
		printf(" can't open\n");
		exit(0);
	}else{
		for(i=0;i<x_row;i++){
			for(j=0;j<x_col;j++){
				 fscanf(fp,"%d",&face[i][j]);
				 //printf("%d\t",face[i][j]);
			}
			//printf("\n");
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

	int h_fc1[fc1_col];

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

	int y_conv[fc2_col];
	for(i=0;i<fc2_col;i++){
		for(j=0;j<fc2_row;j++){
			y_conv[i]+=h_fc1[j]*fc2[j][i];
		}
		y_conv[i]=y_conv[i]/t+bc2[i];
		printf("%d\t",y_conv[i]);
	}
	printf("\n");

}
