#pragma once

#include <QPainter>
#include <QWidget>

class ArtificialHorizon : public QWidget {
public:
    ArtificialHorizon(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    double yaw;
    double pitch;
    QPainter painter;

    void drawPitchLines(int index, QLineF lines[3]);
};
