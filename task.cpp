#include "task.h"
#include "ui_task.h"
#include <QVBoxLayout>
#include <QFormLayout>
Task::Task(QWidget *parent) :
    QDialog(parent)
   // ui(new Ui::Task)
{
   // ui->setupUi(this);
   createWidgets();
   placeWidgets();
   makeConnections();


}

Task::~Task()
{
    //elete ui;
    delete DueDate;
    delete Tag;
    delete LineEdit;
    delete ok;
    delete cancel;
    delete finished;

}

void Task::createWidgets()
{
     DueDate = new QDateEdit;
     Tag = new  QComboBox;
     LineEdit = new  QLineEdit;
     finished = new QCheckBox;
     ok = new QPushButton("OK");
     cancel = new QPushButton("Cancel");


}

void Task::placeWidgets()
{
//auto container = new QWidget;
auto layout = new QVBoxLayout;
auto layout1 = new QFormLayout;
auto layout2 = new QHBoxLayout;
layout1->addRow("Description",LineEdit);
Tag->addItem("Work");
Tag->addItem("Life");
Tag->addItem("Other");
layout1->addRow("Tag",Tag);
layout1->addRow("Finished",finished);
layout1->addRow("Due Date",DueDate);
layout->addLayout(layout1);
layout2->addSpacing(100);
ok->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
cancel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
layout2->addWidget(ok);
layout2->addWidget(cancel);
layout->addLayout(layout2);
setLayout(layout);

}

void Task::makeConnections()
{
    connect(ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
}

bool Task::get_finished()
{
    return finished->isChecked();
}

int Task::get_Tag()
{
    return Tag->currentIndex();
}

QString Task::get_Description()
{
    return LineEdit->text();
}

QDate Task::get_Due_Date()
{
    return DueDate->date();
}
