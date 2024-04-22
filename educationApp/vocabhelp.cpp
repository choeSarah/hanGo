/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Anand Palukuri
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief Displays is the help window for vocab page.
 */



#include "vocabhelp.h"
#include "ui_vocabhelp.h"

VocabHelp::VocabHelp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VocabHelp)
{
    ui->setupUi(this);

    QPixmap pixmap(":/help_images/vocabHelp.png");

    QSize imageSize = ui->image->size();
    ui->image->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setAlignment(Qt::AlignCenter);
}

VocabHelp::~VocabHelp()
{
    delete ui;
}
