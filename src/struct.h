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

typedef struct t_buff
{
    stat variation;
    stat duration;
} Buff;

typedef struct t_entity
{
    int id;
    char character_name[25];
    char character_class;
} Entity;



#endif