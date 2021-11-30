#ifndef COMMAND_H
#define COMMAND_H

#include <QUndoCommand>
#include <QPointF>

#include "mainwindow.h"
#include <QAction>

/* Базовые классы для команд стека Undo/Redo и обработчиков действий */

class QGraphicsScene;
class QGraphicsItem;

class Command : public QUndoCommand
{
public:
    Command(QGraphicsScene *graphicsScene, QGraphicsItem *graphicsItem, QUndoCommand *parent = 0)
        : QUndoCommand(parent)
        , scene(graphicsScene)
        , item(graphicsItem)
    {

    }

    virtual ~Command(){}

protected:
    QGraphicsItem *item;
    QGraphicsScene *scene;
};

class ActionController : public QObject
{
    Q_OBJECT

public:
    ActionController(QWidget* /*controlWidget*/, QUndoStack *stack, MainWindow *parent = 0)
        : QObject(parent)
        , mainWindow(parent)
        , undoStack(stack)
    {
    }

    virtual void MousePressEvent(QPointF, QGraphicsScene*){};
    virtual void MouseReleaseEvent(QGraphicsScene*){};

    // изменение состояния соответствующей кнопки тулбара
    void CheckAction(bool check){ action->setChecked(check); }

private slots:
    virtual void ActionProcess() = 0;

protected:
    QAction *action;
    QUndoStack *undoStack;
    MainWindow *mainWindow;
};


// создает массив контроллеров (связывают деяствия с обработчиками)
QVector<ActionController*> CreateActions(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

#endif // COMMAND_H
