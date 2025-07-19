#include <stdio.h>
#include <math.h>
#include <stdbool.h>

struct Tuple {
    double min;
    double max;
};

struct Tuple get_min_max(double *array, int size){
    double min = INFINITY;
    double max = -INFINITY;
    for(int i = 0; i < size; i ++){
	if(array[i] < min){
	    min = array[i];
	}
	else if (array[i] >= max){
	    max = array[i];
	}
    }
    struct Tuple tuple = {min, max};
    return tuple;
}

double scale_in_range_01(double x, double a, double b){
    return (x - a)/(b - a);
}

int get_index_by_value(double value, double *array, int size){
    for(int i = 0; i < size; i++){
	if(value == array[i]){
	    return i;
	}
    }
    return -1;
}

void show_scatter_plot(double *x, int size_x, double *y, int size_y, int term_width, int term_height){
    struct Tuple tuple_x = get_min_max(x, size_x);
    struct Tuple tuple_y = get_min_max(y, size_y);

    double scaled_x[size_x];
    double scaled_y[size_y];


    for(int i = 0; i < size_y; i++){
	scaled_x[i] = (int)(scale_in_range_01(x[i], tuple_x.min, tuple_x.max) * term_width);
    }
    for(int i = 0; i < size_y; i++){
	scaled_y[i] = (int)(scale_in_range_01(y[i], tuple_y.min, tuple_y.max) * term_height);
    }

    // int scaled_x_size = sizeof(scaled_x) / sizeof(scaled_x[0]);
    int scaled_y_size = sizeof(scaled_y) / sizeof(scaled_y[0]);
    char row_buffer[term_width + 1];
    
    for(int i = term_height; i > -1; i--){
	for(int j = 0; j < term_width + 1; j++){
	    row_buffer[j] = ' ';
	}
	row_buffer[term_width + 1] = '\n';

	for(int j = 0; j < scaled_y_size; j++){
	    if(!(scaled_y[j] == i)){
		continue;
	    }
	    int x_value = (int)scaled_x[j];
	    if (x_value < term_width + 1) {
		row_buffer[x_value] = '*';
            }
	}

	for (int j = 0; j < term_width + 1; j++) {
            if (row_buffer[j] == '*') {
                printf("\x1b[1;31;41m*");
            } else {
                printf("\x1b[1;30;40m*");
            }
        }
	printf("\x1b[1;39;49m\n");
    }
}

double* range(int a, int b, int n);

int main(){
    double x[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    double y[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int x_size = sizeof(x) / sizeof(x[0]);
    int y_size = sizeof(y) / sizeof(y[0]);

    int term_width = 120;
    int term_height = 30;

    show_scatter_plot(x, x_size, y, y_size, term_width, term_height);
    return 69;
}
