#ifndef COMMANDS_H
#define COMMANDS_H

/* Реализация ActionController'ов и команд для стека Undo/Redo */

#include "command.h"

class MainWindow;

// Команда добавления фигуры
class AddCommand : public Command
{
public:
    AddCommand(QGraphicsScene *graphicsScene, QGraphicsItem *graphicsItem, QUndoCommand *parent = 0);
    virtual ~AddCommand();

    void undo() override;
    void redo() override;
};


// Команда удаления фигуры
class DeleteCommand : public Command
{
public:
    DeleteCommand(QGraphicsScene *graphicsScene, QGraphicsItem *graphicsItem, QUndoCommand *parent = 0);
    virtual ~DeleteCommand();
    void undo() override;
    void redo() override;
};



// Обработчик действия "Стереть все"
class ClearController : public ActionController
{
    Q_OBJECT

public:
    ClearController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

private slots:
    void ActionProcess();
};


// Обработчик действия "Выбрать"
class SelectController : public ActionController
{
    Q_OBJECT

public:
    SelectController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

    void MousePressEvent(QPointF pos, QGraphicsScene *scene);

private slots:
    void ActionProcess();
};


// Обработчик действия "Добавить прямоугольник"
class AddRectController : public ActionController
{
    Q_OBJECT

public:
    AddRectController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

    void MousePressEvent(QPointF pos, QGraphicsScene *scene);
    void MouseReleaseEvent(QGraphicsScene *scene);

private slots:
    void ActionProcess();

private:
    const int w = 50;
    const int h = 20;
};


// Обработчик действия "Добавить эллипс"
class AddEllipseController : public ActionController
{
    Q_OBJECT

public:
    AddEllipseController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

    void MousePressEvent(QPointF pos, QGraphicsScene *scene);
    void MouseReleaseEvent(QGraphicsScene *scene);

private slots:
    void ActionProcess();

private:
    const int w = 50;
    const int h = 20;
};


// Обработчик действия "Удалить фигуру"
class DeleteController : public ActionController
{
    Q_OBJECT

public:
    DeleteController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

private slots:
    void ActionProcess();
};


// Обработчик действия "Отмена"
class UndoController : public ActionController
{
    Q_OBJECT

public:
    UndoController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

private slots:
    void ActionProcess(){}
};


// Обработчик действия "Повтор"
class RedoController : public ActionController
{
    Q_OBJECT

public:
    RedoController(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent = 0);

private slots:
    void ActionProcess(){}
};




#endif // COMMANDS_H
