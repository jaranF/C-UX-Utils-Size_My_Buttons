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

int calcCSSPixels(float width, float height, float screenDiagnalSize, int screenPPI);
int* calcX(float width, float height, float screenDiagnalSize, int screenPPI);
char* Executables_Path( char* );


#define kUnitsLookupLen             3
#define kUnitNameBufferSize         3

int* calcX(float width, float height, float screenDiagnalSize, int screenPPI){
  int dimensionsWidthHeight[2] = { 9, 8 };
  int* dimensionsPointer;
  dimensionsPointer = dimensionsWidthHeight; // shortcut for dimensionsPointer = &(dimensions[0]);
  return dimensionsPointer;
}

int main(int argc, const char * argv[]) {
    int userArgsOffset = 0;
    char filePath[PATH_MAX + 1];
    
    char fileToExamine[1 + PATH_MAX + FILENAME_MAX];
    char fileNameOnly[FILENAME_MAX];

    float fWidth = 0.0;
    float fHeight = 0.0;
    float dimensionNumber;
    float unitConversionMultiplier;
    int bWidthFound = 0; // FALSE
    char unit[kUnitNameBufferSize];
    int dimWidthHeightCSSPixels[2];
    int* dimWHPointer = calcX(6.0, 4.5, 5.5, 401);
    int w = *(dimWHPointer);
    int h = *(++dimWHPointer);
    printf("\ndim = %d\n", w );
    printf("\ndim = %d\n", h );
    
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
    //sort_structs_example();
    Executables_Path(filePath);
    // printf("\nargv counun %4d\n", argc);
    if (argc > 0) {
        if(strstr(argv[0], filePath) != NULL) {
            userArgsOffset = 1;
        } //end if

        int i = userArgsOffset;
        char switchParamHelp[7];
        char validCharsForOfNumber[12];
        strcpy(validCharsForOfNumber, ".0123456789");
        strcpy(switchParamHelp, "--help");
        unsigned long parseableDimensionSlen;
        

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
                char keys[] = "mci";
                unsigned long k;
                k = strcspn (argv[i],keys);
                printf ("The first number in str is at position %zu.\n",k);
                
                strncpy(fileNameOnly, argv[i], k);
                fileNameOnly[k] = '\0';
                int width = atoi(fileNameOnly);
                printf("fileNameOnly = %s\n", fileNameOnly);
                printf("\nwidth = %d\n", width + 1);
            }
            printf("arg[%d] = \'%s\'\n", i, argv[i]);
            i++;
        } //end while
        printf("fWidth = %.2f ",  fWidth);
        printf("fHeight = %f ", fHeight);
        calcCSSPixels(fWidth, fHeight, 5.5, 401);
        strcpy(fileToExamine, filePath); // printf("fileToExamine = %s\n", fileToExamine);
        strcat(fileToExamine, fileNameOnly); // printf("fileToExamine = %s\n", fileToExamine);

        
        
    } //end if argc > 0 (args length greater than zero
    printf("\nfinished\n");
    return 0;
}
