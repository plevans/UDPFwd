


cmake_minimum_required( VERSION 2.6 )
project( peprintf )
 
set( PROJECT_SRCS 
	peprintf.c
)

set ( PROJECT_HEADERS 
	peprintf.h
)

 
add_library( ${PROJECT_NAME} STATIC ${PROJECT_SRCS} ${PROJECT_HEADERS} )