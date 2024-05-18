/*Online unzipping*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    /* The filename should be passed as first argument */
    FILE *fptr;
    char filename[1000];
    char myString[1000];
    char command[1000];
    printf("Enter the filename to open \n");
    scanf("%s", filename);

    /* If no argument is given, a small error/usage message should be printed */
    if (filename == NULL) {
        printf("Usage: %s filename\n", filename);
        exit(1);
    }

    /* Use strstr() to locate the substring ".gz" in the filename. If it is contained,
    the file should be decompressed via the help of the system() function. */
    if (strstr(filename, ".gz") != NULL) {
        strcpy(command, "gunzip ");
        strcat(command, filename);
        system(command);
    }

    /* The file should be printed linme by line */
    fptr = fopen(filename, "r");
    if (fptr != NULL) {
        while(fgets(myString, 1000, fptr)) {
        printf("%s", myString);
    }
    // Close file
    fclose(fptr);
    }
    else {
        printf("File not found\n");
    }

    /* If the file was compressed before it was printed, it should be compressed
    again, before the program stops */
    if (strstr(filename, ".gz") != NULL) {
        strcpy(command, "gzip ");
        strcat(command, filename);
        system(command);
    }

    return 0;
}