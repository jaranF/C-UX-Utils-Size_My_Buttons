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

char* Executables_Path( char* );

int main(int argc, const char * argv[]) {
    
    int userArgsOffset = 0;
    char filePath[PATH_MAX + 1];
    
    char fileToExamine[1 + PATH_MAX + FILENAME_MAX];
    char fileNameOnly[FILENAME_MAX];


    //sort_structs_example();
    Executables_Path(filePath);
    printf("\nargv counun %4d\n", argc);
    if (argc > 0) {
        if(strstr(argv[0], filePath) != NULL) {
            userArgsOffset = 1;
        } //end if

        int i = userArgsOffset;
        char switchParamHelp[7];
        strcpy(switchParamHelp, "--help");
        while (i < argc) {
            if ( strncmp(argv[i], switchParamHelp, 2) == 0 ) {
                printf("\nUsage...\nsizemebtns <width> [<height>] [device]\n");
                printf("<width> .... A dimension of the desired width of a button {\'mm\', \'cm\' or \'in\'}\n");
                printf("<height> ... [optional] If not supplied assumed to be same as \'width\' {\'mm\', \'cm\' or \'in\'}\n");
                printf("<device> ... i.e. \'iPhone 4s\' or \'iPhone X\' or a phone family eg \'iPhone 6\'\n");
                
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
        strcpy(fileToExamine, filePath); // printf("fileToExamine = %s\n", fileToExamine);
        strcat(fileToExamine, fileNameOnly); // printf("fileToExamine = %s\n", fileToExamine);

        
        
    } //end if argc > 0 (args length greater than zero
    return 0;
}
