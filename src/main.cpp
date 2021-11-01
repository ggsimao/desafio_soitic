#include <QApplication>
#include <QWidget>
#include <qwidgets/principal.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Principal janela;

    janela.setWindowTitle("Sistema de Locadora");
    janela.setGeometry(500, 500, 200, 200);
    janela.show();

    return app.exec();
}