#include "vocabhelp.h"
#include "ui_vocabhelp.h"

VocabHelp::VocabHelp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VocabHelp)
{
    ui->setupUi(this);

    QPixmap pixmap(":/vocab_help/vocabHelp.png");

    QSize imageSize = ui->image->size();
    ui->image->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setAlignment(Qt::AlignCenter);
}

VocabHelp::~VocabHelp()
{
    delete ui;
}
