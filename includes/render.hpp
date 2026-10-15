#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
class BorderlessGuiContext;
QT_END_NAMESPACE

class BorderlessGuiContext : public QWidget
{
public:
    BorderlessGuiContext();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    QPoint position;
    bool clicking;
};
