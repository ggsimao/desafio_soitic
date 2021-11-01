cmake_minimum_required(VERSION 3.15)

project(desafiosoitic VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include)

add_executable(desafiosoitic
    src/main.cpp
    src/filme.cpp
    src/locadora.cpp
    src/qwidgets/adicionar.cpp
    src/qwidgets/editar.cpp
    src/qwidgets/erro.cpp
    src/qwidgets/principal.cpp
)

target_link_libraries(desafiosoitic PRIVATE Qt5::Widgets)
