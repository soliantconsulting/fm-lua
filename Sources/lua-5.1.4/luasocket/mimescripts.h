#ifndef _____MIMESCRIPTS__
#define _____MIMESCRIPTS__

#include "../lua.h"

#ifndef LUAOPEN_API 
#define LUAOPEN_API 
#endif

LUAOPEN_API int luaopen_mime(lua_State *L);

#endif /* _____MIMESCRIPTS__ */
