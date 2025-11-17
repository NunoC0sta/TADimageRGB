#include <stdio.h>
#include <assert.h>
#include "imageRGB.h"


// Helper to compare dimensions
int CheckDimensions(Image img, int expectedW, int expectedH) {
    if (ImageWidth(img) != expectedW) return 0;
    if (ImageHeight(img) != expectedH) return 0;
    return 1;
}

int TestImageCopyAndEquality() {
    printf("Testing ImageCopy and ImageIsEqual...\n");

    Image img = ImageCreateChess(4, 4, 2, 0xFF0000);
    Image copy = ImageCopy(img);

    // They should be equal initially
    if (!ImageIsEqual(img, copy)) {
        ImageDestroy(&img);
        ImageDestroy(&copy);
        printf("FAILED: copy is not equal to original.\n");
        return 1;
    }

    // Modify rotated image to ensure inequality
    Image rot90 = ImageRotate90CW(copy);
    if (ImageIsEqual(img, rot90)) {
        ImageDestroy(&img);
        ImageDestroy(&copy);
        ImageDestroy(&rot90);
        printf("FAILED: rotated image is still equal to original.\n");
        return 1;
    }

    ImageDestroy(&img);
    ImageDestroy(&copy);
    ImageDestroy(&rot90);

    printf("ImageCopy and ImageIsEqual tests passed!\n");
    return 0;
}


int TestImageRotate90CW() {
    printf("Testing ImageRotate90CW...\n");

    Image img = ImageCreatePalete(4, 4, 1);
    Image rotated = ImageRotate90CW(img);
    

    int expectedWidth = ImageWidth(img);
    int expectedHeight = ImageHeight(img);

    if(!CheckDimensions(img, expectedWidth, expectedHeight)){
        return 1;
    }

    // Rotate 4 times → back to original
    Image rot2 = ImageRotate90CW(rotated);
    Image rot3 = ImageRotate90CW(rot2);
    Image rot4 = ImageRotate90CW(rot3);
    

    if (ImageWidth(rot4) != ImageWidth(img) ||
        ImageHeight(rot4) != ImageHeight(img)) 
    {
        printf("FAILED: rotating 4 times did not return to original size.\n");
        ImageDestroy(&img);
        ImageDestroy(&rotated);
        ImageDestroy(&rot2);
        ImageDestroy(&rot3);
        ImageDestroy(&rot4);
        return 1;
    }

    ImageDestroy(&img);
    ImageDestroy(&rotated);
    ImageDestroy(&rot2);
    ImageDestroy(&rot3);
    ImageDestroy(&rot4);

    printf("ImageRotate90CW tests passed!\n");
    return 0;
}


int TestImageRotate180CW() {
    printf("Testing ImageRotate180CW...\n");

    Image img = ImageCreatePalete(4, 4, 1);
    Image rotated = ImageRotate180CW(img);
    int expectedwith = ImageWidth(rotated);
    int expectedheight = ImageHeight(rotated); 

    // Check dimensions
    if (!CheckDimensions(rotated, expectedwith, expectedheight)) {
        printf("FAILED: rotated dimensions incorrect.\n");
        ImageDestroy(&img);
        ImageDestroy(&rotated);
        return 1;
    }

    // Rotate twice = original
    Image rot2 = ImageRotate180CW(rotated);
    if (!ImageIsEqual(img, rot2)) {
        printf("FAILED: rotating twice did not return to original.\n");
        ImageDestroy(&img);
        ImageDestroy(&rotated);
        ImageDestroy(&rot2);
        return 1;
    }

    ImageDestroy(&img);
    ImageDestroy(&rotated);
    ImageDestroy(&rot2);

    printf("ImageRotate180CW tests passed!\n");
    return 0;
}


int TestEdgeCases() {
    printf("Testing edge cases...\n");

    //
    // 1×1 image
    //
    Image img = ImageCreate(1, 1);
    Image copy = ImageCopy(img);

    if (!ImageIsEqual(img, copy)) {
        printf("FAILED: 1x1 copy not equal.\n");
        ImageDestroy(&img);
        ImageDestroy(&copy);
        return 1;
    }

    Image rot90 = ImageRotate90CW(img);
    Image rot180 = ImageRotate180CW(img);

    if (!ImageIsEqual(img, rot90)) {
        printf("FAILED: 1x1 rot90 not equal.\n");
        ImageDestroy(&img);
        ImageDestroy(&copy);
        ImageDestroy(&rot90);
        ImageDestroy(&rot180);
        return 1;
    }

    if (!ImageIsEqual(img, rot180)) {
        printf("FAILED: 1x1 rot180 not equal.\n");
        ImageDestroy(&img);
        ImageDestroy(&copy);
        ImageDestroy(&rot90);
        ImageDestroy(&rot180);
        return 1;
    }

    ImageDestroy(&img);
    ImageDestroy(&copy);
    ImageDestroy(&rot90);
    ImageDestroy(&rot180);


    //
    // Big × Big
    //
    Image imgBIG = ImageCreate(15000, 15000);

    Image copyBIG = ImageCopy(imgBIG);
    if (!ImageIsEqual(imgBIG, copyBIG)) {
        printf("FAILED: big copy not equal.\n");
        ImageDestroy(&imgBIG);
        ImageDestroy(&copyBIG);
        return 1;
    }

    Image rot90BIG = ImageRotate90CW(imgBIG);
    Image rot180BIG = ImageRotate180CW(imgBIG);

    if (!ImageIsEqual(imgBIG, rot90BIG)) {
        printf("FAILED: big rot90 not equal.\n");
        ImageDestroy(&imgBIG);
        ImageDestroy(&copyBIG);
        ImageDestroy(&rot90BIG);
        ImageDestroy(&rot180BIG);
        return 1;
    }

    if (!ImageIsEqual(imgBIG, rot180BIG)) {
        printf("FAILED: big rot180 not equal.\n");
        ImageDestroy(&imgBIG);
        ImageDestroy(&copyBIG);
        ImageDestroy(&rot90BIG);
        ImageDestroy(&rot180BIG);
        return 1;
    }

    ImageDestroy(&imgBIG);
    ImageDestroy(&copyBIG);
    ImageDestroy(&rot90BIG);
    ImageDestroy(&rot180BIG);

    printf("Edge case tests passed!\n");
    return 0;
}

int main() {
    ImageInit();
    printf("Starting test suite...\n\n");

    int total = 0;
    int passed = 0;
    int failed = 0;

    int result;

    // Test 1
    total++;
    result = TestImageCopyAndEquality();
    if (result == 0) passed++; else failed++;

    // Test 2
    total++;
    result = TestImageRotate90CW();
    if (result == 0) passed++; else failed++;

    // Test 3
    total++;
    result = TestImageRotate180CW();
    if (result == 0) passed++; else failed++;

    // Test 4
    total++;
    result = TestEdgeCases();
    if (result == 0) passed++; else failed++;

    printf("\n===== TEST SUMMARY =====\n");
    printf("Total tests: %d\n", total);
    printf("Passed:      %d\n", passed);
    printf("Failed:      %d\n", failed);

    if (failed == 0)
        printf("\nAll tests passed successfully!\n");
    else
        printf("\nSome tests FAILED.\n");

    return failed > 0;
}

