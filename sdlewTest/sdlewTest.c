#include <stdlib.h>
#include <stdio.h>
#include "sdlew.h"
#include "SDL/SDL.h"

int main(int argc, char **argv) {
  if (sdlewInit() == SDLEW_SUCCESS) {
    printf("SDL Found\n");
    SDL_Init(0);
  }
  return EXIT_SUCCESS;
}
