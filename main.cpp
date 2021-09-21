#include <QApplication>
#include <QtCharts>

#include "mainwindow.h"
#include "mainpresenter.h"
#include "settings.h"

Settings settings;

auto main(int argc, char *argv[]) -> int
{
    settings._sql_settings = {
        "QODBC",
        "MasterMove_Examination_Development",
        {{"office.logcontrol.hu", 9876}, {"172.16.1.5", 1433}},
        "sa",
        "Gtr7jv8fh2"
    };
    QApplication a(argc, argv);

    MainWindow w;
    MainPresenter p;
    p.appendView(&w);
    w.show();    
    p.initView(&w);

    return a.exec();
}
