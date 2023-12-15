#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gameview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GameView *gameView = new GameView(this);
    setCentralWidget(gameView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
