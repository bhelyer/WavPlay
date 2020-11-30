cmake_minimum_required(VERSION 3.19)
project(WavPlay)

find_package(OpenAL CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(WavPlay WavPlay/main.cpp)
if(WIN32)
    target_compile_options(WavPlay PRIVATE /W4 /WX)
endif()
target_link_libraries(WavPlay PRIVATE OpenAL::OpenAL)
