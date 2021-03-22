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

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -pedantic-errors")

add_executable(decoder file_decoder/main_decode.c file_decoder/decoder.c)
add_executable(testfft decomposition/main.c decomposition/fft.c)

TARGET_LINK_LIBRARIES(testfft ${FFTW3_LIBRARIES})
