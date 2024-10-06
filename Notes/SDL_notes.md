# SDL NOTES

## <i>Initialize</i>
- Use <b><u>SDL_Init</b></u> to initialize SDL API and check for errors:
```c
if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
    printf( "Error initializing SDL: %s", SDL_GetError() );
    return false; // bool defined as enum
}
```
- Create a window using <b><u>SDL_CreateWindow</b></u>:
```c
window = SDL_CreateWindow(
    "Example", // window name
    SDL_WINDOWPOS_UNDEFINED, // x pos of window
    SDL_WINDOWPOS_UNDEFINED, // y pos of window
    800, // h
    800, // w
    SDL_WINDOW_SHOWN // shown or hidden
    );
```
- Get the surface using <b><u>SDL_GetWindowSurface</b></u>:
```c
winSurface = SDL_GetWindowSurface( window );
if ( !winsurface ) {
    printf( "Error getting surface: %s", SDL_GetError);
    return false; // bool defined as enum
}
```
## <i>Quiting SDL program</i>
- Exit SDL gracefully
```c
SDL_FreeSurface( image ); // free any allocated memory
SDL_DestroyWindow( window );
SDL_Quit();
```
