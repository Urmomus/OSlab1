#include "user_input.h"
#include <getopt.h>
#include <stdlib.h>

int get_user_input(int argc, char **argv, char **input_path, char **output_path)
{
    int arch_flag = 0;
    int dearch_flag = 0;
    int output_flag = 0;
    *output_path = NULL;
    *input_path = NULL;
    int c;
    while ((c = getopt(argc, argv, "a::d::o:")) != -1)
    {
        switch (c)
        {
        case 'a':
            arch_flag = 1;
            *input_path = optarg;
            if (*input_path == NULL)
                return NO_ARCH_PATH;
            break;
        case 'd':
            dearch_flag = 1;
            *input_path = optarg;
            if (*input_path == NULL)
                return NO_DEARCH_PATH;
            break;
        case 'o':
            *output_path = optarg;
            if (*output_path == NULL)
                return NO_OUTPUT;
            break;
        case '?':
            return UNKNOWN_OPT;
        default:
            abort();
        }
    }
    if (!arch_flag && !dearch_flag)
        return NO_FLAGS_DEFINED;
    if (arch_flag && dearch_flag)
        return CONFLICTING_FLAGS;
    if (arch_flag)
        return ARCHIVING;
    if (dearch_flag)
        return DEARCHIVING;
}

int print_input_error(UserInput e)
{
    switch (e)
    {
    case ARCHIVING:
        return 0;
    case DEARCHIVING:
        return 0;
    case NO_ARCH_PATH:
        fprintf(stderr, "Have to specify path to a folder with -a option\n");
        return 1;
    case NO_DEARCH_PATH:
        fprintf(stderr, "Have to specify path to an archive with -d option\n");
        return 1;
    case NO_OUTPUT:
        fprintf(stderr, "Have to specify output path with -o option\n");
        return 1;
    case UNKNOWN_OPT:
        fprintf(stderr, "Unknown option\n");
        return 1;
    case NO_FLAGS_DEFINED:
        fprintf(stderr, "Have to specify -a to archivate or -d to dearchvate\n");
        return 1;
    case CONFLICTING_FLAGS:
        fprintf(stderr, "Cannot specify both -a and -d options\n");
        return 1;
    default:
        abort();
    }
}

int print_archiving_error(ArchivingError e)
{
    switch (e)
    {
    case STAT_ERROR:
        fprintf(stderr, "Invalid input directory\n");
        break;
    case NOT_DIR:
        fprintf(stderr, "Input path is not a directory\n");
        break;
    case INVALID_OUTPUT:
        fprintf(stderr, "Invalid output file path\n");
    default:
        abort();
    }
}

int print_dearchiving_error(DearchivingError e)
{
    switch (e)
    {
    case INVALID_ARCHIVE_OUTPUT:
        fprintf(stderr, "Invalid archive path\n");
        break;
    case PARSE_ERROR:
        fprintf(stderr, "Error while parsing archive file\n");
        break;
    case D_STAT_ERROR:
        fprintf(stderr, "Invalid output directory path\n");
        break;
    case INVALID_OUTPUT_DIR:
        fprintf(stderr, "Output path is not a directory\n");
        break;
    default:
        abort();
    }
}
