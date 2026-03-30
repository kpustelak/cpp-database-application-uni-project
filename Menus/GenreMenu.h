#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_GENREMENU_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_GENREMENU_H
#include "../Service/GenreService.h"
#include "../Helpers/Helpers.h"

class GenreMenu {
private:
    Helpers helpers;
public:
    void AddGenre(GenreService &s);
    void FindById(GenreService &s);
    void ShowAllGenres(GenreService &s);
    void EditGenre(GenreService &s);
    void DeleteGenre(GenreService &s);

    void Show(GenreService &s);
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_GENREMENU_H