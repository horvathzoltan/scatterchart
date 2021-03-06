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
    virtual QList<MainViewModel::Lab> get_color_serie_lab() = 0;
    virtual void set_selected(QList<int> e)=0;
    virtual void initRange() =0;
    virtual MainViewModel::Load load() =0;
    virtual MainViewModel::Filter1 getFilter1Params() =0;
    virtual MainViewModel::Filter2 getFilter2Params() =0;
    virtual MainViewModel::Filter3 getFilter3Params() =0;

public: // signals
    virtual void LoadActionTriggered(IMainView *sender) = 0;
    virtual void SaveSelectedActionTriggered(IMainView *sender) = 0;
    virtual void SQLUpdActionTriggered(IMainView *sender) =0;
    virtual void Filter1ActionTriggered(IMainView *sender) =0;
    virtual void Filter2ActionTriggered(IMainView *sender) =0;
    virtual void Filter3ActionTriggered(IMainView *sender) =0;
};

#endif // IMAINVIEW_H
