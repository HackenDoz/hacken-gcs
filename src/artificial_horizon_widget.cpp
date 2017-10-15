#include "artificial_horizon_widget.h"

#include <QDebug>

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
    int gap = h / 7;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(black);
    painter.drawRect(0, 0, w, h);

    painter.setWindow(-w / 2, -h / 2, w, h);
    painter.rotate(20);
    painter.translate(0, gap);

    painter.setPen(Qt::NoPen);
    painter.setBrush(ground);
    painter.drawRect(-w, 0, 2 * w, h);
    painter.setPen(Qt::NoPen);
    painter.setBrush(sky);
    painter.drawRect(-w, -h, 2 * w, h);

    painter.setPen(linePen);
//    painter.drawLine(w / 2, 0, w / 2, h);
    painter.drawLine(-w, 0, w, 0);

    QFont font("monospace", 32);
    QFontMetrics metrics(font);
    painter.setFont(font);
    char s[2] = {'0', '0'};
    for (int i = 1; i <= 9; i++) {
        s[0] = static_cast<char>(i + '0');
        int textw = metrics.width(s);

        painter.drawLine(-w / 18, gap * (i - 1) + gap / 4,
                         w / 18, gap * (i - 1) + gap / 4);
        painter.drawLine(-w / 10, gap * (i - 1) + gap / 2,
                         w / 10, gap * (i - 1) + gap / 2);
        painter.drawLine(-w / 18, gap * (i - 1) + 3 * gap / 4,
                         w / 18, gap * (i - 1) + 3 * gap / 4);
        painter.drawLine(-w / 6, gap * i,
                         w / 6, gap * i);

        painter.drawLine(-w / 18, -gap * (i - 1) + -gap / 4,
                         w / 18, -gap * (i - 1) + -gap / 4);
        painter.drawLine(-w / 10, -gap * (i - 1) + -gap / 2,
                         w / 10, -gap * (i - 1) + -gap / 2);
        painter.drawLine(-w / 18, -gap * (i - 1) + 3 * -gap / 4,
                         w / 18, -gap * (i - 1) + 3 * -gap / 4);
        painter.drawLine(-w / 6, -gap * i,
                         w / 6, -gap * i);

        painter.drawText(-w / 6 - textw - 10, gap * i + font.pointSize() / 2, s);
        painter.drawText(w / 6 + 10, gap * i + font.pointSize() / 2, s);

        painter.drawText(-w / 6 - textw - 10, -gap * i + font.pointSize() / 2, s);
        painter.drawText(w / 6 + 10, -gap * i + font.pointSize() / 2, s);
    }

    painter.end();
}
