#ifndef FILTERS_H
#define FILTERS_H

#include "mainviewmodel.h"

#include <QList>



class Filters
{
public:
    static QList<int> Filter1(MainViewModel::Filter1 m);
    static QList<int> Filter2(MainViewModel::Filter2 m);

    struct Filter3Model{
        double d;
        QList<CIEDE2000::LAB> unfc;
        QList<MainViewModel::Lab> m;
    };
    static QList<int> Filter3(Filter3Model m);
};

#endif // FILTERS_H
