#include "window.h"

#include <QMenuBar>
#include <QMessageBox>

Window::Window() {
    setObjectName("window");

    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    setupActions();
    setupMenus();

    QString str = QString("Test");
    createDock(str, new QWidget(this), Qt::LeftDockWidgetArea);
}

void Window::setupActions() {
    actAbout = new QAction("About", this);
    connect(actAbout, &QAction::triggered, this, &Window::about);
    actExit = new QAction("Exit", this);
    connect(actExit, &QAction::triggered, this, &Window::close);
}

void Window::setupMenus() {
    menuFile = menuBar()->addMenu("File");
    menuFile->addAction(actExit);
    menuHelp = menuBar()->addMenu("Help");
    menuHelp->addAction(actAbout);
}

void Window::createDock(QString &title, QWidget *widget, Qt::DockWidgetArea area) {
    GCSDockWidget *dock = new GCSDockWidget(title, this);
    dock->setWidget(widget);
    docks.push_back(dock);
    addDockWidget(area, dock);

    int index = docks.length() - 1;
    connect(dock, &QObject::destroyed, [this, index]{
        docks.removeAt(index);
    });
}

void Window::createToolbar() {

}

void Window::about() {
    QMessageBox::about(this, "About", "<b>hacken-gcs</b> is a dank program.");
}

