#include <QPainter>
#include <QMouseEvent>
#include <render.hpp>

BorderlessGuiContext::BorderlessGuiContext()
{
    this->clicking = false;

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(800, 600);
}

void BorderlessGuiContext::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->clicking)
        return;

    move(event->globalPosition().toPoint() - this->position);
}

void BorderlessGuiContext::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->clicking = true;
        this->position = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void BorderlessGuiContext::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        this->clicking = false;
}

void BorderlessGuiContext::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::red);
    p.setBrush(QColor(255, 0, 0, 128));
    p.drawText(200, 200, "fuck you");

    // // p.setPen(Qt::white);
    // p.setFont(QFont("Arial", 24));
    p.drawText(rect(), Qt::AlignCenter, "son of a bitch");
}