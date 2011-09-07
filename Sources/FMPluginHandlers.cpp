//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMPluginHandlers.cpp - Functions for handling optional plug-in events
//
//  Version 3.0, Copyright ©2002-2010 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky, HOnza Koudelka, and Petr Miksik
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
//  This source file contains code for the Startup, Shutdown, Preferences, and
//  Idle handlers. Please see comments attached to each individual function
//  for instructions on writing code for them. We suggest that you don't add
//  more functions to this file if they would be referenced from other files.
//  If you have a need for utility functions that you would call from different
//  places, you should create a separate source file for them.
//
////////////////////////////////////////////////////////////////////////////////


#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"



////////////////////////////////////////////////////////////////////////////////
//
//  Startup()
//
/////////////////////////////////////////////////////////////////////////////
//
//  This function will get called once each time your plug-in needs to be
//  initialized. That is during the FileMaker application startup, or right
//  after clicking on the checkbox that enables your plug-in in the
//  application's Preferences dialog.
//
//  If your plug-in has any software or hardware requirements that might
//  not be met, you should perform the necessary environment check here,
//  and disable the plug-in if the environment is not sufficient.
//
//  Return TRUE as a result from this function to enable the plug-in.
//  If you decide that the plug-in should be disabled, return FALSE.
//  

FMX_Boolean Startup()
{
    FMX_Boolean enable = TRUE;    // Enable the plug-in by default

    // Write your initialization/environment check code here.
    // Set the enable variable to FALSE if you want to disable the plug-in.
    
    return enable;                // Return TRUE to enable the plug-in
}


////////////////////////////////////////////////////////////////////////////////
//
//  Shutdown()
//
/////////////////////////////////////////////////////////////////////////////
//
//  When user disables your plug-in in the application's Preferences dialog
//  or when he quits the FileMaker application, this will be the last function
//  that will get called.
//  
//  If your plug-in allocates any system resources, such as memory, that
//  remain allocated across multiple calls to the plug-in's functions, you
//  should release the resources and perform any necessary cleanup in this
//  function.
//
//  Keep in mind that once deactivated, your plug-in can be re-activated
//  in the application's Preferences dialog, so make sure you recover the
//  plug-in into exactly the same state it was before getting activated for
//  the first time.
//
//  This function does not take any input parameters nor does it have to
//  return any value as a result.
//

void Shutdown()
{
    // Write your shutdown/cleanup code here.
    // Don't forget to release any occupied system resources.
}


////////////////////////////////////////////////////////////////////////////////
//
//  Preferences()
//
/////////////////////////////////////////////////////////////////////////////
//
//  If you set the WANT_PREFERENCES constant in the FMTConfig.h file to 1,
//  your plug-in will have an enabled "Configure..." button in the Plug-In
//  pane of the application's Preferences dialog. When a user clicks on that
//  button, the following function will get called. After then, you are
//  supposed to display your plug-in's preferences dialog to let user modify
//  your plug-in's preferences.
//
//  If you don't want to use any user-configurable values in your plug-in,
//  you should set the WANT_PREFERENCES constant to 0. Then the following
//  function should never get called. Anyway, it is still a good idea to at
//  least beep or display an error message in here, just for the case you
//  forget to set the WANT_PREFERENCES constant to 0.
//
//  This function does not take any input parameters nor does it have to
//  return any value as a result.
//

#if WANT_PREFERENCES

void Preferences()
{
    XPLAT_ALERT("This plug-in does not have any configurable options")
}

#endif //WANT_PREFERENCES


////////////////////////////////////////////////////////////////////////////////
//
//  SafeIdle()
//  SemiSafeidle(idleLevel)
//  UnsafeIdle()
//
/////////////////////////////////////////////////////////////////////////////
//
//  If the WANT_IDLE constant is set to 1 in the FMTConfig.h file, and if
//  your plug-in is enabled, these three functions will get called
//  periodically when the FileMaker application has nothing else to do.
//  There is no control over how often this will happen, so you should not
//  rely on any specific frequency. Which of the three functions will actually
//  get called depends on the current idle level.
//
//  You can put any idle processing in the SafeIdle function, such as
//  background activity, scheduled actions, etc., but you should return
//  the control to FileMaker quickly as it is stuck while you are doing
//  your idle processing. In general you have to be very careful about doing
//  something in the SemiSafeIdle function and you should not have a reason
//  to do anything in the UnsafeIdle function.
//

#if WANT_IDLE

void SafeIdle()
{
    // The plug-in is at user idle time and can do idle processing
}

void SemiSafeIdle(FMX_IdleLevel idleLevel)
{
    // FileMaker was nice to give you some processing time but it is
    // doing something, so be careful and return as soon as possible
    
    // Check idle state
    switch (idleLevel)
    {
        case kFMXT_UserNotIdle:
        case kFMXT_ScriptPaused:
        case kFMXT_ScriptRunning:
          break;            
    
    };// switch idleLevel 
}

void UnsafeIdle()
{
    // The plug-in should wait and do nothing at this time.
}

#endif //WANT_IDLE
