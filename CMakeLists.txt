cmake_minimum_required(VERSION 3.15)
project(loot_library.h)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if (WIN32)
    set(CMAKE_C_FLAGS "-D_WIN32")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3 -DDEBUG")

set(HEADERS
        src/logging.h
        src/loot_functions.h
        src/loot_table_context.h
        src/mc_loot.h
        src/rng.h
        src/cjson/cJSON.h
)
set(SOURCES
        src/loot_functions.c
        src/loot_table_context.c
        src/loot_table_parser.c
        src/cjson/cJSON.c
        src/examples/example.c
)

add_library(objects OBJECT ${SOURCES})
set_property(TARGET objects PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(loot_library.h SHARED $<TARGET_OBJECTS:objects>)
add_library(loot_library.h_static STATIC $<TARGET_OBJECTS:objects>)

if (WIN32)
    set_target_properties(loot_library.h PROPERTIES PREFIX "")
endif()


install(TARGETS loot_library.h loot_library.h_static DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
