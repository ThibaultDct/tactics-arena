#ifndef struct_h
#define struct_h

typedef struct t_player
{
    int classe;
} Player;

typedef struct t_mob
{
    int type;
} Mob;

typedef struct t_entity
{
    int pdv;
    union
    {
        Player player;
        Mob mob;
    };
} Entity;

#endif