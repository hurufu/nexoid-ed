cmake_minimum_required(VERSION 3.15)
project(nexoid VERSION 1.0.0 LANGUAGES C)

# --- General Compiler Settings ---
# Replicates the STD := gnu11 requirement
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON) # Allows GNU extensions (gnu11)

# Enable exporting all symbols on Windows (replaces Cygwin's --export-all-symbols)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Cross-platform threading (replaces -pthread hardcoding)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# --- Warnings and Compiler Flags ---
# Abstracting GCC-specific flags for cross-platform support
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    # Replicates WARNINGS := all extra and specific GCC features
    add_compile_options(-Wall -Wextra -fno-plt)
    
    # Optional features defined in the Makefile
    option(USE_LTO "Use Link Time Optimization" OFF)
    if(USE_LTO)
        include(CheckIPOSupported)
        check_ipo_supported(RESULT ipo_supported)
        if(ipo_supported)
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        endif()
    endif()
endif()

# --- Code Generation: Drakon (SQL -> DRN -> C/H) ---
# Simulates the sqlite3 and drakon-gen pipeline
set(DRAKON_SQL "src/NexoFast.sql")
set(DRAKON_DRN "${CMAKE_CURRENT_BINARY_DIR}/NexoFast.drn")
set(DRAKON_C "${CMAKE_CURRENT_BINARY_DIR}/NexoFast.c")
set(DRAKON_H "${CMAKE_CURRENT_BINARY_DIR}/NexoFast.h")

# Ensure you have paths configured for these tools or they are in the system PATH
find_program(SQLITE3_CMD sqlite3 REQUIRED)
find_program(DRAKON_GEN_CMD drakon-gen) # Assuming drakon-gen is in PATH

add_custom_command(
    OUTPUT ${DRAKON_DRN}
    COMMAND ${SQLITE3_CMD} -batch ${DRAKON_DRN} < ${CMAKE_CURRENT_SOURCE_DIR}/${DRAKON_SQL}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${DRAKON_SQL}
    COMMENT "Generating DRN from SQL using sqlite3..."
)

add_custom_command(
    OUTPUT ${DRAKON_C} ${DRAKON_H}
    COMMAND ${DRAKON_GEN_CMD} -in ${DRAKON_DRN}
    DEPENDS ${DRAKON_DRN}
    COMMENT "Generating C and H files using drakon-gen..."
)

# --- Library Sources ---
set(SOURCES 
    src/common.c 
    src/tag_retrival.c 
    ${DRAKON_C}
)

# Handle Cygwin/Windows specific stub files
if(WIN32 OR CYGWIN)
    list(APPEND SOURCES src/stubs.c)
endif()

# --- Targets: Shared and Static Libraries ---
# Shared Library
add_library(nexoid_shared SHARED ${SOURCES})
set_target_properties(nexoid_shared PROPERTIES OUTPUT_NAME nexoid)
target_include_directories(nexoid_shared PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> # For generated headers
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(nexoid_shared PRIVATE Threads::Threads)

# Static Library
add_library(nexoid_static STATIC ${SOURCES})
set_target_properties(nexoid_static PROPERTIES OUTPUT_NAME nexoid)
target_include_directories(nexoid_static PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(nexoid_static PRIVATE Threads::Threads)

# --- Unit Tests ---
enable_testing()

# Find 'check' unit testing framework (pkg-config check)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

# Code generation for tests (.t -> .c) via checkmk
find_program(CHECKMK_CMD checkmk REQUIRED)

# Assuming you are testing on one architecture for now (abstracting machine name)
set(UT_CHECK_FILE "ut/nexoid-ut.t")
set(UT_GEN_C "${CMAKE_CURRENT_BINARY_DIR}/nexoid-ut.c")

add_custom_command(
    OUTPUT ${UT_GEN_C}
    COMMAND ${CHECKMK_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/${UT_CHECK_FILE} > ${UT_GEN_C}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${UT_CHECK_FILE}
    COMMENT "Generating Unit Test C code via checkmk..."
)

add_executable(ut_nexoid ut/common.c ${UT_GEN_C})
target_include_directories(ut_nexoid PRIVATE ${CHECK_INCLUDE_DIRS})
target_link_libraries(ut_nexoid PRIVATE 
    nexoid_static 
    Threads::Threads 
    ${CHECK_LIBRARIES}
)

add_test(NAME UnitTests COMMAND ut_nexoid)

# --- Installation ---
# Replicates PREFIX and DESTDIR logic
include(GNUInstallDirs)

install(TARGETS nexoid_shared nexoid_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # For Windows DLLs
)

# Install headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nexoid FILES_MATCHING PATTERN "*.h")
install(FILES ${DRAKON_H} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nexoid)