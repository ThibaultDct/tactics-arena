/**
 * \file creation.c
 * \brief program to save data in files
 * \details Contains program to save data structures in files
 * \author Robin BUTEL
 * \version 0.0.1
 * \date 04/02/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "common.h"

err_t create_class(Class * class)
{
    FILE *fp = NULL;
    fp=fopen("tactics_arena/data/classes","a");
    if(fp==NULL) return POINTER_NULL;
    fclose(fp);
}

int main()
{
    return 0;
}