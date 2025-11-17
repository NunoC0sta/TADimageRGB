#include "imageRGB.h"
#include <stdio.h>

int main(void) {
    // Initialize library (for instrumentation)
    ImageInit();

    printf("=== Creating a simple chess image ===\n");
    Image chess = ImageCreateChess(8, 8, 2, 0xff0000);  // Red color
    ImageRAWPrint(chess);

    printf("=== Saving chess image to PPM ===\n");
    ImageSavePPM(chess, "chess.ppm");

    printf("=== Loading the saved PPM ===\n");
    Image loaded = ImageLoadPPM("./img/chess.ppm");
    ImageRAWPrint(loaded);

    printf("=== Checking equality ===\n");
    if (ImageIsEqual(chess, loaded)) {
        printf("Success: Loaded image matches original!\n");
    } else {
        printf("Error: Images differ!\n");
    }

    printf("=== Rotating the image 90 CW ===\n");
    Image rotated90 = ImageRotate90CW(chess);
    ImageRAWPrint(rotated90);
    ImageSavePPM(rotated90, "./img/chess_rot90.ppm");

    printf("=== Rotating the image 180 CW ===\n");
    Image rotated180 = ImageRotate180CW(chess);
    ImageRAWPrint(rotated180);
    ImageSavePPM(rotated180, "chess_rot180.ppm");

    printf("=== Copying the image ===\n");
    Image copy = ImageCopy(chess);
    if (ImageIsEqual(copy, chess)) {
        printf("Success: Copy matches original!\n");
    }

    // Cleanup
    ImageDestroy(&chess);
    ImageDestroy(&loaded);
    ImageDestroy(&rotated90);
    ImageDestroy(&rotated180);
    ImageDestroy(&copy);

    printf("All tests completed.\n");
    return 0;
}
