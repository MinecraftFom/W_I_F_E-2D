#include <QApplication>
#include <render.hpp>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    BorderlessGuiContext context;
    context.show();
    return app.exec();
}