cmake_minimum_required(VERSION 3.0)
project(icarus_minotaur VERSION 0.0.0.0)

add_definitions(-DVERSION_MAJOR="${PROJECT_VERSION_MAJOR}")
add_definitions(-DVERSION_MINOR="${PROJECT_VERSION_MINOR}")
add_definitions(-DVERSION_PATCH="${PROJECT_VERSION_PATCH}")
add_definitions(-DVERSION_TWEAK="${PROJECT_VERSION_TWEAK}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(CMAKE_MODULE_PATH ${icarus_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

add_definitions(-DOUTPUT_DIRECTORY="${CMAKE_BINARY_DIR}")
add_definitions(-DSOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

#
# BOOST
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(BOOST_ROOT "$ENV{HOME}/libs/boost_1_63_0")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
find_package(Boost REQUIRED log_setup log system filesystem program_options regex date_time unit_test_framework)
message("--   include: ${Boost_INCLUDE_DIRS}")
message("--   library: ${Boost_LIBRARY_DIRS}")
message("")
add_definitions(-DBOOST_LOG_DYN_LINK=1)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(minotaur SHARED

	src/minotaur/fileinfo.h

	src/minotaur/compiler.h
	src/minotaur/compiler.cpp

	src/minotaur/parser.h
	src/minotaur/parser.cpp

	src/minotaur/cpptemplatebuilder.h
	src/minotaur/cpptemplatebuilder.cpp

	src/minotaur/exceptions.h
	src/minotaur/exceptions.cpp

	src/minotaur/metainfo.h
	src/minotaur/metainfo.cpp

	src/minotaur/templatebuilder.h
	src/minotaur/templatebuilder.cpp
)

add_executable(mntr
	src/minotaur/mntr.cpp
)

target_link_libraries(mntr
	boost_system
	boost_filesystem
	boost_program_options
	boost_regex

	minotaur
)

# Test configuration thanks to http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/

enable_testing()

add_definitions(-DTEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources")
set(TEST_OUTPUT ${CMAKE_BINARY_DIR}/tests)
message("-- Tests")

file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/minotaur/*.cpp)
foreach (testSrc ${TEST_SRCS})
	get_filename_component(testName ${testSrc} NAME_WE)
	string(REPLACE "test/" "" testPackage "${testSrc}")
	string(REPLACE "${testName}.cpp" "" testPackage "${testPackage}")
	string(REPLACE "/" "_" testPackage "${testPackage}")
	set(testName "test_${testPackage}${testName}")
	message("--   ${testSrc} as ${testName}")

	add_executable(${testName} ${testSrc})

	target_link_libraries(${testName}
		${Boost_LIBRARIES}

		minotaur
	)

	set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT})

	add_test(NAME ${testName}
		WORKING_DIRECTORY ${TEST_OUTPUT}
		COMMAND ${TEST_OUTPUT}/${testName}
		)
endforeach (testSrc)
message("")
