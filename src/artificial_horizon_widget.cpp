#include "artificial_horizon_widget.h"

#include <QDebug>
#include <QStaticText>

ArtificialHorizon::ArtificialHorizon(QWidget *parent) : QWidget(parent) {
    setObjectName("artificialHorizon");
}

void ArtificialHorizon::paintEvent(QPaintEvent *event) {
    QPen linePen(Qt::white, 5);
    QBrush black(Qt::black, Qt::SolidPattern);
    QBrush ground(QColor(255, 128, 0), Qt::SolidPattern);
    QBrush sky(QColor(0, 114, 185), Qt::SolidPattern);

    int w = width();
    int h = height();
    painter.begin(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(black);
    painter.drawRect(0, 0, w, h);

    painter.setPen(Qt::NoPen);
    painter.setBrush(ground);
    painter.drawRect(0, h / 2, w, h / 2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(sky);
    painter.drawRect(0, 0, w, h / 2);

    painter.setPen(linePen);
//    painter.drawLine(w / 2, 0, w / 2, h);
    painter.drawLine(0, h / 2, w, h / 2);

    QFont font("monospace", 32);
    QFontMetrics metrics(font);
    painter.setFont(font);
    char s[2] = {'0', '0'};
    for (int i = 1; i <= 9; i++) {
        s[0] = static_cast<char>(i + '0');
        int textw = metrics.width(s);

        painter.drawLine(4 * w / 9, h / 2 + 100 * (i - 1) + 25,
                         5 * w / 9, h / 2 + 100 * (i - 1) + 25);
        painter.drawLine(2 * w / 5, h / 2 + 100 * (i - 1) + 50,
                         3 * w / 5, h / 2 + 100 * (i - 1) + 50);
        painter.drawLine(4 * w / 9, h / 2 + 100 * (i - 1) + 75,
                         5 * w / 9, h / 2 + 100 * (i - 1) + 75);
        painter.drawLine(1 * w / 3, h / 2 + 100 * i,
                         2 * w / 3, h / 2 + 100 * i);

        painter.drawLine(4 * w / 9, h / 2 - 100 * (i - 1) - 25,
                         5 * w / 9, h / 2 - 100 * (i - 1) - 25);
        painter.drawLine(2 * w / 5, h / 2 - 100 * (i - 1) - 50,
                         3 * w / 5, h / 2 - 100 * (i - 1) - 50);
        painter.drawLine(4 * w / 9, h / 2 - 100 * (i - 1) - 75,
                         5 * w / 9, h / 2 - 100 * (i - 1) - 75);
        painter.drawLine(1 * w / 3, h / 2 - 100 * i,
                         2 * w / 3, h / 2 - 100 * i);


        painter.drawText(1 * w / 3 - textw - 10, h / 2 - 100 * i + font.pointSize() / 2, s);
        painter.drawText(2 * w / 3 + 10, h / 2 - 100 * i + font.pointSize() / 2, s);

        painter.drawText(1 * w / 3 - textw - 10, h / 2 + 100 * i + font.pointSize() / 2, s);
        painter.drawText(2 * w / 3 + 10, h / 2 + 100 * i + font.pointSize() / 2, s);
    }


    painter.end();
}
