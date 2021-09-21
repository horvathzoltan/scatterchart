#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "friendlyrgb.h"
#include <QtGlobal>
#include <QList>
#include <QColor>

class MainViewModel
{
public:
    struct Load{
        bool plus;
        bool minus;
    };

    struct Lab{
        double l;
        double a;
        double b;
    };

    struct Rgb{        
        unsigned char r;
        unsigned char g;
        unsigned char b;

        static Rgb fromFriendlyRGB(const FriendlyRGB& c){
            return {c.r,c.g,c.b};
        }

        static Rgb fromQColor(const QColor& c)
        {
            return{
                static_cast<unsigned char>(c.red()),
                static_cast<unsigned char>(c.green()),
                static_cast<unsigned char>(c.blue())
            };
        }
    };

    //Q_DECLARE_TYPEINFO(MainViewModel::Rgb, QTypeInfo::Q_PRIMITIVE_TYPE);
    //template<typename T> struct Rgb;

    struct ColorSerieItem{
        Lab lab;
        Rgb rgb;

        static ColorSerieItem fromRgb(Rgb i){
            FriendlyRGB fc(i.r, i.g, i.b);
            auto lab = fc.toLab();
            //todo mapper
            return {{lab.l, lab.a, lab.b}, i};
        }
    };

    struct ColorSerie{
        QList<ColorSerieItem> items;

        static ColorSerie fromFriendlyRGB(const QList<MainViewModel::Rgb>&m ){
            ColorSerie r;
            for(auto&i:m) r.items.append(ColorSerieItem::fromRgb(i));
            return r;
        }
    };        

};


#endif // MAINVIEWMODEL_H
