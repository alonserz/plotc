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

double linear_interpolation(double x, double x1, double y1, double x2, double y2){
    return y1 + ((y2 - y1)/(x2 - x1)) * (x - x1);
}

double scale_in_range_01(double x, double a, double b){
    return (x - a)/(b - a);
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
void show_line_plot(double *x, int size_x, double *y, int size_y, int term_width, int term_height){
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

    int scaled_x_size = sizeof(scaled_x) / sizeof(scaled_x[0]);
    // int scaled_y_size = sizeof(scaled_y) / sizeof(scaled_y[0]);
    char row_buffer[term_width + 1];
    

    for(int i = term_height; i > -1; i--){
	for(int j = 0; j < term_width + 1; j++){
	    row_buffer[j] = ' ';
	}
	row_buffer[term_width + 1] = '\n';

	int offset = 0;
	for(int j = 0; j < scaled_x_size; j++){

	    double x1 = scaled_x[offset];
	    double y1 = scaled_y[offset];
	    double x2 = scaled_x[offset + 1];
	    double y2 = scaled_y[offset + 1];
	    offset++;
	    for(int k = x1; k < x2; k++){
		int res = (int)linear_interpolation(k, x1, y1, x2, y2);
		if(!(res == i)) continue;
		row_buffer[k] = '*';
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
int main(){
    double x[] = {-2 * M_PI, (-3 * M_PI) / 2, -1 * M_PI, (-1 * M_PI) / 2, 0, M_PI / 2, M_PI, (3 * M_PI) / 2, 2 * M_PI};
    int x_size = sizeof(x) / sizeof(x[0]);
    double y[x_size];
    for(int i = 0; i < x_size; i++){
	y[i] = sin(x[i]);
    }
    int y_size = sizeof(y) / sizeof(y[0]);

    int term_width = 120;
    int term_height = 25;

    show_line_plot(x, x_size, y, y_size, term_width, term_height);
    return 69;
}
