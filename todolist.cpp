#include "todolist.h"
#include "ui_todolist.h"
#include "task.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
#include <QList>
ToDoList::ToDoList(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::ToDoList)
{    //ui->setupUi(this);
   createAction();
   createMenues();
   createToolBars();
   main_();
   makeConnections();
   DB();
   load_();
    }

ToDoList::~ToDoList()
{

    // delete ui;

}

void ToDoList::createAction()
{
    quit = new QAction("&Quit", this);
     QPixmap pending_task_icon(":/pendingTask.png");
    pending_task = new QAction(pending_task_icon,"&Pending",this);
    save = new QAction ("&Save",this);
    about = new QAction("&About",this);
     QPixmap done_task_icon(":/completedTask.png");
    done_task = new QAction(done_task_icon,"&Done",this);
    QPixmap new_task_icon(":/NewTask.png");
    new_task =new QAction(new_task_icon,"&New",this);

}

void ToDoList::createMenues()
{
      file = new QMenu("&File", this);
      menuBar()->addMenu(file);
      options = new QMenu("&Options",this);
      menuBar()->addMenu(options);

      help = new QMenu("&Help",this);
      menuBar()->addMenu(help);

}

void ToDoList::createToolBars()
{

    toolbar = addToolBar("Toolbar");
    toolbar->addAction(new_task);
    toolbar->addAction(pending_task);
    toolbar->addAction(done_task);


}

void ToDoList::makeConnections()
{
connect(new_task,&QAction::triggered,this,&ToDoList::new_slot);
connect(pending_task,&QAction::triggered,this,&ToDoList::hide_pending);
connect(done_task,&QAction::triggered,this,&ToDoList::hide_finished);
}

void ToDoList::main_()
{
    QWidget *container = new QWidget;
    listWidget1 = new QListWidget;
    listWidget2 = new QListWidget;
    listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto layout1 = new QHBoxLayout;
    auto layout = new QVBoxLayout;
    listWidget3 = new QListWidget;
    listWidget3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSplitter *splitter1 = new QSplitter;
    QSplitter * splitter2 = new QSplitter(Qt::Horizontal);
    splitter1->addWidget(listWidget1);
    splitter1->addWidget(listWidget2);
    layout->addWidget(splitter1);
    splitter2->addWidget(listWidget3);
    layout->addWidget(splitter2);
    layout->addLayout(layout1);
    container->setLayout(layout);
    setCentralWidget(container);

}


void ToDoList::DB()
{
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setHostName("acidalia");
       db.setDatabaseName("/media/hp/data/Database/db");
       db.setUserName("mojito");

       db.open();
    /*
       if(db.isOpen()){
           QMessageBox msgBox;
           msgBox.setText("Connected");
           msgBox.exec();

       }
*/


QSqlQuery qry;
if(qry.exec(query)){
    qDebug()<<"Successful";

    }

}

void ToDoList::load_()
{

    QSqlQuery query;
    QString F ="";
    QString P ="";
    QString T ="";
    if(query.exec("SELECT * FROM T1"))
    {
        while(query.next())
        {
            for(int x=0; x < query.record().count(); ++x)
            {

               qDebug()<<query.record().value(x).toString();
             //   listWidget2->addItem(query.record().value(x).toString());

                 if(query.record().value(x).toString()== "Finished Task: " )
             {

                      for(int i =x;i<=x+4;i++){
                     F.append(query.record().value(i).toString());
                     F.append(" ");
                      }

                     x=x+3;
                  }

            else if ( query.record().value(x).toString() == "Pending Task: " )
               {
                     for(int i =x;i<x+4;i++){

                 P.append(query.record().value(i).toString());
                 P.append(" ");

               }
                     x=x+3;
                 }
                 else if(query.record().value(x).toString() == "Today´s Task: " ){

                  {
                         for(int i =x;i<x+4;i++){
                     T.append(query.record().value(i).toString());
                     T.append(" ");

                   }
                         x=x+3;
                  }
                 }

        }

    }

      QStringList F1 = F.split("Finished Task: ");
      QStringList P1 = P.split("Pending Task: ");
      QStringList T1 = T.split("Today´s Task: ");
          for(int i =0 ; i< qMax(F1.size(),qMax(P1.size(),T1.size()));i++){
              if(i<T1.size()){
                  QString s1 ="Finished Task: ";
                  s1.append(T1.at(i));
               listWidget1->addItem(s1);
               qDebug()<<s1;
              }
              if(i<P1.size()){
                  QString s2 ="Pending Task: ";
                  s2.append(P1.at(i));
               listWidget2->addItem(s2);
               qDebug()<<s2;
              }
              if(i<F1.size()){
                  QString s3 ="Today´s Task: ";
                  s3.append(F1.at(i));
               listWidget3->addItem(s3);
                qDebug()<<s3;
                  }
}
}
}

void ToDoList::new_slot()
{
   Task task1;
   auto rep = task1.exec();
     if(rep == QDialog::Accepted && task1.get_finished()){

        QString text ="Finished Task: ";
        state.clear();
        state = "Finished";
        text.append(task1.get_Due_Date().toString());
        text.append(" ");
        text.append(task1.get_Description());
        text.append(" Tag: ");
        text.append(QString::number(task1.get_Tag()));
        listWidget3->addItem(text);

    }else if(rep == QDialog::Accepted && !task1.get_finished()){
           if(task1.get_Due_Date().toString()==QDateTime::currentDateTime().date().toString()){
               QString text ="Today´s Task: ";
               state.clear();
               state = "Today";
               text.append(task1.get_Due_Date().toString());
               text.append(" ");
              text.append(task1.get_Description());
               text.append(" Tag: ");
               text.append(QString::number(task1.get_Tag()));
               item2 = new QListWidgetItem;
               item2->setText(text);
               listWidget1->addItem(text);

           }else if(task1.get_Due_Date() >= QDateTime::currentDateTime().date()){
               QString text ="Pending Task: ";
               state.clear();
               state ="Pending";
               text.append(task1.get_Due_Date().toString());
               text.append(" ");
               text.append(task1.get_Description());
               text.append(" Tag: ");
               text.append(QString::number(task1.get_Tag()));
               item3 = new QListWidgetItem;
               item3->setText(text);
               listWidget2->addItem(text);

           }
    }

   QSqlQuery qry;
   qry.prepare("INSERT INTO T1 (STATE, DUE_DATE, Description, TAG)VALUES (?,?,?,?);");
   qry.addBindValue(state.append(" Task: "));
   qry.addBindValue(task1.get_Due_Date());
   qry.addBindValue(task1.get_Description());
   qry.addBindValue(task1.get_Tag());
   qry.exec();

















}

void ToDoList::hide_pending()
{
for(int i =0;i<listWidget2->count();i++){
    if(listWidget2->item(i)->isHidden()){
        listWidget2->item(i)->setHidden(0);
    }else{
        listWidget2->item(i)->setHidden(1);
    }
}

}
void ToDoList::hide_finished()
{
    for(int i =0;i<listWidget3->count();i++){
        if(listWidget3->item(i)->isHidden()){
            listWidget3->item(i)->setHidden(0);
        }else{
            listWidget3->item(i)->setHidden(1);
        }
    }
}
