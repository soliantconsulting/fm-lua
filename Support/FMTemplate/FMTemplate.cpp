//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMTemplate.cpp - Main entry point and underlying code for 24U Plug-In Template
//
//  Version 3.0, Copyright ©2002-2010 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky, HOnza Koudelka, and Josef Andrysek
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

//
//  This source file was derived from FileMaker template plug-in provided
//  by FileMaker, Inc. as a part of FileMaker Developer.
//
////////////////////////////////////////////////////////////////////////////////

//
//  Use this file as a part of all compiled parts of your plug-in.
//  Without this file your own code will never get called by FileMaker as it
//  contains the key routines which connect the FileMaker API to your code.
//
////////////////////////////////////////////////////////////////////////////////


//  FMTConfig.h is required somewhere as it configures the FM Template
#include "FMTConfig.h"

#include "FMTemplate/FMTemplate.h"

#if FMX_WIN_TARGET
    #include <Windows.h>
#endif

#define if_error( cond, label )  if(cond) goto label

// ====== Forward Declaration ==============================================================================

static FMX_Long     Do_PluginInit(FMX_Short version);
static void         Do_PluginShutdown(void);

#if WANT_IDLE
static void         Do_PluginIdle(FMX_IdleLevel idleLevel);
#endif //WANT_IDLE

#if WANT_PREFERENCES
static void         Do_PluginPrefs();
#endif //WANT_PREFERENCES

static void         Do_PluginGetString();

static void         ProvideConfigString( FMX_UniChar* ioBuffer, FMX_ULong iBufferSize );
static void         ProvideNameString( FMX_UniChar* ioBuffer, FMX_ULong iBufferSize );
static void         ProvidePreferencesString( FMX_UniChar* ioBuffer, FMX_ULong iBufferSize );

       FMX_Boolean  RegisterExternalFunctions();
       void         UnRegisterExternalFunctions();
       


// ====== Global Variables =================================================================================

    FMX_ExternCallPtr   gFMX_ExternCallPtr=NULL;
    FMX_Boolean         gPlugInInitialized=0;
    FMX_Boolean         gPrefsOpen=0;


void FMX_ENTRYPT FMExternCallProc(FMX_ExternCallPtr pb)
{
    // Setup global defined in FMxExtern.h
    gFMX_ExternCallPtr = pb;

    // Message dispatcher
    switch (gFMX_ExternCallPtr->whichCall) 
    {
        case kFMXT_Init:
            gFMX_ExternCallPtr->result = Do_PluginInit(gFMX_ExternCallPtr->extnVersion);
            break;
            
        case kFMXT_Shutdown:
            Do_PluginShutdown();
            break;
            
        case kFMXT_GetString:
            Do_PluginGetString();
            break;

        #if WANT_IDLE
            case kFMXT_Idle:
                Do_PluginIdle(gFMX_ExternCallPtr->parm1);
                break;
        #endif //WANT_IDLE
        
        #if WANT_PREFERENCES
            case kFMXT_DoAppPreferences:
                Do_PluginPrefs();
                break;
        #endif //WANT_PREFERENCES
        
    };// switch whichCall

} // FMExternCallProc


// ====== Handlers =========================================================================================

static FMX_Long Do_PluginInit(FMX_Short version) 
{
    // Check the app API version
    if ((version < k70ExtnVersion) || (version > kMaxExtnVersion)) 
    {
        // This version of FileMaker is not supported; let FileMaker disable this 
        // plug-in and report the problem to the user.
        return (kBadExtnVersion);
    }

    if( Startup() )
    {
        if( RegisterExternalFunctions() )
        {
            gPlugInInitialized = 1;
            return kCurrentExtnVersion;
        }
        else
            Shutdown();
    }
    
    return kDoNotEnable;
    
} // Do_PluginInit


static void Do_PluginShutdown(void) 
{
    gPlugInInitialized = 0;

    UnRegisterExternalFunctions();
    Shutdown();
} // Do_PluginShutdown


#if WANT_IDLE
    void Do_PluginIdle(FMX_IdleLevel idleLevel) 
    {
        //  eliminate the race condition we would be called when Startup is not yet done!
        if( gPlugInInitialized )
        {
            if( idleLevel == kFMXT_UserIdle )
                SafeIdle();
            else if ( idleLevel == kFMXT_Unsafe)
                UnsafeIdle();
            else 
                SemiSafeIdle(idleLevel);
        }
    } // Do_PluginIdle
#endif //WANT_IDLE


#if WANT_PREFERENCES    
    static void Do_PluginPrefs()
    {
        //  Avoid opening multiple instances of the preferences dialog
        if (!gPrefsOpen)
        {
            gPrefsOpen = 1;
            Preferences();
            gPrefsOpen = 0;
        }
    }
#endif //WANT_PREFERENCES


static void Do_PluginGetString()
{
    FMX_Strings   stringType          = gFMX_ExternCallPtr->parm1;
   // FMX_ULong     windowsLanguageID   = gFMX_ExternCallPtr->parm2;
    FMX_ULong     outStringBufferSize = gFMX_ExternCallPtr->parm3;
    FMX_Unichar*  outStringBuffer     = (FMX_Unichar*)(gFMX_ExternCallPtr->result);
         
    switch( stringType )
    {
        case    kFMXT_OptionsStr:
            ProvideConfigString(outStringBuffer,outStringBufferSize);
            break;
        
        case    kFMXT_NameStr:
            ProvideNameString(outStringBuffer,outStringBufferSize);
            break;
            
        case    kFMXT_AppConfigStr:
            ProvidePreferencesString(outStringBuffer,outStringBufferSize);
            break;
    }
}


#if FMX_WIN_TARGET
    HINSTANCE   GetPluginInstance()
    {
        return (HINSTANCE)gFMX_ExternCallPtr->instanceID;
    }
#endif


#if FMX_MAC_TARGET
    CFBundleRef GetPluginBundle()
    {
        return (CFBundleRef)gFMX_ExternCallPtr->instanceID;
    }
#endif


void ProvideConfigString( FMX_UniChar* ioBuffer, FMX_ULong iBufferSize )
{
    #pragma unused(iBufferSize)
    
    //  Provide plug-in config string here.
    
    ioBuffer[ 0] = ((unsigned char*)PLUGIN_ID_STRING)[0];
    ioBuffer[ 1] = ((unsigned char*)PLUGIN_ID_STRING)[1];
    ioBuffer[ 2] = ((unsigned char*)PLUGIN_ID_STRING)[2];
    ioBuffer[ 3] = ((unsigned char*)PLUGIN_ID_STRING)[3];
    ioBuffer[ 4] = '1'; 

    #if WANT_PREFERENCES
        ioBuffer[ 5] = 'Y';
    #else
        ioBuffer[ 5] = 'n';
    #endif

    ioBuffer[ 6] = 'n';
    ioBuffer[ 7] = 'Y';

    #if WANT_IDLE
        ioBuffer[ 8] = 'Y';
    #else
        ioBuffer[ 8] = 'n';
    #endif

    ioBuffer[ 9] = 'n';
    ioBuffer[10] = 'n';
    ioBuffer[11] = 0;
}


void ProvideNameString( FMX_Unichar* ioBuffer, FMX_ULong iBufferSize )
{
    //  Provide plug-in name string here.

    ReadString( ioBuffer, iBufferSize, PLUGIN_NAME_ID );
}


void ProvidePreferencesString( FMX_Unichar* ioBuffer, FMX_ULong iBufferSize )
{
    //  Provide plug-in name string here.

    ReadString( ioBuffer, iBufferSize, PLUGIN_PREFERENCES_ID );
}


FMX_Boolean RegisterExternalFunctions()
{   
    //  if enable = FALSE is returned, Shutdown will 
    //  be called and plug-in will not be activated.
    
    FMX_Boolean enable = FALSE;

    // Register plug-in functions
    fmx::errcode            err;
    
    #ifdef FUNCTION_1_C_NAME
    fmx::ulong              regFunction1Flags  = 0 | FUNCTION_1_FLAGS;
    #endif
    #ifdef FUNCTION_2_C_NAME
    fmx::ulong              regFunction2Flags  = 0 | FUNCTION_2_FLAGS;
    #endif
    #ifdef FUNCTION_3_C_NAME
    fmx::ulong              regFunction3Flags  = 0 | FUNCTION_3_FLAGS;
    #endif
    #ifdef FUNCTION_4_C_NAME
    fmx::ulong              regFunction4Flags  = 0 | FUNCTION_4_FLAGS;
    #endif
    #ifdef FUNCTION_5_C_NAME
    fmx::ulong              regFunction5Flags  = 0 | FUNCTION_5_FLAGS;
    #endif
    #ifdef FUNCTION_6_C_NAME
    fmx::ulong              regFunction6Flags  = 0 | FUNCTION_6_FLAGS;
    #endif
    #ifdef FUNCTION_7_C_NAME
    fmx::ulong              regFunction7Flags  = 0 | FUNCTION_7_FLAGS;
    #endif
    #ifdef FUNCTION_8_C_NAME
    fmx::ulong              regFunction8Flags  = 0 | FUNCTION_8_FLAGS;
    #endif
    #ifdef FUNCTION_9_C_NAME
    fmx::ulong              regFunction9Flags  = 0 | FUNCTION_9_FLAGS;
    #endif
    #ifdef FUNCTION_10_C_NAME
    fmx::ulong              regFunction10Flags  = 0 | FUNCTION_10_FLAGS;
    #endif


    #ifdef FUNCTION_1_C_NAME
    err = RegisterExternalFunction( 1, FUNCTION_1_PARAMS, regFunction1Flags, FUNCTION_1_C_NAME );
    if_error(err,bail);
    #endif
    #ifdef FUNCTION_2_C_NAME
    err = RegisterExternalFunction( 2, FUNCTION_2_PARAMS, regFunction2Flags, FUNCTION_2_C_NAME );
    if_error(err,bail1);
    #endif
    #ifdef FUNCTION_3_C_NAME
    err = RegisterExternalFunction( 3, FUNCTION_3_PARAMS, regFunction3Flags, FUNCTION_3_C_NAME );
    if_error(err,bail2);
    #endif
    #ifdef FUNCTION_4_C_NAME
    err = RegisterExternalFunction( 4, FUNCTION_4_PARAMS, regFunction4Flags, FUNCTION_4_C_NAME );
    if_error(err,bail3);
    #endif
    #ifdef FUNCTION_5_C_NAME
    err = RegisterExternalFunction( 5, FUNCTION_5_PARAMS, regFunction5Flags, FUNCTION_5_C_NAME );
    if_error(err,bail4);
    #endif
    #ifdef FUNCTION_6_C_NAME
    err = RegisterExternalFunction( 6, FUNCTION_6_PARAMS, regFunction6Flags, FUNCTION_6_C_NAME );
    if_error(err,bail5);
    #endif
    #ifdef FUNCTION_7_C_NAME
    err = RegisterExternalFunction( 7, FUNCTION_7_PARAMS, regFunction7Flags, FUNCTION_7_C_NAME );
    if_error(err,bail6);
    #endif
    #ifdef FUNCTION_8_C_NAME
    err = RegisterExternalFunction( 8, FUNCTION_8_PARAMS, regFunction8Flags, FUNCTION_8_C_NAME );
    if_error(err,bail7);
    #endif
    #ifdef FUNCTION_9_C_NAME
    err = RegisterExternalFunction( 9, FUNCTION_9_PARAMS, regFunction9Flags, FUNCTION_9_C_NAME );
    if_error(err,bail8);
    #endif
    #ifdef FUNCTION_10_C_NAME
    err = RegisterExternalFunction( 10, FUNCTION_10_PARAMS, regFunction10Flags, FUNCTION_10_C_NAME );
    if_error(err,bail9);
    #endif
    //#ifdef FUNCTION_11_C_NAME
    //err = RegisterExternalFunction( 11, FUNCTION_11_PARAMS, regFunction11Flags, FUNCTION_11_C_NAME );
    //if_error(err,bail10);
    //#endif
    //...
    
    enable = TRUE;

    goto bail;
    
//...
#ifdef FUNCTION_10_C_NAME
//bail10:  UnRegisterExternalFunction( 10 );
bail9: 
#endif
#ifdef FUNCTION_9_C_NAME
 UnRegisterExternalFunction( 9 );
 bail8:
#endif
#ifdef FUNCTION_8_C_NAME
 UnRegisterExternalFunction( 8 );
 bail7:
#endif
#ifdef FUNCTION_7_C_NAME
 UnRegisterExternalFunction( 7 );
 bail6:
#endif
#ifdef FUNCTION_6_C_NAME
 UnRegisterExternalFunction( 6 );
 bail5:
#endif
#ifdef FUNCTION_5_C_NAME
 UnRegisterExternalFunction( 5 );
 bail4: 
#endif
#ifdef FUNCTION_4_C_NAME
 UnRegisterExternalFunction( 4 );
 bail3: 
#endif
#ifdef FUNCTION_3_C_NAME
 UnRegisterExternalFunction( 3 );
 bail2: 
#endif
#ifdef FUNCTION_2_C_NAME
 UnRegisterExternalFunction( 2 );
 bail1: 
#endif
#ifdef FUNCTION_1_C_NAME
  UnRegisterExternalFunction( 1 );
#endif
bail: 
    
    return enable;
}

void UnRegisterExternalFunctions()
{
    // Unregister plug-in functions
    fmx::QuadCharAutoPtr    pluginID(PLUGIN_ID_STRING[0], PLUGIN_ID_STRING[1], PLUGIN_ID_STRING[2], PLUGIN_ID_STRING[3]);

    #ifdef FUNCTION_10_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 10 );
    #endif
    #ifdef FUNCTION_9_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 9 );
    #endif
    #ifdef FUNCTION_8_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 8 );
    #endif
    #ifdef FUNCTION_7_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 7 );
    #endif
    #ifdef FUNCTION_6_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 6 );
    #endif
    #ifdef FUNCTION_5_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 5 );
    #endif
    #ifdef FUNCTION_4_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 4 );
    #endif
    #ifdef FUNCTION_3_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 3 );
    #endif
    #ifdef FUNCTION_2_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 2 );
    #endif
    #ifdef FUNCTION_1_C_NAME
        (void) fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, 1 );
    #endif
}
