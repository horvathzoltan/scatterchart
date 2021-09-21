#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "imainview.h"

const QRect MainWindow::_null_rect = {QPoint(-120,120),QPoint(120,-120)};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart();
    chart->setTitle(QStringLiteral("CIE L*a*b*"));
    chart->setAcceptHoverEvents(true);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartLayout = new QGridLayout();
    chartLayout->addWidget(chartView);
    ui->frame_chart->setLayout(chartLayout);

    //ui->frame_chart->resize(600,600);


    chartLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);

    axisX = new QValueAxis();    
    axisX->setTitleText(QStringLiteral("a"));
    axisY = new QValueAxis();
    axisX->setTitleText(QStringLiteral("b"));
    initRange();   
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    _ryb_serie.setName(QStringLiteral("RYB"));
    _ryb_serie.setColor(Qt::black);
    _ryb_serie.setMarkerSize(13);
    _ryb_serie.setMarkerShape(QScatterSeries::MarkerShape::MarkerShapeRectangle);
    _ryb_serie.setBorderColor(Qt::transparent);
    _ryb_serie.setPen(QColor(Qt::transparent));
    chart->addSeries(&_ryb_serie);
    _ryb_serie.attachAxis(axisX);
    _ryb_serie.attachAxis(axisY);


    _rgb_serie.setName(QStringLiteral("RGB"));
    _rgb_serie.setColor(Qt::black);
    _rgb_serie.setMarkerSize(10);
    _rgb_serie.setMarkerShape(QScatterSeries::MarkerShape::MarkerShapeRectangle);
    _rgb_serie.setBorderColor(Qt::transparent);
    _rgb_serie.setPen(QColor(Qt::transparent));
    chart->addSeries(&_rgb_serie);
    _rgb_serie.attachAxis(axisX);
    _rgb_serie.attachAxis(axisY);

    _color_serie.setName(QStringLiteral("data"));
    _color_serie.setColor(Qt::blue);
    _color_serie.setMarkerSize(5.0);
    _color_serie.setMarkerShape(QScatterSeries::MarkerShape::MarkerShapeCircle);
    _color_serie.setBorderColor(Qt::transparent);
    _color_serie.setPen(QColor(Qt::transparent));
    _color_serie.setOpacity(255);
    chart->addSeries(&_color_serie);
    _color_serie.attachAxis(axisX);
    _color_serie.attachAxis(axisY);

    QObject::connect(&_rgb_serie, SIGNAL(clicked(const QPointF &)),
                     this, SLOT(on_rgb_clicked(const QPointF &)));
    QObject::connect(&_ryb_serie, SIGNAL(clicked(const QPointF &)),
                     this, SLOT(on_ryb_clicked(const QPointF &)));
    QObject::connect(&_color_serie, SIGNAL(clicked(const QPointF &)),
                     this, SLOT(on_color_clicked(const QPointF &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


//https://www.handprint.com/HP/WCL/color18a.html
//https://www.handprint.com/HP/WCL/vismixmap.html
// http://www.guiart.com/guien4.htm



void MainWindow::set_ryb_serie(const MainViewModel::ColorSerie &m)
{
    _ryb_map.clear();
    _ryb_serie.clear();
    set_serie(&_ryb_serie, m, &_ryb_map, _selected_ryb);
}

void MainWindow::set_rgb_serie(const MainViewModel::ColorSerie &m)
{
    _rgb_map.clear();
    _rgb_serie.clear();
    set_serie(&_rgb_serie, m, &_rgb_map, _selected_rgb);
}


void MainWindow::set_color_serie(const MainViewModel::ColorSerie &m)
{
    set_serie(&_color_serie, m, &_color_map, _selected_color);
}

auto MainWindow::get_selected_color_serie()->QList<MainViewModel::Rgb>
{
    QList<MainViewModel::Rgb> e;
    const QSet<int>& keys = _selected_color.points;
    const QMap<int, QBrush>& color_map = _color_map;
    for(auto key:keys){
        if(color_map.contains(key)){
            const QColor& c = color_map.value(key).color();
            auto rgb = MainViewModel::Rgb::fromQColor(c);
            e.append(rgb);
        }
    }
    return e;
}

//https://stackoverflow.com/questions/65537064/is-it-possible-to-have-an-individual-marker-color-for-each-point-in-a-qscatterse
// m-ben van az items, az itemben van az rgb
void MainWindow::set_serie(QScatterSeries* s, const MainViewModel::ColorSerie& m,  QMap<int, QBrush>* map, const SelectedItems& si){
    for(const MainViewModel::ColorSerieItem&j:m.items){
        int key = toKey(j.lab.a, j.lab.b);
        _color_serie_all.append(j);
        s->append({j.lab.a, j.lab.b});
        if(isOwnColor()){
            map->insert(key, {{j.rgb.r, j.rgb.g, j.rgb.b}, Qt::SolidPattern});
        } else {
            map->insert(key, {{128,128,128}, Qt::SolidPattern});
        }
    }
    for(int i= 0; i < s->count(); i++){
        QPointF p = s->at(i);
        setSerieItemColor(s, p, map, si.isSelected(p));
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    _color_serie.clear();
    _color_serie_all.clear();
    _color_map.clear();
}


void MainWindow::on_pushButton_load_clicked()
{
    emit LoadActionTriggered(this);
}

void MainWindow::on_rgb_clicked(const QPointF &point)
{
    select_serie_item(&_rgb_serie, &_rgb_map, point, &_selected_rgb);
    if(!_selected_rgb.points.isEmpty()){
        ui->label_rgb->setText("RGB:"+_selected_rgb.color.name());
    }else {
        ui->label_rgb->clear();
    }
}

void MainWindow::on_ryb_clicked(const QPointF &point)
{
    select_serie_item(&_ryb_serie, &_ryb_map, point, &_selected_ryb);
    if(!_selected_ryb.points.isEmpty()){
        ui->label_rgb->setText("RYB:"+_selected_ryb.color.name());
    } else {
        ui->label_rgb->clear();
    }
}

void MainWindow::on_color_clicked(const QPointF &point)
{
    select_serie_item(&_color_serie, &_color_map, point, &_selected_color);
    if(!_selected_color.points.isEmpty()){
        ui->label_rgb->setText("FC:"+_selected_color.color.name());
    } else {
        ui->label_rgb->clear();
    }
}


void MainWindow::select_serie_item(QScatterSeries* s, QMap<int, QBrush>* map, const QPointF &point, SelectedItems* selected)
{
    int key = toKey(point);
    bool is_selected = false;
    if(selected->points.contains(key)) { // ha egyenlő akkor togglézünk
        selected->points.remove(key);
    } else { // ha nem, akkor töröljük az előzőt
        is_selected = get_serie_color(s, point, map, selected);
        if(is_selected){
            selected->points.insert(key);
        }
    }
    setSerieItemColor(s, point, map, is_selected);
}

bool MainWindow::get_serie_color(QScatterSeries* s, const QPointF& point,  QMap<int, QBrush>* map, SelectedItems* selected)
{
    int key = toKey(point);

    if(!map->contains(key)) return false;

    auto b=map->value(key);
    selected->color = b.color();
    return true;
}

void MainWindow::setSerieItemColor(QScatterSeries* s, const QPointF &p, QMap<int, QBrush>* map, bool isSelected){
    QBrush b{{64,64,64}, Qt::SolidPattern};
    QBrush selected_b{{255,64,64}, Qt::Dense4Pattern};
    int ix=0, ix2=0;
    int key = toKey(p);
    QPointF p0 = chart->mapToPosition(p , s);
    QPoint p1 = chartView->mapFromScene(p0);
    auto its = chartView->items(p1);
    for(auto &it:its){
        if(auto *ellipse = dynamic_cast<QGraphicsEllipseItem*>(it)){
            if(isSelected){
                ellipse->setBrush(selected_b);
            } else {
                if(map->contains(key)){
                    ellipse->setBrush(map->value(key));
                } else {
                    ellipse->setBrush(b);
                }
            }
            ix++;
        }
        else if(auto *rect = dynamic_cast<QGraphicsRectItem*>(it)){
            if(rect->rect().width()<=18){
                if(isSelected){
                    rect->setBrush(selected_b);
                } else {
                    if(map->contains(key)){
                    rect->setBrush(map->value(key));
                    } else {
                        rect->setBrush(b);
                    }
                }
                rect->setRotation(45);
                ix2++;
            }
        }
    }
}

bool MainWindow::isOwnColor()
{
    return ui->checkBox_isOwnColor->isChecked();
}

void MainWindow::on_pushButton_background_toggle_toggled(bool checked)
{
    static QBrush b_chartView = chartView->backgroundBrush();
    static QBrush b_chart = chart->backgroundBrush();
    if(checked){
        b_chartView = chartView->backgroundBrush();
        b_chart = chart->backgroundBrush();
        chartView->setBackgroundBrush({Qt::black, Qt::SolidPattern});
        chart->setBackgroundBrush({Qt::black, Qt::SolidPattern});
    } else {
        chartView->setBackgroundBrush(b_chartView);
        chart->setBackgroundBrush(b_chart);
    }
}


void MainWindow::on_pushButton_save_selected_clicked()
{
    emit SaveSelectedActionTriggered(this);
}


void MainWindow::initRange()
{
    setRange(_null_rect);
}

MainViewModel::Load MainWindow::load()
{
    if(ui->radioButton_all->isChecked()) return {true,true};
    return {
        ui->radioButton_plus->isChecked(),
        ui->radioButton_minus->isChecked()
    };
}

void MainWindow::on_radioButton_0_clicked(bool checked)
{
    if(checked) initRange();
}

void MainWindow::setRange(const QRect& r)
    {
    axisX->setMin(r.left());
    axisX->setMax(r.right());
    axisY->setMax(r.top());
    axisY->setMin(r.bottom());    
    };

void MainWindow::on_radioButton_1_clicked(bool checked)
{
    static const QRect r(QPoint(-100,100),QPoint(10,-10));
    if(checked) setRange(r);
}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    static const QRect r(QPoint(-10,90),QPoint(90,-10));
    if(checked) setRange(r);
}


void MainWindow::on_radioButton_3_clicked(bool checked)
{
    static const QRect r(QPoint(-10,10),QPoint(90,-120));
    if(checked) setRange(r);
}


void MainWindow::on_radioButton_4_clicked(bool checked)
{
    static const QRect r(QPoint(-90,10),QPoint(10,-90));
    if(checked) setRange(r);
}


void MainWindow::on_pushButton_sqlupd_clicked()
{
    qDebug() << "on_pushButton_sqlupd_clicked";
    emit SQLUpdActionTriggered(this);
}

