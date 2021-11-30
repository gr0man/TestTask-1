
#include "commands.h"

#include <QWidget>
#include <QAction>
#include <QGraphicsRectItem>
#include <QPointF>

#include "mainwindow.h"
#include "graphicsscene.h"
#include "figures.h"


// Команда добавления фигуры
AddCommand::AddCommand(QGraphicsScene *graphicsScene, QGraphicsItem *graphicsItem, QUndoCommand *parent)
    :Command(graphicsScene, graphicsItem, parent)
{
}

AddCommand::~AddCommand()
{
}

void AddCommand::undo()
{
    scene->removeItem(item);
    scene->clearSelection();
    scene->update();
}

void AddCommand::redo()
{
    scene->addItem(item);
    scene->clearSelection();
    scene->update();
}


// Команда удаления фигуры
DeleteCommand::DeleteCommand(QGraphicsScene *graphicsScene, QGraphicsItem *graphicsItem, QUndoCommand *parent)
    :Command(graphicsScene, graphicsItem, parent)
{
}

DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::undo()
{
    scene->addItem(item);
    scene->clearSelection();
    scene->update();
}

void DeleteCommand::redo()
{
    scene->removeItem(item);
    scene->clearSelection();
    scene->update();
}



// Обработчик действия "Стереть все"
ClearController::ClearController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = new QAction(tr("&Clear"), parent);
    connect(action, SIGNAL(triggered()), this, SLOT(ActionProcess()));
    controlWidget->addAction(action);
}

void ClearController::ActionProcess()
{
    mainWindow->GetScene()->SetCrController(0);
    mainWindow->setCursor(Qt::ArrowCursor);
    mainWindow->UnchectControllers(this);
    mainWindow->Clear();
}


// Обработчик действия "Выбрать"
SelectController::SelectController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = new QAction(tr("&Select"), parent);
    action->setCheckable(true);
    connect(action, SIGNAL(triggered()), this, SLOT(ActionProcess()));
    controlWidget->addAction(action);
}

void SelectController::ActionProcess()
{
    mainWindow->UnchectControllers(this);
    mainWindow->GetScene()->SetCrController(this);
    mainWindow->setCursor(Qt::ArrowCursor);
}

void SelectController::MousePressEvent(QPointF pos, QGraphicsScene *scene)
{
    bool isSelect = false;
    scene->clearSelection();
    for(QGraphicsItem *sceneItem : scene->items())
    {
        if(sceneItem->boundingRect().contains(pos))
        {
            sceneItem->setSelected(true);
            isSelect = true;
        }

    }

    if(isSelect)
        scene->update();
}



// Обработчик действия "Добавить прямоугольник"
AddRectController::AddRectController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = new QAction(tr("Add &Rect"), parent);
    action->setCheckable(true);
    connect(action, SIGNAL(triggered()), this, SLOT(ActionProcess()));
    controlWidget->addAction(action);
}

void AddRectController::ActionProcess()
{
    mainWindow->UnchectControllers(this);
    mainWindow->GetScene()->SetCrController(this);
    mainWindow->setCursor(Qt::CrossCursor);
}

void AddRectController::MousePressEvent(QPointF pos, QGraphicsScene *scene)
{
    QGraphicsItem *item = new Rect(pos.x()-w/2, pos.y()-h/2, w, h);


    // проверка на пересечения
    for(auto const &sceneItem : scene->items())
    {
        if(sceneItem->boundingRect().intersects(item->boundingRect()))
        {
            mainWindow->setCursor(Qt::ForbiddenCursor);
            delete item;
            return;
        }
    }

    AddCommand *cmd = new AddCommand(scene, item);
    undoStack->push(cmd);

    scene->update();

}

void AddRectController::MouseReleaseEvent(QGraphicsScene *scene)
{
    mainWindow->setCursor(Qt::CrossCursor);
    scene->update();
}


// Обработчик действия "Добавить эллипс"
AddEllipseController::AddEllipseController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = new QAction(tr("Add &Ellipse"), parent);
    action->setCheckable(true);
    connect(action, SIGNAL(triggered()), this, SLOT(ActionProcess()));
    controlWidget->addAction(action);
}

void AddEllipseController::ActionProcess()
{
    mainWindow->UnchectControllers(this);
    mainWindow->GetScene()->SetCrController(this);
    mainWindow->setCursor(Qt::CrossCursor);
}

void AddEllipseController::MousePressEvent(QPointF pos, QGraphicsScene *scene)
{
    QGraphicsItem *item = new Ellipse(pos.x()-w/2, pos.y()-h/2, w, h);

    // проверка на пересечения
    for(auto const &sceneItem : scene->items())
    {
        if(sceneItem->boundingRect().intersects(item->boundingRect()))
        {
            mainWindow->setCursor(Qt::ForbiddenCursor);
            return;
        }
    }

    AddCommand *cmd = new AddCommand(scene, item);
    undoStack->push(cmd);

    scene->update();
}

void AddEllipseController::MouseReleaseEvent(QGraphicsScene *scene)
{
    mainWindow->setCursor(Qt::CrossCursor);
    scene->update();
}


// Обработчик действия "Удалить фигуру"
DeleteController::DeleteController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = new QAction(tr("&Delete"), parent);
    connect(action, SIGNAL(triggered()), this, SLOT(ActionProcess()));
    controlWidget->addAction(action);
}

void DeleteController::ActionProcess()
{

    // удаляет выбранную фигуру в режиме "select"
    QList<QGraphicsItem *> selection = mainWindow->GetScene()->selectedItems();
    for(auto item : selection)
    {
        QUndoCommand *cmd = new DeleteCommand(mainWindow->GetScene(), item);
        undoStack->push(cmd);
        mainWindow->GetScene()->update();
    }
}


// Обработчик действия "Отмена"
UndoController::UndoController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = stack->createUndoAction(parent, tr("&Undo"));
    controlWidget->addAction(action);
}


// Обработчик действия "Повтор"
RedoController::RedoController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
    : ActionController(controlWidget, stack, parent)
{
    action = stack->createRedoAction(parent, tr("R&edo"));
    controlWidget->addAction(action);
}
