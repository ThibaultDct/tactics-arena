#ifndef common_h
#define common_h

#define STR_SHORT 50
#define STR_LONG 256
#define NUM_ERROR 4

typedef enum error_type {OK, POINTER_NULL, SDL_ERROR, COORD_OUT_OF_BOUND} err_t;

char error_message[NUM_ERROR][STR_SHORT] = {"OK\n", "ERROR: Pointer is Null\n", "ERROR : SDL\n", "ERROR : Coordinates out of limits\n"};

#endif
