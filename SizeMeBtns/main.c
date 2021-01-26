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
#include <limits.h>     /* LONG_MIN / LONG_MAX */
#include <errno.h>
#include "calcCSSPixels.h"
#include "calcScreenWidthHeight.h"
#include "common.h"

//  I M P R O V E M E N T S    L I S T
// ==================================
// 0\  ̶C̶h̶a̶n̶g̶e̶ ̶u̶s̶e̶ ̶o̶f̶ ̶#̶d̶e̶f̶i̶n̶e̶ ̶m̶a̶c̶r̶o̶ ̶l̶a̶b̶e̶l̶s̶ ̶t̶o̶ ̶c̶l̶e̶a̶r̶e̶r̶ ̶n̶a̶m̶e̶s̶ ̶ ̶
// 1\  ̶U̶s̶e̶ ̶t̶y̶p̶e̶d̶e̶f̶s̶.̶ ̶ ̶
// 2\  ̶P̶e̶r̶s̶i̶s̶t̶ ̶t̶h̶e̶ ̶D̶e̶v̶i̶c̶e̶s̶D̶e̶f̶i̶n̶i̶t̶i̶o̶n̶s̶ ̶d̶a̶t̶a̶ ̶t̶o̶ ̶a̶ ̶f̶i̶l̶e̶ ̶t̶h̶a̶t̶ ̶i̶s̶ ̶r̶e̶a̶d̶ ̶i̶n̶ ̶a̶s̶ ̶a̶ ̶l̶i̶n̶k̶e̶d̶ ̶l̶i̶s̶t̶.̶ ̶ ̶
// 3\  ̶U̶s̶e̶ ̶u̶n̶i̶o̶n̶ ̶i̶n̶s̶t̶e̶a̶d̶ ̶o̶f̶ ̶t̶w̶o̶ ̶s̶e̶p̶a̶r̶a̶t̶e̶ ̶l̶a̶r̶g̶e̶l̶y̶ ̶s̶i̶m̶i̶l̶a̶r̶ ̶s̶t̶r̶u̶c̶t̶s̶ ̶s̶t̶r̶u̶c̶t̶ ̶W̶H̶D̶i̶m̶s̶ ̶a̶n̶d̶ ̶s̶t̶r̶u̶c̶t̶ ̶W̶H̶P̶i̶x̶e̶l̶D̶i̶m̶s̶.̶ ̶ ̶ ̶
// 4\  ̶E̶m̶p̶l̶o̶y̶ ̶u̶s̶e̶ ̶o̶f̶ ̶C̶O̶N̶S̶T̶s̶ ̶w̶h̶e̶r̶e̶ ̶a̶p̶p̶r̶o̶p̶r̶i̶a̶t̶e̶.̶ ̶ ̶
// 5\ Separate out into separate files.

WidthHeightDims calcCSSPixels(float width, float height, WidthHeightDims screenWidthHeightInMM, WidthHeightDims CSSPixelDims, WidthHeightDims PhysicalPixelDims, int screenPPI);
WidthHeightDims calcScreenWidthHeight(int widthInPixels, int heightInPixels, float screenDiagnalSizeInMM);
char* Executables_Path( char* );
DeviceDefn * readInToDefinitionList( const char* );
int parsePipeDelimited(DeviceDefn* deviceDefnPtrLinkedList, char* line);
int checkStrToLongNum(char *charBuff);
int checkStrToFloat(char *charBuff);
void freeList( DeviceDefn * );

int main(int argc, const char * argv[]) {
    int i;
    int userArgsOffset;
    char filePath[PATH_MAX + 1];
    
    const char switchParamHelp[7] = "--help\0";
    const char validCharsForOfNumber[12] = ".0123456789\0";

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
    const char unitsConversionTable[kNumOfDifferentUnits][2][kUnitNameBufferSize] = {
        {{"mm"}, 5},
        {{"cm"}, 50},
        {{"in"}, kInchesToMMmultiplier * 5}
    };
    i = 0;
    //
    Executables_Path(filePath);
    DeviceDefn *deviceDefinitionPtrLinkedList = readInToDefinitionList(filePath);
    if (deviceDefinitionPtrLinkedList == NULL) {
        fprintf(stderr, "Error couldn't read device definitions file");
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
                        // printf("FOUND UNIT strncmp %d = %d ... and unit is \'%s\'\n", k, strcmp(unit, &(unitsConversionTable[k][0][0])), unit);
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
            const WidthHeightDims screenXYDimsInMMs = calcScreenWidthHeight(currentItemPtr->CSSPixelDims.width.inPixels, currentItemPtr->CSSPixelDims.height.inPixels, currentItemPtr->diagonalScreenSize * kInchesToMMmultiplier);
            
            // printf("--------------------------------------------------\n");
            //  printf("fWidth = %.2f ",  screenXYDimsInMMs.width.inMMs);
            // printf("fHeight = %f ", screenXYDimsInMMs.height.inMMs);
            // printf("\n%s\n", device.deviceName);
            // printf("%d (width)\n", device.CSSPixelDims.width);
            // printf("%d (height)\n", device.CSSPixelDims.height);
            // printf("%d (ppi)\n", device.ppi);
            // printf("%.6f width (mm), %.6f (height)\n", screenXYDimsInMMs.width, screenXYDimsInMMs.height);
            const WidthHeightDims CSSPixelDims = calcCSSPixels(fWidth, fHeight, screenXYDimsInMMs, currentItemPtr->CSSPixelDims, currentItemPtr->PhysicalPixelDims, currentItemPtr->ppi);
            printf("CSS PIXEL DIMENSIONS TO YEILD DESIRED PHYSICAL SIZE ARE (width = %dpx), (height = %dpx)\n for device \'%s\'", CSSPixelDims.width.inPixels, CSSPixelDims.height.inPixels, currentItemPtr->deviceName );
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
    DeviceDefn *deviceDefnPtrLinkedList = NULL;
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

int parsePipeDelimited(DeviceDefn* destinationStructPtr, char* line)
{
    int numOfFmtStrMatches = sscanf (line,"%[^|]|%d|%d|%d|%d|%f|%hd",
                                     (*destinationStructPtr).deviceName,
                                     &(destinationStructPtr->CSSPixelDims.width.inPixels),
                                     &(destinationStructPtr->CSSPixelDims.height.inPixels),
                                     &(destinationStructPtr->PhysicalPixelDims.width.inPixels),
                                     &(destinationStructPtr->PhysicalPixelDims.height.inPixels),
                                     &(destinationStructPtr->diagonalScreenSize),
                                     &(destinationStructPtr->ppi)
                                     );
    //printf("\n-------------\nnumOfFmtStrMatches = %zu\n-------------\n", LONG_MAX);
    if (numOfFmtStrMatches != 7) { //Determine where error is
        if (1 != (sscanf (line, "%[^|]|", (*destinationStructPtr).deviceName))) {
            fprintf(stderr, "Error parsing Devices Definition data file. Expected \'|\' (PIPE delimited lines with first item being device name (i.e. \'iPhone X\')");
        } else {
            char delim[2] = "|\0";
            char *pch = strtok(line, delim);
            int i = 0;
            while (pch != NULL)
            {
                if (i == 5 && checkStrToFloat(pch) != 0) {
                    fprintf(stderr, "Error parsing Devices Definition data file. Expected one float in 6th position of | (PIPE) delimited line");
                } else if (i && checkStrToLongNum(pch) != 0) {
                     fprintf(stderr, "Error parsing Devices Definition data file. Expected four ints (long precision) after device name all delimited by pipe");
                }
                pch = strtok (NULL, delim);
                i++;
            }
            
        }
        return -1;
    }
    return 0;
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

int checkStrToLongNum(char *charBuff) {
    char c = '\0';
    char *pEnd = &c;
    errno = 0;
    long int result = strtol(charBuff, &pEnd, 10);
    if ((result == LONG_MAX || result == LONG_MIN) && errno != 0)
    {
        return -1; // Under / Over -flow
    }
    if (*pEnd != '\0')
    {
        return -2; // Extra garbage to the right of chars parseable as valid number.
    }
    return 0;
}

int checkStrToFloat(char *charBuff) {
    char c = '\0';
    char *pEnd = &c;
    errno = 0;
    strtof(charBuff, &pEnd);
    if (errno == ERANGE)
    {
        return -1;
    }
    if (*pEnd != '\0')
    {
        return -2;
    }
    return 0;
}
