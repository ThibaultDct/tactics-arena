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

err_t create_class(Class * class)
{
    FILE * fp;
    char * path = malloc(sizeof(char)*20);
    char num[3];

    itoa(class->cla_id, num, 10);
    sprintf(path, "../data/%s_%s",num,class->cla_name);
    printf("\n%s\n",path);

    if((fp=fopen(path,"wb"))==NULL) return POINTER_NULL;

    if(fwrite(class, sizeof(Class),1,fp)!=1) printf("%s\n",strerror(errno));

    free(path);
    fclose(fp);
    return OK;
}

int main()
{
    Class class = {Ranger,"Ranger",{0,1,2,3,4,5},NULL};
    printf("%s\n",error_message[create_class(&class)]);

    Class * read = malloc(sizeof(Class));

    FILE *fp;

    fp=fopen("../data/1_Ranger","rb");
    fread(read, sizeof(Class), 1, fp);
    printf("%d\n%s\n%d %d %d %d %d %d\n",read->cla_id,read->cla_name,read->basic_stats[0],read->basic_stats[1],read->basic_stats[2],read->basic_stats[3],read->basic_stats[4],read->basic_stats[5]);
    fclose(fp);
    free(read);
    return 0;
}
