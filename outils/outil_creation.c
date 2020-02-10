/**
 * \file outil_creation.c
 * \brief program to save data in files
 * \details Contains program to save data structures in files
 * \author Robin BUTEL
 * \version 0.0.1
 * \date 04/02/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "../src/struct.h"
#include "../src/common.h"

err_t create_class(Class * class)
{
    FILE *fp = NULL;
    if(fp=fopen("tactics_arena/data/classes","a")==NULL) return POINTER_NULL;
    
    fclose(fp);
}

int main()
{

    return 0;
}