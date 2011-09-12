//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMPluginVersion.cpp - Default external function for returning plug-in version
//
//  Version 3.0, Copyright ©2002-2010 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky & HOnza Koudelka
//
////////////////////////////////////////////////////////////////////////////////
//
//  The latest version of 24U Plug-In Template is available for download from:
//
//  http://www.24uSoftware.com/PlugInTemplate 
//
////////////////////////////////////////////////////////////////////////////////
//
//  24U Sample Code - Terms of use
//
//  Under the terms of the 24U Software License Agreement, 24U s.r.o. grants
//  you a non-exclusive royalty-free Developer License (3.2) to use 24U Plug-In
//  Template solely to compile plug-ins for use with FileMaker products.
//
//  Redistribution of 24U Sample Code in the source form, as part of
//  an open-source plug-in project is permitted provided that the following
//  conditions are met:
//
//  * Redistributions of source code must retain the copyright notice, the terms
//    of use, and the "24U Software License Agreement" document.
//
//  * We require that you make it clear in the source wherever modified that the
//    code was descended from 24U Sample Code, but that you've made changes.
//
//  See the "License.txt" and "24U Software License Agreement.pdf" files
//  for detailed terms of use and licensing conditions.
//
////////////////////////////////////////////////////////////////////////

// This file has been edited from the plugin template
////////////////////////////////////////////////////////////////////////////////


#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#pragma mark X24FT_Version



/**
 * provie a function to let lua call ExecuteFileSQL
 * 
 * returns the error result
 */
/*
commenting this out for now as ExecuteFileSQL really only works on 11
and does not link nicely with the current sdk.
int lua_fmExecuteFileSQL(lua_State *L)
{
	int n = lua_gettop(L);
    
	//we need to get passed something to eval
	if (n == 0)
		return -1;
    
	fmx::ExprEnvAutoPtr fenvCurrEnv; 
	fmx::TextAutoPtr	expression;
	fmx::TextAutoPtr	filename;
    fmx::DataVectAutoPtr data;
    fmx::RowVectAutoPtr row; 
	fmx::errcode		err			= 0;
	fmx::DataAutoPtr result;
    
	//get the current envirement
	err = FMX_SetToCurrentEnv(&(*fenvCurrEnv));
	//it looks like we failed to get the envirement :( that's bad
	if (err != 0)
	{
		lua_pushnumber(L, err);
		lua_pushstring(L,"Internal Error getting Filemaker Envirement" );
		return 2;
	}
	//get the string from lua
	expression->AssignWithLength(lua_tostring(L, 1), lua_strlen(L, 1), fmx::Text::kEncoding_UTF8);
    filename->AssignWithLength(lua_tostring(L, 2),lua_strlen(L, 2),  fmx::Text::kEncoding_UTF8);
	//tell filemaker to evaluate the string
	//ExecuteFileSQL ( const Text &expression, const Text &filename, const DataVect &parameters, RowVect& result ) const;
    err = fenvCurrEnv->ExecuteFileSQL( *expression, *filename, *data, *row );
	
	lua_pushnumber(L, err);
	return 1;
}*/

/**
 * provie a function to let lua call executesql
 * 
 * returns the error result
 */
int lua_fmExecuteSQL(lua_State *L)
{
	int n = lua_gettop(L);
    
	//we need to get passed something to eval
	if (n == 0)
		return -1;
    
	fmx::ExprEnvAutoPtr fenvCurrEnv; 
	fmx::TextAutoPtr	expression;
	fmx::unichar		colSep		= 0x0009;
	fmx::unichar		rowSep		= 0x000d;
	fmx::errcode		err			= 0;
	fmx::DataAutoPtr result;
    
	//get the current envirement
	err = FMX_SetToCurrentEnv(&(*fenvCurrEnv));
	//it looks like we failed to get the envirement :( that's bad
	if (err != 0)
	{
		lua_pushnumber(L, err);
		lua_pushstring(L,"Internal Error getting Filemaker Envirement" );
		return 2;
	}
	//get the string from lua
	expression->AssignWithLength(lua_tostring(L, 1), lua_strlen(L, 1), fmx::Text::kEncoding_UTF8);
    
	//tell filemaker to evaluate the string
	//err = fenvCurrEnv->Evaluate(*ftxtCalc, *fdatResults);
    err = fenvCurrEnv->ExecuteSQL( *expression, *result, colSep, rowSep );
	//Looks like filemaker didn't like the code so return the error code and a string
	
	lua_pushnumber(L, err);
	return 1;
}


/**
 * provie a function to let lua call evaluate 
 * 
 * returns the error result and a string
 */
int lua_fmEvaluate(lua_State *L)
{
	int n = lua_gettop(L);
    
	//we need to get passed something to eval
	if (n == 0)
		return -1;
    
	fmx::ExprEnvAutoPtr fenvCurrEnv; 
	fmx::errcode ferrResult; 
	fmx::TextAutoPtr ftxtCalc; 
	fmx::DataAutoPtr fdatResults; 
	fmx::TextAutoPtr ftxtResults; 
    
	//get the current envirement
	ferrResult = FMX_SetToCurrentEnv(&(*fenvCurrEnv));
	//it looks like we failed to get the envirement :( that's bad
	if (ferrResult != 0)
	{
		lua_pushnumber(L, ferrResult);
		lua_pushstring(L,"Internal Error getting Filemaker Envirement" );
		return 2;
	}
	//get the string from lua
	ftxtCalc->AssignWithLength(lua_tostring(L, 1), lua_strlen(L, 1), fmx::Text::kEncoding_UTF8);
    
	//tell filemaker to evaluate the string
	ferrResult = fenvCurrEnv->Evaluate(*ftxtCalc, *fdatResults);
    
	//Looks like filemaker didn't like the code so return the error code and a string
	if (ferrResult != 0)
	{
		lua_pushnumber(L, ferrResult);
		lua_pushstring(L,"Error Executing script" );
		return 2;
	}
    
	//pull the resault text back from filemaker :-)
	ftxtResults->SetText(fdatResults->GetAsText());
    
	int paramLen = ftxtResults->GetSize() +1;
	char *utf8Text;
	utf8Text = new char[paramLen];
    
	ftxtResults->GetBytes( utf8Text, paramLen, 0, paramLen, fmx::Text::kEncoding_UTF8 ); 
    
	lua_pushnumber(L, ftxtResults->GetSize() );
	lua_pushstring(L,utf8Text );
	return 2;
}

/**
 * provie a function to let lua call a script with in a file.  I need to add support for passing a paramater.
 * 
 * returns the error result
 */
int lua_fmScript(lua_State *L)
{
	int n = lua_gettop(L);
    
	//we need to get passed a file and script
	if (n < 2)
		return 0;
    
	fmx::ExprEnvAutoPtr fenvCurrEnv; 
	fmx::errcode ferrResult; 
	fmx::TextAutoPtr file;
	fmx::TextAutoPtr script; 
	fmx::DataAutoPtr fdatResults;
	fmx::TextAutoPtr param; 
    
	//get the current envirement
	ferrResult = FMX_SetToCurrentEnv(&(*fenvCurrEnv));
	//it looks like we failed to get the envirement :( that's bad
	if (ferrResult != 0)
	{
		lua_pushnumber(L, ferrResult);
		lua_pushstring(L,"Internal Error getting Filemaker Envirement" );
		return 2;
	}
	//get the string from lua
	file->Assign(lua_tostring(L, 1), fmx::Text::kEncoding_UTF8);
	script->Assign(lua_tostring(L, 2), fmx::Text::kEncoding_UTF8);
    
	int result = 0;
    
	//call the script.  if we get a third param it must be for the script
	if ( n > 2)
	{
		param->AssignWithLength(lua_tostring(L, 3),lua_strlen(L, 3),  fmx::Text::kEncoding_UTF8);
		fmx::LocaleAutoPtr locale;
		fmx::DataAutoPtr theData; 
		theData->SetAsText(*param, *locale);
        
		result = FMX_StartScript( &(*file), &(*script), kFMXT_Pause, &(*theData) );
	}
	else
	{
		result = FMX_StartScript( &(*file), &(*script), kFMXT_Pause, NULL );
	}
    
    
	lua_pushnumber(L, result );
	return 1;
}


//Execute_Lua
FMX_PROC(fmx::errcode) Execute_Lua(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result)
{
#pragma unused(funcId,environment)
	
    fmx::errcode        err = 0;
    fmx::TextAutoPtr    tempText;
    fmx::TextAutoPtr    resultText;
    
    if( dataVect.Size() > 0 )
    {
        //We have at least one parameter. Read it and return correct information.
        
        const fmx::Text& parameter1 = dataVect.AtAsText(0);
        const fmx::Text& outText = dataVect.AtAsText(0); 
        
		int error;
		
		lua_State *L  = lua_open();
        
		/* load various Lua libraries */
		luaL_openlibs(L);
		
		//register our custom functions
		lua_register(L, "fmEvaluate", lua_fmEvaluate);
		lua_register(L, "fmScript", lua_fmScript);
        lua_register(L, "fmExecuteSQL", lua_fmExecuteSQL);
        //lua_register(L, "fmExecuteFileSQL", lua_fmExecuteFileSQL);
		const long paramLen = outText.GetSize() + 1;
		//unsigned long intParamSize = *parameter1->GetSize(); 
		char *utf8Text;
		utf8Text = new char[paramLen];
		outText.GetBytes( utf8Text, paramLen, 0, paramLen, fmx::Text::kEncoding_UTF8 ); 
		error = luaL_dostring(L,utf8Text);
        
		resultText->AssignWithLength(lua_tostring(L, -1), lua_strlen(L, -1), fmx::Text::kEncoding_UTF8);
		
		/* cleanup Lua */
		lua_close(L);
        
        err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
    }
    
    return err;
}
