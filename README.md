# ToDoList
## Overview 
The goal of this lab is to create an application to manage tasks. It should have all the features of main application such as menues, actions and toolbar. The application must store an archive of all the pending and finished tasks.

We will proceed as follows:

First, we will make an itembased solution using QListWidget.

### Creating menues and toolbars :
This part of this project is already well explained in the previous lab spreadsheet.

* [x] **Let´s create Actions,menues,toolbars and some methods:**

In the header file:

```cpp
private:
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
   void createAction();
   void createMenues();
   void createToolBars();
   void makeConnections();
```
In cpp file:

* [x] **Implementation of createActions():**

```cpp

    quit = new QAction("&Quit", this);
     QPixmap pending_task_icon(":/pendingTask.png");
    pending_task = new QAction(pending_task_icon,"&Pending",this);
    save = new QAction ("&Save",this);
    about = new QAction("&About",this);
     QPixmap done_task_icon(":/completedTask.png");
    done_task = new QAction(done_task_icon,"&Done",this);
    QPixmap new_task_icon(":/NewTask.png");
    new_task =new QAction(new_task_icon,"&New",this);
```
* [x] **Implementation of createToolBars():**

```cpp
    toolbar = addToolBar("Toolbar");
    toolbar->addAction(new_task);
    toolbar->addAction(pending_task);
    toolbar->addAction(done_task);
 ```
* [x] **Implementation of createMenues():**

 ```cpp
  file = new QMenu("&File", this);
      menuBar()->addMenu(file);
      file->addAction("&new_task");
      file->addAction("&pending_task");
      file->addAction("&done_task");
      options = new QMenu("&Options",this);
      menuBar()->addMenu(options);
      options->addAction("&save");
      options->addAction("&quit");
      help = new QMenu("&Help",this);
      menuBar()->addMenu(help);
      help->addAction("&about");
```
* [x] **Now let´s connect the Actions:**
```cpp
connect(new_task,&QAction::triggered,this,&ToDoList::new_slot);
connect(pending_task,&QAction::triggered,this,&ToDoList::hide_pending);
connect(done_task,&QAction::triggered,this,&ToDoList::hide_finished);
```
### Main Widget:

Our main widget should be splitted into three areas:
We will create three listWidgets.
```cpp
 QListWidget *listWidget1 ;
  QListWidget *listWidget2;
  QListWidget *listWidget3;
  ```
Now, we will try to arrange them in a specific way:

listWidget1 and listWidget2 will be laid horizontally and the last one will be laid vertically.
I will be using QSplitter,layouts and a QWidget as a container and a central widget .Here is the full code:

```cpp
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
  ```
After creating the main widget,we will be going to create customized slots for each action:
First,for the hide_pending slot,here is the full code:
```cpp
//iterating over the listWidget2(The one that contains Pending task)
for(int i =0;i<listWidget2->count();i++){
 //Check if the item is hidden
    if(listWidget2->item(i)->isHidden()){
     //Show the item(pending task)
        listWidget2->item(i)->setHidden(0);
    }else{
       //Hide the item(pending task)
        listWidget2->item(i)->setHidden(1);
    }
}
```
Then comes the hide_finished slot:
```cpp
//iterating over the listWidget2(The one that contains finished tasks)
 for(int i =0;i<listWidget3->count();i++){
  //Check if the item is hidden
        if(listWidget3->item(i)->isHidden()){
             //Show the item(finished task)
            listWidget3->item(i)->setHidden(0);
        }else{
        //Hide the item (finished task)
            listWidget3->item(i)->setHidden(1);
        }
    }
```
Finally the new_slot:
```cpp
   Task task1;
   auto rep = task1.exec();
   //Check if the the dialog is accepted and the task is already finished:
     if(rep == QDialog::Accepted && task1.get_finished()){
      //Creating the text that will be displayed in the finished task listwidget:
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

           }else if(task1.get_Due_Date() != QDateTime::currentDateTime().date()){
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
    
    ```
    ### Linking my ToDoList with a DB:
    First we will create a database in the header file:
    ```cpp
      QSqlDatabase  db ;
      //method
      void DB();
      ```
      Implementation of DB method:
      ``cpp
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName("/media/hp/data/Database/db");
       db.open();
       QSqlQuery qry;
       //executing the query
    if(qry.exec(query)){
    qDebug()<<"Successful";
    }
   ```
   The query:
   ```cpp
    QString query ="CREATE TABLE IF NOT EXISTS T1 ("
  "STATE VARCHAR(20),"
   "DUE_DATE date,"
  "Description VARCHAR(40),"
  "TAG integer);";
  ```
Now it´s time to make use of this database:
Basically,I will be using it to store the tasks and also to load them while opening the ToDo List.
To do so,I will be adding the following in the new slot in order to save the tasks while creating them:
```cpp
 QSqlQuery qry;
   qry.prepare("INSERT INTO T1 (STATE, DUE_DATE, Description, TAG)VALUES (?,?,?,?);");
   qry.addBindValue(state.append(" Task: "));
   qry.addBindValue(task1.get_Due_Date());
   qry.addBindValue(task1.get_Description());
   qry.addBindValue(task1.get_Tag());
   qry.exec();
```
For the loading part,I will create and implement a method called load_:
Here is the full implementation:
```cpp

    QSqlQuery query;
    QString F ="";
    QString P ="";
    QString T ="";
    if(query.exec("SELECT * FROM T1"))
    {
   // Retrieving the next record 
        while(query.next())
        {
        //iterating over the records:
            for(int x=0; x < query.record().count(); ++x)
            {
              //check whether the value stored is Finished task:
                 if(query.record().value(x).toString()== "Finished Task: " )
             {
                      //Get the other information of the task and storing them in a QString
                      for(int i =x;i<=x+4;i++){
                     F.append(query.record().value(i).toString());
                     F.append(" ");
                      }

                     x=x+3;
                  }
                //check whether the value stored is Pending task:
            else if ( query.record().value(x).toString() == "Pending Task: " )
               {
                     for(int i =x;i<x+4;i++){
                 /Get the other information of the task and storing them in a QString
                 P.append(query.record().value(i).toString());
                 P.append(" ");

               }
                     x=x+3;
                 }
                   //check whether the value stored is Today´s task:
                 else if(query.record().value(x).toString() == "Today´s Task: " ){

                  {
                         for(int i =x;i<x+4;i++){
                         /Get the other information of the task and storing them in a QString
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
      //iterating over the QString list
          for(int i =0 ; i< qMax(F1.size(),qMax(P1.size(),T1.size()));i++){
     
              if(i<T1.size()){
                  QString s1 ="Finished Task: ";
                  s1.append(T1.at(i));
                  //add the finished task in the listWidget
               listWidget1->addItem(s1);
               
              }
              if(i<P1.size()){
                  QString s2 ="Pending Task: ";
                  s2.append(P1.at(i));
                  //adding the pending task in th list Widget
               listWidget2->addItem(s2);
              
              }
              if(i<F1.size()){
                  QString s3 ="Today´s Task: ";
                  s3.append(F1.at(i));
                   //adding today´s task in the list Widget
               listWidget3->addItem(s3);
             
                  }
}
}
```
# MVC Solution:
For the MVC solution,I will be using QListView and QSqlDatabase.I will skip the first part which is the creation of toolbars,actions and menues.
Instead of creating QListWidgets,I used three QListViews and three models.

```cpp
//creating a QWidget that will be used as container of the layouts
   container = new QWidget;
   //creating a splitter
   splitter2 = new QSplitter;
   //creating a second splitter
   splitter1 = new QSplitter;
   //creating the first QListView listV 
    listV = new QListView;
    //creating the model
    model = new QStringListModel;
    listV->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //set the model model in the listV
   listV->setModel(model);
   //adding a QHBoxLayout
   auto layout1 = new QHBoxLayout;
      //adding a QVBoxLayout
   auto layout = new QVBoxLayout;
   //add the listV in the vertical layout layout
   layout->addWidget(listV);
   //creating the second QListView listV1
     listV1 = new QListView;
    listV1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //creating the model model1
     model1 = new QStringListModel;
     //setting the model model1 in listV1
     listV1->setModel(model1);
     //laying out the listV and the listV1 vertically
    splitter1->addWidget(listV);
    splitter1->addWidget(listV1);
    layout->addWidget(splitter1);
    //creating the third QListView listV2
       listV2 = new QListView;
    //creating the model model2
       model2 = new QStringListModel;
       listV2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     //setting the model model2 in listV2
       listV2->setModel(model2);
     //laying out the listV2 vertically
       splitter2->addWidget(listV2);
       //adding splitter2 in the horizontal layout
       layout1->addWidget(splitter2);
       //adding the vertical layout in the horizontal layout
       layout1->addLayout(layout);
       //add the horizontal layout in the container
       container->setLayout(layout1);
       setCentralWidget(container);
       ```
When it comes to the slots,I will keep the same reasoning that I used for the itembased solution with some slight modifications.

* [x] **The hide_finished slot**
```cpp

    for(int i =0;i<model1->rowCount();i++){
        if(listV1->isRowHidden(i)){
           listV1->setRowHidden(i,0);
        }else{
            listV1->setRowHidden(i,1);
        }
    }
   }
   ```
 * [x] **The hide_pending slot**   
```cpp
 for(int i =0;i<model->rowCount();i++){
        if(listV2->isRowHidden(i)){
           listV2->setRowHidden(i,0);
        }else{
            listV2->setRowHidden(i,1);
        }
    }
   }
   ```
  * [x] **The new_slot slot**   
  ```cpp
  task2 task;
    QStringList list;
    QStringList list1;
    QStringList list2;
    auto rep = task.exec();
    //check if the dialog is accepted and the task is finished
      if(rep == QDialog::Accepted && task.get_finished()){
      //creating the text that will be dispalyed in the model
         QString text ="Finished Task: ";
         state.clear();
         state = "Finished";
         text.append(task.get_Due_Date().toString());
         text.append(" ");
         text.append(task.get_Description());
         text.append(" Tag: ");
         text.append(QString::number(task.get_Tag()));
         //adding the text in the QStringList list1
         list1.append(text);
         //setting the list1 in the model
         model1->setStringList(list1);


     }else if(rep == QDialog::Accepted && !task.get_finished()){
            if(task.get_Due_Date().toString()==QDateTime::currentDateTime().date().toString()){
                QString text ="Today´s Task: ";
                state.clear();
                state = "Today";
                text.append(task.get_Due_Date().toString());
                text.append(" ");
               text.append(task.get_Description());
                text.append(" Tag: ");
                text.append(QString::number(task.get_Tag()));
                list2.append(text);
                model2->setStringList(list2);

            }else if(task.get_Due_Date() != QDateTime::currentDateTime().date() ){
                QString text ="Pending Task: ";
                state.clear();
                state ="Pending";
                text.append(task.get_Due_Date().toString());
                text.append(" ");
                text.append(task.get_Description());
                text.append(" Tag: ");
                text.append(QString::number(task.get_Tag()));
               list.append(text);
               model->setStringList(list);

            }
     }
     ```
    Now,we should link our ToDoList to a database.I will just adjust the previous code.
    Since the creation of the database,storage of the tasks and the iteration over the records won´t change,I used the same code (for the itembased solution) and     I will skip this part.
    For the loading method,I only changed the second part.Here is the modifications that I made:
    ```cpp
      QStringList F1 = F.split("Finished Task: ");
      QStringList P1 = P.split("Pending Task: ");
      QStringList T1 = T.split("Today´s Task: ");
      QStringList list;
          for(int i =0 ; i< qMax(F1.size(),qMax(P1.size(),T1.size()));i++){
           
              if(i<T1.size() && T1.size()>1){
               QString s1 ="Finished Task: ";
               s1.append(T1.at(i));
               list.clear();
               list.append(s1);
               model1->setStringList(list);
           
              }

              if(i<P1.size() && P1.size()>1){
                  QString s2 ="Pending Task: ";
                  s2.append(P1.at(i));
                  list.clear();
                  list.append(s2);
                  model->setStringList(list);

              }
              if(i<F1.size() && F1.size()>1){
                  QString s3 ="Today´s Task: ";
                  s3.append(F1.at(i));
                  list.clear();
                  list.append(s3);
                  model2->setStringList(list);
            
                  }
```
    
    
    
