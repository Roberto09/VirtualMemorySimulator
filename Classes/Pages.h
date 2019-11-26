//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_PAGES_H
#define VIRTUALMEMORYSIMULATOR_PAGES_H


class Pages {
public:
    Pages();
    Page(int idProcess, int pageNumber);
    int getIDProcess();
    int getPageNumber();
    void setIDProcess(int);
    void setPageNumber(int);
private:
    int idProcess, pageNumber;
};


#endif //VIRTUALMEMORYSIMULATOR_PAGES_H
