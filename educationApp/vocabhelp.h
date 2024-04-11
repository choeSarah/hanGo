#ifndef VOCABHELP_H
#define VOCABHELP_H

#include <QDialog>
#include <QSize>

namespace Ui {
class VocabHelp;
}

class VocabHelp : public QDialog
{
    Q_OBJECT

public:
    explicit VocabHelp(QWidget *parent = nullptr);
    ~VocabHelp();

private:
    Ui::VocabHelp *ui;
};

#endif // VOCABHELP_H
