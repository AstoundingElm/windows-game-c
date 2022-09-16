set files=main.cpp include/glad/glad.c
set libs=C:/Users/peter/OneDrive/Desktop/game/lib/SDL2main.lib C:/Users/peter/OneDrive/Desktop/game/lib/SDL2.lib 

CL /Zi  /W4 /std:c++20 /I include %files% /link %libs% /OUT:mygame.exe

pause