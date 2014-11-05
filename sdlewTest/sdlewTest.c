#include <stdlib.h>
#include <stdio.h>
#include "sdlew.h"
#include "SDL/SDL.h"

int main(int argc, char **argv) {
  if (sdlewInit() == SDLEW_SUCCESS) {
    const SDL_version *version;
    printf("SDL Found\n");
    version = SDL_Linked_Version();
    printf("Version: %d %d %d\n",
           version->major,
           version->minor,
           version->patch);
  }
  else {
    printf("SDL-1.2 vas not found\n");
  }
  return EXIT_SUCCESS;
}
