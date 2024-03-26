By Jonathan Mitelman

// Usage:  <source file> <prefix file name> <chunk size (K) (dont actually write in K just put the number)> <number of chunks to combine>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
// in the event of an error this function will report it, otherwise if no error is present it will say the file was healed succesfully.
int error(int error_detected){
    if (error_detected == 1){
        printf("Error: files could not be healed.\n");
        exit(1);
    }
    else{
        printf("File was healed succesfully!\n");
        exit(1);
    }
    return 0;
}
// this function is responsible for ensuring proper chunk sizes.
void chunk_verify(int chunk_size){
if (chunk_size <= 0){
    printf("%d", chunk_size);
    printf("The chunk size needs to be at least 1k\n");
    exit(1);
}

if (chunk_size >= (1024 * 1024 * 1024)){
    printf("The chunk size needs to be less than 1g\n");
    exit(1);
    }

}

// This function is the main hub for the myheal program and is in charge of almost everything. 
int main(int argc, char *argv[]){
    // this ensures proper inputs from the start
    if (argc != 5){
        printf("argc = %d => usage: myheal <source> <prefix> <chunk size (K)> <num chunks>\n", argc);
        exit(0);
    }
    // assuming inputs are proper it will declare the variables
    char *source = argv[1];
    char *prefix = argv[2];
    int chunk_size = atoi(argv[3]);
    chunk_size = chunk_size * 1024;
    int num_chunks = atoi(argv[4]);
    // here it verifies the chunk size
    chunk_verify(chunk_size);
    // this opens the file as a binary data file as opposed to regular one to ensure data can be read properly in the right forms.
    FILE *source_file = fopen(source, "wb");
    if (source_file == NULL) {
        fprintf(stderr, "Unable to create or open file '%s' for writing.\n", source);
        exit(1);
    }
    // here we declare the size of the buffer for the memory of each chunk file
    char buffer[chunk_size];
    int count = 0;
    int error_detected = 0;
    // this loop iterates through each of the chunks combing them to the file that was given at the start
    while (count < num_chunks) {
        sprintf(buffer, "%s.%032d", prefix, count++);
        // since the chunk files dont need to be edited but only read we will open them in rb, once again via binary.
        FILE *chunk_file = fopen(buffer, "rb");
        // when a chunk file is missing it will be mentioned that an error is detected at the end, also the error is automatically told.
        if (chunk_file == NULL) {
            fprintf(stderr, "Missing the chunk file '%s'\n", buffer);
            error_detected = 1;
            continue;
        }
        // this part of the program checks the size of chunk file and makes sure it is valid
        fseek(chunk_file, 0, SEEK_END);
        double size = ftell(chunk_file);
        rewind(chunk_file);
        if (size != chunk_size && count < num_chunks) {
            fprintf(stderr, "Incorrect chunk size for the file '%s', it should be %d\n", buffer, chunk_size/1024);
            error_detected = 1;
            fclose(chunk_file);
            continue;
        }
        // this part is for reading in the current chunk file into the main file 
        int bytes_read;
        int program_runner = 2;
        int run_allowed = 1;
        int counter = -1;
        while (program_runner > 1) {
            if (run_allowed == 1){
            bytes_read = fread(buffer, 1, chunk_size, chunk_file);
            
            if (bytes_read < 1){
                program_runner = 1;
                }
            
            while (counter < bytes_read - 1 && program_runner >= 2) {
                counter = counter + 1;
                // puts characters into the source file via the buffer
                if (putc(buffer[counter], source_file) == EOF) {
                    fprintf(stderr, "Error writing to the file '%s'\n", source);
                    error_detected = 1;
                    break;
                }
            }
            
            counter = 0;
        }
        // closes file
        fclose(chunk_file);
        }
        run_allowed = 2;
    }
    // closes source file showing it is done and then runs the error function.
    fclose(source_file);
    error(error_detected);
    return 0;
}
