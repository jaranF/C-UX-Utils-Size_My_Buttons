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
#define kDevicesDefnFileName        "./definitionData.txt"
#define kScanToNewlinePattern       "%[^\n]\n"
#define kOK                         1
#define SIZEOFDELIMITEDSTRUCT( A ) sizeof(A.deviceName) + 1 + sizeof(A.CSSPixelDims) + 1 + sizeof(A.PhysicalPixelDims) + 1 + sizeof(A.diagonalScreenSize) + 1 + sizeof(A.ppi)
typedef struct WHDimsTag {
    float width;
    float height;
} WHDims;
typedef struct WHPixelDimsTag {
    int width;
    int height;
} WHPixelDims;
typedef struct DeviceDefnTag {
    char deviceName[16];
    WHPixelDims CSSPixelDims;
    WHPixelDims PhysicalPixelDims;
    float diagonalScreenSize;
    int ppi;
    struct DeviceDefnTag* nextItemPtr;
} DeviceDefn;

#endif /* common_h */
