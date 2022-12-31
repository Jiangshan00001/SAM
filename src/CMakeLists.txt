aux_source_directory(. SRC_LISTA)
#aux_source_directory(util SRC_LISTB)

#include_directories(.)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})


#include(FetchContent)
#FetchContent_Declare(oflex URL https://github.com/Jiangshan00001/oflex/archive/refs/heads/master.zip)
#FetchContent_MakeAvailable(oflex)

#FetchContent_Declare(obison_old URL https://github.com/Jiangshan00001/obison/archive/refs/heads/main.zip)
#FetchContent_MakeAvailable(obison_old)

find_package(SDL2 QUIET)
include_directories(${SDL2_INCLUDE_DIRS})

if (${SDL2_FOUND})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSESDL")

else  (${SDL2_FOUND})
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")

endif  (${SDL2_FOUND})

add_executable(sam ${SRC_LISTA} ${SRC_LISTB} ${SRC_LISTC})
target_link_libraries(sam ${SDL2_LIBRARIES})
