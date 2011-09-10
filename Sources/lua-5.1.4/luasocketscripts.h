#ifndef _____LUASOCKETSCRIPTS__
#define _____LUASOCKETSCRIPTS__

#include "lua.h"

#ifndef LUAOPEN_API 
#define LUAOPEN_API 
#endif

LUAOPEN_API int luaopen_socket(lua_State *L);
LUAOPEN_API int luaopen_socket_ftp(lua_State *L);
LUAOPEN_API int luaopen_socket_http(lua_State *L);
LUAOPEN_API int luaopen_socket_smtp(lua_State *L);
LUAOPEN_API int luaopen_socket_tp(lua_State *L);
LUAOPEN_API int luaopen_socket_url(lua_State *L);

#endif /* _____LUASOCKETSCRIPTS__ */
