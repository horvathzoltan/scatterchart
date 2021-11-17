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
    QString FcFileNameToMarkerName(const QString &fc);
    int FcFileNameToMarkerId(const QString &fc);

private:
    void refreshView(IMainView *w) const;

    int GetMarkerIdByName(const QString &mn);
    struct SQLFc{
        FriendlyRGB rgb;
        QString colorint;
        int flag;
    };
    bool InsertMarkerColor(int markerId,const QList<SQLFc>& fcs);
    bool DeleteMarkerColors(int markerId);
    int GetMarkerCorrectionId(int markerId);
    bool InsertMarkerCorrection(int markerId,
                           const QString& name,
                           const QString& comments);
    bool DeleteMarkerCorrectionItems(int markerCorrectionId);
    bool InsertMarkerCorrectionItems(int markerCorrectionId,const QList<SQLFc>& fcs);
private:
    QList<IMainView*> _views;
    QList<MainViewModel::Rgb> LoadFcs2(const QString &folder,const MainViewModel::Load& m);
    QList<MainViewModel::Rgb> LoadFcs(const MainViewModel::Load& m);
private slots:
    void processLoadAction(IMainView *sender);
    void processSaveSelectedAction(IMainView *sender);
    void processSQLUpdAction(IMainView *sender);
    void processFilter1Action(IMainView *sender);
    void processFilter2Action(IMainView *sender);
};

#endif // MAINPRESENTER_H
