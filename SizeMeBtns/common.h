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
// todo remove above
#define kInchesToMMmultiplier       25.4
#define kDevicesDefnFileName        "./definitionsData.txt"
#define kScanToNewlinePattern       "%[^\n]\n"
#define kOK                         1
#define kTypeDescriptionMaxLen      7
#define SIZEOFDELIMITEDSTRUCT( A ) ((sizeof(A.deviceName)) + 1 + 12 + 1 + 12 + 1 + 8 + 1 + 6)
//+1 accounts for delimiter of | pipe; Also +12 for the two ints of CSSPixelDims /PhysicalPixelDims;  +8 for float of diagonalScreenSize; and +6 of the short int of ppi
// iPhone 5|320|568|640|1136|4|326

typedef struct WHDimsTag {
    float width;
    float height;
} WHDims;
typedef struct WHPixelDimsTag {
    int width;
    int height;
} WHPixelDims;
typedef struct DeviceDefnTag {
    char deviceName[50];
    WHPixelDims CSSPixelDims;
    WHPixelDims PhysicalPixelDims;
    float diagonalScreenSize;
    u_short ppi;
    struct DeviceDefnTag* nextItemPtr;
} DeviceDefn;

#endif /* common_h */
