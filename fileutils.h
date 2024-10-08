#if !defined(FILE_UTILS)
#define FILE_UTILS

#include <inttypes.h>
#include <stddef.h>

int build_path(char *dest, size_t size, const char *dir, const char *subdir);
const char *get_basename(const char *dir_path);
uint64_t get_file_size(const char *file_path);
void write_file_to_buff(const char *file_name, char *buff, size_t file_size);
int write_bytes_to_file(const char *bytes, uint64_t file_size, const char *file_path);

#endif // FILE_UTILS
