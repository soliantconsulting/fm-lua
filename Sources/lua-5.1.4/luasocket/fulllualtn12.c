#include "../lua.h"
#include "../lauxlib.h"

#include "lualtn12scripts.h"
#include "fulllualtn12.h"

LUAPRELOAD_API int luapreload_fulllualtn12(lua_State *L) {
	luaL_findtable(L, LUA_GLOBALSINDEX, "package.preload", 1);
	
	lua_pushcfunction(L, luaopen_ltn12);
	lua_setfield(L, -2, "ltn12");
	
	lua_pop(L, 1);
	return 0;
}
