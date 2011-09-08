lua5.1 ..\..\..\..\Projects\preloader\precompiler.lua -l ?.lua -o ..\lualtn12scripts ltn12.lua
cd ..
lua5.1 ..\..\..\Projects\preloader\preloader.lua -o fulllualtn12 lualtn12scripts.h

pause