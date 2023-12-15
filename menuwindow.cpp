#include "menuwindow.h"
#include "ui_menuwindow.h"

#include "mainwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_pushButton_startGame_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    close();
}

void MenuWindow::on_pushButton_quit_clicked()
{
    close();
}
