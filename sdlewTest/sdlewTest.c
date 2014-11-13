#include <stdlib.h>
#include <stdio.h>
#include "sdlew.h"
#include "SDL2/SDL.h"

int main(int argc, char **argv) {
  if (sdlewInit() == SDLEW_SUCCESS) {
    SDL_version version;
    printf("SDL Found\n");
    SDL_GetVersion(&version);
    printf("Version: %d %d %d\n",
           version.major,
           version.minor,
           version.patch);
  }
  else {
    printf("SDL-1.2 vas not found\n");
  }
  return EXIT_SUCCESS;
}
