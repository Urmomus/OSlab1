#if !defined(USER_INPUT)
#define USER_INPUT

#include "archivator.h"
#include "dearchivator.h"

typedef enum 
{
    ARCHIVING,
    DEARCHIVING,
    NO_ARCH_PATH,
    NO_DEARCH_PATH,
    NO_OUTPUT,
    UNKNOWN_OPT,
    NO_FLAGS_DEFINED,
    CONFLICTING_FLAGS
} UserInput;

int get_user_input(int argc, char **argv, char **input_path, char **output_path);
int print_input_error(UserInput e);
int print_archiving_error(ArchivingError e);
int print_dearchiving_error(DearchivingError e);

#endif // USER_INPUT
