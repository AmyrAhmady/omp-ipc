project(omp-rpc-component LANGUAGES C CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_definitions(
            -D_CRT_SECURE_NO_WARNINGS
            -DWIN32_LEAN_AND_MEAN
    )
endif ()

# Dependencies

add_subdirectory(
        ${PROJECT_SOURCE_DIR}/../deps/omp-sdk deps/omp-sdk
)

include_directories(
        ${PROJECT_SOURCE_DIR}/../deps/json
        ${PROJECT_SOURCE_DIR}
)

# Linking

conan_omp_add_lib(nng 1.5.2)

file(GLOB_RECURSE OMPRPC_FILES
    *.hpp
    *.h
    *.cpp
)

add_library(${PROJECT_NAME} SHARED ${OMPRPC_FILES})

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
