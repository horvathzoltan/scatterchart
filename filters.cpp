#include "filters.h"
#include "friendlycolors.h"
#include "geomath.h"
#include <QDebug>

QList<int> Filters::Filter1(MainViewModel::Filter1 m){
    qDebug() << "Filter1";
    qDebug() << "colors: "+QString::number(m.m.count());

    QList<int> e;

    for(int g=0;g<=255;g+=1){
        //auto gray = FriendlyRGB::toLab(g,g,0.71*g);
        auto gray = FriendlyRGB::toLab(g,g,g);
        //auto gray = FriendlyRGB::toLab(128,128,128);

        for(int i=0;i<m.m.count();i++){
            auto c=(m.m)[i];
            CIEDE2000::LAB l{c.l, c.a, c.b};
            auto d = CIEDE2000::CIEDE2000(gray,l);

    //        auto t = GeoMath::Dist(a.a, a.b);
    //        if(t>30){
    //            e.append(i);
    //        }

            if(d<m.d){//12.5){//25
                e.append(i);
            }
            //FriendlyRGB fc(i.r, i.g, i.b);
            //auto hex = fc.toHexString();
            //e.append(hex);

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

    for(int i=0;i<m.m.count();i++){
        auto c=(m.m)[i];
        CIEDE2000::LAB l{c.l, c.a, c.b};

        double d0;
        int ix = FriendlyColors::GetRYBIxWheelN(l,&d0,6);
        if(color_name.isEmpty()){
            color_name = FriendlyColors::GetName(ix);
            qDebug() << "color_name: "+color_name;
        }

        double a_cold, a_warm;
        a_cold = CIEDE2000::deg2Rad(m.aCold);
        a_warm = CIEDE2000::deg2Rad(-m.aWarm);

        double aa1, bb1; // <- cool + angle
        GeoMath::Rotate(c.a, c.b, a_cold, &aa1, &bb1);
        CIEDE2000::LAB l1{c.l, aa1, bb1};
        int ix1 = FriendlyColors::GetRYBIxWheelN(l1,&d0,6);

        double aa2, bb2; // -> warm - angle
        GeoMath::Rotate(c.a, c.b, a_warm, &aa2, &bb2);
        CIEDE2000::LAB l2{c.l, aa2, bb2};
        int ix2 = FriendlyColors::GetRYBIxWheelN(l2,&d0,6);

        QSet<QString> a;
        if(ix==ix1 && ix==ix2){
            e.append(i);
        }
        else{

            //a.insert();
        }
    }

    QList<int> e2;
    for(int i=0;i<m.m.count();i++){
        if(!e.contains(i)) continue;
        e2.append(i);
    }
    return e2;
}

