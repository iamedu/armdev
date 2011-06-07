#ifndef ARMIDESIGNER_H
#define ARMIDESIGNER_H
#include <QMainWindow>
#include <QtGui>
#include <QFile>
#include <QFileDialog>
#include <QTextEdit>
#include "ui_armidesigner.h"

class ARMIDesigner : public QMainWindow, public Ui::MainWindow
{
   Q_OBJECT

public:
    ARMIDesigner(QWidget *parent = 0);
private slots:
    void newFile();
    bool open();
    bool save();
    void upload();
    void build();
    void about();
};

#endif
