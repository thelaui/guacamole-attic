
project(guacamole)

include(schism_project)
include(schism_boost)
include(schism_macros)

set(SRC_DIR                         "${guacamole_SOURCE_DIR}/../../src")
set(SCM_PROJECT_SOURCE_DIR          ${SRC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${SCHISM_LIBRARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${SCHISM_LIBRARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${SCHISM_LIBRARY_DIR})

# source files
scm_project_files(SOURCE_FILES      ${SRC_DIR} *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR} *.hpp *.inl)

scm_project_files(SOURCE_FILES      ${SRC_DIR}/renderer *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR}/renderer *.hpp *.inl)

scm_project_files(SOURCE_FILES      ${SRC_DIR}/scenegraph *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR}/scenegraph *.hpp *.inl)

scm_project_files(SOURCE_FILES      ${SRC_DIR}/traverser *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR}/traverser *.hpp *.inl)

scm_project_files(SOURCE_FILES      ${SRC_DIR}/utils *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR}/utils *.hpp *.inl)

# include header and inline files in source files for visual studio projects
if (WIN32)
    if (MSVC)
        set (SOURCE_FILES ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES} ${KERNEL_FILES})
    endif (MSVC)
endif (WIN32)

# set include and lib directories
scm_project_include_directories(ALL   ${SRC_DIR}
                                      ${SCM_ROOT_DIR}/scm_core/src
                                      ${SCM_ROOT_DIR}/scm_data/src
                                      ${SCM_ROOT_DIR}/scm_gl_core/src
                                      ${SCM_ROOT_DIR}/scm_gl_util/src
                                      ${SCM_BOOST_INC_DIR})

scm_project_include_directories(WIN32 ${GLOBAL_EXT_DIR}/inc
                                      ${GLOBAL_EXT_DIR}/inc/freeimage)
scm_project_include_directories(UNIX  /opt/OpenCL/include)

# set library directories
scm_project_link_directories(ALL      ${SCM_LIB_DIR}/${SCHISM_PLATFORM}
                                      ${SCM_BOOST_LIB_DIR})

scm_project_link_directories(WIN32    ${GLOBAL_EXT_DIR}/lib)

if (WIN32)
    # add preprocessor defines
    add_definitions(-DSCM_BUILD_LIBRARY_guacamole=\(\))
endif (WIN32)

# add/create library
if (SCHISM_BUILD_STATIC)
    add_definitions(-DSCM_STATIC_BUILD)
	add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
else (SCHISM_BUILD_STATIC)
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
endif (SCHISM_BUILD_STATIC)

# link libraries
scm_link_libraries(ALL
    general scm_core
    general scm_data
    general scm_gl_core
    general scm_gl_util
)
scm_link_libraries(WIN32
    general OpenCL
    general FreeImage
    general FreeImagePlus
    optimized libboost_thread-${SCM_BOOST_MT_REL}           debug libboost_thread-${SCM_BOOST_MT_DBG}
)
scm_link_libraries(UNIX
    freeimageplus
    boost_thread${SCM_BOOST_MT_REL}
)

add_dependencies(${PROJECT_NAME}
    scm_core
    scm_data
    scm_gl_core
    scm_gl_util
)

