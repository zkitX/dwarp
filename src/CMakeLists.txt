file (GLOB_RECURSE src CONFIGURE_DEPENDS RELATIVE ${CMAKE_SOURCE_DIR}/src/ *.cpp *.h *.hpp *.inl)

add_executable(dwarp ${src})

source_group(TREE "${PROJECT_SOURCE_DIR}" FILES ${src})

target_compile_features(dwarp PRIVATE cxx_std_17)

target_include_directories(dwarp
    PRIVATE
    ${CMAKE_SOURCE_DIR}/extern/ELFIO
    ${CMAKE_SOURCE_DIR}/src
    )