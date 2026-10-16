#include <QApplication>
#include <render.hpp>

#include "engine.hpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    W2_NAMESPACE W2BorderlessCanvas context(700, 800);
    W2_NAMESPACE W2TextComponent component(100, 200, "awa");
    context.add(&component);
    context.show();
    return app.exec();
}