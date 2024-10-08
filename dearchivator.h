#if !defined(DEARCH)
#define DEARCH

typedef enum 
{
    NO_DEARCH_ERROR,
    INVALID_ARCHIVE_OUTPUT,
    PARSE_ERROR,
    D_STAT_ERROR,
    INVALID_OUTPUT_DIR
} DearchivingError;

DearchivingError dearchivate(const char *archive_path, char *output_dir);

#endif // DEARCH
