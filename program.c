#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "en_US.UTF-8"); // Set locale for UTF-8 support

    if (argc < 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open file in binary mode to read raw bytes
    FILE *input = fopen(argv[1], "rb");
    if (!input)
    {
        printf("Failed to open file\n");
        return 1;
    }

    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    // Allocate buffer with extra space
    char *buffer = malloc(size + 100);
    if (!buffer)
    {
        printf("Memory allocation failed\n");
        fclose(input);
        return 1;
    }
    
    size_t bytes_read = fread(buffer, 1, size, input);
    buffer[bytes_read] = '\0';
    fclose(input);

    // Replace "bad" with "good"
    char *pos = strstr(buffer, "xun");
    if (pos)
    {
        size_t index = pos - buffer;
        size_t old_len_1 = strlen("xun");
        size_t new_len_1 = strlen("wanaagsan");
        long new_size_1 = bytes_read + (new_len_1 - old_len_1);

        char *new_buffer_1 = malloc(new_size_1 + 1);
        new_buffer_1[new_size_1] = '\0';

        memcpy(new_buffer_1, buffer, index);
        memcpy(new_buffer_1 + index, "wanaagsan", new_len_1);
        memcpy(new_buffer_1 + index + new_len_1, buffer + index + old_len_1, bytes_read - index - old_len_1);

        free(buffer);
        buffer = new_buffer_1;
        bytes_read = new_size_1;

    }

    // Replace "nacas" with "fariid"
    char *pos2 = strstr(buffer, "nacas");
    if (pos)
    {
        size_t index = pos2 - buffer;
        size_t old_len_2 = strlen("nacas");
        size_t new_len_2 = strlen("fariid");
        long new_size_2 = bytes_read + (new_len_2 - old_len_2);

        char *new_buffer = malloc(new_size_2 + 1);
        new_buffer[new_size_2] = '\0';
        
        memcpy(new_buffer, buffer, index);
        memcpy(new_buffer + index, "fariid", new_len_2);
        memcpy(new_buffer + index + new_len_2, buffer + index + old_len_2, bytes_read - index - old_len_2);
        
        free(buffer);
        buffer = new_buffer;
        bytes_read = new_size_2;
    }


    // Open output file in binary mode for UTF-8
    FILE *output = fopen("output.txt", "wb");
    if (!output)
    {
        printf("Failed to open output file\n");
        free(buffer);
        return 4;
    }

    fwrite(buffer, 1, bytes_read, output);
    fclose(output);
    free(buffer);
    
    printf("File processed successfully\n");
    return 0;
}