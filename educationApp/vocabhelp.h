/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Sarah Choe
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief This is the help window for vocab page.
 */


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
