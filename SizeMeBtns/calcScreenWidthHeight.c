//
//  calcScreenWidthHeight.c
//  SizeMeBtns
//
//  Created by Jaran F on 24/05/2018.
//  Copyright © 2018 JaranF Information Technology. All rights reserved.
//
#include <math.h>
#include "calcScreenWidthHeight.h"

struct WHDims {
    float width;
    float height;
};

struct WHDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM);

struct WHDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM){
    struct WHDims screenDimsInMM;
    float heightInMM = sqrt(((screenDiagnalSizeInMM * screenDiagnalSizeInMM) * (heightInPixels * heightInPixels)) / ( (widthInPixels * widthInPixels) + (heightInPixels * heightInPixels)   ));
    // Math.sqrt((((4 * 2.54) * (4* 2.54)) * (  (568) * (568)   )) / ( ((320) * (320) ) + (568 * 568)   ))
    screenDimsInMM.height = heightInMM;
    screenDimsInMM.width  = heightInMM * (float)widthInPixels / (float)heightInPixels;
    return screenDimsInMM;
}