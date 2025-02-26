#include "Crypto.h"
#include "GrayscaleImage.h"

// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage& secret_image, int message_length) {
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    // 2. Calculate the image dimensions.
    // 3. Determine the total bits required based on message length.
    // 4. Ensure the image has enough pixels; if not, throw an error.
    // 5. Calculate the starting pixel from the message_length knowing that  
    //    the last LSB to extract is in the last pixel of the image.
    // 6. Extract LSBs from the image pixels and return the result.

    secret_image.reconstruct();
    int height = secret_image.get_height();
    int width = secret_image.get_width();
    int totalbit = message_length * 7;
    if (totalbit > height*width){
        throw "You dont have enough pixels for this message";
    }
    int iofstart = (height*width) - totalbit;
    int i1=0;
    int i2=0;
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            if (i>j){
                if (i*width+j<iofstart){
                    i1++;
                } else {
                    if (secret_image.get_lower_triangular()[i1]%2==0){ // In binary form, even numbers have 0 in last digit. So thats why I used this calculations.
                        LSB_array.push_back(0);
                    } else {
                        LSB_array.push_back(1);
                    }
                    i1++;
                }
            } else if (i<=j){
                if (i*width+j<iofstart){
                    i2++;
                } else {
                    if (secret_image.get_upper_triangular()[i2]%2==0){
                        LSB_array.push_back(0);
                    } else {
                        LSB_array.push_back(1);
                    }
                    i2++;
                }    
            }
        }
    }
    return LSB_array;
}

// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int>& LSB_array) {
    std::string message;
    // TODO: Your code goes here.

    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    // 2. Convert each group of 7 bits into an ASCII character.
    // 3. Collect the characters to form the decrypted message.
    // 4. Return the resulting message.

    if (LSB_array.size()%7!=0){
        throw "Wrong message";
    }
    for (int i=0; i<LSB_array.size(); i+=7){
        int num = 0;
        for (int j=0; j<7; j++){
            num += LSB_array[i+j] * (1 << (6-j));
        }
        char asciiChar = static_cast<char>(num);
        message.push_back(asciiChar);
    }
    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string& message) {
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.
    // 2. Collect the bits into the LSB array.
    // 3. Return the array of bits.

    for (int i=0; i<message.size(); i++){
        int asciiValue = static_cast<int>(message[i]);
        for (int j=0; j<7; j++){
            int divider = pow(2,6-j);
            if (asciiValue-divider>=0){
                asciiValue -= pow(2,6-j);
                LSB_array.push_back(1);
            } else if (asciiValue-divider<0) {
                LSB_array.push_back(0);
            }
        }
    }
    
    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array) {
    // TODO: Your code goes here.

    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    // 2. Find the starting pixel based on the message length knowing that  
    //    the last LSB to embed should end up in the last pixel of the image.
    // 3. Iterate over the image pixels, embedding LSBs from the array.
    // 4. Return a SecretImage object constructed from the given GrayscaleImage 
    //    with the embedded message.

    int height = image.get_height();
    int width = image.get_width();
    if (height*width<LSB_array.size()){
        throw "Error";
    }
    int iofstart = (height*width) - LSB_array.size();
    int k=0;
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            if (i*width+j>=iofstart){
                int pixval = image.get_data()[i][j];
                pixval = (pixval & ~1) | LSB_array[k++];
                image.set_pixel(i,j,pixval);
            }
        }
    }
    SecretImage secret_image(image);
    return SecretImage(image);
}
