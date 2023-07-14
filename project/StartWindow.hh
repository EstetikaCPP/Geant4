#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>


int StartWindow(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Button Example");
    mainWindow.setGeometry(100, 100, 400, 300);

    QPushButton button("Click Me", &mainWindow);
    button.setGeometry(150, 120, 100, 30);


    // Подключение сигнала clicked к слоту myFunction
    QObject::connect(&button, &QPushButton::clicked, &mainWindow, &QMainWindow::close);

    mainWindow.show();


    return app.exec();
}
