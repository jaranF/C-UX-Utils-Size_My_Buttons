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

struct WHDims calcScreenWidthHeight(float ratio, float screenDiagnalSize);

struct WHDims calcScreenWidthHeight(float ratio, float screenDiagnalSize){
    struct WHDims myDims;
    myDims.height = 8.0;
    myDims.width  = 1.0;
    return myDims;
}