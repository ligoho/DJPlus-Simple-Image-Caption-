#include "m_label.h"

m_label::m_label(QWidget *parent) : QLabel(parent)
{
    this->setPixmap(QPixmap(":/pic/res/img.png"));
}

void m_label::mousePressEvent(QMouseEvent *ev)
{
    point.push_back(QPoint(ev->pos().x(),ev->pos().y()));

    c_x = ev->pos().x();
    c_y = ev->pos().y();
    update();
}

void m_label::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);//先调用父类的绘图事件，否则无法看到给父类设置的背景
    QPainter painter(this);
    painter.setPen(QPen(Qt::green,5,Qt::SolidLine,Qt::RoundCap));
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing); //开启抗锯齿

    if(!isClear)
    {
        if(!isDraw)
        {
            int size = static_cast<int>(point.size());
            QPointF points[size];
            for(int i=0; i < size; ++i)
            {
                points[i].setX(point[i].x());
                points[i].setY(point[i].y());
            }
            painter.drawPoints(points,size);
        }
        else
        {
            painter.setPen(QPen(Qt::green,2,Qt::SolidLine,Qt::RoundCap));

            int size = static_cast<int>(point.size());
            QPolygonF polygon;
            for(int i=0; i < size; ++i)
            {
                polygon << QPointF(point[i]);
            }
            painter.drawPolygon(polygon, Qt::WindingFill);

            isDraw = false;
        }
    }
    else
    {
        isClear = false;
    }
}

void m_label::drawLine()
{
    isDraw = true;

    update();
}

void m_label::clearLine()
{
    isClear = true;
    point.clear();

    update();
}

std::vector<QPointF> m_label::getPoints()
{
    return point;
}


