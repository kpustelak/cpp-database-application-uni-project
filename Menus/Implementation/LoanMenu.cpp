//
// Created by kornel on 3/30/26.
//

#include "../Header/LoanMenu.h"
#include <iostream>

void LoanMenu::AddLoan(LoanService &l, ReaderService &r, BookService &b) {
    helpers.ClearScreen();

    std::string readerPhrase = helpers.EnterData("Enter reader name or surname to search");
    std::vector<Reader> readers = r.GetByNameOrSurnameMatch(readerPhrase);
    if (readers.empty()) {
        std::cout << "No readers found" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto reader : readers) {
        std::cout << reader.Id << ". " << reader.Name << " " << reader.Surname
                  << " | " << reader.PhoneNumber << std::endl;
    }
    int readerId = helpers.EnterInt("Enter reader id");

    helpers.ClearScreen();
    std::string bookPhrase = helpers.EnterData("Enter book title or author to search");
    std::vector<Book> books = b.GetBooksByDataMatch(bookPhrase);
    if (books.empty()) {
        std::cout << "No books found" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto book : books) {
        std::cout << book.Id << ". " << book.Title << " - " << book.Author << std::endl;
    }
    int bookId = helpers.EnterInt("Enter book id");

    helpers.ClearScreen();
    std::vector<BookCopy> copies = b.FindBookCopies(bookId);
    if (copies.empty()) {
        std::cout << "No copies found" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto copy : copies) {
        bool available = l.IsCopyAvailable(copy.Id);
        std::cout << copy.Id << ". Condition: " << copy.Condition
                  << " | " << (available ? "Available" : "Borrowed") << std::endl;
    }
    int copyId = helpers.EnterInt("Enter copy id");

    if (!l.IsCopyAvailable(copyId)) {
        std::cout << "This copy is not available" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }

    try {
        l.Add(readerId, copyId);
        std::cout << "Loan added" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void LoanMenu::ReturnBook(LoanService &l) {
    helpers.ClearScreen();
    std::vector<Loan> active = l.FindAllActive();
    if (active.empty()) {
        std::cout << "No active loans" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto loan : active) {
        std::cout << loan.Id << ". Reader: " << loan.ReaderId
                  << " | Copy: " << loan.BookCopiesId
                  << " | Date: " << loan.LoanDate << std::endl;
    }

    int loanId = helpers.EnterInt("Enter loan id to return");
    if (!helpers.Confirm("Are you sure you want to return this book?")) {
        helpers.PressEnterToContinue();
        return;
    }
    try {
        l.ReturnBook(loanId);
        std::cout << "Book returned" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void LoanMenu::GetActiveLoans(LoanService &l) {
    helpers.ClearScreen();
    std::vector<Loan> loans = l.FindAllActive();
    if (loans.empty()) {
        std::cout << "No active loans" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto loan : loans) {
        std::cout << loan.Id << ". Reader: " << loan.ReaderId
                  << " | Copy: " << loan.BookCopiesId
                  << " | Date: " << loan.LoanDate << std::endl;
    }
    helpers.PressEnterToContinue();
}

void LoanMenu::GetOverdueLoans(LoanService &l) {
    helpers.ClearScreen();
    std::vector<Loan> loans = l.FindOverdue();
    if (loans.empty()) {
        std::cout << "No overdue loans" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto loan : loans) {
        std::cout << loan.Id << ". Reader: " << loan.ReaderId
                  << " | Copy: " << loan.BookCopiesId
                  << " | Date: " << loan.LoanDate << std::endl;
    }
    helpers.PressEnterToContinue();
}

void LoanMenu::GetLoansByReader(LoanService &l) {
    helpers.ClearScreen();
    int readerId = helpers.EnterInt("Enter reader id");
    std::vector<Loan> loans = l.FindByReaderId(readerId);
    if (loans.empty()) {
        std::cout << "No loans found for this reader" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto loan : loans) {
        std::cout << loan.Id << ". Copy: " << loan.BookCopiesId
                  << " | Date: " << loan.LoanDate
                  << " | Returned: " << (loan.IsReturned ? "Yes" : "No") << std::endl;
    }
    helpers.PressEnterToContinue();
}

// Show
void LoanMenu::Show(LoanService &l, ReaderService &r, BookService &b) {
    int choice;
    do {
        helpers.ClearScreen();
        std::cout << "\n=== LOAN MENU ===\n";
        std::cout << "1. Borrow book\n";
        std::cout << "2. Return book\n";
        std::cout << "3. Show active loans\n";
        std::cout << "4. Show overdue loans\n";
        std::cout << "5. Show loans by reader\n";
        std::cout << "0. Back\n";

        choice = helpers.EnterInt("Choose");

        switch (choice) {
            case 1: AddLoan(l, r, b); break;
            case 2: ReturnBook(l); break;
            case 3: GetActiveLoans(l); break;
            case 4: GetOverdueLoans(l); break;
            case 5: GetLoansByReader(l); break;
            case 0: break;
            default: std::cout << "Unknown option\n";
        }
    } while (choice != 0);
}