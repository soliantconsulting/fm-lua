lua5.1 ..\..\..\..\Projects\preloader\precompiler.lua -l ?.lua -o ..\luasocketscripts socket.lua socket/ftp.lua socket/http.lua socket/smtp.lua socket/tp.lua socket/url.lua
cd ..
lua5.1 ..\..\..\Projects\preloader\preloader.lua -o fullluasocket luasocket.h luasocketscripts.h

pause