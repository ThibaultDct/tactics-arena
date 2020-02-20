#ifndef struct_h
#define struct_h
#define STR_SHORT 25
#define STR_LONG 50
#define NUM_STATS 6
#define NUM_CLASS 5
#define NUM_AB 4

typedef enum {pv, mv, atk, magic, res_physic, res_magic} statId;

typedef enum {Berserker, Ranger, Mage, Valkyrie, Angel} classId;

typedef enum {Slash, Bolt, Fireball, Focus} abilityId;

typedef enum {Physical_Damage, Magic_Damage, Paralysed, Poisoned, Burning} effectId;

typedef struct
{
    int x;
    int y;
} Coord;

typedef struct
{
    effectId effect_id;
    //TBW
} Effect;

typedef struct
{
    Coord * zone;
    int nb_effects;
    Effect * Effects;
} Cast;


typedef struct
{
    abilityId ab_id;
    char ab_name[STR_SHORT];
    int ab_cost;
    int ab_cooldown;
    int nb_casts;
    Cast * ab_casts;
    int (*function)(int, Coord *);
    char sprite_folder[STR_LONG];
} Ability;

typedef struct
{
    classId cla_id;
    char cla_name[STR_SHORT];
    int basic_stats[NUM_STATS];
    Ability * cla_abilities;
} Class;

typedef struct
{
    int cha_id;
    char cha_name[STR_SHORT];
    Class * cha_class;
    int act_points;
    int stats[NUM_STATS];
    int stat_mods[NUM_STATS];
    char sprite_folder[STR_LONG];
    int selected;
} Entity;



//Structures pour la communication



#endif
