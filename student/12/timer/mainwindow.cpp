#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumberSec->setStyleSheet("background-color: red");
    ui->lcdNumberMin->setStyleSheet("background-color: blue");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(on_startButton_clicked()));
    //connect(timer, SIGNAL(timeout()),this,SLOT(on_stopButton_clicked()));
    //connect(timer, SIGNAL(timeout()),this,SLOT(on_resetButton_clicked()));
    connect(timer, SIGNAL(timeout()),this,SLOT(test()));
    //connect(timer, SIGNAL(timeout()),this, SLOT(lcdNumberSec_display));
    // timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    //qDebug << "why";
    sec_ += 1;
    if (sec_ >= 60){
        min_ += 1;
        sec_ = 0;
    }
    ui->lcdNumberSec->display(sec_);
     ui->lcdNumberMin->display(min_);

}

void MainWindow::on_startButton_clicked()
{
    if (!(timer->isActive())){
        timer->start(1000);
    }
}

void MainWindow::on_stopButton_clicked()
{
   timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    sec_ = 0;
    min_ = 0;
    ui->lcdNumberSec->display(sec_);
    ui->lcdNumberMin->display(min_);


}

