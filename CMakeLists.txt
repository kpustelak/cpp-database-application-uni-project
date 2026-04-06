cmake_minimum_required(VERSION 4.0)
project(cpp_database_application_uni_project)

set(CMAKE_CXX_STANDARD 20)

find_package(PostgreSQL REQUIRED)

add_executable(cpp_database_application_uni_project main.cpp
        Models/Reader.h
        Repositories/Implementation/ReaderRepository.cpp
        Repositories/Header/ReaderRepository.h
        Repositories/Implementation/GenreRepository.cpp
        Repositories/Header/GenreRepository.h
        Models/Genre.h
        Repositories/Implementation/BookRepository.cpp
        Repositories/Header/BookRepository.h
        Models/Book.h
        Models/BookCopy.h
        Models/Loan.h
        Repositories/Implementation/LoanRepository.cpp
        Repositories/Header/LoanRepository.h
        Service/Implementation/GenreService.cpp
        Service/Header/GenreService.h
        Service/Implementation/BookService.cpp
        Service/Header/BookService.h
        Service/Implementation/ReaderService.cpp
        Service/Header/ReaderService.h
        Service/Implementation/LoanService.cpp
        Service/Header/LoanService.h
        Menus/Implementation/GenreMenu.cpp
        Menus/Header/GenreMenu.h
        Menus/Implementation/BookMenu.cpp
        Menus/Header/BookMenu.h
        Helpers/Implementation/Helpers.cpp
        Helpers/Header/Helpers.h
        Menus/Implementation/ReaderMenu.cpp
        Menus/Header/ReaderMenu.h
        Menus/Implementation/LoanMenu.cpp
        Menus/Header/LoanMenu.h
        Helpers/Implementation/RepositoryHelpers.cpp
        Helpers/Header/RepositoryHelpers.h)

target_link_libraries(cpp_database_application_uni_project PostgreSQL::PostgreSQL)