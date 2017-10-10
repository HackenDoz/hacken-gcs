#include "window.h"

#include <QDebug>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QWidgetAction>

Window::Window() {
    setObjectName("window");

    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    setupActions();
    setupMenus();

    QString str = QString("Test");
    createDock(str, new QWidget(this), Qt::LeftDockWidgetArea);
    createDock(str, new QWidget(this), Qt::RightDockWidgetArea);

    QActionGroup *toolbarGroup1 = new QActionGroup(this);
    toolbarGroup1->addAction("Hi");
    createToolbar(str, toolbarGroup1, Qt::TopToolBarArea);

    QActionGroup *toolbarGroup2 = new QActionGroup(this);
    toolbarGroup2->addAction("Bye");
    createToolbar(str, toolbarGroup2, Qt::TopToolBarArea);
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

    connect(dock, &QObject::destroyed, [this, &dock]{
        docks.removeOne(dock);
    });
}

void Window::createToolbar(QString &title, QActionGroup *actions, Qt::ToolBarArea area) {
    QToolBar *toolbar = new QToolBar(title, this);
    toolbar->setObjectName(title);
    toolbar->addActions(actions->actions());
    toolbars.push_back(toolbar);
    addToolBar(toolbar);
}

void Window::about() {
    QMessageBox::about(this, "About", "<b>hacken-gcs</b> is a dank program.");
}

