#ifndef TODOLIST_H
#define TODOLIST_H

#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QToolBar>
#include <QListView>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class ToDoList; }
QT_END_NAMESPACE

class ToDoList : public QMainWindow
{
    Q_OBJECT

public:
    ToDoList(QWidget *parent = nullptr);
    ~ToDoList();
    void createAction();
    void createMenues();
    void createToolBars();
    void makeConnections();
    void main_();
    void check();
    void save_();
    void open();
    void DB();
    void load_();
   QString state;


private:
  //  Ui::ToDoList *ui;

  QAction *new_task;
  QAction *done_task;
  QAction *pending_task;
  QAction *quit;
  QAction *save;
  QAction *about;
  QMenu *file;
  QMenu *options;
  QMenu *help;
  QToolBar *toolbar;
  QListWidget *listWidget1 ;
  QListWidget *listWidget2;
  QListWidget *listWidget3;
  QListWidgetItem *item3;
  QListWidgetItem *item2;

  QSqlDatabase  db ;
 /* QString query ="CREATE TABLE IF NOT EXISTS T2 ("
  "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
  "Description VARCHAR(40),"
  "STATE VARCHAR(20),"
  "TAG  integer,"
  "DUE_DATE date);";
*/

  QString query ="CREATE TABLE IF NOT EXISTS T1 ("
  "STATE VARCHAR(20),"
   "DUE_DATE date,"
  "Description VARCHAR(40),"
  "TAG integer);";




   //QListWidgetItem *newItem;
private slots:
  void new_slot();
  void hide_pending();
  void hide_finished();






};
#endif // TODOLIST_H
