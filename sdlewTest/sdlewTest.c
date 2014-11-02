#include <stdlib.h>
#include "sdlew.h"

int main(int argc, char **argv) {
  if (sdlewInit() == SDLEW_SUCCESS) {
    printf("SDL Found\n");
    SDL_Init(0);
  }
  return EXIT_SUCCESS;
}
