#include <getopt.h>
#include "user_input.h"

int main(int argc, char **argv)
{
    char *output_path;
    char *input_path;
    UserInput input = get_user_input(argc, argv, &input_path, &output_path);
    if (input == ARCHIVING)
    {
        if (output_path == NULL)
            output_path = "./out.archie";
        ArchivingError e;
        if (e = archivate(input_path, output_path))
        {
            print_archiving_error(e);
            return 1;
        }
        return 0;
    }
    else if (input == DEARCHIVING)
    {
        DearchivingError e;
        if (output_path == NULL)
            output_path = ".";
        if (e = dearchivate(input_path, output_path))
        {
            print_dearchiving_error(e);
            return 1;
        }
        return 0;
    }
    else
    {
        print_input_error(input);
        return 1;
    }
}
