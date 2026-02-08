# CMakeLists.txt (поместить в корень проекта: wget_lib/)
cmake_minimum_required(VERSION 3.10)

# Определение проекта с поддержкой обоих языков
project(w_app VERSION 1.0 LANGUAGES C CXX)

# Стандарты языков
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Режимы сборки по умолчанию
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Сбор всех исходных файлов
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.cxx"
)

# Добавление исполняемого файла
add_executable(w_app ${SRC_FILES})

# Подключение заголовочных файлов
target_include_directories(w_app PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Отладочные флаги для режима Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        target_compile_options(w_app PRIVATE /W4 /WX)
    else()
        target_compile_options(w_app PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()

# Оптимизация для Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(NOT MSVC)
        target_compile_options(w_app PRIVATE -O3)
    endif()
endif()

# Установка выходной директории (внутри build/bin)
#set_target_properties(w_app PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)

set_target_properties(w_app PROPERTIES
    # Для одноконфигурационных генераторов (MinGW Makefiles, Unix Makefiles)
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    
    # Для мультиконфигурационных генераторов (Visual Studio) — на всякий случай
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/bin"
)

# Копирование ресурсов (если есть) — опционально
# file(GLOB RESOURCES "${PROJECT_SOURCE_DIR}/resources/*")
# add_custom_target(copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/bin/resources
# )
# add_dependencies(w_app copy_resources)
