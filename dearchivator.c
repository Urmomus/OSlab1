#include "dearchivator.h"
#include "fileutils.h"
#include "int_byte_casts.h"
#include "path_linked_list.h"
#include <linux/limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

DearchivingError dearchivate(const char *archive_path, char *output_dir)
{
    struct stat file_info;
    if (stat(output_dir, &file_info) == -1)
        return D_STAT_ERROR;
    if (!S_ISDIR(file_info.st_mode))
        return INVALID_OUTPUT_DIR;
    char output[4092];
    FILE *archive = fopen(archive_path, "r");
    if (!archive)
        return INVALID_ARCHIVE_OUTPUT;
    size_t archive_size = get_file_size(archive_path);
    char *buff = malloc(archive_size);
    fread(buff, archive_size, 1, archive);
    const char *current_byte = buff;
    Node *root = NULL;
    add_node(&root, output_dir, strlen(output_dir));

    while (1)
    {
        if (*current_byte == 'd')
        {
            ++current_byte;
            uint16_t dir_name_len = bytes_to_uint16(current_byte);
            current_byte += sizeof(uint16_t);
            add_node(&root, current_byte, dir_name_len);
            get_path(root, output);
            mkdir(output, 0777);
            current_byte += dir_name_len;
        }
        else if (*current_byte == 'f')
        {
            ++current_byte;
            uint16_t file_name_len = bytes_to_uint16(current_byte);
            current_byte += sizeof(uint16_t);
            const char *file_name = current_byte;
            current_byte += file_name_len;
            uint64_t file_size = bytes_to_uint64(current_byte);
            current_byte += sizeof(uint64_t);
            add_node(&root, file_name, file_name_len);
            get_path(root, output);
            const char *file_bytes = current_byte;
            write_bytes_to_file(file_bytes, file_size, output);
            current_byte += file_size;
            delete_last_node(&root);
        }
        else if (*current_byte == 'e')
        {
            delete_last_node(&root);
            ++current_byte;
        }
        else if (*current_byte == '\0')
            break;
        else
        {
            free(buff);
            fclose(archive);
            return PARSE_ERROR;
        }
    }
    free(buff);
    fclose(archive);
}
