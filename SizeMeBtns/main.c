//
//  main.c
//  SizeMeBtns
//
//  Created by Jaran F on 14/05/2018.
//

#include <stdio.h>
//Runtime_Environment
#include <limits.h>		/* PATH_MAX */

#include <string.h>		/* strcpy   */
#include <stdlib.h>     /* qsort    */
#include <mach-o/dyld.h>/* bool */
#include "calcCSSPixels.h"
#include "calcScreenWidthHeight.h"
#include "common.h"

char gDeviceDefnStructAnnot[7][2][kTypeDescriptionMaxLen] = {
    {{"string"}, 16},
    {{"int"}, 6},
    {{"int"}, 6},
    {{"int"}, 6},
    {{"int"}, 6},
    {{"float"}, 8},
    {{"int"}, 6}
};


//  I M P R O V E M E N T S    L I S T
// ==================================
// 0\ Change use of #define macro labels to clearer names.
// 1\ Use typedefs.
// 2\ Persist the DevicesDefinitions data to a file that is read in as a linked list.
// 3\ Use union instead of two separate largely similar structs 'struct WHDims' and 'struct WHPixelDims'.
// 4\ Separate out into separate files.

WHPixelDims calcCSSPixels(float width, float height, WHDims screenWidthHeightInMM, WHPixelDims CSSPixelDims, WHPixelDims PhysicalPixelDims, int screenPPI);
WHDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM);
char* Executables_Path( char* );
DeviceDefn * readInToDefinitionList( const char* );
void parsePipeDelimited(DeviceDefn* deviceDefnPtrLinkedList, char* line);
void freeList( DeviceDefn * );

int main(int argc, const char * argv[]) {
    int i;
    int userArgsOffset;
    char filePath[PATH_MAX + 1];
    
    char switchParamHelp[7] = "--help\0";
    char validCharsForOfNumber[12] = ".0123456789\0";

    float dimensionNumber;
    int bWidthFound = 0; // FALSE
    float unitConversionMultiplier;
    char unit[kUnitNameBufferSize];

    DeviceDefn device;
    DeviceDefn devicesArray[kDevicesArrayLen];
    int j = sizeof(devicesArray) / sizeof(device) - 1;;                              // Used for iteration through devices Struct Array
    
    float fWidth = 0.0;
    float fHeight = 0.0;
    // The conversion multiplies to get mm are 10mm (i.e. 10mm to 1cm) and
    // 25.4 (inch). But because chars are treated as signed bytes when you
    // cast them to a number type you can't convert the 25.4 to a whole
    // number using the most staightforward option which is to multiply
    // by 10. Instead I used a lower multiplie, i.e. 5, to keep the
    // numbers below 128 but still have the converted to whole integers.
    char unitsConversionTable[kNumOfDifferentUnits][2][kUnitNameBufferSize] = {
        {{"mm"}, 5},
        {{"cm"}, 50},
        {{"in"}, kInchesToMMmultiplier * 5}
    };
    i = 0;
    //
    Executables_Path(filePath);
    DeviceDefn *deviceDefinitionPtrLinkedList = readInToDefinitionList(filePath);
    if (deviceDefinitionPtrLinkedList == NULL) {
        fprintf(stderr, "Error couldn't red device definitions file");
        exit (-1);
    }
    DeviceDefn *foundItemPtr, *currentItemPtr = deviceDefinitionPtrLinkedList;
    foundItemPtr = NULL;
    if (argc > 0) {
        if(strstr(argv[0], filePath) != NULL) {
            userArgsOffset = 1;
        } //end if
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
                int k = 0;
                //
                //
                while (k < kNumOfDifferentUnits) {
                    //printf("\n-------------\n%s\n", unitLookup[j].unit);printf("%s",unit);
                    if ( strcmp(unit, &(unitsConversionTable[k][0][0])) == 0) {
                         printf("FOUND UNIT strncmp %d = %d ... and unit is \'%s\'\n", k, strcmp(unit, &(unitsConversionTable[k][0][0])), unit);
                        dimensionNumber = atof(argv[i]); // atoi discards initial whitespace interprets a number and additional chars after the part which it regards can be made into a number are discarded. Also atof() to convert to float
                        unitConversionMultiplier = (float)(unitsConversionTable[k][1][0]);
                        dimensionNumber *= unitConversionMultiplier / 5;    // Do the conversion so dimension is now in millimeters.
                        if (bWidthFound == 0) {
                            bWidthFound = 1;
                            fWidth = dimensionNumber;
                        } else {
                            fHeight = dimensionNumber;
                        }
                        break;
                    }
                    k++;
                }
            } else {
                j = 0;
                while (currentItemPtr->nextItemPtr != NULL) {
                    if (strcmp(currentItemPtr->deviceName, argv[i]) == 0) {
                        foundItemPtr = currentItemPtr;
                        break;
                    }
                    currentItemPtr = currentItemPtr->nextItemPtr;
                    j++;
                }
            }
	
            i++;
        } //end while argument array count thru
        i = (j < 0) ? kDevicesArrayLen - 1 : 0; //TODO logic seems to be that if a search thru supplied cmdline args didnt find device name then just set i to all of the devices array. else i is 1 somoutputconverted dims for just one device
        j = (j < 0) ? 0 : j;
        currentItemPtr = foundItemPtr != NULL ? foundItemPtr : deviceDefinitionPtrLinkedList;
        while (currentItemPtr->nextItemPtr != NULL && i > -1) {
            WHDims screenXYDimsInMMs = calcScreenWidthHeight(currentItemPtr->CSSPixelDims.width, currentItemPtr->CSSPixelDims.height, currentItemPtr->diagonalScreenSize * kInchesToMMmultiplier);
            // printf("--------------------------------------------------\n");
            //  printf("fWidth = %.2f ",  fWidth);
            // printf("fHeight = %f ", fHeight);
            // printf("\n%s\n", device.deviceName);
            // printf("%d (width)\n", device.CSSPixelDims.width);
            // printf("%d (height)\n", device.CSSPixelDims.height);
            // printf("%d (ppi)\n", device.ppi);
            // printf("%.6f width (mm), %.6f (height)\n", screenXYDimsInMMs.width, screenXYDimsInMMs.height);
            WHPixelDims CSSPixelDims = calcCSSPixels(fWidth, fHeight, screenXYDimsInMMs, currentItemPtr->CSSPixelDims, currentItemPtr->PhysicalPixelDims, currentItemPtr->ppi);
            printf("CSS PIXEL DIMENSIONS TO YEILD DESIRED PHYSICAL SIZE ARE (width = %dpx), (height = %dpx)\n for device \'%s\'", CSSPixelDims.width, CSSPixelDims.height, currentItemPtr->deviceName );
            // printf("\n--------------------------------------------------\n");
            i--;
            j++;
        }  
    } //end if argc > 0 (args length greater than zero
    if (deviceDefinitionPtrLinkedList != NULL) {
       freeList(deviceDefinitionPtrLinkedList);
    }
    printf("\nfinished\n");
    return 0;
}

DeviceDefn * readInToDefinitionList(const char* filePath) {
    int retValue = 0;
    FILE *fp;
    fp = fopen(kDevicesDefnFileName, "r" );
    DeviceDefn *deviceDefnPtrLinkedList;
    if ( NULL == fp ) {
        printf("Error opening file \'%s\'\n", kDevicesDefnFileName);
        printf("In file path...\n");
        printf("%s\n", filePath);
        retValue = -1;
        DeviceDefn dummyDefn;
        printf("\n-----\n");
        printf("sizeof struct = %zu\n", SIZEOFDELIMITEDSTRUCT( dummyDefn ) +1);

    } else {
        DeviceDefn *currentItemPtr = NULL, *prevItemPtr;
        int scanfResult;
        DeviceDefn dummyDefn;
        char allFieldsLineBuff[199 + 1]; // +1 for pipi separator between struct's field and +1 to that for trailing NULL char/
        prevItemPtr = NULL;
        //
        while (kOK == (scanfResult = fscanf(fp, kScanToNewlinePattern, allFieldsLineBuff))) {
            currentItemPtr = malloc(sizeof(DeviceDefn));
            if (prevItemPtr != NULL) {
                prevItemPtr->nextItemPtr = currentItemPtr;
            } else {
                deviceDefnPtrLinkedList = currentItemPtr;
            }
            parsePipeDelimited(currentItemPtr, allFieldsLineBuff);
            prevItemPtr = currentItemPtr;
            retValue = 0;
        }
        currentItemPtr->nextItemPtr = NULL;
        if (scanfResult != EOF) fprintf( stderr,"invalid data format");
        /*         fprintf( stderr, "Invalid data near offset %lu, %d: %s\n",
         (long unsigned int)ftello(fp), scanResult, strerror(scanResult) );
         */
        fclose(fp);
    }
    return retValue == 0 ? deviceDefnPtrLinkedList : NULL;
}

void parsePipeDelimited(DeviceDefn* destinationStructPtr, char* line)
{
    char *pch, *base;
    char delim[2] = "|\0";
    base = (char*)destinationStructPtr;
    int i = 0;
    pch = strtok (line, delim);
    while (pch != NULL)
    {
        if (i == 0) {
            strlcpy(destinationStructPtr->deviceName, pch, sizeof(destinationStructPtr->deviceName));
        }
        else if (i == 1) {
            destinationStructPtr->CSSPixelDims.width = atoi(pch);
        }
        else if (i == 2) {
            destinationStructPtr->CSSPixelDims.height = atoi(pch);
        }
        else if (i == 3) {
            destinationStructPtr->PhysicalPixelDims.width = atoi(pch);
        }
        else if (i == 4) {
            destinationStructPtr->PhysicalPixelDims.height = atoi(pch);
        }
        else if (i == 5) {
            destinationStructPtr->diagonalScreenSize = atof(pch);
        }
        else if (i == 6) {
            destinationStructPtr->ppi = atoi(pch);
        }
        else  {
            fprintf(stderr, "Help!");
        }
        pch = strtok (NULL, delim);
        i++;
    }
}

void freeList(DeviceDefn *head)
{
    DeviceDefn * tmp;
    //
    while (head != NULL)
    {
        tmp = head;
        head = head->nextItemPtr;
        tmp->nextItemPtr = NULL;
        free(tmp);
    }
}
