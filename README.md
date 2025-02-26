# clear-vision

Program will be invoked via command-line arguments, which determine the operation to be performed.

Below is a description of the available operations and the associated arguments:


Mean Filter : The mean filter is a basic smoothing technique used to reduce noise in images by replacing each pixel with the average of its surrounding pixels.

Gaussian Smoothing Filter : The Gaussian smoothing filter reduces image noise and blurs details using a weighted average around each pixel, where nearby pixels have more influence than those farther away.

Unsharp Masking Filter : This filter sharpens the image by emphasizing the edges, which helps make important features more visible while preserving the clarity of key details.


| Operation Command-Line Arguments  | Description  |
|-----------------------------------|--------------|
| `mean <img> <kernel_size>` | Applies a Mean filter to the input image using a kernel of size `kernel_size`. |
| `gauss <img> <kernel_size> <sigma>` | Applies Gaussian smoothing to the input image with the specified kernel size and `sigma` value. |
| `unsharp <img> <kernel_size> <amount>` | Applies an Unsharp Mask filter to the input image using the given kernel size and amount of sharpening. |
| `add <img1> <img2>` | Adds the pixel values of two images together. |
| `sub <img1> <img2>` | Subtracts the pixel values of `img2` from `img1`. |
| `equals <img1> <img2>` | Compares two images to check if they are identical. Prints the result to the console. |
| `disguise <img>` | Generates a secret image from the given grayscale image and saves it to a `.dat` file. |
| `reveal <dat>` | Reads the given `.dat` file into a secret image, reconstructs it into a grayscale image, and saves it. |
| `enc <img> <message>` | Embeds the provided secret message into the image by modifying the least significant bits (LSBs) of the pixel values. |
| `dec <img> <msg_len>` | Extracts and decrypts the hidden message from the image, assuming the message is of length `msg_len` characters. |


# Run Configuration

Here is an example of how this code will be compiled (note that instead of main.cpp we will use our test files):

$ g++ -g -std=c++11 -o clearvision main.cpp SecretImage.cpp GrayscaleImage.cpp Filter.cpp Crypto.cpp

Or, you can use the provided Makefile or CMakeLists.txt within the sample input to compile the code:

$ make

or

$ mkdir clearvision_build

$ cmake -S . -B clearvision_build/

$ make -C clearvision_build/

After compilation, you can run the program as follows:

$ ./clearvision mean puppy.png 3
