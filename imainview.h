#ifndef IMAINVIEW_H
#define IMAINVIEW_H

#include "mainviewmodel.h"

#include <QColor>
#include <QPointF>
#include <QRect>
#include <QSet>

class IMainView
{
public:    
    virtual void set_ryb_serie(const MainViewModel::ColorSerie& m) = 0;
    virtual void set_rgb_serie(const MainViewModel::ColorSerie& m) = 0;
    virtual void set_color_serie(const MainViewModel::ColorSerie& m) = 0;
    virtual QList<MainViewModel::Rgb> get_selected_color_serie() = 0;
    virtual void initRange() =0;
    virtual MainViewModel::Load load() =0;

public: // signals
    virtual void LoadActionTriggered(IMainView *sender) = 0;
    virtual void SaveSelectedActionTriggered(IMainView *sender) = 0;
    virtual void SQLUpdActionTriggered(IMainView *sender) =0;
};

#endif // IMAINVIEW_H
