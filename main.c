#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kmeans.h"


int main(int argc, char** argv) {

    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments\n");
    }

    srand(time(NULL));

    int width, height;
    float** samples = img_load(argv[1], &width, &height);

    const int n_samples = height * width;
    const int n_clusters = atoi(argv[3]);
    const int n_dims = 3;

    float** centroids = kmeans(samples, n_samples, n_clusters, n_dims);
    quantize(samples, n_samples, centroids, n_clusters, n_dims);
    
    img_store(argv[2], samples, width, height);
    
    return 0;
}

