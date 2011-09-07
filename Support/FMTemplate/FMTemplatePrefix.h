//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMTemplatePrefix.h - Prefix header file for 24U Plug-In Template
//
//  Version 3.0, Copyright ©2006-2010 by 24U Software. All rights reserved.
//
//  Written by Tomas Rycl
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
// This prefix is used to override new CFSTR calls in Mac OS 10.4 which
// casuses FM crash when unloading plugin.
//
////////////////////////////////////////////////////////////////////////////////
 
#if defined( __GNUC__ )

  #undef __CONSTANT_CFSTRINGS__
  
  #include <CoreServices/CoreServices.h>

#endif
    



