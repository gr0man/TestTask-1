#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>

#include "command.h"
#include "graphicsscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("gred sample");

    undoStack = new QUndoStack(this);
    scene = new GraphicsScene();
    scene->setSceneRect(QRect(0, 0, 500, 500));

    setCentralWidget(new QGraphicsView(scene));
    resize(700, 500);

    controllers = CreateActions(ui->mainToolBar, undoStack, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Clear()
{
    scene->clear();
    scene->update();
    undoStack->clear();
}

void MainWindow::UnchectControllers(ActionController *controller)
{
    for(auto ctrl : controllers)
    {
        if(ctrl != controller)
            ctrl->CheckAction(false);
    }
}
