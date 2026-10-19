#pragma once

#include <const.hpp>
#include <QList>

W2_NAMESPACE_BEGINE
class  W2HitBoxAABB;

struct W2Line;
struct W2Position;
struct W2PositionConstant;
struct W2Relative;
struct W2Vector;
W2_NAMESPACE_END

struct W2_NAMESPACE W2Line
{
    W2Line(W2Position *start, W2Position *end);

    W2Position *start, *end;
    // A smooth, straight line is of y=kx + o (k != 0), which O here is OFFSET
    // Here, the let *start = (a, b), *end = (c, d), then the formula of k, o will be:
    // k = (d - b) / (c - a)
    // o = (bc - ad) / (c - a)
    [[nodiscard]] double k() const;
    [[nodiscard]] double o() const;

    [[nodiscard]] bool isOn(W2Position p) const;
    [[nodiscard]] bool isMeeting(W2Line line) const;
};

struct W2_NAMESPACE W2Position
{
    double x(), y();
};

struct W2_NAMESPACE W2PositionConstant : W2Position
{
    W2PositionConstant(double x, double y);
    double x_, y_;

    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
};

struct W2_NAMESPACE W2Relative : W2Position
{
    W2Position *center;
    double x_offset, y_offset;
    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
};

struct W2_NAMESPACE W2Vector
{
    W2Position *start, *end;
};

class W2_NAMESPACE W2HitBoxAABB
{
public:
    W2HitBoxAABB(QList<W2Relative> lines);
    bool hit(const W2HitBoxAABB&);

private:
    // W2Position *center;

    QList<W2Relative> vertices;
    QList<W2Line> sides;
};