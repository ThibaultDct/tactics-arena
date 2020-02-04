/**
 * \file struct.c
 * \brief struct related functions
 * \details Contains functions to initialise and save data structures
 * \author Robin BUTEL
 * \version 0.0.1
 * \date 04/02/2020
 */

#include <stdlib.h>
#include "struct.h"
#include "common.h"

err_t get_classes(Class all_classes[NUM_CLASS])
{
    FILE *fp = NULL;
    fp=fopen("classes","r");
    if(fp==NULL) return ERROR_1;
    fread(all_classes, sizeof(Class), NUM_CLASS, fp);
    fclose(fp);
    
}