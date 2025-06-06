
project(godot_gameplay_attributes)

set(godot_gameplay_attributes_version 1.0.0)
set(godot_gameplay_attributes_output_directory "${CMAKE_SOURCE_DIR}/godot/addons/godot_gameplay_attributes/bin/${PLATFORM}")
set(godot_gameplay_attributes_library_name "${PROJECT_NAME}.${PLATFORM}.template_${DEBUG_RELEASE}.${ARCH}.${EXT}")

# Automatically pick up files added to src
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add a dynamic library called gameplay - this builds gameplay.dll
add_library(${PROJECT_NAME} SHARED ${SOURCES}
        attribute.cpp
        attribute.hpp
        attribute_container.cpp
        attribute_container.hpp
        register_types.cpp
        register_types.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "src")
target_link_libraries(${PROJECT_NAME} PUBLIC godot::cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX src FILES ${SOURCES})

# Copy the library to the godot addons directory after building it ${godot_gameplay_attributes_output_directory}
# The library will be copied to the godot addons directory after building it

message(STATUS "Copying ${PROJECT_NAME} to ${godot_gameplay_attributes_output_directory}/${LIBRARY_NAME}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${PROJECT_NAME}>
        "${godot_gameplay_attributes_output_directory}/${godot_gameplay_attributes_library_name}")
