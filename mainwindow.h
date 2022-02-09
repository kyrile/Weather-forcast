#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QPoint>
#include <QPen>
#include "weatherTool.h"
#include "weatherdata.h"
#include <QMouseEvent>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject* watched,QEvent* event) override;//观察者模式和事件滤波器
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;//事件处理机制中，需要我们显式的使用观察者模式→直接处理底层事件(右键菜单)
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void getWeatherInfo(QNetworkAccessManager *manager);
    void parseJson(QByteArray& arr);
    void setLabelContent();
    void paintSunRiseSet();
    void paintCurve();
private slots:
    void slot_exitApp();
    void replayFinished(QNetworkReply *reply);

    void on_searchBt_clicked();

    void on_refreshBt_clicked();

private:
    Ui::MainWindow *ui;
    QMenu *exitMenu;
    QAction *exitAction;
    //鼠标位置
    QPoint mPos;
    //UI
    QList<QLabel*> forecast_week_list;         //星期
    QList<QLabel*> forecast_date_list;         //日期
    QList<QLabel*> forecast_aqi_list;          //天气指数
    QList<QLabel*> forecast_type_list;         //天气
    QList<QLabel*> forecast_typeIco_list;      //天气图标
    QList<QLabel*> forecast_high_list;         //高温
    QList<QLabel*> forecast_low_list;          //低温
    //请求数据
    QString url;        //接口链接
    QString city;       //访问的城市
    QString cityTmp;    //临时存放城市变量，防止输入错误城市的时候，原来的城市名称还在。
    //网络连接
    WeatherTool tool;
    //天气工具对象(构造函数：
     //1.读取Json文件到字节数组，
     //2.解析成QJsonDocument对象
     //3.转换为QJsonArray
     //4.把每个数组里的城市名-城市代号装进m_mapCity2Code中
    //)
    QNetworkAccessManager* manager;//请求网络数据
    //本地数据
    Today today;
    Forecast forecast[6];

    static const QPoint sun[2];// 日出日落底线
    static const QRect sunRizeSet[2];// 日出日落时间
    static const QRect rect[2];// 日出日落圆弧
    QTimer *sunTimer;

};
#endif // MAINWINDOW_H
