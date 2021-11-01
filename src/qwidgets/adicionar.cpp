#include <qwidgets/adicionar.hpp>

Adicionar::Adicionar(Categoria categoria, QDialog* pai) : QDialog(pai) {
    auto* grid = new QGridLayout(this);

    auto* nomeLabel = new QLabel("Nome: ", this);
    auto* nomeInput = new QLineEdit("", this);

    auto* mais = new QPushButton("+", this);

    auto* adi = new QPushButton("Adicionar", this);
    auto* can = new QPushButton("Cancelar", this);

    grid->addWidget(nomeLabel, 0, 0);
    grid->addWidget(nomeInput, 0, 1);
    grid->addWidget(mais, 1, 0, 1, 2);
    grid->addWidget(adi, 2, 0);
    grid->addWidget(can, 2, 1);

    // this->setLayout(grid);
}

variant Adicionar::recuperarDado() { return this->_dado; }