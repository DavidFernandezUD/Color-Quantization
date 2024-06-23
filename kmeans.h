
#ifndef _KMEANS_H
#define _KMEANS_H

// Euclidean distance between two points in n_dim dimensional space
float dist(float* a, float* b, int n_dims);

// Returns nearest cluster index of a sample based on euclidean distance
int find_nearest_cluster(float* sample, float** centroids, int n_centroids, int n_dims);

// Returns the coordinates of the centroids resulting from aplying k-means to a set of samples
float** kmeans(float** samples, int n_samples, int n_clusters, int n_dims);

// Quantize a set of vectors to a predefined set of vectors
void quantize(float** samples, int n_samples, float** centroids, int n_centroids, int n_dims);

// Load bmp image into float array
float** img_load(char* path, int* width, int* height);

// Store float array as bmp image
void img_store(char* path, float** samples, int width, int height);

#endif // _KMEANS_H

