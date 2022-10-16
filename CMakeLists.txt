# 声明要求的 cmake 最低版本
cmake_minimum_required( VERSION 3.10 )
 
# 声明一个 cmake 工程
project(cosmoVision VERSION 1.0)
# 设置编译模式
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS  "-std=c++11")

# add_compile_options(-fPIC)

#option
option(WITH_BOOST "build with boost" OFF)
option(WITH_OCR "build with ocr" OFF)
option(WITH_FINDCIRCLE "build with circle" OFF)
option(WITH_ARM "build with arm" OFF)
option(WITH_DEMO "build with demo" OFF)
option(WITH_UTILS "build with utils" OFF)


if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES x86_64)
    message(STATUS "current platform : x86")
elseif(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES aarch64)
    message(STATUS "current platform : ARM 64")
    set(WITH_ARM  ON)
else()
    message(STATUS "do matches cmake host system")
endif()

# add code 
INCLUDE_DIRECTORIES("./include")

if (WIN32)
    add_definitions(-DWIN32)
endif()

link_libraries(pthread)

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_libraries(${OpenCV_LIBS})
else()
    message(STATUS "not found OpenCV")
endif()

if (${WITH_BOOST})
    # BOOST
    message(STATUS "build with boost")
    find_package(Boost COMPONENTS
                program_options
                filesystem
                REQUIRED)
    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIRS})
    else()
        message(STATUS, "no boost found")
    endif()
endif()

add_executable(Cast Cast.cpp)
target_link_libraries(Cast)
