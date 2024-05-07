#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char** argv){
    //Check for arguments and valid file
    if(argc < 2){
        printf("Please provide an input file, exiting...\n");
        exit(1);
    }
    FILE* suppression_file = fopen(argv[1], "r");
    if(suppression_file == NULL){
        printf("Suppression file is not valid, exiting...\n");
        exit(1);
    }
    //File is okay to use, go crazy. 
    fseek(suppression_file, 0, SEEK_END);
    int total_bytes = ftell(suppression_file); 
    fseek(suppression_file, 0, 0);
    
    char* buffer = calloc(sizeof(char), total_bytes+1);
    
    fread(buffer, total_bytes, 1, suppression_file);
    char* temp = buffer;
 
    char* original_location = buffer;
    while((temp = strstr(buffer, "{")) != NULL){
        char* temp_2 = strstr(buffer, "}");
        if(temp_2 == NULL){
            break;
        }
        printf("%.*s\n", (int) (temp_2 - temp) + 1, temp);
        // printf("%s\n", temp);
        buffer = temp_2 + 1;
    }
    printf("\n");

    free(original_location);
    fclose(suppression_file);
}