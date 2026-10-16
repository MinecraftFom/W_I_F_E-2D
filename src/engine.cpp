#include <engine.hpp>
#include <QPainter>

W2_NAMESPACE W2Component::W2Component(double x, double y)
{
    this->m_x_offset = x;
    this->m_y_offset = y;
    this->m_clicking = false;
}

double W2_NAMESPACE W2Component::get_x_offset() const
{
    return this->m_x_offset;
}

double W2_NAMESPACE W2Component::get_y_offset() const
{
    return this->m_y_offset;
}

void W2_NAMESPACE W2Component::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->m_clicking) return;

    QPointF mouse = event->globalPosition();
    move(mouse.toPoint() - QPointF(this->m_x_offset, this->m_y_offset).toPoint());
}

void W2_NAMESPACE W2Component::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_clicking = true;
        this->m_x_offset = event->globalPosition().x();
        this->m_y_offset = event->globalPosition().y();
    }
}

void W2_NAMESPACE W2Component::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) this->m_clicking = false;
}

// Place holder. Virtual for implementation
void W2_NAMESPACE W2Component::paint(QPainter *painter, QPaintEvent *event)
{
}

W2_NAMESPACE W2TextComponent::W2TextComponent(double x_offset, double y_offset, const QString &text) : W2Component(x_offset, y_offset), m_text(text)
{
}

void W2_NAMESPACE W2TextComponent::paint(QPainter *painter, QPaintEvent *)
{
    painter->drawText(this->get_x_offset(), this->get_y_offset(), this->m_text);
}
