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
#include <string.h>
#include <errno.h>
#include "../src/struct.h"
#include "../src/common.h"

err_t add_coord(Coord * c, int nb, FILE * fp)
{

}

err_t create_Ability(Ability * abilities, FILE * fp)
{
    int i;
    for(i=0; i<NUM_AB; i++)
    {

        if(fwrite(*(abilities + i), sizeof(Ability),1,fp)!=1) printf("%s\n",strerror(errno));
    }
    return OK;
}

err_t create_class(Class * class)
{
    FILE * fp;
    char * path = malloc(sizeof(char)*20);

    sprintf(path, "../data/%d_%s.bin",class->cla_id,class->cla_name);
    printf("\n%s\n",path);

    if((fp=fopen(path,"wb"))==NULL) return POINTER_NULL;

    create_Ability(class->cla_abilities,fp);
    free(class->cla_abilities);

    if(fwrite(class, sizeof(Class),1,fp)!=1) printf("%s\n",strerror(errno));

    create_Ability(ab,fp);

    free(path);
    fclose(fp);
    return OK;
}

err_t test(Class * class)
{
    FILE * fp;
    char * path = malloc(sizeof(char)*20);
    char num[3];
    Class * target = malloc(sizeof(Class));

    itoa(class->cla_id, num, 10);
    sprintf(path, "../data/%s_%s.bin",num,class->cla_name);

    if((fp=fopen(path,"wb"))==NULL) return POINTER_NULL;

    if(fread(target, sizeof(Class),1,fp)!=1) printf("%s\n",strerror(errno));

    printf("%d\n%s\n%d %d %d %d %d %d %d\n%p\n%s\n", target->cla_id, target->cla_name, target->basic_stats[0], target->basic_stats[1], target->basic_stats[2], target->basic_stats[3], target->basic_stats[4], target->basic_stats[5], target->basic_stats[6], target->cla_abilities, target->sprite_folder);

    free(target);
    free(path);
    fclose(fp);
    return OK;
}

int main()
{
    #include "berserker.h"
    printf("%s\n",error_message[create_class(&class)]);

    return 0;
}
