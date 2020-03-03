#ifndef struct_h
#define struct_h

#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"

#define STR_SHORT 25
#define STR_LONG 50
#define NUM_STATS 6
#define NUM_CLASS 6
#define NUM_AB 4

/* ENUMERATIONS */
typedef enum {pv, mv, vis, atk, magic, res_physic, res_magic} statId;

typedef enum {Berserker, Ranger, Goliath, Mage, Valkyrie, Angel} classId;

typedef enum {Slash, Bolt, Bash} abilityId;

typedef enum {Piercing_Damage, Slowed, Blind, Weakened, Benighted, p_res_red, m_res_red} n_effectId;
typedef enum {Healing, Swifted, Perceptive, Strenghtened, Enlightened, p_res_inc, m_res_inc} p_effectId;

/* BASIC STRUCTURES*/
typedef struct
{
    int x;
    int y;
} Coord;

typedef struct
{
    float x;
    float y;
} Vector;

/* ENTITY STRUCTURES */


typedef struct
{
    abilityId ab_id;
    char ab_name[STR_SHORT];
    int ab_cost;
    int ab_cooldown;
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

/* TERRAIN STRUCTURES */

typedef struct
{
    int tile_id;
    int selected;
    Entity * entity;
} Tile;

/* TEXTURE STRUCTURES */

typedef struct
{
    char * texture_name;
    SDL_Texture *texture;
    SDL_Texture *big_texture;
} TabTexture;


/* COMMUNICATION STRUCTURES */



#endif