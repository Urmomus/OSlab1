#if !defined(MACRO)
#define MACRO

#include <stdio.h>

typedef enum 
{
    OK,
    STAT_ERROR,
    NOT_DIR,
    INVALID_OUTPUT
} ArchivingError;

ArchivingError archivate(const char *input_path, const char *output_file_path);

#endif // MACRO

