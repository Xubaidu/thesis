# cmake 最低版本需求
cmake_minimum_required(VERSION 3.22.1)

# 工程名称
project(main)

# 设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILECOMMANDS ON)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

# 编译源码生成目标
add_executable(cuckoo_test src/cuckoo/cuckoo_test.cpp)
# add_executable(psi_test src/psi/psi_test.cpp)
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)