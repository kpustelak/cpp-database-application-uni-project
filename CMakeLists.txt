cmake_minimum_required(VERSION 4.0)
project(cpp_database_application_uni_project)

set(CMAKE_CXX_STANDARD 20)

find_package(PostgreSQL REQUIRED)

add_executable(cpp_database_application_uni_project main.cpp
        Models/Reader.h
        Repositories/ReaderRepository.cpp
        Repositories/ReaderRepository.h)

target_link_libraries(cpp_database_application_uni_project PostgreSQL::PostgreSQL)