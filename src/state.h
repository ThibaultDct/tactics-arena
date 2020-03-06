typedef struct {
  int nb_tours;
  int id_buff;
  char * buff_name;
} State;

typedef struct {
  StateList * first;
} List;

typedef struct {
  State * value;
  struct StateList * suiv;
} StateList;
