#include "mainpresenter.h"
#include "mainviewmodel.h"
#include "settings.h"

//#include "model.h"
#include "friendlyrgb.h"
#include "filehelper.h"
#include "filters.h"

#include <QFileDialog>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

extern Settings settings;
MainPresenter::MainPresenter(QObject *parent) :QObject(parent)
{

}

void MainPresenter::appendView(IMainView *w)
{
    if(_views.contains(w)) return;
    _views.append(w);

    auto *view_obj = dynamic_cast<QObject*>(w);

    QObject::connect(view_obj, SIGNAL(LoadActionTriggered(IMainView *)),
                     this, SLOT(processLoadAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(SaveSelectedActionTriggered(IMainView *)),
                     this, SLOT(processSaveSelectedAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(SQLUpdActionTriggered(IMainView *)),
                     this, SLOT(processSQLUpdAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(Filter1ActionTriggered(IMainView *)),
                     this, SLOT(processFilter1Action(IMainView *)));

    QObject::connect(view_obj, SIGNAL(Filter2ActionTriggered(IMainView *)),
                     this, SLOT(processFilter2Action(IMainView *)));

    //SaveSelectedActionTriggeredprocessSaveSelectedActionTriggered
//    QObject::connect(&(*view_obj), &IMainView::LoadActionTriggered,
//                     this, &MainPresenter::processLoadAction);
    refreshView(w);
}

auto MainPresenter::GetRYBSerieWM() const -> MainViewModel::ColorSerie
{
    MainViewModel::ColorSerie m;
    for(int i=0;i<FriendlyRGB::WheelColorsRYBLen;i++){
        auto fc = FriendlyRGB::WheelColorsRYB[i];
        auto lab = fc.toLab();
        // TODO mapper
        MainViewModel::ColorSerieItem item{{lab.l, lab.a, lab.b}, {fc.r, fc.g, fc.b}};
        m.items.append(item);
    }
    return m;
}

auto MainPresenter::GetRGBSerieWM() const -> MainViewModel::ColorSerie
{
    MainViewModel::ColorSerie m;
    for(int i=0;i<FriendlyRGB::WheelColorsRGBLen;i++){
        auto fc = FriendlyRGB::WheelColorsRGB[i];
        auto lab = fc.toLab();
        // TODO mapper
        MainViewModel::ColorSerieItem item{{lab.l, lab.a, lab.b}, {fc.r, fc.g, fc.b}};
        m.items.append(item);
    }
    return m;
}

void MainPresenter::refreshView(IMainView *w) const
{

}

void MainPresenter::initView(IMainView *w) const
{
    //w->initRange();
    w->set_ryb_serie(GetRYBSerieWM());
    auto m = GetRGBSerieWM();
    w->set_rgb_serie(m);
}

/*load*/
void MainPresenter::processLoadAction(IMainView *sender)
{
    MainViewModel::Load r = sender->load();

    QList<struct MainViewModel::Rgb> m = LoadFcs(r);
    MainViewModel::ColorSerie vm = MainViewModel::ColorSerie::fromFriendlyRGB(m);
    sender->set_color_serie(vm);
}

void MainPresenter::processSaveSelectedAction(IMainView *sender)
{
    auto m = sender->get_selected_color_serie();
    QStringList e;
    for(auto&i:m){
        FriendlyRGB fc(i.r, i.g, i.b);
        auto hex = fc.toHexString();
        e.append(hex);
    }

    auto fn_template = QString("ufc_X_RYB_NNN_%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss"));
    //QString fn_template = "unfcs_"+fn_timestamp+".txt";
    QString fullfn = QDir(settings.fcspath).filePath(fn_template);

    QString filename = QFileDialog::getSaveFileName(
        nullptr,
        QStringLiteral("Save file"),
        fullfn,
        QStringLiteral("color files (*.txt *.csv)")
        );

    FileHelper::SaveText(filename, e);
}



auto MainPresenter::LoadFcs(const MainViewModel::Load& m) -> QList<MainViewModel::Rgb>{
    QString filename = QFileDialog::getOpenFileName(
        nullptr,
        QStringLiteral("Open file"),
        settings.fcspath,
        QStringLiteral("color files (*.txt *.csv)")
        );
    settings.fcspath = filename;

    return LoadFcs2(filename, m);
}

auto MainPresenter::LoadFcs2(const QString& filename, const MainViewModel::Load& m)->QList<MainViewModel::Rgb>{
    QList<MainViewModel::Rgb> data;

    if(!QFileInfo(filename).exists()) return {};
    auto lines = FileHelper::LoadText(filename);
    if(lines.isEmpty()) return {};
    for(auto&line:lines){
        if(line.isEmpty()) continue;
        if(line.startsWith(' ')) continue;
        bool isPlus=false;
        QString line2 = line;
        if(line2.endsWith('+')){
            line2= line2.left(line2.length()-1);
            isPlus = true;
        }
        if((isPlus&&m.plus) || (!isPlus&&m.minus)){
            bool ok;
            auto fc = FriendlyRGB::FromCSV(line2, FriendlyRGB::CsvType::hex, &ok);
            auto rgb = MainViewModel::Rgb::fromFriendlyRGB(fc);
            //auto fi = FriendlyRGB::ToFriendlyInt(fc.r, fc.g, fc.b);
            data.append(rgb);
        }
    }
    //_fileName = filename;
    qDebug() << "data contains: "+QString::number(data.count())+ " element";
    return data;
}

//////////////// SQL
// a megjelenített fájl fc és ufc párját olvassa be és írja ki

void MainPresenter::processSQLUpdAction(IMainView *sender){
    qDebug() << "processSQLUpdAction";
    QString fullPath = settings.fcspath;

    QFileInfo f(fullPath);
    auto path = f.path();
    auto f1 = f.filePath();
    auto f2 = f.fileName();
    auto filename = f.completeBaseName();
    auto suffix = f.completeSuffix();

    qDebug() << "path: "+path;
    qDebug() << "f1: "+f1;
    qDebug() << "f2: "+f2;
    qDebug() << "filename: "+filename;
    qDebug() << "suffix: "+suffix;
    qDebug() << "----";

    QString fcfilename;
    QString ufcfilename;
    if(filename.startsWith("fc")){
        fcfilename=filename;
        ufcfilename='u'+filename;
    }
    else if(filename.startsWith("ufc")){
        fcfilename = filename.mid(1);
        ufcfilename=filename;
    }

    QFileInfo fcFileInfo(path+'/'+fcfilename+'.'+suffix);
    QFileInfo ufcFileInfo(path+'/'+ufcfilename+'.'+suffix);

    qDebug() << "loading..";
    qDebug() << "ufcFile:"+ufcFileInfo.filePath();

    //QFile fcFile(fcFullPath);
    //fcFile.file
    //mentés - először az első ötöt
    //auto m = sender->get_selected_color_serie();

    QList<SQLFc> fcs;
    if(fcFileInfo.exists()){
        qDebug() << "fcFile:"+fcFileInfo.filePath();
        auto lines = FileHelper::LoadText(fcFileInfo.filePath());
        if(!lines.isEmpty()){
            for(auto&line:lines){
                if(line.isEmpty()) continue;
                if(line.startsWith(' ')) continue;
                bool ok;
                auto fc = FriendlyRGB::FromCSV(line, FriendlyRGB::CsvType::hex, &ok);
                fcs.append({fc,0,0});
            }
        }
    }

    QList<SQLFc> ufcs;
    if(ufcFileInfo.exists()){
        qDebug() << "ufcFile:"+ufcFileInfo.filePath();
        auto lines = FileHelper::LoadText(ufcFileInfo.filePath());
        if(!lines.isEmpty()){
            for(auto&line:lines){
                if(line.isEmpty()) continue;
                if(line.startsWith(' ')) continue;
                int flag = -1;
                QString line2 = line;
                if(line2.endsWith('+')){
                    line2= line2.left(line2.length()-1);
                    flag = 1;
                } else if(line2.endsWith('-')){
                    line2= line2.left(line2.length()-1);
                    flag = -1;
                } else{
                    flag = -1;
                }
                bool ok;
                auto fc = FriendlyRGB::FromCSV(line, FriendlyRGB::CsvType::hex, &ok);
                ufcs.append({fc,0,flag});
            }
        }
    }

    int markerId = FcFileNameToMarkerId(fcfilename);
    qDebug() << "markerId:"+QString::number(markerId);
    if(!fcs.isEmpty()){
        for(auto&f:fcs){
            f.colorint = f.rgb.toDecString();
        }
        DeleteMarkerColors(markerId);
        InsertMarkerColor(markerId, fcs);
    }

    if(!ufcs.isEmpty()){
        int markerCorrId = GetMarkerCorrectionId(markerId);
        if(markerCorrId==-1){
            InsertMarkerCorrection(markerId, ufcfilename, "corrections for "+ufcfilename);
            markerCorrId = GetMarkerCorrectionId(markerId);
        }
        qDebug() << "markerCorrId:"+QString::number(markerCorrId);
        if(markerCorrId!=-1){
            for(auto&f:ufcs){
                f.colorint = f.rgb.toDecString();
            }
            DeleteMarkerCorrectionItems(markerCorrId);
            InsertMarkerCorrectionItems(markerCorrId, ufcs);
        }
    }
}

/*
    int ix = fn.lastIndexOf(QChar('.'));
    if(ix>-1) fn = fn.left(ix);
*/
//ufc_3_RYB_YELLOW.txt
//WC_Marker.Yellow
auto MainPresenter::FcFileNameToMarkerName(const QString& fc) -> QString
{
    QString fn=fc;
    int ix = fn.lastIndexOf(QChar('.'));
    if(ix>-1) fn = fn.left(ix);
    ix = fn.lastIndexOf(QChar('/'));
    if(ix>-1) fn = fn.mid(ix+1);

    qDebug() << "fn: "+fn;
    if(!fn.startsWith("fc")) return QString();

    if(fn.toLower().endsWith("ryb_red")) return "WC_Marker.Red";
    if(fn.toLower().endsWith("ryb_green")) return "WC_Marker.Green";
    if(fn.toLower().endsWith("ryb_blue")) return "WC_Marker.Blue";
    if(fn.toLower().endsWith("ryb_yellow")) return "WC_Marker.Yellow";
    if(fn.toLower().endsWith("ryb_orange")) return "WC_Marker.Orange";
    if(fn.toLower().endsWith("ryb_purple")) return "WC_Marker.Purple";
    return QString();
}

auto MainPresenter::FcFileNameToMarkerId(const QString& fc) -> int{
    QString markerName = FcFileNameToMarkerName(fc);
    qDebug() << "markerName: "+markerName;
    int id = GetMarkerIdByName(markerName);
    return id;
}

auto MainPresenter::GetMarkerIdByName(const QString& mn)->int
{
    if(mn.isEmpty()) return -1;
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                QSqlQuery query(db);
                auto cmd = QStringLiteral("SELECT id FROM exm.Markers WHERE Name = '%1'").arg(mn);
                qDebug() << "cmd: "+cmd;
                db_ok = query.exec(cmd);
                if(db_ok)
                {
                    //int fieldNo = query.record().indexOf("country");
                    rows = 0;
                    while(query.next()){
                        rows++;
                        id = query.value(0).toInt();
                        break;
                    }
                }
            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}

auto MainPresenter::GetMarkerCorrectionId(int markerId)->int
{
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                QSqlQuery query(db);
                auto cmd = QStringLiteral("SELECT id FROM exm.MarkerCorrections WHERE MarkerId = '%1'").arg(markerId);
                qDebug() << "cmd: "+cmd;
                db_ok = query.exec(cmd);
                if(db_ok)
                {
                    //int fieldNo = query.record().indexOf("country");
                    rows = 0;
                    while(query.next()){
                        rows++;
                        id = query.value(0).toInt();
                        break;
                    }
                }
            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}

bool MainPresenter::InsertMarkerColor(int markerId,const QList<SQLFc>& fcs){
    if(fcs.isEmpty()) return -1;
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                int j = 0;
                QString most = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                for(auto&f:fcs){
                    QSqlQuery query(db);
                    QString cmd = QStringLiteral("INSERT INTO exm.MarkerColors (MarkerId, Color, MarkerColorType, LastModified) VALUES  (%1, '%2', %3, '%4')")
                                      .arg(markerId).arg(f.colorint).arg(f.flag).arg(most);
                    qDebug() << "cmd: "+cmd;
                    db_ok = query.exec(cmd);
//                    if(db_ok)
//                    {
//                        rows = 0;
//                        while(query.next()){
//                            rows++;
//                            id = query.value(0).toInt();
//                            break;
//                        }
//                    }
                    j++;
                    //if(j>5) break;
                }
            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}

bool MainPresenter::DeleteMarkerColors(int markerId){
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                int j = 0;
                QString most = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

                QSqlQuery query(db);
                QString cmd = QStringLiteral("DELETE FROM exm.MarkerColors WHERE MarkerId=%1")
                                  .arg(markerId);
                qDebug() << "cmd: "+cmd;
                db_ok = query.exec(cmd);
//                if(db_ok)
//                {
//                    rows = 0;
//                    while(query.next()){
//                        rows++;
//                        id = query.value(0).toInt();
//                        break;
//                    }
//                }

            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}

bool MainPresenter::InsertMarkerCorrection(int markerId,
                                           const QString& name,
                                           const QString& comments){
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                int j = 0;
                QString most = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

                    QSqlQuery query(db);
                    QString cmd = QStringLiteral("INSERT INTO exm.MarkerCorrections (MarkerId, Name, Comments, LastModified) VALUES  (%1, '%2', '%3', '%4')")
                                      .arg(markerId).arg(name).arg(comments).arg(most);
                    qDebug() << "cmd: "+cmd;
                    db_ok = query.exec(cmd);
//                    if(db_ok)
//                    {
//                        rows = 0;
//                        while(query.next()){
//                            rows++;
//                            id = query.value(0).toInt();
//                            break;
//                        }
//                    }

            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}


bool MainPresenter::DeleteMarkerCorrectionItems(int markerCorrectionId){
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                int j = 0;
                QString most = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

                QSqlQuery query(db);
                QString cmd = QStringLiteral("DELETE FROM exm.MarkerCorrectionItems WHERE MarkerCorrectionId=%1")
                                  .arg(markerCorrectionId);
                qDebug() << "cmd: "+cmd;
                db_ok = query.exec(cmd);
//                if(db_ok)
//                {
//                    rows = 0;
//                    while(query.next()){
//                        rows++;
//                        id = query.value(0).toInt();
//                        break;
//                    }
//                }

            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}

bool MainPresenter::InsertMarkerCorrectionItems(int markerCorrectionId, const QList<SQLFc>& fcs){
    if(fcs.isEmpty()) return -1;
    int id=-1;
    SQLHelper sqlh;
    static const QString CONN = QStringLiteral("conn1");
    {
        auto db = sqlh.Connect(settings._sql_settings, CONN);
        if(db.isValid()){
            //qDebug() << "db.isValid";
            bool db_ok = db.open();
            QString dberr(QLatin1String(""));

            int rows=0;
            if(db_ok)
            {
                int j = 0;
                QString most = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                for(auto&f:fcs){
                    QSqlQuery query(db);
                    QString cmd = QStringLiteral("INSERT INTO exm.MarkerCorrectionItems (MarkerCorrectionId, Color, MarkerColorType, LastModified) VALUES  (%1, '%2', %3, '%4')")
                                      .arg(markerCorrectionId).arg(f.colorint).arg(f.flag).arg(most);
                    qDebug() << "cmd: "+cmd;
                    db_ok = query.exec(cmd);
                    //                    if(db_ok)
                    //                    {
                    //                        rows = 0;
                    //                        while(query.next()){
                    //                            rows++;
                    //                            id = query.value(0).toInt();
                    //                            break;
                    //                        }
                    //                    }
                    j++;
                    //if(j>5) break;
                }
            }

            if(!db_ok)
            {
                QSqlError a = db.lastError();
                dberr = a.text().trimmed();
            }
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(CONN);
    return id;
}

void MainPresenter::processFilter1Action(IMainView *sender){
    qDebug() << "processFilter1Action";
    //auto m = sender->get_color_serie_lab();
    auto m = sender->getFilter1Params();
    auto e = Filters::Filter1(m);
    qDebug() << "filtered: "+QString::number(e.count());
    sender->set_selected(e);
}

void MainPresenter::processFilter2Action(IMainView *sender){
    qDebug() << "processFilter2Action";
    //auto m = sender->get_color_serie_lab();
    auto m = sender->getFilter2Params();
    auto e = Filters::Filter2(m);
    qDebug() << "filtered: "+QString::number(e.count());
    sender->set_selected(e);
}
