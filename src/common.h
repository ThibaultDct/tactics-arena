#ifndef common_h
#define common_h

#define STR_SHORT 25
#define STR_LONG 50
#define NUM_ERROR 4

typedef enum {OK, POINTER_NULL, SDL_ERROR} err_t;

char error_message[NUM_ERROR][STR_LONG] = {"OK\n", "ERROR: Pointer is Null\n", "ERROR : SDL\n"};

#endif
