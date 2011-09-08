#include "../lua.h"
#include "../lauxlib.h"

#include "mime.h"
#include "mimescripts.h"
#include "fullluamime.h"

LUAPRELOAD_API int luapreload_fullluamime(lua_State *L) {
	luaL_findtable(L, LUA_GLOBALSINDEX, "package.preload", 2);
	
	lua_pushcfunction(L, luaopen_mime_core);
	lua_setfield(L, -2, "mime.core");
	lua_pushcfunction(L, luaopen_mime);
	lua_setfield(L, -2, "mime");
	
	lua_pop(L, 1);
	return 0;
}
