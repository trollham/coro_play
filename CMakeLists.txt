cmake_minimum_required(VERSION 3.21.0)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()
set(CMAKE_CXX_EXTENSIONS OFF)
project(coro_play VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(coro_play INTERFACE)

target_compile_features(coro_play INTERFACE cxx_std_20)

if (UNIX)
    target_compile_options(coro_play INTERFACE -fcoroutines -fconcepts)
endif()

target_include_directories(coro_play INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(test)