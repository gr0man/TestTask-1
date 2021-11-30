#include "command.h"

#include <QVector>

#include "command.h"
#include "commands.h"


QVector<ActionController*> CreateActions(QWidget *controlWidget, QUndoStack *stack, MainWindow *parent)
{
    QVector<ActionController*> controllers;

    controllers.push_back(new ClearController(controlWidget, stack, parent));
    controllers.push_back(new SelectController(controlWidget, stack, parent));
    controllers.push_back(new AddRectController(controlWidget, stack, parent));
    controllers.push_back(new AddEllipseController(controlWidget, stack, parent));
    controllers.push_back(new DeleteController(controlWidget, stack, parent));
    controllers.push_back(new UndoController(controlWidget, stack, parent));
    controllers.push_back(new RedoController(controlWidget, stack, parent));

    return std::move(controllers);
}
