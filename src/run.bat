set files=C:/Users/peter/OneDrive/Desktop/game/src/main.cpp C:/Users/peter/OneDrive/Desktop/game/src/glad.c
set libs=C:/Users/peter/OneDrive/Desktop/game/lib/SDL2main.lib C:/Users/peter/OneDrive/Desktop/game/lib/SDL2.lib 

CL /Zi -Fmmygame.map -Od -GR- -EHa- -FC  -W0 -wd4100  /std:c++20 /I include %files% /link %libs% /OUT:C:\Users\peter\OneDrive\Desktop\game\src\mygame.exe 

pause