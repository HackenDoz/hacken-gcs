#include "artificial_horizon_widget.h"

#include <QResizeEvent>

#define PITCH10 40
#define PITCH5 (PITCH10 / 2)
#define PITCH25 (PITCH10 / 4)

ArtificialHorizon::ArtificialHorizon(QWidget *parent) : QWidget(parent) {
    setObjectName("artificialHorizon");
    pitch = 12.25;
    roll = 4;
}

void ArtificialHorizon::paintEvent(QPaintEvent *event) {
    QPen linePen(Qt::white, 1.5);
    QBrush black(Qt::black, Qt::SolidPattern);
    QBrush ground(QColor(111, 42, 1), Qt::SolidPattern);
    QBrush sky(QColor(1, 125, 251), Qt::SolidPattern);

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setWindow(-100, -100, 200, 200);

    painter.rotate(roll);
    painter.translate(0, (PITCH10 / 10) * pitch);

    // Draw ground
    painter.setPen(Qt::NoPen);
    painter.setBrush(ground);
    painter.drawRect(-200, 0, 400, 200);
    // Draw sky
    painter.setPen(Qt::NoPen);
    painter.setBrush(sky);
    painter.drawRect(-200, -200, 400, 200);

    // Draw dividing line
    painter.setPen(linePen);
    painter.drawLine(-200, 0, 400, 0);

    QLineF lines[3] = {
            QLineF(-10, 0, 10, 0), // small line (2.5 degrees)
            QLineF(-20, 0, 20, 0), // medium line (5 degrees)
            QLineF(-40, 0, 40, 0), // large line (10 degrees)
    };

    QFont font("monospace", 12);
    QFontMetrics metrics(font);
    painter.setFont(font);
    for (int i = 1; i <= 9; i++) {
        char s[2] = {static_cast<char>(i + '0'), '0'};
        s[0] = static_cast<char>(i + '0');
        int textw = metrics.width(s);

        // Draw negative pitch
        painter.save();
        drawPitchLines(i, lines);
        painter.drawText(-40 - textw - 5, 40 * i + font.pointSize() / 2, s);
        painter.drawText(40 + 5, 40 * i + font.pointSize() / 2, s);
        painter.restore();

        // Draw positive pitch
        painter.save();
        painter.scale(1, -1);
        drawPitchLines(i, lines);
        painter.restore();
        painter.drawText(-40 - textw - 5, -40 * i + font.pointSize() / 2, s);
        painter.drawText(40 + 5, -40 * i + font.pointSize() / 2, s);
    }


    QRect viewport = painter.viewport();
    painter.resetTransform();
    painter.setWindow(-100, -100, 200, 200);
    painter.setViewport(viewport);

    QPen crossHair(Qt::white, 1);
    crossHair.setJoinStyle(Qt::MiterJoin);

    QPointF points[6] = {
            QPointF(0, 0),
            QPointF(0, 8),
            QPointF(3, 8),
            QPointF(3, 3),
            QPointF(25, 3),
            QPointF(25, 0),
    };

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(crossHair);
    painter.setBrush(black);

    painter.save();
    painter.translate(0, -1.5);
    painter.drawRect(QRectF(-1.5, 0, 3, 3));

    // Draw left crosshair
    painter.save();
    painter.translate(30, 0);
    painter.drawPolygon(points, 6);
    painter.restore();

    // Draw right crosshair
    painter.save();
    painter.translate(-30, 0);
    painter.scale(-1, 1);
    painter.drawPolygon(points, 6);
    painter.restore();
    painter.restore();

    painter.end();
}

void ArtificialHorizon::resizeEvent(QResizeEvent *event) {
    int size = qMin(event->size().width(), event->size().height());
    resize(size, size);
}

void ArtificialHorizon::drawPitchLines(int i, QLineF lines[3]) {
    painter.save();
    painter.translate(0, PITCH10 * i - (PITCH10 - PITCH25));
    painter.drawLine(lines[0]);
    painter.translate(0, PITCH10 / 2);
    painter.drawLine(lines[0]);
    painter.restore();

    painter.save();
    painter.translate(0, PITCH10 * i - (PITCH10 - PITCH5));
    painter.drawLine(lines[1]);
    painter.restore();

    painter.save();
    painter.translate(0, PITCH10 * i);
    painter.drawLine(lines[2]);
    painter.restore();
}

