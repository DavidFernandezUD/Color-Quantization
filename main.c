#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


enum color {
    red = 0,
    green = 1,
    blue = 2
};

struct Point {
    float x;
    float y;
    float z;
};

float distance(struct Point p1, struct Point p2) {
    return sqrtf(powf(p1.x - p2.x, 2.f) + powf(p1.y - p2.y, 2.f) + powf(p1.z - p2.z, 2.f));
}

static void init_centroids(struct Point* centroids, int n_centroids) {
    for (int i = 0; i < n_centroids; i++) {
        centroids[i].x = (float) rand() / RAND_MAX;
        centroids[i].y = (float) rand() / RAND_MAX;
        centroids[i].z = (float) rand() / RAND_MAX;
    }
}

void kmeans(struct Point* samples, int n_samples, int* clusters, int n_clusters, int iters) {
    
    struct Point* centroids = (struct Point*) malloc(sizeof(struct Point) * n_clusters);
    float* distances = (float*) malloc(sizeof(float) * n_clusters * n_samples);
    
    // Init centroids
    init_centroids(centroids, n_clusters);
    
    // TODO: Implement stopping criteria
    for (int i = 0; i < iters; i++) {

        // Calculate distances from every point to every centroid
        for (int centroid = 0; centroid < n_clusters; centroid++) {
            for (int point = 0; point < n_samples; point++) {
                distances[centroid * n_samples + point] = distance(centroids[centroid], samples[point]);
            }
        }

        // Assign each point the class of the nearest centroid
        for (int point = 0; point < n_samples; point++) {
            int nearest_centroid = -1;
            float min_distance = INFINITY;
            for (int centroid = 0; centroid < n_clusters; centroid++) {
                float distance = distances[centroid * n_samples + point];
                if (distance < min_distance) {
                    nearest_centroid = centroid;
                    min_distance = distance;
                }
            }
            clusters[point] = nearest_centroid;
        }

        // Calculate center of mass and update centroids
        int num_points[n_clusters];
        memset(num_points, 0, sizeof(int) * n_clusters);
        memset(centroids, 0, sizeof(struct Point) * n_clusters);
        for (int point = 0; point < n_samples; point++) {
            int cluster = clusters[point];
            centroids[cluster].x += samples[point].x;
            centroids[cluster].y += samples[point].y;
            centroids[cluster].z += samples[point].z;
            num_points[cluster]++;
        }
        
        for (int centroid = 0; centroid < n_clusters; centroid++) {
            float sum = (float) num_points[centroid];
            if (sum > 0) {
                centroids[centroid].x /= sum;
                centroids[centroid].y /= sum;
                centroids[centroid].z /= sum;
            }
        }
    }

    // Quantize vectors
    for (int point = 0; point < n_samples; point++) {
        samples[point] = centroids[clusters[point]];
    }
}

int main() {
    
    srand(time(NULL));

    const int num_clusters = 4;
    const int iters = 100;

    int width, height, channels;
    unsigned char* img = stbi_load("sample2.bmp", &width, &height, &channels, 0);
    assert(channels == 3);
    const int num_points = width * height;

    // Create clusters
    struct Point* samples = (struct Point*) malloc(sizeof(struct Point) * num_points);
    for (int i = 0; i < num_points; i++) {
        int index = i * channels;
        samples[i].x = img[index + red] / 255.f;
        samples[i].y = img[index + green] / 255.f;
        samples[i].z = img[index + blue] / 255.f;
    }
    
    int* clusters = (int*) malloc(sizeof(int) * num_points);
    
    // Perform kmeans
    kmeans(samples, num_points, clusters, num_clusters, iters);

    for (int i = 0; i < num_points; i++) {
        int index = i * channels;
        
        unsigned char r = samples[i].x * 255;
        unsigned char g = samples[i].y * 255;
        unsigned char b = samples[i].z * 255;

        img[index + red] = r;
        img[index + green] = g;
        img[index + blue] = b;
    }

    stbi_write_bmp("out.bmp", width, height, channels, img);

    stbi_image_free(img);

    return 0;
}

