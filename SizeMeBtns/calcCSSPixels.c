//
//  calcCSSPixels.c
//  SizeMeBtns
//
//  Created by Jaran F on 21/05/2018.
//
#include <math.h>
#include "calcCSSPixels.h"
#include "common.h"


WidthHeightDims calcCSSPixels(float width, float height, WidthHeightDims screenWidthHeightInMM, WidthHeightDims CSSPixelDims, WidthHeightDims PhysicalPixelDims, int screenPPI);

WidthHeightDims calcCSSPixels(float width, float height, WidthHeightDims screenWidthHeightInMM, WidthHeightDims CSSPixelDims, WidthHeightDims PhysicalPixelDims, int screenPPI) {
    WidthHeightDims calculatedCSSPixelDims;
    const float screenPPMM = (screenPPI / kInchesToMMmultiplier);  //Pixels per MilliMeter
    calculatedCSSPixelDims.width.inPixels = (width * screenPPMM) / (PhysicalPixelDims.width.inPixels / CSSPixelDims.width.inPixels);
    calculatedCSSPixelDims.height.inPixels = (height * screenPPMM) / (PhysicalPixelDims.height.inPixels / CSSPixelDims.height.inPixels);
    return calculatedCSSPixelDims;
}
// screenDimsInMM.height.inMMs = heightInMM;
