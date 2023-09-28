#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QWidget>

G4String convert(QString word){

    return word.toStdString();

}




int StartWindow(int argc, char **argv, G4String& material)
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Button Example");
    mainWindow.setGeometry(100, 100, 400, 300);

    QPushButton button("Click Me", &mainWindow);
    button.setGeometry(150, 120, 100, 30);

    QComboBox* select_offset = new QComboBox(&mainWindow);

    select_offset->addItem("5 cm");
    select_offset->addItem("10 cm");
    select_offset->addItem("15 cm");

    select_offset->move(10, 10);
    select_offset->resize(150, 30);

    select_offset->setCurrentIndex(0);

    material = convert(select_offset->currentText());


    QVBoxLayout layout(&mainWindow);
    layout.addWidget(select_offset);

    QObject::connect(&mainWindow, &QWidget::destroyed, &app, &QCoreApplication::quit);

    mainWindow.show();

    return app.exec();
}

