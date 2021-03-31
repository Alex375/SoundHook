cmake_minimum_required(VERSION 3.17)
project(SoundHook C)




set(CMAKE_C_STANDARD 99)

if(APPLE)
    message(STATUS, "APPLE")
    find_package(PkgConfig)
    pkg_check_modules(FFTW3 REQUIRED fftw3)
    include_directories(${fftw3_include_dirs})
    link_directories (${FFTW3_LIBRARY_DIRS})
    add_definitions (${fftw33_cflags_other})
endif()


add_executable(main main.c)

file(GLOB src_decode file_decoder/*.c)
file(GLOB src_decode_wav file_decoder/wav/*.c)
file(GLOB src_graph GraphTools/*)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -pedantic-errors")

add_executable(decoder ${src_decode} ${src_decode_wav})
add_executable(testfft decomposition/main.c decomposition/fft.c ${src_decode} ${src_decode_wav} ${src_graph})


TARGET_LINK_LIBRARIES(testfft ${FFTW3_LIBRARIES})
