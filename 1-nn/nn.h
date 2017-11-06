#define w_row 784
#define w_col 10
#define b_row 1
#define b_col 10
#define x_row 10
#define x_col 784
#define y_row 10
#define y_col 10

typedef struct protocolIO
{ int w[w_row][w_col],b[b_row][b_col],x[x_row][x_col];
  int res[10];
} protocolIO;

void nn(void* args);

