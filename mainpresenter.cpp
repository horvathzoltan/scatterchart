#include "mainpresenter.h"
#include "mainviewmodel.h"
#include "settings.h"

#include "model.h"
#include "friendlyrgb.h"
#include "filehelper.h"

#include <QFileDialog>
#include <QDateTime>

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
    return data;
}
