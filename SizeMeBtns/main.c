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
#include "deviceDefinitions.h"
#include "calcCSSPixels.h"
#include "calcScreenWidthHeight.h"

int calcCSSPixels(float width, float height, float screenDiagnalSize, int screenPPI);
struct WHDims calcScreenWidthHeight(float ratio, float screenDiagnalSize);
char* Executables_Path( char* );
struct DeviceDefn* getDevices();

#define kUnitsLookupLen             3
#define kUnitNameBufferSize         3
#define kDevicesArrayLen            13

struct WHDims {
    float width;
    float height;
};
struct WHPixelDims {
    int width;
    int height;
};
struct DeviceDefn {
    char deviceName[20];
    struct WHPixelDims pixelDims;
    float diagonalScreenSize;
    int ppi;
};


int main(int argc, const char * argv[]) {
    int i;
    int userArgsOffset;
    char switchParamHelp[7];
    char validCharsForOfNumber[12];    char filePath[PATH_MAX + 1];
    char fileNameOnly[FILENAME_MAX]; // @Todo : rename

    float fWidth = 0.0;
    float fHeight = 0.0;
    float dimensionNumber;
    float unitConversionMultiplier;
    int bWidthFound = 0; // FALSE
    char unit[kUnitNameBufferSize];
    size_t devicesStructLen;
    int j;                              // Used for iteration through devices Struct Array
    struct WHDims screenWidthHeight = calcScreenWidthHeight(0.5635, 5.5);
    // printf("\n........\n%7.4f\n%7.4f\n........\n", screenWidthHeight.height, screenWidthHeight.width );

    
    // The conversion multiplies to get mm are 10mm (i.e. 10mm to 1cm) and
    // 25.4. But because chars are treated as sign ints when you cast them
    // to a number type you can't conevert the 25.4 to a whole number using
    // the most staightforward option which is to multiply by 10. Instead I
    // used a lower multiplie, i.e. 4, to keep the numbers below 127.
    char unitsConversionTable[kUnitsLookupLen][2][kUnitNameBufferSize] = {
        {{'m',  'm',  '\0'}, 4},
        {{'c',  'm',  '\0'}, 40},
        {{'i',  'n',  '\0'}, 98}
    };
    struct DeviceDefn* devicesLookupPointer = getDevices();
    devicesStructLen = sizeof(devicesLookupPointer[0]);
    printf("devicesStructArray[2] First Struct Item / Struct Len = %zu", devicesStructLen);
    printf("\n++++++++++\n%s\n__________\n", devicesLookupPointer[2].deviceName);
    //sort_structs_example();
    Executables_Path(filePath);
    
    // printf("\nargv counun %4d\n", argc);
    if (argc > 0) {
        if(strstr(argv[0], filePath) != NULL) {
            userArgsOffset = 1;
        } //end if
    printf("\n++++++++++\n%s\n--------\n", devicesLookupPointer[0].deviceName);
         strncpy(validCharsForOfNumber, ".0123456789", 11);
        validCharsForOfNumber[11] = '\0';
         printf("\n++++++++++\n%s\n¬¬¬¬¬¬¬¬¬¬\n", devicesLookupPointer[2].deviceName);
        strncpy(switchParamHelp, "--help", 6);
        unsigned long parseableDimensionSlen;
        i = 0;
        while (i < argc) {
            if (strlen(argv[i]) < kUnitNameBufferSize) { // Mininum dimension arg length is 3 i.e. 2mm or 1in etc.
                i++;
                continue;
            }
            printf("looking for params");
            if ( strncmp(argv[i], switchParamHelp, 2) == 0 ) {
                printf("\nUsage...\nsizemebtns <width> [<height>] [device]\n");
                printf("<width> .... A dimension of the desired width of a button {\'mm\', \'cm\' or \'in\'}\n");
                printf("<height> ... [optional] If not supplied assumed to be same as \'width\' {\'mm\', \'cm\' or \'in\'}\n");
                printf("<device> ... i.e. \'iPhone 4s\' or \'iPhone X\' or a phone family eg \'iPhone 6\'\n");
                
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
                        dimensionNumber *= unitConversionMultiplier / 4;
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
                j = 0;
                
                while (j < kDevicesArrayLen) {
                                    if (strcmp(devicesLookupPointer[j].deviceName, argv[i]) == 0) {
                      printf("\n-------------\n");
                      printf("%s\n", devicesLookupPointer[j].deviceName);
                      printf("%d (width)\n", devicesLookupPointer[j].pixelDims.width);
                      printf("%d (height)\n", devicesLookupPointer[j].pixelDims.height);
                      printf("%d (ppi)\n", devicesLookupPointer[j].ppi);
                      printf("\n-------------\n");
                  }
                  j++;
                }
                // devicesStructsArrayLen = sizeof(DeviceDefn);

                char keys[] = "e";
                unsigned long k;
                k = strcspn (argv[i],keys);
                printf ("The first number in str is at position %zu.\n",k);
                
                strncpy(fileNameOnly, argv[i], k);
                fileNameOnly[k] = '\0';
                printf("fileNameOnly = %s\n", fileNameOnly);
            }
            printf("arg[%d] = \'%s\'\n", i, argv[i]);
            i++;
        } //end while
        printf("fWidth = %.2f ",  fWidth);
        printf("fHeight = %f ", fHeight);
        calcCSSPixels(fWidth, fHeight, 5.5, 401);

        
        
    } //end if argc > 0 (args length greater than zero
    printf("\nfinished\n");
    return 0;
}
