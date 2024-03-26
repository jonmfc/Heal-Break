By Jonathan Mitelman
// Usage: ./mybreak <source file> <prefix of new file name> <chunk size (K)>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// this function is responsible for ensuring that the chunk size is not larger the 1gb and smaller then 1kb. 
void chunk_verify(int chunk_size){
if (chunk_size <= 0){
    printf("%d", chunk_size);
    printf("The chunk size needs to be at least 1k\n");
    exit(1);
}
}

// this is the primary function and acts as the main hub for the entire program of breaking up a file into smaller files
int main(int argc, char *argv[]){
    // ensures inputs are valid, if they are not it won't run
    if (argc != 4){
        printf("argc = %d => usage: mybreak <source> <prefix> <chunk size (K)>\n", argc);
        exit(1);
    }
    // this is all declaring variables and then opening the file
    char *files_names = argv[1];
    char *prefix_names = argv[2];
    int chunk_size = atoi(argv[3]);
    chunk_size = chunk_size * 1024;
    FILE* file = fopen(files_names, "r");
    // when file cant be opened it will exit
    if (file == NULL)
        printf("Error, could not open file: %s\n", files_names), exit(1);

    int chunk_counter = 1024;
    int count = 1;
    chunk_verify(chunk_size);
    int file_num = 0;
    char *name_buffer = malloc((1024) * sizeof(char));
    memset(name_buffer, 0, 1024);

int chunk_count = 0;
// this loop is responsible for moving the file contents into the smaller chunk files
while (1) {
    // this part is in
    FILE* prefix_file = NULL;
    asprintf(&name_buffer, "%s.%.32d", prefix_names, file_num);
    prefix_file = fopen(name_buffer, "w");
    
    // if can't be created it will exit and report the error.
    if (prefix_file == NULL) {
        printf("Error, could not created: '%s'\n", name_buffer);
        exit(1);
    }

    char buffer[chunk_size];
    
    int bytes_read = fread(buffer, 1, chunk_size, file);
    // when the bytes cant be read that means the loop is done and itll exit.
    if (bytes_read == 0) {
        remove(name_buffer);
        break;
    }
    else{
        printf(" starting %s\n", name_buffer);
        chunk_count = chunk_count + 1;
    }
    
    // this part is in charge of inputting characters from the file directly into the prefix file. this goes through the buffer.
    int character_read = 0;
    while  (character_read < bytes_read){
            putc(buffer[character_read], prefix_file);
                character_read = character_read + 1;
    }


    fclose(prefix_file);

    file_num = file_num + 1;
    
}
printf("Finished [%d] chunks produced for %s\n", chunk_count, files_names);
}
