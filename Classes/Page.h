//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_PAGE_H
#define VIRTUALMEMORYSIMULATOR_PAGE_H


class Page {
public:
    Page();
    Page(int idProcess, int pageNumber);
    int getIDProcess();
    int getPageNumber();
    void setIDProcess(int);
    void setPageNumber(int);
private:
    int idProcess, pageNumber;
};


#endif //VIRTUALMEMORYSIMULATOR_PAGE_H
