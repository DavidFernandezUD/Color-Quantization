# COLOR QUANTIZATION

![example image](images/example.bmp)

**NOTE: Image quantized to 5 discrete colors**

Color quantization is quantization applied to vectors in a three dimensional color space. In this case the color palette choosen for color quantization, is obteined through performing the k-means algorithm with the RGB values of each pixel in an image, as points in a three dimensional space. Afterwards the values of each pixel are rounded or quantized to the nearest centroid obtained from the k-means algorithm.

## Usage

This algorithm can be applied to a bitmap image, and produces an output bitmap image with n different colors, trying to conserve the original colors as acurately as possible.

1. Build with 
    
    `make`
2. Run the program with

    `./main <src image> <out image> <num colors>`

