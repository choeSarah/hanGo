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
