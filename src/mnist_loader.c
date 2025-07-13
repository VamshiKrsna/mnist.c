// definition of mnist dataset handling utils.

#include "mnist_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

// reads idx file into a buffer and returns dimensions
static int read_idx(const char *path, uint8_t **out, int *ndims, int **dims) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    uint32_t magic;
    fread(&magic, 4, 1, f);
    magic = ntohl(magic);
    *ndims = magic & 0xFF;
    *dims = malloc((*ndims) * sizeof(int));
    for (int i = 0; i < *ndims; i++) {
        uint32_t d; fread(&d, 4, 1, f);
        (*dims)[i] = ntohl(d);
    }
    size_t total = 1;
    for (int i = 0; i < *ndims; i++) total *= (*dims)[i];
    *out = malloc(total);
    fread(*out, 1, total, f);
    fclose(f);
    return 0;
}

int load_mnist(const char *img_path, const char *lbl_path, Dataset *ds) {
    uint8_t *img_buf = NULL, *lbl_buf = NULL;
    int nd1, nd2; int *d1 = NULL, *d2 = NULL;
    if (read_idx(img_path, &img_buf, &nd1, &d1) ||
        read_idx(lbl_path, &lbl_buf, &nd2, &d2)) {
        return -1;
    }
    if (nd1 != 3 || nd2 != 1 || d1[0] != d2[0]) {
        return -2;
    }
    int n = d1[0], rows = d1[1], cols = d1[2];
    ds->n = n; ds->r = rows; ds->c = cols;
    ds->images = malloc((size_t)n * rows * cols * sizeof(double));
    ds->labels = malloc((size_t)n * sizeof(uint8_t));
    for (int i = 0; i < n; i++) {
        size_t off = (size_t)i * rows * cols;
        for (int j = 0; j < rows * cols; j++) {
            ds->images[off + j] = img_buf[off + j] / 255.0;
        }
        ds->labels[i] = lbl_buf[i];
    }
    free(img_buf); free(lbl_buf); free(d1); free(d2);
    return 0;
}

void free_mnist(Dataset *ds) {
    free(ds->images);
    free(ds->labels);
    ds->n = ds->r = ds->c = 0;
}
