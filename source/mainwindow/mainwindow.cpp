#include "../../header/mainwindow/mainwindow.h"
#include "ui_mainwindow.h"
#include "../../header/mainwindow/jumpbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(scene, this))
    , timer(new QTimer)
{
    ui->setupUi(this);
    const int window_width = 1024, window_height = 1024 / 4 * 3;
    //the size of the main window is fixed

    QPixmap tmp(":/agent/CHSkadi/CHSkadi_2");
    QPixmap bgf = tmp.scaled(window_width, window_height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    const int scene_orix = (bgf.width() - window_width) / 2, scene_oriy = (bgf.height() - window_height) / 2;
    this->setFixedSize(window_width, window_height);
    scene->setSceneRect((bgf.width() - window_width) / 2, (bgf.height() - window_height) / 2, window_width, window_height);
    scene->setBackgroundBrush(bgf);
    //to set the background image at a proper position

    JumpButton *fightbutton = new JumpButton(scene_orix + window_width *2 / 3 - 30, scene_oriy + window_height / 6, window_width / 3,  window_height / 6, QPixmap(":/other/jumpbutton"), "作战");
    scene->addItem(fightbutton);

    view->resize(window_width, window_height);
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

