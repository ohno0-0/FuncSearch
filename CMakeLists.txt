cmake_minimum_required(VERSION 3.15)
project(FuncSearch VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== 新增：强制编译器使用 UTF-8 编码 =====
if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()
# ==========================================

set(CMAKE_AUTOMOC ON) # 自动处理 Qt 的 MOC
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找 Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 收集源文件和头文件
set(SOURCES
    src/PathManager.cpp
    src/FuncSearchEngine.cpp
    src/SearchDialog.cpp
)

set(HEADERS
    include/PathManager.h
    include/FuncSearchEngine.h
    include/SearchDialog.h
)

# 构建为一个动态库/静态库，方便接入其他项目
add_library(FuncSearch ${SOURCES} ${HEADERS})

target_include_directories(FuncSearch PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# PUBLIC 确保 Qt 的头文件路径传递给使用该库的目标 (如 TestSearch)
target_link_libraries(FuncSearch PUBLIC Qt5::Widgets)

# 构建测试程序 (无需再显式链接 Qt5::Widgets，因为 QtFuncSearch 已经 PUBLIC 传递了)
add_executable(TestSearch test_main.cpp)

# 在编译后，将源码目录的 resources 文件夹复制到构建目录（即 exe 所在目录）
add_custom_command(TARGET TestSearch POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resource"
    "$<TARGET_FILE_DIR:TestSearch>/resource"
)

target_link_libraries(TestSearch PRIVATE FuncSearch)
