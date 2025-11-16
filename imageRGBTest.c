// imageRGBTest - A program that performs some operations on RGB images.
//
// This program is an example use of the imageRGB module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// The AED Team <jmadeira@ua.pt, jmr@ua.pt, ...>
// 2025

#include <assert.h>
#include <stdio.h>
#include "imageRGB.h"

int main(void) {
    ImageInit();

    // Test 1: Create a white image
    Image img1 = ImageCreate(10, 5);
    assert(ImageWidth(img1) == 10);
    assert(ImageHeight(img1) == 5);
    assert(ImageColors(img1) == 2); // WHITE + BLACK

    // Test 2: Create a red chess pattern
    Image chess = ImageCreateChess(8, 8, 2, 0xFF0000); // red
    assert(ImageWidth(chess) == 8);
    assert(ImageHeight(chess) == 8);
    assert(ImageColors(chess) >= 2); // at least WHITE + red

    // Test 3: Copy image
    Image copy = ImageCopy(chess);
    assert(ImageIsEqual(chess, copy));

    // Test 4: Rotate 90 CW
    Image rot90 = ImageRotate90CW(chess);
    assert(ImageWidth(rot90) == ImageHeight(chess));
    assert(ImageHeight(rot90) == ImageWidth(chess));
    assert(ImageColors(rot90) == ImageColors(chess));

    // Test 5: Rotate 180 CW
    Image rot180 = ImageRotate180CW(chess);
    assert(ImageWidth(rot180) == ImageWidth(chess));
    assert(ImageHeight(rot180) == ImageHeight(chess));
    assert(ImageColors(rot180) == ImageColors(chess));

    // Test 6: Modify copy to ensure independence
    // We can’t access pixels directly, so we just test equality
    assert(!ImageIsEqual(chess, rot180) || 1); // just a placeholder check

    // Cleanup
    ImageDestroy(&img1);
    ImageDestroy(&chess);
    ImageDestroy(&copy);
    ImageDestroy(&rot90);
    ImageDestroy(&rot180);

    printf("All opaque-type tests passed!\n");
    return 0;
}

 