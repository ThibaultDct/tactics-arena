#include <stdio.h>
#include <math.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "graphics.h"
#include "struct.h"
#include "audio.h"

List * initStateList()
{
  List *list = malloc(sizeof(*list));
  StateList *state_list = malloc(sizeof(*state_list));

  if (list == NULL || state_list == NULL) exit(EXIT_FAILURE);

  state_list->value->id_buff = -1;
  state_list->value->nb_tours = -1;
  state_list->value->buff_name = "";
  state_list->suiv = NULL;
  list->first = state_list;

  return list;
}

// void insertIntoStateList(List *list, State newState)
// {
//   StateList *new = malloc(sizeof(*new));
//   if (list == NULL || new == NULL) exit(EXIT_FAILURE);
//   new->value = newState;

//   new->suiv = list->first;
//   list->first = new;
// }

void removeFirstState(List *list)
{
  if (list == NULL) exit(EXIT_FAILURE);

  if (list->first != NULL)
  {
    StateList *toRemove = list->first;
    list->first = list->first->suiv;
    free(toRemove);
  }
}

void printStateList(List *list)
{
  if (list == NULL) exit(EXIT_FAILURE);

  StateList *current = list->first;

  while (current != NULL)
  {
    printf("ID : %d - Buff : %s - Turns : %d\n", current->value->id_buff, current->value->buff_name, current->value->nb_tours);
    current = current->suiv;
  }
}
