#ifndef struct_h
#define struct_h
#define STR_SHORT 25
#define STR_LONG 50
#define NUM_STATS 6
#define NUM_CLASS 5
#define NUM_AB 4

/* ENUMERATIONS */
typedef enum {pv, mv, atk, magic, res_physic, res_magic, act} statId;

typedef enum {Berserker, Ranger, Goliath, Mage, Valkyrie, Angel} classId;

typedef enum {Slash, Bolt, Bash, Fireball} abilityId;

typedef enum {Physical_Damage, Magic_Damage, Piercing_Damage, Paralysed, Bleeding, Burning, Slowed} effectId;

/* BASIC STRUCTURES*/
typedef struct
{
    int x;
    int y;
} Coord;

typedef struct
{
    effectId effect_id;
    int nb_targeted;
    statId * targeted_stat;
} Type_effects;

/* ENTITY STRUCTURES */
typedef struct
{
    Type_effects * eff_type;
    int value;
    int duration;
} Effect;

typedef struct
{
    int range;
    int nb_coords;
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
    int (*function)(int, Coord *); //Takes caster ID, Coordinates, and pointer to state chain
    char sprite_folder[STR_LONG];
} Ability;

typedef struct
{
    classId cla_id;
    char cla_name[STR_SHORT];
    int basic_stats[NUM_STATS];
    Ability * cla_abilities;
    char sprite_folder[STR_LONG];
} Class;

typedef struct
{
    int cha_id;
    char cha_name[STR_SHORT];
    Class * cha_class;
    // Item List
} Character;

typedef struct
{
    Character * character;
    int act_points;
    int base_stats[NUM_STATS];
    int stat_mods[NUM_STATS];
} Entity;


/* COMMUNICATION STRUCTURES */



#endif