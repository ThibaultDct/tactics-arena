#ifndef graphics_h
#define graphics_h

void displayText(SDL_Renderer *renderer; TTF_Font *police, int x, int y, int size, char *content, int r, int g, int b);
int createWindow(int x, int y);

#endif