cmake_minimum_required(VERSION 3.5.0)
project(lab1 VERSION 0.1.0 LANGUAGES C)
add_executable(archiver main.c archivator.c dearchivator.c fileutils.c path_linked_list.c int_byte_casts.c user_input.c)
