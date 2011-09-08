lua5.1 ..\..\..\..\Projects\preloader\precompiler.lua -l ?.lua -o ..\mimescripts mime.lua
cd ..
lua5.1 ..\..\..\Projects\preloader\preloader.lua -o fullluamime mime.h mimescripts.h

pause