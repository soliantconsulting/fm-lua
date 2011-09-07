#!/bin/bash

##################################################################################
#  
# 24u_plist_compiler.sh - generates info.plist and Localizable.strings using
#				          information from header files and project settings
#
#  Version 3.0, Copyright ©2004-2010 by 24U Software. All rights reserved.
#
#  Written by Josef Andrysek
#
##################################################################################
#
#  The latest version of 24U Plug-In Template is available for download from:
#
#  http://www.24uSoftware.com/PlugInTemplate 
#
##################################################################################
#
#  24U Sample Code - Terms of use
#
#  Under the terms of the 24U Software License Agreement, 24U s.r.o. grants
#  you a non-exclusive royalty-free Developer License (3.2) to use 24U Plug-In
#  Template solely to compile plug-ins for use with FileMaker products.
#
#  Redistribution of 24U Sample Code in the source form, as part of
#  an open-source plug-in project is permitted provided that the following
#  conditions are met:
#
#  * Redistributions of source code must retain the copyright notice, the terms
#    of use, and the "24U Software License Agreement" document.
#
#  * We require that you make it clear in the source wherever modified that the
#    code was descended from 24U Sample Code, but that you've made changes.
#
#  See the "License.txt" and "24U Software License Agreement.pdf" files
#  for detailed terms of use and licensing conditions.
#
##################################################################################

#
#  This file contains a simple technology to generate files using template files.
#
##################################################################################


#process each line of input
while read command;do

	# Slightly preprocess each input line  which comes from preprocessor 
	# Each input line can contain my_variable= "something" " something else" " something else"
	# We have to convert it to the form  my_variable= "something something else something else"
	com1=${command/'""'/}
	com2=${com1/'" "'/}
	com3=${com2/'"  "'/}
	com4=${com3/'"   "'/}
	com5=${com4/©/Â©}
	# Now the result can be evaluated as a shell command
	eval $com5
done



# Define shortnames to all template placeholders
kBundleName=$PRODUCT_NAME
kBundleVersion=$my_plugin_version
kBundleShortVersion="$kBundleName version $kBundleVersion"
kBundleGetInfo="$kBundleShortVersion, $my_copy_statement"
kBundleIdentifier=$my_plugin_bundle_id
kPluginName=$my_plugin_name
kPluginInfo=$my_plugin_info
kPluginIdString=$my_plugin_id_string

# If there actually exist  info.plist, delete it
plist_file="$BUILD_DIR/$INFOPLIST_PATH"
if [ -f "$plist_file" ]
then
	rm "$plist_file"
fi


# Now create the new info.plist file using the infoplist.template
while read line;do
	y=${line/kBundleIdentifier/$kBundleIdentifier}
	y=${y/kBundleShortVersion/$kBundleShortVersion}
	y=${y/kBundleName/$kBundleName}
	y=${y/kBundleGetInfo/$kBundleGetInfo}
	y=${y/kBundleVersion/$kBundleVersion}
	y=${y/kPluginIdString/$kPluginIdString}
	echo $y>>"$plist_file"
done <"$XCODE_SUPPORT_DIR/infoplist.template"



# If there doesn't exist the directory Resources, create it
resource_dir="$BUILD_DIR/$UNLOCALIZED_RESOURCES_FOLDER_PATH"
if [ ! -d "$resource_dir" ]
then
	mkdir "$resource_dir"
fi

# If there doesn't exist the directory Englis.lproj  create it
string_dir="$resource_dir/English.lproj"
if [ ! -d "$string_dir" ]
then
	mkdir "$string_dir"
fi

# If there actually exist Localizable.string, delete it
string_file="$string_dir/Localizable.strings"
if [ -f "$string_file" ]
then
	rm "$string_file"
fi


# Now create the new Localizable.string file using the localizablestring.template
while read line;do
	y=${line/kPluginName/$kPluginName}
	y=${y/kPluginInfo/$kPluginInfo}
	y=${y/kBundleVersion/$kBundleVersion}
	echo "$y">>"$string_file"
done< "$XCODE_SUPPORT_DIR/localizablestrings.template"
 
# Add prototypes of used functions to the file Localizable.string
if [ "${my_function_1_prototype+1}" = "1" ] ; then echo $my_function_1_prototype_str '= "'$my_function_1_prototype'";'>>"$string_file" ; fi
if [ "${my_function_2_prototype+1}" = "1" ] ; then echo $my_function_2_prototype_str '= "'$my_function_2_prototype'";'>>"$string_file" ; fi
if [ "${my_function_3_prototype+1}" = "1" ] ; then echo $my_function_3_prototype_str '= "'$my_function_3_prototype'";'>>"$string_file" ; fi
if [ "${my_function_4_prototype+1}" = "1" ] ; then echo $my_function_4_prototype_str '= "'$my_function_4_prototype'";'>>"$string_file" ; fi
if [ "${my_function_5_prototype+1}" = "1" ] ; then echo $my_function_5_prototype_str '= "'$my_function_5_prototype'";'>>"$string_file" ; fi
if [ "${my_function_6_prototype+1}" = "1" ] ; then echo $my_function_6_prototype_str '= "'$my_function_6_prototype'";'>>"$string_file" ; fi
if [ "${my_function_7_prototype+1}" = "1" ] ; then echo $my_function_7_prototype_str '= "'$my_function_7_prototype'";'>>"$string_file" ; fi
if [ "${my_function_8_prototype+1}" = "1" ] ; then echo $my_function_8_prototype_str '= "'$my_function_8_prototype'";'>>"$string_file" ; fi
if [ "${my_function_9_prototype+1}" = "1" ] ; then echo $my_function_9_prototype_str '= "'$my_function_9_prototype'";'>>"$string_file" ; fi
if [ "${my_function_10_prototype+1}" = "1" ] ; then echo $my_function_10_prototype_str '= "'$my_function_10_prototype'";'>>"$string_file" ; fi

