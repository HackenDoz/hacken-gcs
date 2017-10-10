#include "window.h"

#include <QMenuBar>
#include <QMessageBox>

Window::Window() {
    setObjectName("window");

    createActions();
    createMenus();
}

void Window::createActions() {
    actAbout = new QAction("About", this);
    connect(actAbout, &QAction::triggered, this, &Window::about);
    actExit = new QAction("Exit", this);
    connect(actExit, &QAction::triggered, this, &Window::close);
}

void Window::createMenus() {
    menuFile = menuBar()->addMenu("File");
    menuFile->addAction(actExit);
    menuHelp = menuBar()->addMenu("Help");
    menuHelp->addAction(actAbout);
}

void Window::about() {
    QMessageBox::about(this, "About", "<b>hacken-gcs</b> is a dank program.");
}

