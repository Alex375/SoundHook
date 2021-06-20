cmake_minimum_required(VERSION 3.17)
project(SoundHook C)


set(CMAKE_C_STANDARD 99)



if(APPLE)
    message(STATUS, "APPLE")
    find_package(PkgConfig)
    pkg_check_modules(FFTW REQUIRED fftw3)
    include_directories(${fftw_include_dirs})
    link_directories (${FFTW_LIBRARY_DIRS})
    add_definitions (${fftw_cflags_other})

    find_package(PkgConfig)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)
    include_directories(${GTK_INCLUDE_DIRS})
    link_directories(${GTK_LIBRARY_DIRS})
    add_definitions(${GTK_CFLAGS_OTHER})
endif()


add_executable(main main.c)



file(GLOB src_file_decoder file_decoder/*/*/*.c)
file(GLOB src_gui GUI/*/*.c)

file(GLOB src_fft decomposition/*.c)
file(GLOB src_fft_treat decomposition/Treat/*.c)
file(GLOB src_graph GraphTools/*.c)
file(GLOB src_wavelet wavlet/*.c)
file(GLOB src_wavelib wavelib/src/*c)
file(GLOB src_wavelibaux wavelib/auxiliary/*.c)


#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -pedantic-errors")



add_executable(mainUI mainUI.c ${src_gui} ${src_file_decoder} ${src_fft} ${src_fft_treat} ${src_graph} ${src_wavelib} ${src_wavelet} ${src_wavelibaux})
add_executable(TESTGRAPH testGraph.c)
TARGET_LINK_LIBRARIES(mainUI ${GTK_LIBRARIES} ${FFTW_LIBRARIES} -lm ${LIBS})
TARGET_LINK_LIBRARIES(TESTGRAPH ${GTK_LIBRARIES} ${FFTW_LIBRARIES} -lm ${LIBS})


