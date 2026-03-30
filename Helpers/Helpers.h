#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_HELPERS_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_HELPERS_H

#include <string>
#include <vector>

class Helpers {
public:
    std::string EnterData(std::string text);
    int EnterInt(std::string text);
    bool Confirm(std::string text);
    int PickFromList(std::vector<std::string> options, std::string title);
    void PressEnterToContinue();
    void ClearScreen();
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_HELPERS_H