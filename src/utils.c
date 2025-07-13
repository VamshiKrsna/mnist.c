// definitions of utils functions

#include "utils.h"
#include <stdio.h>

void print_sample_ascii(const Dataset *ds, int index, double threshold) { 
    if (!ds || index < 0 || index >= ds->n) {
        printf("Invalid dataset or index\n");
        return; 
    }

    int rows = ds->r;
    int cols = ds->c; 

    const double *img = ds->images + index * rows * cols;

    printf("Label : %u\n", ds->labels[index]);

    for (int i = 0; i < rows ; ++i){
        for (int j = 0; j < cols ; ++j) {
            double v = img[i * cols + j];
            char ch = (v >= threshold ? '@' : ' ');
            putchar(ch);
        }
        putchar('\n');
    }
    putchar('\n');
}

void normalize_dataset(Dataset *ds, int zero_mean_unit_std) {
    if (!ds || !ds->images) return;
    int n = ds->n;
    int size = ds->r * ds->c;
    if (zero_mean_unit_std) {
        double mean = 0.1307;
        double std = 0.3081;
        for (int i = 0; i < n * size; i++) {
            ds->images[i] = (ds->images[i] - mean) / std;
        }
    } else {
        for (int i = 0; i < n * size; i++) {
            ds->images[i] = ds->images[i]; // already normalized in load_mnist
        }
    }
}

void shuffle_dataset(Dataset *ds) {
    if (!ds || !ds->images || !ds->labels) return;
    int n = ds->n;
    int size = ds->r * ds->c;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // swap images
        for (int k = 0; k < size; k++) {
            double temp = ds->images[i * size + k];
            ds->images[i * size + k] = ds->images[j * size + k];
            ds->images[j * size + k] = temp;
        }
        // swap labels
        uint8_t temp_label = ds->labels[i];
        ds->labels[i] = ds->labels[j];
        ds->labels[j] = temp_label;
    }
}
