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
