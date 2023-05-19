#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main() {
    // Create Tesseract API instance
    tesseract::TessBaseAPI tess;

    // Initialize Tesseract with English language (change as needed)
    if (tess.Init(nullptr, "eng")) {
        std::cerr << "Could not initialize Tesseract." << std::endl;
        return 1;
    }

    // Load the image using Leptonica library
    Pix *image = pixRead("image.png");
    if (!image) {
        std::cerr << "Could not open image file." << std::endl;
        return 1;
    }

    // Set the region of interest (ROI) coordinates where the number is located
    int x = 100;      // Replace with the appropriate x-coordinate
    int y = 100;      // Replace with the appropriate y-coordinate
    int width = 200;  // Replace with the appropriate width
    int height = 50;  // Replace with the appropriate height

    // Create a sub-image (ROI) using Leptonica
    Box *roi = boxCreate(x, y, width, height);
    Pix *croppedImage = pixClipRectangle(image, roi, nullptr);

    // Set the sub-image as the input image for Tesseract
    tess.SetImage(croppedImage);

    // Perform OCR
    char *result = tess.GetUTF8Text();
    std::string number(result);

    // Clean up resources
    tess.Clear();
    tess.End();
    pixDestroy(&croppedImage);
    pixDestroy(&image);
    boxDestroy(&roi);

    // Print the extracted number
    std::cout << "Extracted number: " << number << std::endl;

    return 0;
}

