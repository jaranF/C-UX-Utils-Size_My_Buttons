//
//  main.c
//  SizeMeBtns
//
//  Created by Jaran F on 14/05/2018.
//  Copyright © 2018 JaranF Information Technology. All rights reserved.
//

#include <stdio.h>
//Runtime_Environment
#include <limits.h>		/* PATH_MAX */

#include <string.h>		/* strcpy   */
#include <stdlib.h>     /* qsort    */
#include <mach-o/dyld.h>/* bool */
#include "calcCSSPixels.h"
#include "calcScreenWidthHeight.h"

#define kUnitsLookupLen             3
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

struct WHPixelDims calcCSSPixels(float width, float height, struct WHDims screenWidthHeightInMM, struct WHPixelDims CSSPixelDims, struct WHPixelDims PhysicalPixelDims, int screenPPI);
struct WHDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM);
char* Executables_Path( char* );

int main(int argc, const char * argv[]) {
    int i;
    int userArgsOffset;
    char filePath[PATH_MAX + 1];
    
    char switchParamHelp[7];
    char validCharsForOfNumber[12];

    float dimensionNumber;
    int bWidthFound = 0; // FALSE
    float unitConversionMultiplier;
    char unit[kUnitNameBufferSize];

    struct DeviceDefn device;
    struct DeviceDefn devicesArray[kDevicesArrayLen];
    int j = kDevicesArrayLen - 1;;                              // Used for iteration through devices Struct Array
    
    float fWidth = 0.0;
    float fHeight = 0.0;
    // The conversion multiplies to get mm are 10mm (i.e. 10mm to 1cm) and
    // 25.4 (inch). But because chars are treated as signed bytes when you
    // cast them to a number type you can't convert the 25.4 to a whole
    // number using the most staightforward option which is to multiply
    // by 10. Instead I used a lower multiplie, i.e. 5, to keep the
    // numbers below 128 but still have the converted to whole integers.
    char unitsConversionTable[kUnitsLookupLen][2][kUnitNameBufferSize] = {
        {{'m',  'm',  '\0'}, 5},
        {{'c',  'm',  '\0'}, 50},
        {{'i',  'n',  '\0'}, kInchesToMMmultiplier * 5}
    };
    i = 0;
    strcpy(device.deviceName, "iPhone 5");
    device.CSSPixelDims.width = 320;
    device.CSSPixelDims.height = 568;
    device.PhysicalPixelDims.width = 640;
    device.PhysicalPixelDims.height = 1136;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 5s");
    device.CSSPixelDims.width = 320;
    device.CSSPixelDims.height = 568;
    device.PhysicalPixelDims.width = 640;
    device.PhysicalPixelDims.height = 1136;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 5c");
    device.CSSPixelDims.width = 320;
    device.CSSPixelDims.height = 568;
    device.PhysicalPixelDims.width = 640;
    device.PhysicalPixelDims.height = 1136;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 5SE");
    device.CSSPixelDims.width = 320;
    device.CSSPixelDims.height = 568;
    device.PhysicalPixelDims.width = 640;
    device.PhysicalPixelDims.height = 1136;
    device.diagonalScreenSize = 4;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 6");
    device.CSSPixelDims.width = 375;
    device.CSSPixelDims.height = 667;
    device.PhysicalPixelDims.width = 750;
    device.PhysicalPixelDims.height = 1344;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 6s");
    device.CSSPixelDims.width = 375;
    device.CSSPixelDims.height = 667;
    device.PhysicalPixelDims.width = 750;
    device.PhysicalPixelDims.height = 1344;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 7");
    device.CSSPixelDims.width = 375;
    device.CSSPixelDims.height = 667;
    device.PhysicalPixelDims.width = 750;
    device.PhysicalPixelDims.height = 1344;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 8");
    device.CSSPixelDims.width = 375;
    device.CSSPixelDims.height = 667;
    device.PhysicalPixelDims.width = 750;
    device.PhysicalPixelDims.height = 1344;
    device.diagonalScreenSize = 4.7;
    device.ppi = 326;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 6+");
    device.CSSPixelDims.width = 414;
    device.CSSPixelDims.height = 736;
    device.PhysicalPixelDims.width = 1080;
    device.PhysicalPixelDims.height = 1920;
    device.diagonalScreenSize = 5.51;
    device.ppi = 401;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 6s+");
    device.CSSPixelDims.width = 414;
    device.CSSPixelDims.height = 736;
    device.PhysicalPixelDims.width = 1080;
    device.PhysicalPixelDims.height = 1920;
    device.diagonalScreenSize = 5.5;
    device.ppi = 401;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 7+");
    device.CSSPixelDims.width = 414;
    device.CSSPixelDims.height = 736;
    device.PhysicalPixelDims.width = 1080;
    device.PhysicalPixelDims.height = 1920;
    device.diagonalScreenSize = 5.5;
    device.ppi = 401;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone 8+");
    device.CSSPixelDims.width = 414;
    device.CSSPixelDims.height = 736;
    device.PhysicalPixelDims.width = 1080;
    device.PhysicalPixelDims.height = 1920;
    device.diagonalScreenSize = 5.5;
    device.ppi = 401;
    devicesArray[i++] = device;
        
    strcpy(device.deviceName, "iPhone X");
    device.CSSPixelDims.width = 375;
    device.CSSPixelDims.height = 812;
    device.PhysicalPixelDims.width = 1125;
    device.PhysicalPixelDims.height = 2436;
    device.diagonalScreenSize = 5.8;
    device.ppi = 458;
    devicesArray[i++] = device;

    Executables_Path(filePath);

    if (argc > 0) {
        if(strstr(argv[0], filePath) != NULL) {
            userArgsOffset = 1;
        } //end if
        strncpy(validCharsForOfNumber, ".0123456789", 11);
        validCharsForOfNumber[11] = '\0';
        strncpy(switchParamHelp, "--help", 6);
        unsigned long parseableDimensionSlen;
        i = userArgsOffset;
        while (i < argc) {
            if (strlen(argv[i]) < kUnitNameBufferSize) { // Mininum dimension arg length is 3 i.e. 2mm or 1in etc.
                i++;
                continue;
            }
            if ( strncmp(argv[i], switchParamHelp, 2) == 0 ) {
                printf("\nUsage...\nsizemebtns <width> [<height>] [device]\n");
                printf("<width> .... A dimension of the desired width of a button {\'mm\', \'cm\' or \'in\'}\n");
                printf("<height> ... [optional] If not supplied assumed to be same as \'width\' {\'mm\', \'cm\' or \'in\'}\n");
                printf("<device> ... i.e. \'iPhone 4s\' or \'iPhone X\' or a phone family eg \'iPhone 6\'\n");
                return 0;
            } else if (strcspn(argv[i], validCharsForOfNumber) == 0) {
                // Arg starting with a decimal point or number has been found.
                parseableDimensionSlen = strlen(argv[i]); // Length excluding terminating NULL char.
                strncpy(unit, (argv[i])+ (parseableDimensionSlen - 2) , 3);
                int j = 0;
                

                while (j < kUnitsLookupLen) {
                    //printf("\n-------------\n%s\n", unitLookup[j].unit);printf("%s",unit);
                    if ( strcmp(unit, &(unitsConversionTable[j][0][0])) == 0) {
                        printf("FOUND UNIT strncmp %d = %d ... and unit is \'%s\'\n", j, strcmp(unit, &(unitsConversionTable[j][0][0])), unit);
                        dimensionNumber = atof(argv[i]); // atoi discards initial whitespace interprets a number and additional chars after the part which it regards can be made into a number are discarded. Also atof() to convert to float
                        unitConversionMultiplier = (float)(unitsConversionTable[j][1][0]);
                        dimensionNumber *= unitConversionMultiplier / 5;    // Do the conversion so dimension is now in millimeters.
                        if (bWidthFound == 0) {
                            bWidthFound = 1;
                            fWidth = dimensionNumber;
                        } else {
                            fHeight = dimensionNumber;
                        }
                        break;
                    }
                    j++;
                }
            } else {
                j = kDevicesArrayLen - 1;
                while (j > -1) {
                    if (strcmp(devicesArray[j].deviceName, argv[i]) == 0) {
                        break;
                    }
                    j--;
                }
                printf("\nj counter value = %d \n", j);
            }

            i++;
        } //end while argument array count thru
        
        i = (j < 0) ? kDevicesArrayLen - 1 : 0;
        j = (j < 0) ? 0 : j;
        while (i > -1) {
            struct DeviceDefn device = devicesArray[j];
            struct WHDims screenXYDimsInMMs = calcScreenWidthHeight(device.CSSPixelDims.width, device.CSSPixelDims.height, device.diagonalScreenSize * kInchesToMMmultiplier);
            printf("--------------------------------------------------\n");
            printf("fWidth = %.2f ",  fWidth);
            printf("fHeight = %f ", fHeight);
            printf("\n%s\n", device.deviceName);
            printf("%d (width)\n", device.CSSPixelDims.width);
            printf("%d (height)\n", device.CSSPixelDims.height);
            printf("%d (ppi)\n", device.ppi);
            printf("%.6f width (mm), %.6f (height)\n", screenXYDimsInMMs.width, screenXYDimsInMMs.height);
            struct WHPixelDims CSSPixelDims = calcCSSPixels(fWidth, fHeight, screenXYDimsInMMs, device.CSSPixelDims, device.PhysicalPixelDims, device.ppi);
            printf("CSS PIXEL DIMENSIONS TO YEILD DESIRED PHYSICAL SIZE ARE (width = %dpx), (height = %dpx)", CSSPixelDims.width, CSSPixelDims.height );
            printf("\n--------------------------------------------------\n");
            i--;
            j++;
        }
        

        
        
    } //end if argc > 0 (args length greater than zero
    printf("\nfinished\n");
    return 0;
}
