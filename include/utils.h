// useful utilities definitions

#ifndef UTILS_H
#define UTILS_H 

#include<stdint.h>
#include<stdlib.h>

typedef struct {
    int n; // no. of samples
    int r,c; // img dimensions (28x28)
    double *images; // normalized images -> flattened[n][r * c]
    uint8_t *labels; // corresponding labels
} Dataset;

// normalizing raw pixel vals of images inplace
void normalize_dataset(Dataset *ds, int zero_mean_unit_std);
// Dataset - dataset struct, 
// zero_mean_unit_std - 0/1 - true : x = (x-0.1307)/0.3081
// given that mean and std of MNIST is already known (from DS stack exchange).
// zero_mean_unit_std - false : x = x/255.0 -> map [0,1]

// shuffling dataset in place (using fisher yates aka knuth's shuffle)
void shuffle_dataset(Dataset *ds); 

// sampling a mini batch
// copy 'batch_size' images + labels 
// start at index 'start'
// images_out, labels_out must be freed 
void sample_batch(Dataset *ds, int start, int batch_size, double **images_out, double **labels_out);


// commandline printing of images as ascii (lets try)
void print_sample_ascii(const Dataset *ds, int index, double threshold);

#endif //UTILS_H