#include <hitbox.hpp>

static bool axis_colliding_test(W2_NAMESPACE W2HitBox *hitbox, W2_NAMESPACE W2HitBox *other);
static W2_NAMESPACE W2GeomProjection do_projection(W2_NAMESPACE W2HitBox *hitbox, QPoint axis);

W2_NAMESPACE W2HitBox::W2HitBox(QList<QPoint> *vertices)
{
    this->m_sides    = QList<QLine>();
    this->m_vertices = QList<QPoint>();
    this->m_size = (int) vertices->count();

    int v_x = 0, v_y = 0;

    for (QPoint point: vertices->toList())
    {
        v_x += point.x();
        v_y += point.y();

        this->m_vertices.append(point);
    }

    for (int i = 0; i < this->m_vertices.count(); i++)
    {
        int v_ia = i;
        int v_ib = i + 1 % this->m_size;

        QPoint v_pa = this->m_vertices[v_ia];
        QPoint v_pb = this->m_vertices[v_ib];
        this->m_sides.append(QLine(v_pa, v_pb));
    }

    this->m_center = QPoint(v_x / this->m_size, v_y / this->m_size);
}

bool W2_NAMESPACE W2HitBox::is_colliding_to(W2_NAMESPACE W2HitBox *other)
{
    // From both perspective, test if working.
    return !(axis_colliding_test(this, other) && axis_colliding_test(other, this));
}

int W2_NAMESPACE W2HitBox::size() const
{
    return this->m_size;
}

QPoint W2_NAMESPACE W2HitBox::center() const
{
    return this->m_center;
}

QList<QLine> W2_NAMESPACE W2HitBox::sides() const
{
    return this->m_sides;
}

QList<QPoint> W2_NAMESPACE W2HitBox::vertices() const
{
    return this->m_vertices;
}

QPoint &W2_NAMESPACE W2HitBox::operator[](int index) const
{
    return const_cast<QPoint &>(index < 0 ? this->m_center : this->m_vertices[index]);
}

static bool axis_colliding_test(W2_NAMESPACE W2HitBox *hitbox, W2_NAMESPACE W2HitBox *other)
{
    const int n = hitbox->size();
    for (int i = 0; i < n; i++)
    {
        const QPoint &v_a = hitbox->vertices()[i];
        const QPoint &v_b = hitbox->vertices()[(i + 1) % n];

        QPoint v_edge = v_b - v_a;
        QPoint v_axis(-v_edge.y(), v_edge.x());

        double v_len = std::hypot(v_axis.x(), v_axis.y());
        if (v_len < 1e-12) continue;
        v_axis /= v_len;

        W2_NAMESPACE W2GeomProjection pa = do_projection(hitbox, v_axis);
        W2_NAMESPACE W2GeomProjection pb = do_projection(other, v_axis);

        int v_overlap = std::min(pa.max, pb.max) - std::max(pa.min, pb.min);
        if (v_overlap <= 0) return false;
    }

    return true;
}

static W2_NAMESPACE W2GeomProjection do_projection(W2_NAMESPACE W2HitBox *hitbox, QPoint axis)
{
    W2_NAMESPACE W2GeomProjection v_projection{ 1e300, -1e300 };
    for (const QPointF v : hitbox->vertices())
    {
        double v_d = v.x() * axis.x() + v.y() * axis.y();
        v_projection.min = std::min(v_projection.min, v_d);
        v_projection.max = std::max(v_projection.max, v_d);
    }

    return v_projection;
}