#ifndef struct_h
#define struct_h

typedef struct t_stats
{
    int pv;
    int mv;
    int atk;
    int res_physic;
    int res_magic;
} Stat;

typedef enum {pv, mv, atk, res_physic, res_magic} statId;

typedef enum {Berserker, Ranger, Mage, Valkyrie, Angel} classId;

typedef struct t_class
{
    classId class_id;
    char class_name[25];
    Stat stats;
} Class;

typedef struct t_entity
{
    int id;
    char character_name[25];
    Class character_class;
    char sprite_folder[50];
} Entity;



#endif