cmake_minimum_required(VERSION 3.2)

project(join_server VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(join_server VERSION 0.0)

find_package(Boost COMPONENTS system thread REQUIRED)
SET(Boost_USE_STATIC_LIBS ON)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

include_directories(
	include
)

add_executable(join_server
					main.cpp 
					src/TTable.cpp
					src/TShell.cpp
					src/TDBController.cpp
					src/TCommand.cpp
					src/network.cpp
					)

set_target_properties(join_server PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})
target_link_libraries (join_server ${USED_LIBS})

install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT __shurik@list.ru)

include(CPack)
