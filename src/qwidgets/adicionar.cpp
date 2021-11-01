#include <qwidgets/adicionar.hpp>

Adicionar::Adicionar(Categoria categoria, QDialog* pai)
    : QDialog(pai), _categoria(categoria) {
    _grid = new QGridLayout(this);

    auto* nomeLabel = new QLabel("Nome: ", this);
    _nome = new QLineEdit("", this);

    auto* adi = new QPushButton("Adicionar", this);
    auto* can = new QPushButton("Cancelar", this);

    _grid->addWidget(nomeLabel, 0, 0);
    _grid->addWidget(_nome, 0, 1);
    _grid->addWidget(adi, 2, 0);
    _grid->addWidget(can, 2, 1);

    connect(adi, &QPushButton::clicked, this, &Adicionar::adicionar);
    connect(can, &QPushButton::clicked, this, &Adicionar::cancelar);

    if (categoria == filme) {
        auto* mais = new QPushButton("+", this);
        _grid->addWidget(mais, _grid->rowCount() - 2, 0, 1, 2);
        connect(mais, &QPushButton::clicked, this,
                &Adicionar::adicionarDiretor);
    }
}

void Adicionar::adicionarDiretor() {
    auto widMais = _grid->itemAtPosition(_grid->rowCount() - 2, 0)->widget();
    _grid->removeWidget(widMais);
    delete widMais;

    auto widAdi = _grid->itemAtPosition(_grid->rowCount() - 1, 0)->widget();
    _grid->removeWidget(widAdi);
    delete widAdi;

    auto widCan = _grid->itemAtPosition(_grid->rowCount() - 1, 1)->widget();
    _grid->removeWidget(widCan);
    delete widCan;

    auto* diretorLabel = new QLabel("Diretor (id): ", this);
    auto idLine = new QLineEdit("", this);
    idLine->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), idLine));
    _grid->addWidget(diretorLabel, _grid->rowCount(), 0);
    _grid->addWidget(idLine, _grid->rowCount() - 1, 1);

    _idDiretores.push_back(idLine);

    auto* mais = new QPushButton("+", this);
    _grid->addWidget(mais, _grid->rowCount(), 0, 1, 2);
    connect(mais, &QPushButton::clicked, this, &Adicionar::adicionarDiretor);

    auto* adi = new QPushButton("Adicionar", this);
    auto* can = new QPushButton("Cancelar", this);

    _grid->addWidget(adi, _grid->rowCount(), 0);
    _grid->addWidget(can, _grid->rowCount() - 1, 1);

    connect(adi, &QPushButton::clicked, this, &Adicionar::adicionar);
    connect(can, &QPushButton::clicked, this, &Adicionar::cancelar);
}

void Adicionar::adicionar() {
    _confirmadoSenaoCancelado = true;
    this->close();
}

void Adicionar::cancelar() {
    _confirmadoSenaoCancelado = false;
    this->close();
}

variant Adicionar::recuperarDado() {
    assert(_categoria != nulo);
    variant dado;
    if (_categoria == filme) {
        std::string nome = _nome->text().toStdString();
        std::vector<ushort> ids;
        for (const auto id : _idDiretores) {
            ids.push_back(id->text().toUShort());
        }
        Filme filme(nome, ids);
        dado = filme;
    } else {
        dado = _nome->text().toStdString();
    }
    return dado;
}