/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Cheng-han Pai
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief displays the help window for the Alphabets page.
 */

#include "alphabethelp.h"
#include "ui_alphabethelp.h"

AlphabetHelp::AlphabetHelp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlphabetHelp)
{
    ui->setupUi(this);

    QPixmap pixmap(":/help_images/alphaHelp.png");

    QSize imageSize = ui->image->size();
    ui->image->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setAlignment(Qt::AlignCenter);
}

AlphabetHelp::~AlphabetHelp()
{
    delete ui;
}
