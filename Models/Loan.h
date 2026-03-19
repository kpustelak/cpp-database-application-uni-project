//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_LOAN_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_LOAN_H
#include <string>


class Loan {
public:
    int Id;
    int ReaderId;
    int BookCopiesId;
    std::string LoanDate;
    std::string ReturnDate;
    bool IsReturned;

    Loan(int id, int readerId, int bookCopiesId, std::string loanDate, std::string returnDate, bool isReturned):
        Id(id), ReaderId(readerId), BookCopiesId(bookCopiesId), LoanDate(loanDate),
        ReturnDate(returnDate), IsReturned(isReturned){}
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_LOAN_H