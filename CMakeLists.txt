cmake_minimum_required(VERSION 3.17)
project(SoundHook C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c)

add_executable(decoder file_decoder/main_decode.c file_decoder/decoder.c)
add_executable(testfft decomposition/main.c decomposition/fft.c)
