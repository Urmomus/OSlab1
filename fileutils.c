#include "fileutils.h"
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

const char *get_basename(const char *dir_path)
{
    char *base = strrchr(dir_path, '/');
    return base ? base + 1 : dir_path;
}

uint64_t get_file_size(const char *file_path)
{
    struct stat file_info;
    stat(file_path, &file_info);
    return file_info.st_size;
}

int build_path(char *dest, size_t size, const char *dir, const char *subdir)
{
    if (dest == NULL || size < 1 || subdir == NULL || dir == NULL)
        return 0;
    size_t stored = snprintf(dest, size, "%s/%s", dir, subdir);
    if (stored < 0)
        return stored;
    return (stored < size);
}

void write_file_to_buff(const char *file_name, char *buff, size_t file_size)
{
    FILE *file = fopen(file_name, "r");
    fread(buff, file_size, 1, file);
    fclose(file);
}

int write_bytes_to_file(const char *bytes, uint64_t file_size, const char *file_path)
{
    FILE *file = fopen(file_path, "w");
    if (!file)
        return 1;
    fwrite(bytes, file_size, 1, file);
    fclose(file);
    return 0;
}
