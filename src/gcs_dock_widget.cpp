#include "gcs_dock_widget.h"

#include <QCloseEvent>

GCSDockWidget::GCSDockWidget(QWidget *parent) : QDockWidget(parent) {
}

GCSDockWidget::GCSDockWidget(QString &title, QWidget *parent) : QDockWidget(title, parent) {
    setObjectName(title);
}

void GCSDockWidget::closeEvent(QCloseEvent *event) {
    event->accept();
    deleteLater();
}