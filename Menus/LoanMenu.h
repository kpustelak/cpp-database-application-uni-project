#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANMENU_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANMENU_H
#include "../Service/LoanService.h"
#include "../Helpers/Helpers.h"
#include "../Service/ReaderService.h"
#include "../Service/BookService.h"

class LoanMenu {
private:
    Helpers helpers;
public:
    void AddLoan(LoanService &l, ReaderService &r, BookService &b);
    void Show(LoanService &l, ReaderService &r, BookService &b);
    void ReturnBook(LoanService &l);
    void GetActiveLoans(LoanService &l);
    void GetOverdueLoans(LoanService &l);
    void GetLoansByReader(LoanService &l);
};

#endif