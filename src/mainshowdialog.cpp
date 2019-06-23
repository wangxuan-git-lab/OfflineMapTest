﻿#include "mainshowdialog.h"
#include "ui_mainshowdialog.h"
#include <QTimeLine>
MainShowDialog::MainShowDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainShowDialog)
{
    ui->setupUi(this);
    //设置窗口模式为Window窗口模式
    //设置模式，显示最大，最小按钮
//    this->setModal(Qt::Widget);
//    Qt::WindowFlags flags = Qt::Dialog;
//    flags |= Qt::WindowMinMaxButtonsHint;
//    flags |= Qt::WindowCloseButtonHint;
//    this->setWindowFlags(flags);
    this->showMaximized();
    //初始化选项框
    InitStackWidget();
    on_show_tab_choose_currentChanged(1);
    ui->show_tab_choose->setCurrentIndex(1);
    connect(this->video_widget_,SIGNAL(play_changed(int)),this,SLOT(print_layout(int)));

}

MainShowDialog::~MainShowDialog()
{
    delete ui;
    DELETE_QOBJECT(stacked_widget_);
    DELETE_QOBJECT(map_page_);
    DELETE_QOBJECT(video_page_);
    DELETE_QOBJECT(video_widget_);
    DELETE_QOBJECT(map_show_vbox_layout_);
    DELETE_QOBJECT(video_show_vbox_layout_);
    DELETE_QOBJECT(aggregative_gridLayout_);
    DELETE_QOBJECT(speed_show_chart_widget_);
}
void MainShowDialog::InitStackWidget()
{
    this->stacked_widget_=ui->show_tab_choose;
    //创建地图
//    QQuickView *map_page_view=new QQuickView();
//    map_page_view->setSource(QUrl("qrc:/qml/MainShowWindow.qml"));
//    map_page_view->setResizeMode(QQuickView::SizeRootObjectToView);
    map_page_=new QQuickWidget(QUrl("qrc:/qml/MainShowWindow.qml"));
    map_page_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //获取地图参数
    show_map_=std::shared_ptr<QDeclarativeGeoMap>(map_page_->rootObject()->findChild<QDeclarativeGeoMap *>("show_map"));
    //创建地图布局
    map_show_vbox_layout_=new QVBoxLayout(ui->map_show_page);
    map_show_vbox_layout_->setMargin(0);//设置边距
    map_show_vbox_layout_->addWidget(map_page_);//添加到布局中
    //创建video_page_
    //创建video_page布局
    video_widget_=new VideoShowWidget<StreamVideoWidget>(this);
    ui->horizontalLayout->setMargin(1);
    ui->horizontalLayout->setSpacing(1);
    //ui->videoshow_v_div->setContentsMargins(2,2,2,2);
    ui->horizontalLayout->addWidget(video_widget_);

    //设置仪表盘面板
    speed_show_chart_widget_=new QQuickWidget();
    speed_show_chart_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    speed_show_chart_widget_->setSource(QUrl("qrc:/qml/MyCharts.qml"));
    ui->verticalLayout_4->addWidget(speed_show_chart_widget_);
    //设置回放显示
    video_review_layout_=new QHBoxLayout(ui->show_tab_choosePage4);
    video_review_show_widget_=new QVideoWidget(ui->show_tab_choosePage4);
    //创建回放地图
    re_map_widget_=new QQuickWidget(ui->show_tab_choosePage4);
    re_map_widget_->setSource(QUrl("qrc:/qml/MainShowWindow.qml"));
    re_map_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //获取地图参数
    re_show_map_=std::shared_ptr<QDeclarativeGeoMap>(re_map_widget_->rootObject()->findChild<QDeclarativeGeoMap *>("show_map"));
//  ui->show_tab_choosePage4->setLayout(video_review_layout_);
    video_review_layout_->addWidget(video_review_show_widget_);
    video_review_layout_->addWidget(re_map_widget_);
//    re_map_widget_->show();
//    video_review_layout_->setMargin(5);//设置边距
    video_review_layout_->setSpacing(5);//设置边距

    // video_review_show_widget_->resize(ui->aggregative_show_page->size());
}

void MainShowDialog::on_show_tab_choose_currentChanged(int arg1)
{
    if(arg1==2){
//        ui->verticalLayout_2->insertWidget(0,video_widget_);
//        //ui->verticalLayout_2->addWidget(video_widget_);
//        ui->verticalLayout_2->addWidget(speed_show_chart_widget_);
//        //综合页面进行布局
//        ui->aggregative_horizontalLayout->addWidget(map_page_);
        map_page_->setParent(ui->horizontalWidget);
        map_page_->resize(map_page_->parentWidget()->size());
        map_page_->show();
        ui->verticalLayout_3->addWidget(video_widget_);
    }else{

        if (arg1==0) {
            map_show_vbox_layout_->addWidget(map_page_);
            ui->horizontalLayout->removeWidget(video_widget_);
        }else if (arg1==1) {
            ui->horizontalLayout->addWidget(video_widget_);
            map_show_vbox_layout_->removeWidget(map_page_);
        }else if(arg1==3){
            //ui->aggregative_show_page->update();

            //video_review_show_widget_->resize(video_review_show_widget_->parentWidget()->size());
            video_review_show_widget_->show();
        }
    }

}
void MainShowDialog::print_layout(int index){

//        qDebug()<<"row"<<aggregative_gridLayout_->rowCount();
//        qDebug()<<"col"<<aggregative_gridLayout_->columnCount();
}
