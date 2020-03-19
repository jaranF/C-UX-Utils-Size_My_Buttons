//
//  common.h
//  SizeMeBtns
//
//  Created by Jaran F on 08/06/2018.
//

#ifndef common_h
#define common_h

#define kNumOfDifferentUnits        3
#define kUnitNameBufferSize         3
#define kDevicesArrayLen            13
#define kInchesToMMmultiplier       25.4

typedef struct WHDimsTag {
    float width;
    float height;
} WHDims;
typedef struct WHPixelDimsTag {
    int width;
    int height;
} WHPixelDims;
typedef struct DeviceDefnTag {
    char deviceName[15];
    WHPixelDims CSSPixelDims;
    WHPixelDims PhysicalPixelDims;
    float diagonalScreenSize;
    int ppi;
} DeviceDefn;
#endif /* common_h */
