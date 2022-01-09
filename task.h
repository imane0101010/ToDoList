#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

private:
  //Ui::Task *ui;
    QDateEdit * DueDate;
    QComboBox * Tag;
    QLabel * Description;
    QLineEdit * LineEdit;
    QCheckBox *finished;
    QPushButton *ok;
    QPushButton *cancel;
    void createWidgets();
    void placeWidgets();
    void makeConnections();
 public:
    bool get_finished();
    int get_Tag();
    QString get_Description();
    QDate get_Due_Date();

};

#endif // TASK_H
