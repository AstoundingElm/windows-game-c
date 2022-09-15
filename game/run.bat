set files=src/glad.c main.cpp
set libs=lib\SDL2main.lib lib\SDL2.lib

CL /Zi  /W4 /std:c++20 /I include %files% /link %libs% /OUT:mygame.exe

pause