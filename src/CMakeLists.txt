cmake_minimum_required(VERSION 3.5)

project(kosp)

# #------------------- FETCH FILES -------------------##

# For absolute paths with headers.
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
SET(LIB_BASEPATH "${CMAKE_SOURCE_DIR}/../lib")
SET(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")

# set(SOURCEFILES
# FsAccess/PublicFunctions/FsAccess.c
# FsAccess/PrivateFunctions/FsAccess_FlightLoopCB.c.c
# )
# set(HEADERS
# FsAccess/PrivateFunctions/FsAccess_PrivateFunctions.h
# )
# set(ALL_SOURCES ${SOURCEFILES} ${HEADERS})

# Recursively grab all .c and .h files under src/
file(GLOB_RECURSE ALL_SOURCES
  "${BASEPATH}/*.c"
  "${BASEPATH}/*.h"
)

list(SORT ALL_SOURCES)

# Print a neat message
message(STATUS "Source files to be compiled:")

foreach(file ${SOURCEFILES})
  message(STATUS "  ${file}")
endforeach()

message(STATUS "Header files included:")

foreach(file ${HEADERS})
  message(STATUS "  ${file}")
endforeach()

# #------------------- FETCH LIBRARIES -------------------##

# cJSON
add_subdirectory("${LIB_BASEPATH}/cjson" "${CMAKE_BINARY_DIR}/build_cjson")

# Libacfutils
option(LIBACFUTILS "libacfutils path")

if(${LIBACFUTILS} STREQUAL "OFF")
  message("Missing LIBACFUTILS option. Call cmake -DLIBACFUTILS=<path>")
  return()
endif()

# Platform-specific variables
if(APPLE)
  set(PLAT_SHORT "mac64")
  set(PLAT_LONG "mac-64")
  set(PLAT_ONLY "mac")
  set(PLUGIN_BIN_OUTDIR "mac_x64")
elseif(WIN32)
  set(PLAT_SHORT "win64")
  set(PLAT_LONG "win-64")
  set(PLAT_ONLY "win")
  set(PLUGIN_BIN_OUTDIR "win_x64")
else()
  set(PLAT_SHORT "lin64")
  set(PLAT_LONG "linux-64")
  set(PLAT_ONLY "linux")
  set(PLUGIN_BIN_OUTDIR "lin_x64")
endif()

# Build path setup
file(GLOB GLEW_PREFIX "${LIBACFUTILS}/glew/glew-1.13.0-${PLAT_LONG}/install")
file(GLOB CAIRO_PREFIX "${LIBACFUTILS}/cairo/cairo-${PLAT_LONG}")
file(GLOB PIXMAN_PREFIX "${LIBACFUTILS}/cairo/pixman-${PLAT_LONG}")
file(GLOB LIBPNG_PREFIX "${LIBACFUTILS}/libpng/libpng-${PLAT_LONG}")
file(GLOB FREETYPE_PREFIX "${LIBACFUTILS}/freetype/freetype-${PLAT_LONG}")
file(GLOB OPENSSL_PREFIX "${LIBACFUTILS}/ssl/openssl-${PLAT_LONG}")
file(GLOB ICONV_PREFIX "${LIBACFUTILS}/libiconv/libiconv-${PLAT_LONG}")
file(GLOB CGLM_PREFIX "${LIBACFUTILS}/cglm/cglm-0.7.9")
file(GLOB CURL_PREFIX "${LIBACFUTILS}/curl/libcurl-${PLAT_LONG}")

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} -DDEBUG -g")
# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -O0 -g")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -DDEBUG -g")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -O0 -g")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
if(APPLE)
  add_executable(kosp ${ALL_SOURCES})
else()
  add_library(kosp SHARED ${ALL_SOURCES})
endif()

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 \
	-Wno-unused-local-typedefs -Wno-missing-field-initializers \
	-Wno-deprecated")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 \
    -Wno-unused-local-typedefs -Wno-missing-field-initializers \
    -Wno-deprecated")

if(!APPLE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-gnu-unique")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_C_STANDARD_REQUIRED On)

add_definitions(-D_GNU_SOURCE)
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-DGLEW_BUILD=GLEW_STATIC -DGLEW_MX)
add_definitions("-DCHECK_RESULT_USED=__attribute__((warn_unused_result))")

add_definitions(-DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1 -DXPLM302=1 -DXPLM400=1 -DXPLM401=1 -DXPLM410=1)

if(APPLE)
  add_definitions(-DAPL=1 -DIBM=0 -DLIN=0)
  execute_process(COMMAND ${LIBACFUTILS}/pkg-config-deps mac-64 --cflags
    OUTPUT_VARIABLE DEP_CFLAGS)
  execute_process(COMMAND ${LIBACFUTILS}/pkg-config-deps mac-64 --libs
    OUTPUT_VARIABLE LACF_DEP_LDFLAGS)
  set_target_properties(kosp PROPERTIES LINK_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -fvisibility=hidden -bundle")
elseif(WIN32)
  add_definitions(-DAPL=0 -DIBM=1 -DLIN=0 -D_WIN32_WINNT=0x0600)
  execute_process(COMMAND ${LIBACFUTILS}/pkg-config-deps win-64 --cflags
    OUTPUT_VARIABLE DEP_CFLAGS)
  set_target_properties(kosp PROPERTIES LINK_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -undefined_warning \
	    -fvisibility=hidden -static-libgcc -static-libstdc++")
else()
  add_definitions(-DAPL=0 -DIBM=0 -DLIN=1)
  execute_process(COMMAND ${LIBACFUTILS}/pkg-config-deps linux-64 --cflags
    OUTPUT_VARIABLE DEP_CFLAGS)
  set_target_properties(kosp PROPERTIES LINK_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -rdynamic -nodefaultlibs \
	    -undefined_warning -fvisibility=hidden \
	    -static-libgcc -static-libstdc++")
endif()

string(REGEX REPLACE "\n$" "" DEP_CFLAGS "${DEP_CFLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEP_CFLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEP_CFLAGS}")

# Our own code.
INCLUDE_DIRECTORIES("${BASEPATH}")

# libraries
include_directories(kosp PUBLIC
  "${LIBACFUTILS}/SDK/CHeaders/XPLM"
  "${LIBACFUTILS}/SDK/CHeaders/Widgets"
  "${LIBACFUTILS}/SDK/CHeaders/Wrappers"
  "${LIBACFUTILS}/src"
  "${CAIRO_PREFIX}/include/cairo"
  "${FREETYPE_PREFIX}/include/freetype2"
  "${GLEW_PREFIX}/include"
  "${CGLM_PREFIX}/include"
  "${CURL_PREFIX}/include"
  "${LIB_BASEPATH}/cjson"
)

# linking
link_libraries(m)
file(GLOB LIBACFUTILS_LIBRARY
  "${LIBACFUTILS}/qmake/${PLAT_SHORT}/libacfutils.a")
file(GLOB LIBPNG_LIBRARY "${LIBPNG_PREFIX}/lib/libpng16.a")
file(GLOB ZLIB_LIBRARY "${LIBACFUTILS}/zlib/zlib-${PLAT_LONG}/lib/libz.a")
file(GLOB FREETYPE_LIBRARY "${FREETYPE_PREFIX}/lib/libfreetype.a")
file(GLOB CAIRO_LIBRARY "${CAIRO_PREFIX}/lib/libcairo.a")
file(GLOB PIXMAN_LIBRARY "${PIXMAN_PREFIX}/lib/libpixman-1.a")

if(WIN32)
  file(GLOB GLEW_LIBRARY "${GLEW_PREFIX}/lib/libglew32mx.a")
elseif(APPLE)
  file(GLOB GLEW_LIBRARY "${GLEW_PREFIX}/lib/libGLEWmx.a")
else()
  file(GLOB GLEW_LIBRARY "${GLEW_PREFIX}/lib64/libGLEWmx.a")
endif()

file(GLOB CURL_LIBRARY "${LIBACFUTILS}/curl/libcurl-${PLAT_LONG}/lib/libcurl.a")
file(GLOB SSL_LIBRARY "${OPENSSL_PREFIX}/lib/libssl.a")
file(GLOB CRYPTO_LIBRARY "${OPENSSL_PREFIX}/lib/libcrypto.a")
file(GLOB ICONV_LIBRARY "${ICONV_PREFIX}/lib/libiconv.a")

if(APPLE)
  find_library(XPLM_FRAMEWORK XPLM "${LIBACFUTILS}/SDK/Libraries/Mac")
  find_library(XPWIDGETS_FRAMEWORK XPWidgets
    "${LIBACFUTILS}/SDK/Libraries/Mac")
  find_library(OPENGL_FRAMEWORK OpenGL)
  find_library(AUDIOUNIT_FRAMEWORK AudioUnit)
  find_library(COREAUDIO_FRAMEWORK CoreAudio)
  find_library(COCOA_FRAMEWORK Cocoa)
  find_library(SYSTEM_CONFIGURATION_FRAMEWORK SystemConfiguration)
  set(EXTRA_PLATFORM_LIBS
    ${XPLM_FRAMEWORK}
    ${XPWIDGETS_FRAMEWORK}
    ${OPENGL_FRAMEWORK}
    ${COCOA_FRAMEWORK}
    ${AUDIOUNIT_FRAMEWORK}
    ${COREAUDIO_FRAMEWORK}
    ${SYSTEM_CONFIGURATION_FRAMEWORK}
  )
elseif(WIN32)
  find_library(XPLM_LIBRARY XPLM_64 "${LIBACFUTILS}/SDK/Libraries/Win")
  find_library(XPWIDGETS_LIBRARY XPWidgets_64
    "${LIBACFUTILS}/SDK/Libraries/Win")
  set(EXTRA_PLATFORM_LIBS
    ${XPLM_LIBRARY}
    ${XPWIDGETS_LIBRARY}
    "-lglu32"
    "-lopengl32"
    "-lws2_32"
    "-lwinmm"
    "-ldbghelp"
    "-lpsapi"
    "-lcrypt32"
    "-lbcrypt"
    "-Wl,-Bstatic -lssp -Wl,-Bdynamic"
  )
else()
  set(EXTRA_PLATFORM_LIBS "")
endif()

target_link_libraries(kosp
  ${LIBACFUTILS_LIBRARY}
  ${CURL_LIBRARY}
  ${SSL_LIBRARY}
  ${CRYPTO_LIBRARY}
  ${CAIRO_LIBRARY}
  ${PIXMAN_LIBRARY}
  ${FREETYPE_LIBRARY}
  ${LIBPNG_LIBRARY}
  ${GLEW_LIBRARY}
  ${ICONV_LIBRARY}
  ${ZLIB_LIBRARY}
  ${EXTRA_PLATFORM_LIBS}
  cjson
)

SET_TARGET_PROPERTIES(kosp PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(kosp PROPERTIES SUFFIX "")
set_target_properties(kosp PROPERTIES LINKER_LANGUAGE CXX)

if(XP_12)
  set_target_properties(kosp PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/../kosp/${PLUGIN_BIN_OUTDIR}")
  set_target_properties(kosp PROPERTIES LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/../kosp/${PLUGIN_BIN_OUTDIR}")
else()
  set_target_properties(kosp PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/../kosp/${PLUGIN_BIN_OUTDIR}")
  set_target_properties(kosp PROPERTIES LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/../kosp/${PLUGIN_BIN_OUTDIR}")
endif()

set_target_properties(kosp PROPERTIES OUTPUT_NAME "kosp.xpl")