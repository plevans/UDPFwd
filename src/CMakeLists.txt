cmake_minimum_required( VERSION 2.6 )
project( UdpFwdGUI )
 
set( PROJECT_SRCS 
	main.c
	outputwindow.c
	callbacks.c
	comms.c
	remotelist.c
	enableDisable.c
	packets.c
)

set ( PROJECT_HEADERS 
	udpfwd.h
	widgets.h
)
	
link_directories( ${GTK3_LIB_DIRS} )
include_directories( ${GTK3_INCLUDE_DIRS} )

add_executable( ${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS} )

target_link_libraries( ${PROJECT_NAME} peprintf ${GTK3_LIBRARIES} )

if(WIN32)
  target_link_libraries( ${PROJECT_NAME} wsock32 ws2_32 )
endif()

add_dependencies( ${PROJECT_NAME} peprintf ConfigFiles )


set( ConfigDirs	share/udpfwd )
					
add_custom_target( ConfigFiles )


foreach(ConfigDir ${ConfigDirs})
	file( GLOB ConfigFiles ${ConfigDir}/* )
	add_custom_command(	TARGET ConfigFiles PRE_BUILD
						COMMAND ${CMAKE_COMMAND} -E
                        make_directory ${CMAKE_BINARY_DIR}/${ConfigDir} )
	add_custom_command(	TARGET ConfigFiles PRE_BUILD
						COMMAND ${CMAKE_COMMAND} -E
                        copy ${ConfigFiles} ${CMAKE_BINARY_DIR}/${ConfigDir} )
endforeach()
					   

