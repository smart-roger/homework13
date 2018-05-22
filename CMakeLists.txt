cmake_minimum_required(VERSION 3.2)

#project(join_server VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
project(join_server VERSION 0.0)

include_directories(
	include
)

find_package (Threads)

add_executable(join_server
					main.cpp 
					src/TTable.cpp
					src/TShell.cpp
					src/TQueryResult.cpp
					src/TOperationResult.cpp
					src/TDBController.cpp
					src/TCommand.cpp
					)

set_target_properties(join_server PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)


target_link_libraries (join_server ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT __shurik@list.ru)

include(CPack)
