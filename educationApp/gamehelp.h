/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Sarah Choe
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief This is the help window for game page.
 */


#ifndef GAMEHELP_H
#define GAMEHELP_H

#include <QDialog>
#include <QSize>

namespace Ui {
class GameHelp;
}

class GameHelp : public QDialog
{
    Q_OBJECT

public:
    explicit GameHelp(QWidget *parent = nullptr);
    ~GameHelp();

private:
    Ui::GameHelp *ui;
};

#endif // GAMEHELP_H
