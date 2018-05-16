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

#define kCardinalOfDigits           4
#define kUnitsLookupLen             3
char* Executables_Path( char* );

int main(int argc, const char * argv[]) {
    
    int userArgsOffset = 0;
    char filePath[PATH_MAX + 1];
    
    char fileToExamine[1 + PATH_MAX + FILENAME_MAX];
    char fileNameOnly[FILENAME_MAX];

    float fWidth = 0.0;
    float fHeight = 0.0;
    float conversionFactor = 1.0;
    float dimensionNumber;
    int bWidthFound = 0; // FALSE
    char unit[3];
    // It would be nice to have the conversion ratio as part of this array but at moment do not know how to mix chars with floats in multi-dim array
    const char unitsLookup[kUnitsLookupLen][3] = {
        {'m',  'm',  0},
        {'c',  'm',  0},
        {'i',  'n',  0}
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
        char validParseableUnitsMM[3];
        char validParseableUnitsCM[3];
        char validParseableUnitsIN[3];
        strcpy(validCharsForOfNumber, ".0123456789");
        strcpy(validParseableUnitsMM, "mm");
        validParseableUnitsMM[2] = '\0';
        strcpy(validParseableUnitsCM, "cm");
        validParseableUnitsCM[2] = '\0';
        strcpy(validParseableUnitsIN, "in");
        validParseableUnitsIN[2] = '\0';
        unsigned long parseableDimensionSlen;
        
        strcpy(switchParamHelp, "--help");
        while (i < argc) {
            if (strlen(argv[i]) < 3) {
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
                strncpy(unit, (argv[i])+ (parseableDimensionSlen - 2) , 2);
                int j = 0;
                while (j < kUnitsLookupLen) {
                    if ( strcmp(unit, unitsLookup[j]) == 0) {
                        printf("FOUND UNIT strncmp %d = %d ... and unit is \'%s\'\n", j, strcmp(unit, unitsLookup[j]), unit);
                        dimensionNumber = atof(argv[i]); // atoi discards initial whitespace interprets a number and additional chars after the part which it regards can be made into a number are discarded. Also atof() to convert to float
                        if ( strcmp(unit, "in") == 0 ) {
                            conversionFactor = 25.4;
                        } else if ( strcmp(unit, "cm") == 0) {
                            conversionFactor = 10;
                        } else {
                            conversionFactor = 1.0;
                        }
                        dimensionNumber *= conversionFactor;
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
                unsigned long j;
                j = strcspn (argv[i],keys);
                printf ("The first number in str is at position %zu.\n",j);
                
                strncpy(fileNameOnly, argv[i], j);
                fileNameOnly[j] = '\0';
                int width = atoi(fileNameOnly);
                printf("fileNameOnly = %s\n", fileNameOnly);
                printf("\nwidth = %d\n", width + 1);
            }
            printf("arg[%d] = \'%s\'\n", i, argv[i]);
            i++;
        } //end while
        printf("fWidth = %.2f ",  fWidth);
        printf("fHeight = %f ", fHeight);
        strcpy(fileToExamine, filePath); // printf("fileToExamine = %s\n", fileToExamine);
        strcat(fileToExamine, fileNameOnly); // printf("fileToExamine = %s\n", fileToExamine);

        
        
    } //end if argc > 0 (args length greater than zero
    printf("\nfinished\n");
    return 0;
}
