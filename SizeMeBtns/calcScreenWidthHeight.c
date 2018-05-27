//
//  calcScreenWidthHeight.c
//  SizeMeBtns
//
//  Created by Jaran F on 24/05/2018.
//  Copyright © 2018 JaranF Information Technology. All rights reserved.
//

#include "calcScreenWidthHeight.h"

struct WHDims {
    float width;
    float height;
};

struct WHDims calcScreenWidthHeight(float ratio, float screenDiagnalSizeInMM);

struct WHDims calcScreenWidthHeight(float ratio, float screenDiagnalSizeInMM){
    struct WHDims screenDimsInMM;
    // Math.sqrt((((4 * 2.54) * (4* 2.54)) * (  (568) * (568)   )) / ( ((320) * (320) ) + (568 * 568)   ))
    screenDimsInMM.height = 8.0;
    screenDimsInMM.width  = 2.0;
    return screenDimsInMM;
}