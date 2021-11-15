#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QtCharts>
#include "imainview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainView
{
    Q_OBJECT
private:
    static const QRect _null_rect;

    struct SelectedItems{
        QSet<int> points;
        QColor color;

        bool isSelected(const QPointF& p) const
        {
            int key = toKey(p);//(int)p.x()*10000*10000+(int)p.y()*10000;
            return points.contains(key);
        }
    };

    static int toKey(const QPointF& p){
        return toKey(p.x(), p.y());
    };

    static int toKey(qreal x, qreal y){
        return (int)x*10000*10000+(int)y*10000;
    };

    SelectedItems _selected_rgb;
    SelectedItems _selected_ryb;
    SelectedItems _selected_color;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void refreshView();
    void set_ryb_serie(const MainViewModel::ColorSerie&m);
    void set_rgb_serie(const MainViewModel::ColorSerie&m);
    void set_color_serie(const MainViewModel::ColorSerie&m);
    QList<MainViewModel::Rgb> get_selected_color_serie();
    //void Clear_null_serie();
    //void clear_color_serie();
    void setRange(const QRect& r);
    void initRange();
    MainViewModel::Load load();
signals:
        void LoadActionTriggered(IMainView *sender);
        void SaveSelectedActionTriggered(IMainView *sender);
        void SQLUpdActionTriggered(IMainView *sender);
        void Filter1ActionTriggered(IMainView *sender);
private slots:
    void on_pushButton_clear_clicked();
    void on_pushButton_load_clicked();
    void on_rgb_clicked(const QPointF &);
    void on_ryb_clicked(const QPointF &);
    void on_color_clicked(const QPointF &);

    void on_pushButton_background_toggle_toggled(bool checked);
    void on_pushButton_save_selected_clicked();

    void on_radioButton_0_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_1_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

    void on_pushButton_sqlupd_clicked();

    void on_pushButton_filter1_clicked();

private:
    static const int MAX = 120;
    bool isOwnColor();
    Ui::MainWindow *ui;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QScatterSeries _ryb_serie;
    QMap<int, QBrush> _ryb_map;
    QMap<int, QBrush> _rgb_map;
    QScatterSeries _rgb_serie;
    QScatterSeries _color_serie;
    QList<MainViewModel::ColorSerieItem> _color_serie_all;
    QMap<int, QBrush> _color_map;
    QGridLayout *chartLayout;


    void set_serie(QScatterSeries *s, const MainViewModel::ColorSerie &m, QMap<int, QBrush>* map,const SelectedItems& si);
    bool get_serie_color(QScatterSeries* s, const QPointF& point,  QMap<int, QBrush>* map, SelectedItems* selected);
    void select_serie_item(QScatterSeries* s, QMap<int, QBrush>* map, const QPointF &point, SelectedItems* selected);


    //void clear_serie(QScatterSeries *s);
    void setSerieItemColor(QScatterSeries *s, const QPointF &p, QMap<int, QBrush> *map, bool isOwncolor);
};
#endif // MAINWINDOW_H
