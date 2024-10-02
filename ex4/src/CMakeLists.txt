cmake_minimum_required(VERSION 3.16)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_tzlilcoh
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        main.cpp
        MlpNetwork.h )


add_executable(test
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        oh_tests_const.cpp
        MlpNetwork.h )


add_executable(test_exceptions
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        oh_tests_exceptions.cpp
        MlpNetwork.h )