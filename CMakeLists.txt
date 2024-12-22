cmake_minimum_required(VERSION 3.2)
project(V8-use-demo)

set(V8_DIR /Users/peng/go/src/googlesource/v8/v8/out/arm64.release/)

include_directories(${V8_DIR}/gen/include)

add_executable(V8-use-demo main.cpp)
 
target_link_libraries(V8-use-demo
    ${V8_DIR}/libv8_monolithic.a
    -lpthread  # V8需要pthread库
    -ldl       # V8需要dl库
    -lrt       # 在一些Linux系统上需要
)

# include_directories(/Users/peng/go/src/googlesource/v8/v8/include)

# link_directories(
#   ${V8_DIR}/obj
# )
# link_libraries(
#   libwee8.a
# )

# set(SOURCE_FILES ./main.cpp)
# add_executable(clang ${SOURCE_FILES})



