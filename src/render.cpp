#include <QDateTime>
#include <QPainter>
#include <render.hpp>

W2_NAMESPACE W2BorderlessCanvas::W2BorderlessCanvas(const int w, const int h)
{
    this->clicking = false;
    this->subnodes = QList<W2Component*>();

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->w = w;
    this->h = h;
    resize(this->w, this->h);
}

void W2FonnEngine::W2BorderlessCanvas::add(W2Component *component)
{
    this->subnodes.push_back(component);
}

void W2_NAMESPACE W2BorderlessCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->clicking)
        return;

    move(event->globalPosition().toPoint() - this->position);
}

void W2_NAMESPACE W2BorderlessCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->clicking = true;
        this->position = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void W2_NAMESPACE W2BorderlessCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        this->clicking = false;
}

void W2_NAMESPACE W2BorderlessCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::red);
    painter.setBrush(QColor(255, 0, 0, 128));
    for (W2Component *component: this->subnodes)
        component->paint(&painter, event);
}