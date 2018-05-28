//
//  calcCSSPixels.c
//  SizeMeBtns
//
//  Created by Jaran F on 21/05/2018.
//  Copyright © 2018 JaranF Information Technology. All rights reserved.
//
#include <math.h>
#include "calcCSSPixels.h"

#define kInchesToMMmultiplier       25.4

struct WHDims {
    float width;
    float height;
};
struct WHPixelDims {
    int width;
    int height;
};

struct WHPixelDims calcCSSPixels(float width, float height, struct WHDims screenWidthHeightInMM, struct WHPixelDims CSSPixelDims, struct WHPixelDims PhysicalPixelDims, int screenPPI);

struct WHPixelDims calcCSSPixels(float width, float height, struct WHDims screenWidthHeightInMM, struct WHPixelDims CSSPixelDims, struct WHPixelDims PhysicalPixelDims, int screenPPI) {
    struct WHPixelDims calculatedCSSPixelDims;
    float screenPPMM = (screenPPI / kInchesToMMmultiplier);
    calculatedCSSPixelDims.width = (width * screenPPMM) / (PhysicalPixelDims.width / CSSPixelDims.width);
    calculatedCSSPixelDims.height = (height * screenPPMM) / (PhysicalPixelDims.height / CSSPixelDims.height);

    return calculatedCSSPixelDims;
}
