/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Cheng-han Pai
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief This is the help window for the Alphabets page.
 */


#ifndef ALPHABETHELP_H
#define ALPHABETHELP_H

#include <QDialog>
#include <QSize>

namespace Ui {
class AlphabetHelp;
}

class AlphabetHelp : public QDialog
{
    Q_OBJECT

public:
    explicit AlphabetHelp(QWidget *parent = nullptr);
    ~AlphabetHelp();

private:
    Ui::AlphabetHelp *ui;
};

#endif // ALPHABETHELP_H
