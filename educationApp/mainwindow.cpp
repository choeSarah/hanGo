#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QComboBox *pageComboBox = new QComboBox;

    pageComboBox->addItem(tr("alphabet"));
    pageComboBox->addItem(tr("vocabulary"));
    pageComboBox->addItem(tr("game"));

    connect(pageComboBox,
            &QComboBox::activated,
            ui->stackedWidget,
            &QStackedWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_alphabet_navBtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_alphabet_navBtn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_alphabet_navBtn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_vocabulary_navBtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_vocabulary_navBtn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_vocabulary_navBtn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_game_navBtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_game_navBtn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_game_navBtn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

