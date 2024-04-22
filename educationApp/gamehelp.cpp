/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Anand Palukuri
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief Displays is the help window for game page.
 */



#include "gamehelp.h"
#include "ui_gamehelp.h"

GameHelp::GameHelp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameHelp)
{
    ui->setupUi(this);

    QPixmap pixmap(":/help_images/gameHelp.png");

    QSize imageSize = ui->image->size();
    ui->image->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setAlignment(Qt::AlignCenter);
}

GameHelp::~GameHelp()
{
    delete ui;
}
