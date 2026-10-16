#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
class W2BorderlessCanvas;
QT_END_NAMESPACE

class W2BorderlessCanvas : public QWidget
{
public:
    W2BorderlessCanvas(int w, int h);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

    int w;
    int h;

private:
    QPoint position;
    bool clicking;
};