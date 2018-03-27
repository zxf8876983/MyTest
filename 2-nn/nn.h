#define w_len 5
#define fc1_row 644
#define fc1_col 1024
#define fc2_row 1024
#define fc2_col 41
#define x_row 112
#define x_col 92
#define x_row_pool1 56
#define x_col_pool1 46
#define x_row_pool2 28
#define x_col_pool2 23
#define y_row 1
#define y_col 41

typedef struct protocolIO{	

int b1,b2,
	bc1[fc1_col],bc2[fc2_col],
	w1[w_len][w_len],w2[w_len][w_len],
	fc1[fc1_row][fc1_col],fc2[fc1_col][fc2_col],
	face[x_row][x_col];
    int res;
} protocolIO;

void nn(void* args);
