cmake_minimum_required( VERSION 2.6 )
project( UdpFwd )

# Set a default build type if none was specified
set( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build Type (Release/Debug)" FORCE )

# Should help eclipse find library headers for source code highlighting
SET(CMAKE_VERBOSE_MAKEFILE ON)

## libs required by gtk3 and its dependencies
set( gtk_libnames
		gtk-3
		gdk-3
		epoxy
		pangocairo-1.0
		pango-1.0
		atk-1.0
		cairo-gobject
		cairo
		z
		pixman-1
		png16
		gdk_pixbuf-2.0
		gio-2.0
		gmodule-2.0
		gobject-2.0
		ffi
		glib-2.0
		intl
		xml2
		pcre
		)
set( gtk_incnames
		gdk/gdk.h
		gtk/gtk.h
		cairo.h
		pango/pango.h
		atk/atk.h
		pixman.h
		png.h
		gdk-pixbuf/gdk-pixbuf.h
		glib.h
		glib-object.h
		glibconfig.h
	)	
set( gtk_pathsuffixes 
		gtk-3.0
		cairo
		pango-1.0
		atk-1.0
		pixman-1
		libpng16
		gdk-pixbuf-2.0
		glib-2.0
		lib/glib-2.0/include
	)
# windows specific / windows api
if( WIN32 )
	list( APPEND gtk_libnames pangowin32-1.0 )
endif( WIN32 )

function( find_lib _export_name _libnames _incnames _pathsuffixes )
	set( _found 1 )
	set( _inc_dirs )
	set( _lib_dirs )
	set( _libs )
			
	foreach( _lib ${_libnames} )
		message( STATUS "Looking for lib${_lib}.a" )
				
		find_library( _${_lib}_LIB
			NAMES ${_lib}
		)
		
		get_filename_component( _${_lib}_LIB_DIR ${_${_lib}_LIB} DIRECTORY )
		
		if( _${_lib}_LIB )
			list( APPEND _libs ${_${_lib}_LIB} )
		else()
			set( _found 0 )
			message( SEND_ERROR "Failed to find lib${_lib}.a" )
		endif()
		
		if( _${_lib}_LIB_DIR )
			list( APPEND _lib_dirs ${_${_lib}_LIB_DIR} )
		else()
			set( _found 0 )
		endif()
		
		unset( _${_lib}_LIB CACHE )
	endforeach()
	
	foreach( _inc ${_incnames} )
		message( STATUS "Looking for ${_inc}" )
		find_path(	_${_inc}_INC
					NAMES ${_inc}
					PATH_SUFFIXES ${_pathsuffixes}
				)
					
		if( _${_inc}_INC )
			list( APPEND _inc_dirs ${_${_inc}_INC} )
		else()
			set( _found 0 )
			message( SEND_ERROR "Failed to find ${_inc}" )
		endif()
		
		unset( _${_inc}_INC CACHE )
	endforeach()
	
	list( REMOVE_DUPLICATES _libnames )
	list( REMOVE_DUPLICATES _lib_dirs )
	list( REMOVE_DUPLICATES _inc_dirs )
	
	set(  ${_export_name}_LIBRARIES ${_libnames} CACHE STRING "Paths to ${_export_name} libararies" )
	set(  ${_export_name}_INCLUDE_DIRS ${_inc_dirs} CACHE STRING "Paths to ${_export_name} headers"  )
	set(  ${_export_name}_LIB_DIRS ${_lib_dirs} CACHE STRING "Paths to ${_export_name} libs"  )
	set(  ${_export_name}_FOUND ${_found} CACHE BOOL " ${_export_name} was found" )

endfunction( find_lib )

 
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

SET( CMAKE_USE_RELATIVE_PATHS ON ) 

add_definitions( -DMS_HAVE_PEPRINTF )

include_directories( "src/peprintf" )
include_directories( "src/" )
		
find_lib( "GTK3" "${gtk_libnames}" "${gtk_incnames}" "${gtk_pathsuffixes}" )

add_subdirectory( "src/dummyHIL" )
add_subdirectory( "src/peprintf" )
add_subdirectory( "src/" )


					






