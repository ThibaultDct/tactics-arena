/**
 * \struct t_player struct.h
 * \brief Entity that represents a player character
 */
typedef struct t_player
{
    int classe;
} Player;

/**
 * \struct t_mob struct.h
 * \brief Entity that represents a mob (enemy)
 */
typedef struct t_mob
{
    int type;
} Mob;

/**
 * \struct t_entity struct.h
 * \brief Entity that represents a mob or a player
 */
typedef struct t_entity
{
    int pdv;
    union
    {
        Player player;
        Mob mob;
    };
} Entity;