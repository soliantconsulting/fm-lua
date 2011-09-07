//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMUtils.h - Header file for 24U Plug-In Template's utility functions
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

//
//  This file defines a few functions you might find handy when writing
//  your plug-in's code. You don't need to explicitly include this header
//  file as it is included by the FMTemplate.h header.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef __FMUtils_h__
#define __FMUtils_h__

  #if __cplusplus
    extern "C" {
  #endif

#pragma mark ReadString

////////////////////////////////////////////////////////////////////////////////
//
    void ReadString( FMX_Unichar* ioBuffer, 
                     FMX_ULong iBufferSize, 
                     FMX_ULong iStringID    );
//
////////////////////////////////////////////////////////////////////////////////
//
//  This function is a cross-platform accessor to localizable strings.
//  On Mac OS X, this functions appends the iStringID to "String" and then
//  uses the result string as a key to Localizable.strings.
//  On Windows, it simply tries to load the string from a STRINGTABLE resource
//  with the specified ID.
//
//  ioBuffer    <- an allocated storage for the requested string
//              -> the requested string if it was successfully obtained
//
//  iBufferSize <- size of the allocated buffer
//
//  iStringID   <- ID of the string to obtain
//
////////////////////////////////////////////////////////////////////////////////


#pragma mark RegisterExternalFunction

////////////////////////////////////////////////////////////////////////////////
//
    fmx::errcode RegisterExternalFunction( FMX_UShort iFunctionID,
                                       FMX_Short iMinArgs,
                                       FMX_Short iMaxArgs,
                                       FMX_ULong iTypeFlags,
                                       fmx::ExtPluginType iFunctionPtr );
//
////////////////////////////////////////////////////////////////////////////////
//
//  Registers an external function to be available for FileMaker calculations.
//  This is a simplified version of FileMaker's function for registering
//  external functions. This function takes the necessary parameters, and
//  constructs the other ones bases on the constants defined in FMTConfig.h.
//
//  iFunctionsID <- ID of the function to register (within the current plug-in)
//  iMinArgs     <- minimum number of parameters the function accepts
//  iMaxArgs     <- maximum number of parameters the function accepts
//  iTypeFlags   <- flags defining where the functions should be available
//  iFunctionPtr <- pointer to the function's handler
//
//  result       -> returns an error code if the function registration fails
//
////////////////////////////////////////////////////////////////////////////////


#pragma mark UnRegisterExternalFunction

////////////////////////////////////////////////////////////////////////////////
//
    fmx::errcode UnRegisterExternalFunction( FMX_UShort iFunctionID );
//
////////////////////////////////////////////////////////////////////////////////
//
//  Unregisters an existing external function, so that it is no longer available
//  for FileMaker calculations.
//  This is a simplified version of FileMaker's function for registering
//  external functions. This function takes the function's ID and unregisters
//  the function in the current plug-in's context.
//
//  iFunctionsID <- ID of the function to unregister (within the current plug-in)
//
//  result       -> returns an error code if the function unregistration fails
//
////////////////////////////////////////////////////////////////////////////////


#pragma mark XPLAT_ALERT

////////////////////////////////////////////////////////////////////////////////
//
//  void XPLAT_ALERT( const char* iMessage );
//
////////////////////////////////////////////////////////////////////////////////
//
//  This macro provides a simple cross-platform way to display an alert
//  when critical conditions preventing the plug-in's functionality happen.
//  You can use this macro in the Startup() function to inform user when
//  your check for required environment fails.
//
//  iMessage <- message to display to the user
//
////////////////////////////////////////////////////////////////////////////////
//
    #if FMX_WIN_TARGET
        #define XPLAT_ALERT(msg)    MessageBoxA(NULL, msg, (char*)"\0\0", MB_TASKMODAL|MB_OK|MB_ICONEXCLAMATION);
    #else
        #define XPLAT_ALERT(msg)    { SInt16 item; StandardAlert(kAlertCautionAlert, "\p" msg, "\p", NULL, &item); }
    #endif
//
////////////////////////////////////////////////////////////////////////////////


#if FMX_MAC_TARGET
	unsigned long Sub_OSXLoadString(unsigned long stringID, FMX_Unichar* intoHere, long intoHereMax);
#endif

  #if __cplusplus
    }
  #endif
#endif // __FMUtils_h__

