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
    char * path = malloc(sizeof(char)*15);
    char num[3];

    itoa(class->cla_id, num, 10);
    sprintf(path, "../data/%s",num);

    if(fp=fopen(path,"ab")==NULL) return POINTER_NULL;
    fwrite(class, sizeof(Class), 1, fp);
    fclose(fp);
}

int main()
{
  //Class class = {Ranger};

    create_class(&class);
    return 0;
}
