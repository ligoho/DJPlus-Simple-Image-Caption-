#ifndef M_LABEL_H
#define M_LABEL_H

#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>


class m_label : public QLabel
{

    Q_OBJECT

public:
    m_label(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent* event);

public slots:
    void drawLine();
    void clearLine();
    std::vector<QPointF> getPoints();

signals:

private:
    std::vector<QPointF> point;

    float c_x;
    float c_y;

    bool isDraw = false;
    bool isClear = true;
};

#endif // M_LABEL_H
