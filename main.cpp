#include <stdio.h>
#include "logger.cpp"

//Define some contants
#define N 5
#define M 3
#define TRUE 1
#define FALSE 0


//Global variables
double orders[N][M];

void generate_orders(double[N], double[N], double[N]);
void sort_orders(double*);
void initialize_orders(void);
void show_orders(void);
int is_in_list(double[N], double);
int test_generate_order(void);
void set_up(void);
int assert_equals(void);


int main(void)
{
    logger(INFO, "Running main()\n");
    if (test_generate_order() == FALSE)
    {
        logger(ASSERTION_ERROR, "Test failed");
        return FALSE;
    }
    
    logger(SUCCESS, "Test passed");
    show_orders();
    return TRUE;
}

void initialize_orders()
{
    logger(INFO, "Initializing orders\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) orders[i][j] = 0;
    }
}

void sort_orders(double *total_values)
{
    logger(INFO, "Sorting orders\n");
    int steps = 0;
    double pawn = -1.0;

    for (int i=0; i < N-1; i++)
    {
        for (int j=i+1; j < N;)
        {
            if (total_values[i] > total_values[j])
            {
                pawn = total_values[i];
                total_values[i] = total_values[j];
                total_values[j] = pawn;
                steps++;

            }
            else j++;
        }
    }
}

int is_in_list(double list_items[N], double elem)
{
    for(int i=0; i<N; i++)
    {   
        if(list_items[i] == elem) return i;
    }
    return -1;
}

void generate_orders(double ship_values[N], double item_values[N], double total_values[N])
{
    logger(INFO, "Processing and generating orders\n");

    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++) 
        {
            double sum = item_values[j] + ship_values[i];
            int pos = is_in_list(total_values, sum);

            if (pos != -1) 
            {
                orders[pos][0] = ship_values[i];
                orders[pos][1] = item_values[j];
                orders[pos][2] = total_values[pos];

            }
        }
    }
}

void show_orders(void)
{
    logger(INFO, "Showing orders");
    for (int i=0; i < N; i++)
    {
        printf("{pedido %d: { ship_value: ", i+1);
        for (int j=0; j < M; j++)
        {
	        if (j == M-1) printf(" %f ", orders[i][j]);
	        else printf(" %f, ", orders[i][j]);
		
        }
        printf("} }\n");
    }
}


void set_up(void)
{
    //Declaring variables
    double ship_values[N] = {25, 30, 20, 10, 15};
    double item_values[N] = {50, 51, 52, 53, 54};
    double total_values[N] = {61,65,74,77,83};

    initialize_orders();
    sort_orders(total_values);
    generate_orders(ship_values, item_values, total_values);


}

int assert_equals(void)
{
    double test_orders[N][M] = {
        {10, 51, 61},
        {15, 50, 65},
        {20, 54, 74},
        {25, 52, 77},
        {30, 53, 83}
    };

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (orders[i][j] != test_orders[i][j]) return FALSE;
        }
    }

    return TRUE;
}


int test_generate_order()
{
    logger(INFO, "Initializing tests");

    set_up();
    int test_result = assert_equals();

    return test_result;

}
