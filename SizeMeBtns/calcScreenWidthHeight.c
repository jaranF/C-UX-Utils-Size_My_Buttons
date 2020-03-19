//
//  calcScreenWidthHeight.c
//  SizeMeBtns
//
//  Created by Jaran F on 24/05/2018.
//
#include <math.h>
#include "calcScreenWidthHeight.h"
#include "common.h"


WHDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM);

WHDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM){
    WHDims screenDimsInMM;
    int heightSquared = heightInPixels * heightInPixels;
    int widthSquared = widthInPixels * widthInPixels;
    float heightInMM = sqrt(((screenDiagnalSizeInMM * screenDiagnalSizeInMM) * heightSquared) / (widthSquared + heightSquared));
    // Math.sqrt((((4 * 2.54) * (4* 2.54)) * (  (568) * (568)   )) / ( ((320) * (320) ) + (568 * 568)   ))
    screenDimsInMM.height = heightInMM;
    screenDimsInMM.width  = heightInMM * (float)widthInPixels / (float)heightInPixels;
    return screenDimsInMM;
}
