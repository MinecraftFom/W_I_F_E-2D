#include <hitbox.hpp>
#include <utility>

W2_NAMESPACE_BEGINE
W2PositionConstant::W2PositionConstant(const double x, const double y)
{
    this->x_ = x;
    this->y_ = y;
}

double W2PositionConstant::x() const
{
    return this->x_;
}

double W2PositionConstant::y() const
{
    return this->y_;
}

W2Line::W2Line(W2Position *start, W2Position *end)
{
    this->start = start;
    this->end = end;
}

double W2Line::k() const
{
    const double csa = this->end->x() - this->start->x();
    const double dsb = this->end->y() - this->start->y();
    return dsb / csa;
}

double W2Line::o() const
{
    const double csa = this->end->x() - this->start->x();
    const double bmc = this->end->x() * this->start->y();
    const double amd = this->end->y() * this->start->x();
    return (bmc - amd) / csa;
}

// Formula:
// 0 <= (a - x1) / (x2 - x1) <= 1
// 0 <= (b - y1) / (y2 - y1) <= 1
// Here, p(a, b), *start(x1, y1), *end(x2, y2)
bool W2Line::isOn(W2Position p) const
{
    const double statement_0 = (p.x() - this->start->x()) / (this->end->x() - this->start->x());
    const double statement_1 = (p.y() - this->start->y()) / (this->end->y() - this->start->y());
    const bool condition_0 = 0 <= statement_0 && statement_0 <= 1;
    const bool condition_1 = 0 <= statement_1 && statement_1 <= 1;
    return condition_0 && condition_1;
}

// Meeting point if those weren't vectors.
// P(x, y)
// x = (d - b) / (a - c)
// y = (ad - bc) / (a - c)
bool W2Line::isMeeting(const W2Line line) const
{
    const double a = line.k();
    const double b = line.o();
    const double c = this->k();
    const double d = this->o();
    const double asc = a - c;

    const double x = (d - b) / asc;
    const double y = (a * d - b * c) / asc;

    const W2Position dot = W2PositionConstant(x, y);
    return this->isOn(dot);
}

double W2Relative::x() const
{
    return this->center->x() + this->x_offset;
}

double W2Relative::y() const
{
    return this->center->y() + this->y_offset;
}

W2HitBoxAABB::W2HitBoxAABB(QList<W2Relative> vertices)
{
    this->vertices = QList(std::move(vertices));
    this->sides = QList<W2Line>();

    const int size = this->vertices.count();
    for (int i = 0; i < size; i++)
    {
        int next = (i + 1) % size;

        W2Relative c = this->vertices.at(i);
        W2Relative n = this->vertices.at(next);
        this->sides.append(W2Line(&c, &n));
    }
}

bool W2HitBoxAABB::hit(const W2HitBoxAABB& other)
{
    bool result = false;

    for (W2Line line: this->sides)
        for (W2Line line2: other.sides)
            if (line.isMeeting(line2))
                result = true;

    return result;
}

W2_NAMESPACE_END
