#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "kmeans.h"


float dist(float* a, float* b, int n_dims) {
    float res = 0;
    for (int i = 0; i < n_dims; i++) {
        res += powf(a[i] - b[i], 2.f);
    }
    return sqrtf(res);
}

int find_nearest_cluster(float* sample, float** centroids, int n_centroids, int n_dims) {
    int nearest_cluster = 0;
    float min_distance = dist(sample, centroids[0], n_dims);
    for (int i = 1; i < n_centroids; i++) {
        float* centroid = centroids[i];
        float distance = dist(sample, centroid, n_dims);
        if (distance < min_distance) {
            nearest_cluster = i;
            min_distance = distance;
        }
    }
    return nearest_cluster;
}

static void init_centroids(float** centroids, int n_centroids, float** samples, int n_samples, int n_dims) {
    for (int i = 0; i < n_centroids; i++) {
        float* rsample = samples[rand() % n_samples];
        for (int j = 0; j < n_dims; j++) {
            centroids[i][j] = rsample[j];
        }
    }
}

float** kmeans(float** samples, int n_samples, int n_clusters, int n_dims) {
    
    // Allocate cluster centroids
    float** centroids = (float**) malloc(n_clusters * sizeof(float*));
    for (int i = 0; i < n_clusters; i++) {
        centroids[i] = (float*) malloc(n_dims * sizeof(float));
    }

    init_centroids(centroids, n_clusters, samples, n_samples, n_dims);
    
    // Allocate cluster sample counter
    int* samples_per_cluster = (int*) malloc(n_clusters * sizeof(int));
    
    // Allocate sample cluster indexes
    int* sample_labels = (int*) malloc(n_samples * sizeof(int));
    memset(sample_labels, -1, n_samples * sizeof(int));

    // TODO: Change stopping criteria
    for (int i = 0; i < 100; i++) {
        
        memset(samples_per_cluster, 0, n_clusters * sizeof(int));

        // Assign the nearest centroid to every point in samples
        for (int i = 0; i < n_samples; i++) {
            int cluster_index = find_nearest_cluster(samples[i], centroids, n_clusters, n_dims);
            sample_labels[i] = cluster_index;
            samples_per_cluster[cluster_index]++;
        }
    
        // Set centroids to 0
        for (int i = 0; i < n_clusters; i++)
            memset(centroids[i], 0, n_dims * sizeof(float));
    
        // Update centroids
        for (int i = 0; i < n_samples; i++) {
            float* centroid = centroids[sample_labels[i]];
            float* sample = samples[i];
            for (int j = 0; j < n_dims; j++) {
                centroid[j] += sample[j];
            }
        }

        for (int i = 0; i < n_clusters; i++) {
            for (int j = 0; j < n_dims; j++) {
                centroids[i][j] /= samples_per_cluster[i];
            }
        }
    }
    
    free(samples_per_cluster);
    free(sample_labels);

    return centroids;
}

void quantize(float** samples, int n_samples, float** centroids, int n_centroids, int n_dims) {
    for (int i = 0; i < n_samples; i++) {
        int nearest_index = find_nearest_cluster(samples[i], centroids, n_centroids, n_dims);
        memcpy(samples[i], centroids[nearest_index], n_dims * sizeof(float));
    }
}

float** img_load(char* path, int* width, int* height) {
    
    int channels;
    unsigned char* img = stbi_load(path, width, height, &channels, 0);
    if (img == NULL) {
        fprintf(stderr, "Failed loading bitmap image\n");
        exit(1);
    }

    const size_t n_pixels = (*width) * (*height);

    float** samples = (float**) malloc(n_pixels * sizeof(float*));
    for (size_t i = 0; i < n_pixels; i++) {
        samples[i] = (float*) malloc(3 * sizeof(float));
        
        int index = i * channels;
        samples[i][0] = img[index + 0] / 255.f;
        samples[i][1] = img[index + 1] / 255.f;
        samples[i][2] = img[index + 2] / 255.f;
    }

    stbi_image_free(img);

    return samples;
}

void img_store(char* path, float** samples, int width, int height) {
    
    const size_t n_pixels = width * height;
    unsigned char* img = (unsigned char*) malloc(n_pixels * 3);

    for (size_t i = 0; i < n_pixels; i++) {
        int index = i * 3;

        unsigned char r = samples[i][0] * 255;
        unsigned char g = samples[i][1] * 255;
        unsigned char b = samples[i][2] * 255;

        img[index + 0] = r;
        img[index + 1] = g;
        img[index + 2] = b;
    }

    stbi_write_bmp(path, width, height, 3, img);
    
    free(img);
}

