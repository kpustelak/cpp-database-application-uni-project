cmake_minimum_required(VERSION 4.0)
project(cpp_database_application_uni_project)

set(CMAKE_CXX_STANDARD 20)

find_package(PostgreSQL REQUIRED)

add_executable(cpp_database_application_uni_project main.cpp
        Models/Reader.h
        Repositories/ReaderRepository.cpp
        Repositories/ReaderRepository.h
        Repositories/GenreRepository.cpp
        Repositories/GenreRepository.h
        Models/Genre.h
        Repositories/BookRepository.cpp
        Repositories/BookRepository.h
        Models/Book.h
        Models/BookCopy.h
        Models/Loan.h
        Repositories/LoanRepository.cpp
        Repositories/LoanRepository.h
        Service/GenreService.cpp
        Service/GenreService.h
        Service/BookService.cpp
        Service/BookService.h
        Service/ReaderService.cpp
        Service/ReaderService.h
        Service/LoanService.cpp
        Service/LoanService.h
        Menus/GenreMenu.cpp
        Menus/GenreMenu.h
        Menus/BookMenu.cpp
        Menus/BookMenu.h
        Helpers/Helpers.cpp
        Helpers/Helpers.h)

target_link_libraries(cpp_database_application_uni_project PostgreSQL::PostgreSQL)