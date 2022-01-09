#include "todolist.h"
#include "task.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QSplitter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ToDoList w;
    w.show();



    return a.exec();
}
