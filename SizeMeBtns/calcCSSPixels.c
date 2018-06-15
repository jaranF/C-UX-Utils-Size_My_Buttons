//
//  calcCSSPixels.c
//  SizeMeBtns
//
//  Created by Jaran F on 21/05/2018.
//
#include <math.h>
#include "calcCSSPixels.h"
#include "common.h"


struct WHPixelDims calcCSSPixels(float width, float height, struct WHDims screenWidthHeightInMM, struct WHPixelDims CSSPixelDims, struct WHPixelDims PhysicalPixelDims, int screenPPI);

struct WHPixelDims calcCSSPixels(float width, float height, struct WHDims screenWidthHeightInMM, struct WHPixelDims CSSPixelDims, struct WHPixelDims PhysicalPixelDims, int screenPPI) {
    struct WHPixelDims calculatedCSSPixelDims;
    float screenPPMM = (screenPPI / kInchesToMMmultiplier);
    calculatedCSSPixelDims.width = (width * screenPPMM) / (PhysicalPixelDims.width / CSSPixelDims.width);
    calculatedCSSPixelDims.height = (height * screenPPMM) / (PhysicalPixelDims.height / CSSPixelDims.height);

    return calculatedCSSPixelDims;
}
