cmake_minimum_required(VERSION 3.19)
project(omp-ipc-component LANGUAGES C CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

function(GroupSourcesByFolder target)
    set(SOURCE_GROUP_DELIMITER "/")
    set(last_dir "")
    set(files "")

    get_target_property(sources ${target} SOURCES)

    foreach(file ${sources})
        file(RELATIVE_PATH relative_file "${CMAKE_CURRENT_SOURCE_DIR}" ${file})
        get_filename_component(dir "${relative_file}" PATH)
        if(NOT "${dir}" STREQUAL "${last_dir}")
            if(files)
                source_group("${last_dir}" FILES ${files})
            endif()
            set(files "")
        endif()
        set(files ${files} ${file})
        set(last_dir "${dir}")
    endforeach()

    if(files)
        source_group("${last_dir}" FILES ${files})
    endif()
endfunction()

if (WIN32)
    add_definitions(
            -D_CRT_SECURE_NO_WARNINGS
            -DWIN32_LEAN_AND_MEAN
    )
endif ()

add_subdirectory(deps/omp-sdk)

include_directories(
    ${CMAKE_SOURCE_DIR}/deps/json
    ${CMAKE_SOURCE_DIR}/src
)

conan_omp_add_lib(nng 1.5.2)

file(GLOB_RECURSE OMPIPC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${OMPIPC_FILES})

if (WIN32)
    set(LIBRARIES shlwapi dbghelp winmm)
else ()
    set(LIBRARIES pthread dl m)
endif ()

target_link_libraries(${PROJECT_NAME}
    ${LIBRARIES}
    CONAN_PKG::nng
    OMP-SDK
)

GroupSourcesByFolder(${PROJECT_NAME})
