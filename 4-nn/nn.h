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

	int bc2[fc2_col],h_fc1[fc1_col],fc2[fc1_col][fc2_col];
	int y_conv[y_col];
    int res;
} protocolIO;

void nn(void* args);
