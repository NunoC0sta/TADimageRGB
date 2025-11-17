#include <stdio.h>
#include <assert.h>
#include "imageRGB.h"

// Helper to check that rotation preserves LUT
void CheckLUTPreserved(const Image img1, const Image img2) {
    assert(ImageColors(img1) == ImageColors(img2));
}

// Helper to compare dimensions
void CheckDimensions(const Image img, int expectedWidth, int expectedHeight) {
    assert(ImageWidth(img) == expectedWidth);
    assert(ImageHeight(img) == expectedHeight);
}

void TestImageCopyAndEquality() {
    printf("Testing ImageCopy and ImageIsEqual...\n");

    Image img = ImageCreateChess(4, 4, 2, 0xFF0000);
    Image copy = ImageCopy(img);

    // They should be equal initially
    assert(ImageIsEqual(img, copy));

    // Modify rotated image to ensure inequality
    Image rot90 = ImageRotate90CW(copy);
    assert(!ImageIsEqual(img, rot90));

    ImageDestroy(&img);
    ImageDestroy(&copy);
    ImageDestroy(&rot90);

    printf("ImageCopy and ImageIsEqual tests passed!\n");
}

void TestImageRotate90CW() {
    printf("Testing ImageRotate90CW...\n");

    Image img = ImageCreatePalete(4, 4, 1);
    Image rotated = ImageRotate90CW(img);

    CheckDimensions(rotated, ImageHeight(img), ImageWidth(img));
    CheckLUTPreserved(img, rotated);

    // Rotate 4 times = original
    Image rot2 = ImageRotate90CW(rotated);
    Image rot3 = ImageRotate90CW(rot2);
    Image rot4 = ImageRotate90CW(rot3);
    assert(ImageWidth(rot4) == ImageWidth(img));
    assert(ImageHeight(rot4) == ImageHeight(img));

    ImageDestroy(&img);
    ImageDestroy(&rotated);
    ImageDestroy(&rot2);
    ImageDestroy(&rot3);
    ImageDestroy(&rot4);

    printf("ImageRotate90CW tests passed!\n");
}

void TestImageRotate180CW() {
    printf("Testing ImageRotate180CW...\n");

    Image img = ImageCreatePalete(4, 4, 1);
    Image rotated = ImageRotate180CW(img);

    CheckDimensions(rotated, ImageWidth(img), ImageHeight(img));
    CheckLUTPreserved(img, rotated);

    // Rotate twice = original
    Image rot2 = ImageRotate180CW(rotated);
    assert(ImageIsEqual(img, rot2));

    ImageDestroy(&img);
    ImageDestroy(&rotated);
    ImageDestroy(&rot2);

    printf("ImageRotate180CW tests passed!\n");
}

void TestEdgeCases() {
    printf("Testing edge cases...\n");

    // 1x1 image
    Image img = ImageCreate(1, 1);
    Image copy = ImageCopy(img);
    assert(ImageIsEqual(img, copy));

    Image rot90 = ImageRotate90CW(img);
    Image rot180 = ImageRotate180CW(img);
    assert(ImageIsEqual(img, rot90));
    assert(ImageIsEqual(img, rot180));

    ImageDestroy(&img);
    ImageDestroy(&copy);
    ImageDestroy(&rot90);
    ImageDestroy(&rot180);

    Image imgBIG = ImageCreate(15000, 15000);
    Image copyBIG = ImageCopy(imgBIG);
    assert(ImageIsEqual(imgBIG, copyBIG));

    Image rot90BIG = ImageRotate90CW(imgBIG);
    Image rot180BIG = ImageRotate180CW(imgBIG);
    assert(ImageIsEqual(imgBIG, rot90BIG));
    assert(ImageIsEqual(imgBIG, rot180BIG));

    ImageDestroy(&imgBIG);
    ImageDestroy(&copyBIG);
    ImageDestroy(&rot90BIG);
    ImageDestroy(&rot180BIG);

    printf("Edge case tests passed!\n");
}

int main() {
    ImageInit();
    printf("Starting test suite...\n\n");

    TestImageCopyAndEquality();
    TestImageRotate90CW();
    TestImageRotate180CW();
    TestEdgeCases();

    printf("\nAll tests passed successfully!\n");
    return 0;
}
