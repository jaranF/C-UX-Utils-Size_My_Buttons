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

struct WHDims {
    float width;
    float height;
};
struct WHPixelDims {
    int width;
    int height;
};
struct DeviceDefn {
    char deviceName[15];
    struct WHPixelDims CSSPixelDims;
    struct WHPixelDims PhysicalPixelDims;
    float diagonalScreenSize;
    int ppi;
};
#endif /* common_h */
