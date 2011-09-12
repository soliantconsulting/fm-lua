#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
//int lua_fmExecuteFileSQL(lua_State *L);

int lua_fmExecuteSQL(lua_State *L);

int lua_fmEvaluate(lua_State *L);

int lua_fmScript(lua_State *L);

FMX_PROC(fmx::errcode) Execute_Lua(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result);

