#include "filters.h"
#include "friendlycolors.h"
#include "geomath.h"
#include <QDebug>

QList<int> Filters::Filter1(MainViewModel::Filter1 m){
    qDebug() << "Filter1";
    qDebug() << "colors: "+QString::number(m.m.count());

    QList<int> e;

    for(int g=0;g<=255;g+=1){
        auto gray = FriendlyRGB::toLab(g,g,g);

        for(int i=0;i<m.m.count();i++){
            auto c=(m.m)[i];
            CIEDE2000::LAB l{c.l, c.a, c.b};
            auto d = CIEDE2000::CIEDE2000(gray,l);
            if(d >= m.d) continue;

            e.append(i);
        }
    }

    QList<int> e2;
    for(int i=0;i<m.m.count();i++){
        if(e.contains(i)) continue;
        e2.append(i);
    }
    return e2;
}

QList<int> Filters::Filter2(MainViewModel::Filter2 m){
    qDebug() << "Filter2";
    qDebug() << "colors: "+QString::number(m.m.count());

    QList<int> e;
    QString color_name;

    double a_cold, a_warm;
    a_cold = CIEDE2000::deg2Rad(m.aCold);
    a_warm = CIEDE2000::deg2Rad(-m.aWarm);
    double cosa_cold = cos(a_cold);
    double sina_cold = sin(a_cold);

    double cosa_warm = cos(a_warm);
    double sina_warm = sin(a_warm);

    for(int i=0;i<m.m.count();i++){
        auto c=(m.m)[i];
        CIEDE2000::LAB l{c.l, c.a, c.b};

        double d0;
        int ix = FriendlyColors::GetRYBIxWheelN(l,&d0,6);
        if(color_name.isEmpty()){
            color_name = FriendlyColors::GetName(ix);
            qDebug() << "color_name: "+color_name;
        }       

        double aa, bb;
        GeoMath::Rotate(c.a, c.b, sina_warm, cosa_warm, &aa, &bb);
        CIEDE2000::LAB l1{c.l, aa, bb};
        int ix1 = FriendlyColors::GetRYBIxWheelN(l1,&d0,6);
        if(ix!=ix1) continue;

        GeoMath::Rotate(c.a, c.b, sina_cold, cosa_cold, &aa, &bb);
        CIEDE2000::LAB l2{c.l, aa, bb};
        ix1 = FriendlyColors::GetRYBIxWheelN(l2,&d0,6);
        if(ix!=ix1) continue;

        e.append(i);
    }

    QList<int> e2;
    for(int i=0;i<m.m.count();i++){
        if(!e.contains(i)) continue;
        e2.append(i);
    }
    return e2;
}

QList<int> Filters::Filter3(Filter3Model m){
    qDebug() << "Filter3";
    qDebug() << "colors: "+QString::number(m.m.count());

    QList<int> e;

    for(auto&l0:m.unfc){
        for(int i=0;i<m.m.count();i++){
            auto c=(m.m)[i];
            auto d = CIEDE2000::CIEDE2000(l0,{c.l, c.a, c.b});
            if(d >= m.d) continue;

            e.append(i);
        }
    }

    QList<int> e2;
    for(int i=0;i<m.m.count();i++){
        if(e.contains(i)) continue;
        e2.append(i);
    }
    return e2;
}

