# ToDoList
## Overview 
The goal of this lab is to create an application to manage tasks. It should have all the features of main application such as menues, actions and toolbar. The application must store an archive of all the pending and finished tasks.

We will proceed as follows:

First, we will make an itembased solution using QListWidget.

### Creating menues and toolbars :
I already explained this part step by step in the previous lab spreadsheet.
1-Let´s create Actions,menues and toolbars:
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

```
2-Now,we will try to connec
```cpp

```

### Main Widget:
Our main widget should be splitted into three areas:
Basically we will create three listWidgets.
```cpp
 QListWidget *listWidget1 ;
  QListWidget *listWidget2;
  QListWidget *listWidget3;
  ```
Now.we will try to arrange them in a specific way:

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
  ### Linking my 
