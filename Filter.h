#ifndef FILTER_H
#define FILTER_H

#include "GrayscaleImage.h"

class Filter {
public:
    // Apply the Mean Filter
    static void apply_mean_filter(GrayscaleImage& image, int kernelSize = 3);

    // Apply Gaussian Smoothing Filter
    static void apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize = 3, double sigma = 1.0);

    // Apply Unsharp Masking Filter
    static void apply_unsharp_mask(GrayscaleImage& image, int kernelSize = 3, double amount = 1.5);

    static int find_mean_value(GrayscaleImage& copy, int kernelSize, int i, int j);

    static int find_gauss_value(GrayscaleImage& copyimage, int kernelSize, double sigma, double** kernel, int i, int j);

    static double** calculate_normalized_kernel(int kernelSize, double sigma);
};

#endif // FILTER_H
