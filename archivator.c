#include "archivator.h"
#include "fileutils.h"
#include "int_byte_casts.h"
#include <dirent.h>
#include <inttypes.h>
#include <linux/limits.h>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int _archivate_dir_tree(const char *path, FILE *output_file);
void _start_dir(const char *dir_path, FILE *output_file);
void _end_dir(FILE *output_file);
void _add_file(const char *file_path, FILE *output_file);

ArchivingError archivate(const char *input_path, const char *output_file_path)
{
    struct stat file_info;
    if (stat(input_path, &file_info) == -1)
        return STAT_ERROR;
    if (!S_ISDIR(file_info.st_mode))
        return NOT_DIR;
    FILE *output_file = fopen(output_file_path, "w");
    if (!output_file)
        return INVALID_OUTPUT;
    _archivate_dir_tree(input_path, output_file);
    fclose(output_file);
}

int _archivate_dir_tree(const char *path, FILE *output_file)
{
    DIR *directory = opendir(path);
    if (!directory)
    {
        _add_file(path, output_file);
        return 1;
    }
    struct dirent *entry;

    _start_dir(path, output_file);

    while ((entry = readdir(directory)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue;
        char new_dir[PATH_MAX];
        build_path(new_dir, BUFSIZ, path, entry->d_name);
        _archivate_dir_tree(new_dir, output_file);
    }

    _end_dir(output_file);

    closedir(directory);
    return 0;
}

void _start_dir(const char *dir_path, FILE *output_file)
{
    const char *dir_name = get_basename(dir_path);
    uint16_t dir_name_len = strlen(dir_name);
    size_t bufsize = 1 + dir_name_len + sizeof(uint16_t);
    char *buf = malloc(bufsize);
    buf[0] = 'd';
    emplace_uint16_to_buff(dir_name_len, buf + 1);
    memcpy(buf + 3, dir_name, dir_name_len);
    fwrite(buf, bufsize, 1, output_file);
    free(buf);
}

void _end_dir(FILE *output_file)
{
    char end_of_dir[] = {'e'};
    fwrite(end_of_dir, 1, 1, output_file);
}

void _add_file(const char *file_path, FILE *output_file)
{
    const char *file_name = get_basename(file_path);
    uint16_t file_name_len = strlen(file_name);
    uint64_t file_size = get_file_size(file_path);
    size_t bufsize = 1 + file_name_len + sizeof(uint16_t) + sizeof(size_t) + file_size;
    char *buf = malloc(bufsize);
    buf[0] = 'f';
    emplace_uint16_to_buff(file_name_len, buf + 1);
    memcpy(buf + 3, file_name, file_name_len);
    emplace_uint64_to_buff(file_size, buf + 3 + file_name_len);
    write_file_to_buff(file_path, buf + 3 + file_name_len + 8, file_size);
    fwrite(buf, bufsize, 1, output_file);
    free(buf);
}
