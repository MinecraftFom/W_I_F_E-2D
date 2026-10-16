#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <render.hpp>

constexpr const char * choosable_quotes[] = {
    "Son of a bitch",
    "乐子",
    "母狗",
    "滚木",
    "你马斯了",
    "Joker",
    "Nothing more than laughter",
    "Shit",
    "Sense of stupidity",
    "Foolish",
    "杂鱼～哥哥～"
};

W2BorderlessCanvas::W2BorderlessCanvas(const int w, const int h)
{
    this->clicking = false;

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->w = w;
    this->h = h;
    resize(this->w, this->h);
}

void W2BorderlessCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->clicking)
        return;

    move(event->globalPosition().toPoint() - this->position);
}

void W2BorderlessCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->clicking = true;
        this->position = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void W2BorderlessCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        this->clicking = false;
}

void W2BorderlessCanvas::paintEvent(QPaintEvent *)
{
    int length = 11;
    QRandomGenerator generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());
    int v = generator.bounded(length);
    int v2 = generator.bounded(length);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::red);
    p.setBrush(QColor(255, 0, 0, 128));
    p.drawText(200, 200, choosable_quotes[v]);

    // // p.setPen(Qt::white);
    // p.setFont(QFont("Arial", 24));
    p.drawText(rect(), Qt::AlignCenter, choosable_quotes[v2]);
}