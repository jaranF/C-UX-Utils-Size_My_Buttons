//
//  calcCSSPixels.c
//  SizeMeBtns
//
//  Created by Jaran F on 21/05/2018.
//
#include <math.h>
#include "calcCSSPixels.h"
#include "common.h"


WHPixelDims calcCSSPixels(float width, float height, WHDims  screenWidthHeightInMM, WHPixelDims CSSPixelDims, WHPixelDims PhysicalPixelDims, int screenPPI);

WHPixelDims calcCSSPixels(float width, float height, WHDims  screenWidthHeightInMM, WHPixelDims CSSPixelDims, WHPixelDims PhysicalPixelDims, int screenPPI) {
    WHPixelDims calculatedCSSPixelDims;
    float screenPPMM = (screenPPI / kInchesToMMmultiplier);
    calculatedCSSPixelDims.width = (width * screenPPMM) / (PhysicalPixelDims.width / CSSPixelDims.width);
    calculatedCSSPixelDims.height = (height * screenPPMM) / (PhysicalPixelDims.height / CSSPixelDims.height);

    return calculatedCSSPixelDims;
}
