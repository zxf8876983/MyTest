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

typedef struct protocolIO{	

	int b1,b2,
		bc1[fc1_col],bc2[fc2_col],
		w1[w_len][w_len],w2[w_len][w_len],
		fc2[fc1_col][fc2_col],face[x_row][x_col];
	int fc1_1[fc1_row][fc1_col/2],fc1_2[fc1_row][fc1_col/2];
	int y_conv[y_col];
    int res;
} protocolIO;

void nn(void* args);
