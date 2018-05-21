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


#define kUnitsLookupLen             3
struct unitsConversionTable {
    char unit[3];
    float conversionWeighting;
};

char* Executables_Path( char* );

int main(int argc, const char * argv[]) {
    int userArgsOffset = 0;
    char filePath[PATH_MAX + 1];
    
    char fileToExamine[1 + PATH_MAX + FILENAME_MAX];
    char fileNameOnly[FILENAME_MAX];

    float fWidth = 0.0;
    float fHeight = 0.0;
    float dimensionNumber;
    int bWidthFound = 0; // FALSE
    char unit[3];
    // It would be nice to have the conversion ratio as part of this array but at moment do not know how to mix chars with floats in multi-dim array
    char unitsTable[3][2][3] = {
        {{'m',  'm',  '\0'}, 10},
        {{'c',  'm',  '\0'}, 100},
        {{'i',  'n',  '\0'}, 254}
    };
printf("%f", ((float)(unitsTable[2][1][0]) / 10));
printf("\n");
char my[3];
char *pointer;
pointer = &(unitsTable[2][0][0]);
strcpy(my, pointer);
printf("%s",my);
printf("\n");
// printf("%d\n", strcmp(my, unitsTable[0][0][0]));
    struct unitsConversionTable unitLookup[3];

    strcpy(unitLookup[0].unit, "mm");
    unitLookup[0].conversionWeighting = 1.0;
    strcpy(unitLookup[1].unit, "cm");
    unitLookup[1].conversionWeighting = 10.0;
    strcpy(unitLookup[2].unit, "in");
    unitLookup[2].conversionWeighting = 25.4;

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
                strncpy(unit, (argv[i])+ (parseableDimensionSlen - 2) , 3);
                int j = 0;
                while (j < kUnitsLookupLen) {
                    //printf("\n-------------\n%s\n", unitLookup[j].unit);printf("%s",unit);
                    if ( strcmp(unit, unitLookup[j].unit) == 0) {
                        printf("FOUND UNIT strncmp %d = %d ... and unit is \'%s\'\n", j, strcmp(unit, unitLookup[j].unit), unit);
                        dimensionNumber = atof(argv[i]); // atoi discards initial whitespace interprets a number and additional chars after the part which it regards can be made into a number are discarded. Also atof() to convert to float
                        dimensionNumber *= unitLookup[j].conversionWeighting;
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
        strcpy(fileToExamine, filePath); // printf("fileToExamine = %s\n", fileToExamine);
        strcat(fileToExamine, fileNameOnly); // printf("fileToExamine = %s\n", fileToExamine);

        
        
    } //end if argc > 0 (args length greater than zero
    printf("\nfinished\n");
    return 0;
}
