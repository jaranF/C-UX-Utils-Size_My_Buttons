//
//  Executables_Path.c
//  Useful_Reusable_Code
//
//  Created by Jaran F on 19/02/2017.
//  Copyright (c) 2017 JaranF. All rights reserved.
//

#include <stdio.h>
#include <mach-o/dyld.h>/* _NSGetExecutablePath */
#include <limits.h>		/* PATH_MAX */
#include <unistd.h>		/* execve   */
#include <libgen.h>		/* dirname  */
#include <string.h>		/* strcpy   */
char* Executables_Path(char*);
void Test_Executables_Path( void );

char* Executables_Path(char* fullPathToExecutable) {
    char pathbuf[PATH_MAX + 1];
    char *bundle_id;
    int unsigned  bufsize = sizeof(pathbuf);
    char* charBuffPointer;
    //Determine Path this executable is running from
    _NSGetExecutablePath( pathbuf, &bufsize);
    
    bundle_id = dirname(pathbuf);
    
    strcpy(fullPathToExecutable, bundle_id);
    strcat(fullPathToExecutable, "/");
    charBuffPointer = fullPathToExecutable;
    return charBuffPointer;
}

void Test_Executables_Path() {
    char filePath[PATH_MAX + 1];
    printf("\n\n%s\n\n", Executables_Path(filePath));
}