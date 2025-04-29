# COLOR QUANTIZATION

![example image](images/example.bmp)

**NOTE: Image quantized to 5 discrete colors**

Color quantization consists in rounding each color vector in each pixel of an image to the nearest vector out of a predefined color palette. In this case the color palette is obteined by applying the k-means algorithm to an image, with the RGB values of each pixel being treated as points in a three dimensional space. Afterwards the value of each pixel is rounded or quantized to the nearest centroid obtained from the k-means algorithm. This way the selected color pallet efficiently uses the restricted number of colors to represent the image faithfully.

## Usage

This algorithm can be applied to a bitmap image, and produces an output bitmap image with n different colors, trying to conserve the original colors as acurately as possible.

1. Build with 
    
    `make`
2. Run the program with

    `./main <src image> <out image> <num colors>`

