#include "SDL2/SDL.h"
#include <string>
#include <iostream>


int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow( "SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer *renderer;

    int renderDriverNum = -1;
    for( int i = 0; i < SDL_GetNumRenderDrivers(); ++i )
    {
        SDL_RendererInfo rendererInfo = {};
        SDL_GetRenderDriverInfo( i, &rendererInfo );

        std::cout << rendererInfo.name << std::endl;
        if(rendererInfo.name != std::string( "direct3d11" ))
        {
            
            continue;
        }
        renderDriverNum = i;

        
        break;
    }
    if(renderDriverNum > -1){
        renderer = SDL_CreateRenderer( window, renderDriverNum, 0 );
    }

    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }


    SDL_Quit();

    return 0;
}
