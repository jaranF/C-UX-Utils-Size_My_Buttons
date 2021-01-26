//
//  calcScreenWidthHeight.c
//  SizeMeBtns
//
//  Created by Jaran F on 24/05/2018.
//
#include <math.h>
#include "calcScreenWidthHeight.h"
#include "common.h"


WidthHeightDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM);

WidthHeightDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM){
    WidthHeightDims screenDimsInMM;
    const int heightSquared = heightInPixels * heightInPixels;
    const int widthSquared = widthInPixels * widthInPixels;
    const float heightInMM = sqrt(((screenDiagnalSizeInMM * screenDiagnalSizeInMM) * heightSquared) / (widthSquared + heightSquared));
    // Math.sqrt((((4 * 2.54) * (4* 2.54)) * (  (568) * (568)   )) / ( ((320) * (320) ) + (568 * 568)   ))
    screenDimsInMM.height.inMMs = heightInMM;
    screenDimsInMM.width.inMMs  = heightInMM * (float)widthInPixels / (float)heightInPixels;
    return screenDimsInMM;
}
