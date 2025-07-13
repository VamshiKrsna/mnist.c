#include "mnist_loader.h"
#include "utils.h"
#include <stdio.h>

int main() {
    Dataset ds;
    if (load_mnist("data/train-images.idx3-ubyte", "data/train-labels.idx1-ubyte", &ds)) {
        fprintf(stderr, "Failed to load MNIST data\n");
        return 1;
    }
    normalize_dataset(&ds, 0);
    shuffle_dataset(&ds);

    printf("Loaded %d samples (%dx%d)\n", ds.n, ds.r, ds.c);
    print_sample_ascii(&ds, 0, 0.5);
    print_sample_ascii(&ds, 1, 0.5);
    print_sample_ascii(&ds, 2, 0.5);
    print_sample_ascii(&ds, 3, 0.5);


    free_mnist(&ds);
    return 0;
}

// Above test is for printing the ascii version of dataset samples