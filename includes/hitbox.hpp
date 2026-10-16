#pragma once

#include <const.hpp>
#include <qlist.h>
#include <qline.h>

W2_NAMESPACE_BEGINE
struct W2GeomProjection;
class W2HitBox;
W2_NAMESPACE_END

struct W2_NAMESPACE W2GeomProjection
{
    double min, max;
};

class W2_NAMESPACE W2HitBox
{
public:
    W2HitBox(QList<QPoint>*);
    bool is_colliding_to(W2HitBox *other);

    [[nodiscard]] int size() const;
    [[nodiscard]] QPoint center() const;
    [[nodiscard]] QList<QLine> sides() const;
    [[nodiscard]] QList<QPoint> vertices() const;

    [[nodiscard]] QPoint &operator[](int index) const;

private:
    int           m_size;

    QPoint        m_center;
    QList<QLine>  m_sides;
    QList<QPoint> m_vertices;
};