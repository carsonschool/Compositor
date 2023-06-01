#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QListView>
#include <QKeyEvent>
#include <QDebug>

class CustomWindowManager : public QMainWindow
{
    Q_OBJECT

public:
    CustomWindowManager(QWidget *parent = nullptr);

protected:
    bool event(QEvent *event) override;
};

CustomWindowManager::CustomWindowManager(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the main window
    QMainWindow *mainWindow = new QMainWindow(this);
    mainWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    mainWindow->setAttribute(Qt::WA_TranslucentBackground);
    mainWindow->setStyleSheet("QMainWindow { background-color: transparent; }");

    // Show the main window
    mainWindow->showFullScreen();
}

bool CustomWindowManager::event(QEvent *event)
{
    // Handle key events
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
        {
            qDebug() << "Escape key pressed. Closing application.";
            // Close the application
            QApplication::quit();
            return true;
        }
    }

    // Call the base class implementation to handle other events
    return QMainWindow::event(event);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CustomWindowManager mainWindow;
    mainWindow.show();

    return app.exec();
}
