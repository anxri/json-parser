cmake_minimum_required(VERSION 3.12)
project(json-parser)

set(CMAKE_CXX_STANDARD 17)

file(
        GLOB HEADER_FILES

        "*.h"
)

file(
        GLOB SOURCE_FILES

        "*.cpp"
)

add_executable(json-parser ./main.cpp ${HEADER_FILES} ${SOURCE_FILES})

include_directories(
        json-parser PUBLIC

        ${CMAKE_CURRENT_SOURCE_DIR}

)

target_link_libraries(json-parser stdc++fs)
