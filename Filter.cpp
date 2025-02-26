#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    // 3. Update each pixel with the computed mean.

    GrayscaleImage copyimage(image);
    int height = copyimage.get_height();
    int width = copyimage.get_width();
    int resdata;

    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            resdata = find_mean_value(copyimage, kernelSize, i, j);
            if (resdata > 255) {resdata = 255;}
            if (resdata < 0) {resdata = 0;}
            image.set_pixel(i,j,resdata);
        }
    }
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {
    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.

    GrayscaleImage copyimage(image);
    int height = copyimage.get_height();
    int width = copyimage.get_width();
    int resdata;
    double** kernel = calculate_normalized_kernel(kernelSize, sigma); // Calculating kernel once. Used for all squares.

    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            resdata = find_gauss_value(copyimage, kernelSize, sigma, kernel, i, j);
            if (resdata > 255) {resdata = 255;}
            if (resdata < 0) {resdata = 0;}
            image.set_pixel(i,j,resdata);
        }
    }
    
    for (int i=0; i<kernelSize; i++){
        delete[] kernel[i];
    }
    delete[] kernel;
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].

    GrayscaleImage blurred(image);
    apply_gaussian_smoothing(blurred, kernelSize);
    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {
            int resdata = static_cast<int>(std::floor(image.get_data()[i][j] + amount * (image.get_data()[i][j] - blurred.get_data()[i][j])));
            if (resdata > 255) resdata = 255;
            if (resdata < 0) resdata = 0;
            image.set_pixel(i, j, resdata);
        }
    }
}

// Calculation of middle square's new color value.
int Filter::find_mean_value(GrayscaleImage& copyimage, int kernelSize, int i, int j){
    double total = 0;
    for (int k=i-kernelSize/2; k<=i+kernelSize/2; k++){
        for (int m=j-kernelSize/2; m<=j+kernelSize/2; m++) {
            if (k>=0 && k<copyimage.get_height() && m>=0 && m<copyimage.get_width()){ // We don't have to calculate squares that are outside of the image. We considered them as 0.
                total += copyimage.get_data()[k][m];
            }
        }
    }
    return static_cast<int>(std::floor(total/(kernelSize*kernelSize)));
}

// It is similar to mean value calculation. But in here, distance from the middle square is changes the effect value. Closer square have bigger role than the far squares.
int Filter::find_gauss_value(GrayscaleImage& copyimage, int kernelSize, double sigma, double** kernel, int i, int j){
    double total = 0;
    for (int k=i-kernelSize/2; k<=i+kernelSize/2; k++){
        for (int m=j-kernelSize/2; m<=j+kernelSize/2; m++){
            if (k>=0 && k<copyimage.get_height() && m>=0 && m<copyimage.get_width()){
                total += copyimage.get_data()[k][m] * kernel[k-(i-kernelSize/2)][m-(j-kernelSize/2)];
            }
        }
    }
    return static_cast<int>(std::floor(total));
}

double** Filter::calculate_normalized_kernel(int kernelSize, double sigma){
    double** kernel = new double* [kernelSize];
    for (int i=0; i<kernelSize; i++){
        kernel[i] = new double[kernelSize];
    }

    double total = 0;
    for (int i=-kernelSize/2; i<=kernelSize/2; i++){ // In formula, i and j stands for distance from middle square. That's why we defined them like this.
        for (int j=-kernelSize/2; j<=kernelSize/2; j++){
            kernel[i+kernelSize/2][j+kernelSize/2] = (1/(2*M_PI*sigma*sigma)) * std::exp(-((i*i+j*j)/(2*sigma*sigma))); // We calculate each coefficient and put them in 2D kernel array.
            total += kernel[i+kernelSize/2][j+kernelSize/2];
        }
    }

    for (int i=0; i<kernelSize; i++){
        for (int j=0; j<kernelSize; j++){
            kernel[i][j] /= total; // We are normalizing them in here.
        }
    }
    return kernel;
}