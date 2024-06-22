
#ifndef _KMEANS_H
#define _KMEANS_H

#define ERR(format, ...) do (fprintf(stderr, format, ##__VA_ARGS__); exit(1)) while(0)

// Euclidean distance between two points in n_dim dimensional space
float dist(float* a, float* b, int n_dims);

// TODO: Implement

#endif // _KMEANS_H

