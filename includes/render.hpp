#pragma once
#include <QWidget>

#include <const.hpp>

#include "engine.hpp"

W2_NAMESPACE_BEGINE
    class W2BorderlessCanvas;
W2_NAMESPACE_END

class W2_NAMESPACE W2BorderlessCanvas : public QWidget
{
public:
    W2BorderlessCanvas(int w, int h);
    void add(W2Component *component);

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

    QList<W2Component*> subnodes;
};