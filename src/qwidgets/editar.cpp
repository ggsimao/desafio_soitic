#include <qwidgets/editar.hpp>

Editar::Editar(Categoria categoria, ushort id, QDialog* pai)
    : QDialog(pai), _categoria(categoria) {
    _grid = new QGridLayout(this);

    auto* nomeLabel = new QLabel("Nome: ", this);

    if (categoria == filme) {
        Filme filme = Locadora::buscarFilme(id);
        _nome = new QLineEdit(QString::fromStdString(filme.nome()), this);
        _grid->addWidget(nomeLabel, 0, 0);
        _grid->addWidget(_nome, 0, 1);

        std::set<ushort> idDiretores = filme.idDiretores();

        for (const auto id : idDiretores) {
            auto* diretorLabel = new QLabel("Diretor (id): ", this);
            auto* idLine = new QLineEdit(
                QString::fromStdString(Locadora::buscarDiretor(id)), this);
            _grid->addWidget(diretorLabel, _grid->rowCount(), 0);
            _grid->addWidget(idLine, _grid->rowCount() - 1, 1);
            idLine->setValidator(
                new QRegExpValidator(QRegExp("[0-9]*"), idLine));

            _idDiretores.push_back(idLine);
        }

        auto* mais = new QPushButton("+", this);
        _grid->addWidget(mais, _grid->rowCount(), 0, 1, 2);
        connect(mais, &QPushButton::clicked, this, &Editar::adicionarDiretor);

    } else {
        _nome = new QLineEdit(
            QString::fromStdString(Locadora::buscarDiretor(id)), this);
        _grid->addWidget(nomeLabel, 0, 0);
        _grid->addWidget(_nome, 0, 1);
    }
    auto* adi = new QPushButton("Editar", this);
    auto* can = new QPushButton("Cancelar", this);

    _grid->addWidget(adi, _grid->rowCount(), 0);
    _grid->addWidget(can, _grid->rowCount() - 1, 1);

    connect(adi, &QPushButton::clicked, this, &Editar::adicionar);
    connect(can, &QPushButton::clicked, this, &Editar::cancelar);
}

void Editar::adicionarDiretor() {
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
    auto* idLine = new QLineEdit("", this);
    idLine->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), idLine));
    _grid->addWidget(diretorLabel, _grid->rowCount(), 0);
    _grid->addWidget(idLine, _grid->rowCount() - 1, 1);

    _idDiretores.push_back(idLine);

    auto* mais = new QPushButton("+", this);
    _grid->addWidget(mais, _grid->rowCount(), 0, 1, 2);
    connect(mais, &QPushButton::clicked, this, &Editar::adicionarDiretor);

    auto* adi = new QPushButton("Editar", this);
    auto* can = new QPushButton("Cancelar", this);

    _grid->addWidget(adi, _grid->rowCount(), 0);
    _grid->addWidget(can, _grid->rowCount() - 1, 1);

    connect(adi, &QPushButton::clicked, this, &Editar::adicionar);
    connect(can, &QPushButton::clicked, this, &Editar::cancelar);
}

void Editar::adicionar() {
    _nomeSalvo = _nome->text().toStdString();
    for (const auto id : _idDiretores) {
        _idsSalvos.push_back(id->text().toUShort());
    }
    _confirmadoSenaoCancelado = true;
    this->close();
}

void Editar::cancelar() {
    _confirmadoSenaoCancelado = false;
    this->close();
}

variant Editar::recuperarDado() {
    assert(_categoria != nulo);
    variant dado;
    if (_categoria == filme) {
        Filme filme(_nomeSalvo, _idsSalvos);
        dado = filme;
    } else {
        dado = _nomeSalvo;
    }
    return dado;
}

bool Editar::confirmadoSenaoCancelado() { return _confirmadoSenaoCancelado; }