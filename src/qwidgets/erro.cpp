#include <qwidgets/erro.hpp>

Erro::Erro(std::string mensagem, QDialog* pai) : QDialog(pai) {
    auto* layout = new QVBoxLayout;

    auto* mensagemLabel = new QLabel(QString::fromStdString(mensagem), this);

    layout->addWidget(mensagemLabel, Qt::AlignCenter, Qt::AlignHCenter);

    this->setLayout(layout);
}