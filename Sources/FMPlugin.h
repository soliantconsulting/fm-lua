//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMPlugin.h - Definitions shared across the plug-in sources
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
//  This header file is dedicated for constants that need to be globally
//  available across all plug-in sources. This is the only file expected
//  to define constants to be used by both the template sources and your
//  own sources.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __FMPlugin_h__
#define __FMPlugin_h__

/////////////////////////////////////////////////////////////////////////////
//
//  Don't modify the following constats, they are not yet fully customizable
//  in this version of 24U Plug-In Template. These constants define IDs of
//  localizable string resources, and are required for the plug-in to
//  work properly.
//

#define PLUGIN_NAME_ID          1
#define PLUGIN_PREFERENCES_ID   2
#define PLUGIN_VERSION_ID       3

#define FUNCTION_OFFSET       100


/////////////////////////////////////////////////////////////////////////////
//
//  We are including this header in FMTConfig.h which is included by
//  FMTemplate.plc. The following definitions are for use in code only,
//  so we are excluding them from Plist definition from.
//

#ifndef __PLIST__

  #if __cplusplus
    extern "C" {
  #endif
  
  ////////////////////////////////////////////
  //
  //  Place your own global definitions here
  //
  ////////////////////////////////////////////
  
  #if __cplusplus
    }
  #endif

#endif //__PLIST__

/////////////////////////////////////////////////////////////////////////////

#endif // __FMPlugin_h__
