#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

//#include "actions.h"
//#include "updates.h"

#include <QList>
#include <QObject>
#include "imainview.h"

class IMainView;
//template <typename T> class QList;

class MainPresenter : public QObject
{
    Q_OBJECT

public:
    explicit MainPresenter(QObject *parent = nullptr);
    void appendView(IMainView *w);
    MainViewModel::ColorSerie GetRYBSerieWM() const;
    MainViewModel::ColorSerie GetRGBSerieWM() const;
    void initView(IMainView *w) const;
private:
    void refreshView(IMainView *w) const;

private:
    QList<IMainView*> _views;
    QList<MainViewModel::Rgb> LoadFcs2(const QString &folder,const MainViewModel::Load& m);
    QList<MainViewModel::Rgb> LoadFcs(const MainViewModel::Load& m);
private slots:
    void processLoadAction(IMainView *sender);
    void processSaveSelectedAction(IMainView *sender);
};

#endif // MAINPRESENTER_H
