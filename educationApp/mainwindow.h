#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_alphabet_navBtn2_clicked();
    void on_alphabet_navBtn1_clicked();
    void on_alphabet_navBtn3_clicked();

    void on_vocabulary_navBtn1_clicked();

    void on_vocabulary_navBtn3_clicked();

    void on_vocabulary_navBtn2_clicked();

    void on_game_navBtn1_clicked();

    void on_game_navBtn3_clicked();

    void on_game_navBtn2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
