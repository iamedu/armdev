#include "armidesigner.h"

ARMIDesigner::ARMIDesigner(QWidget *parent) : QMainWindow(parent){
	setupUi(this);
	connect(actionOpen,SIGNAL(triggered()),this,SLOT(open()));	
	connect(actionNew,SIGNAL(triggered()),this,SLOT(newFile()));	
}

void ARMIDesigner::newFile(){
	int i = tabWidget->addTab(new QTextEdit(tabWidget),"NewFile");
	tabWidget->setCurrentIndex(i);
}
bool ARMIDesigner::open(){
	QString texto;
	QTextEdit *text = new QTextEdit(tabWidget);
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                        		"/home",
                                                 	tr("Files (*.c *.cpp *.m *.h)"));
	QFile file(fileName);
	if (!file.open(QIODevice::ReadWrite)) {
    		QMessageBox::warning(this, tr("NewFile"),
                         tr("Cannot write file %1:\n%2.")
                         .arg(file.fileName())
                         .arg(file.errorString()));
    		return false;
	}

	QFileInfo fi(file);
	QTextStream in(&file);	
	texto = in.readAll();
	text->setText(texto);

	int i = tabWidget->addTab(text,fi.fileName());
        tabWidget->setCurrentIndex(i);

	return true;
}
bool ARMIDesigner::save(){
	return true;
}
void ARMIDesigner::upload(){
}
void ARMIDesigner::build(){
}
void ARMIDesigner::about(){
}

