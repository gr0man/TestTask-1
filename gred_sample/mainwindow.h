#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphicsScene;
class QUndoStack;
class ActionController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GraphicsScene *GetScene(){ return scene; }
    void UnchectControllers(ActionController *controller);
    void Clear();

private:
    Ui::MainWindow *ui;

    GraphicsScene *scene;
    QUndoStack *undoStack;

    QVector<ActionController*> controllers;
};

#endif // MAINWINDOW_H
