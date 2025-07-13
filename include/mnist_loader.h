// Loads images, labels and data to train the model

#ifndef MNIST_LOADER_H 
#define MNIST_LOADER_H 

#include "utils.h"


// loads mnist images and labels IDX paths into a dataset struct
// 0 - success, nonzero - error
int load_mnist(const char *img_path, const char *lbl_path, Dataset *ds);

void free_mnist(Dataset *ds); // destroys ds struct 

#endif 