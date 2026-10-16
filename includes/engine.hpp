#pragma once

#include <const.hpp>
#include <qevent.h>
#include <QWidget>

W2_NAMESPACE_BEGINE
class W2Component;
class W2TextComponent;
W2_NAMESPACE_END

class W2_NAMESPACE W2Component : public QWidget
{
public:
    W2Component(double x_offset, double y_offset);
    [[nodiscard]] double get_x_offset() const;
    [[nodiscard]] double get_y_offset() const;

    virtual void paint(QPainter *painter, QPaintEvent *paint_event);
protected:
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
private:
    bool m_clicking;
    double m_x_offset;
    double m_y_offset;
};

class W2_NAMESPACE W2TextComponent : public W2Component
{
public:
    W2TextComponent(double x_offset, double y_offset, const QString &text);

    void paint(QPainter *painter, QPaintEvent *paint_event) override;
private:
    const QString &m_text;
};