#pragma once

#include <QMainWindow>
#include <QMenu>

class Window : public QMainWindow {
    Q_OBJECT

public:
    Window();

private:
    QMenu* menuFile;
    QMenu* menuHelp;

    QAction* actAbout;
    QAction* actExit;

    void createActions();
    void createMenus();

private slots:
    void about();
};
