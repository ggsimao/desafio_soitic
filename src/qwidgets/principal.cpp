#include <qwidgets/principal.hpp>

Principal::Principal(QWidget *pai) : QWidget(pai) {
    auto *adi = new QPushButton("Adicionar", this);
    auto *edit = new QPushButton("Editar", this);
    auto *rem = new QPushButton("Remover", this);
    auto *busc = new QPushButton("Buscar", this);
    auto *texto = new QLabel("ID selecionado: ", this);
    auto *opcFilme = new QRadioButton("Filme", this);
    auto *opcDiretor = new QRadioButton("Diretor", this);
    _tabela = new QTableWidget(this);

    _idWidget = new QLineEdit("", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(adi, 0, 0);
    grid->addWidget(edit, 0, 1);
    grid->addWidget(rem, 0, 2);
    grid->addWidget(busc, 0, 3);
    grid->addWidget(texto, 0, 4);
    grid->addWidget(opcFilme, 1, 0);
    grid->addWidget(opcDiretor, 2, 0);
    grid->addWidget(_tabela, 1, 1, 2, 5);

    grid->addWidget(_idWidget, 0, 5);

    connect(adi, &QPushButton::clicked, this, &Principal::adicionar);
    connect(edit, &QPushButton::clicked, this, &Principal::editar);
    connect(rem, &QPushButton::clicked, this, &Principal::remover);
    connect(busc, &QPushButton::clicked, this, &Principal::buscar);
    connect(opcFilme, &QRadioButton::clicked, this, &Principal::setFilme);
    connect(opcDiretor, &QRadioButton::clicked, this, &Principal::setDiretor);

    _tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    _idWidget->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), _idWidget));
}

void Principal::adicionar() {
    _tabela->clear();
    int initialCount = _tabela->rowCount();
    for (int i = 0; i < initialCount; i++) {
        _tabela->removeRow(0);
    }

    if (_categoria == nulo) {
        Erro *janela = new Erro("Escolha o que adicionar.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else {
        Adicionar *janela = new Adicionar(_categoria);
        janela->setGeometry(500, 500, 100, 100);
        janela->setWindowTitle("Adicionar");
        janela->exec();

        switch (_categoria) {
            case filme:
                Locadora::adicionarFilme(
                    std::get<Filme>(janela->recuperarDado()));
                break;
            case diretor:
                Locadora::adicionarDiretor(
                    std::get<std::string>(janela->recuperarDado()));
        }

        delete janela;
    }
}

void Principal::remover() {
    _tabela->clear();
    int initialCount = _tabela->rowCount();
    for (int i = 0; i < initialCount; i++) {
        _tabela->removeRow(0);
    }
    auto texto = _idWidget->text();

    if (texto.isEmpty()) {
        Erro *janela = new Erro("Insira um id.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else if (_categoria == nulo) {
        Erro *janela = new Erro("Escolha o que remover.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else {
        int idABuscar = texto.toInt();
        if (_categoria == filme) {
            try {
                Locadora::removerFilme(idABuscar);
            } catch (std::out_of_range oor) {
                Erro *janela = new Erro("Id inválido!");
                janela->setGeometry(500, 500, 200, 50);
                janela->setWindowTitle("Erro");
                janela->exec();
                delete janela;
            }
        } else {
            try {
                Locadora::removerDiretor(idABuscar);
            } catch (std::out_of_range oor) {
                Erro *janela = new Erro("Id inválido!");
                janela->setGeometry(500, 500, 200, 50);
                janela->setWindowTitle("Erro");
                janela->exec();
                delete janela;
            }
        }
    }
}

void Principal::editar() {
    _tabela->clear();
    int initialCount = _tabela->rowCount();
    for (int i = 0; i < initialCount; i++) {
        _tabela->removeRow(0);
    }
}

void Principal::buscar() {
    _tabela->clear();
    int initialCount = _tabela->rowCount();
    for (int i = 0; i < initialCount; i++) {
        _tabela->removeRow(0);
    }

    auto texto = _idWidget->text();

    if (_categoria == nulo) {
        Erro *janela = new Erro("Escolha o que buscar.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else if (texto.isEmpty()) {
        if (_categoria == filme) {
            std::vector<FilmeValor> listaFilmes = Locadora::buscarTodosFilmes();
            for (int i = 0; i < listaFilmes.size(); i++) {
                Filme filme = listaFilmes[i].second;

                _tabela->insertRow(i);

                _tabela->setItem(
                    i, 0,
                    new QTableWidgetItem(QString::fromStdString(filme.nome())));

                _tabela->setItem(i, 1,
                                 new QTableWidgetItem(QString::fromStdString(
                                     this->nomesDosDiretores(filme))));

                _tabela->setItem(i, 2,
                                 new QTableWidgetItem(
                                     QString::number(listaFilmes[i].first)));
            }
        } else {
            std::vector<DiretorValor> listaDiretores =
                Locadora::buscarTodosDiretores();
            for (int i = 0; i < listaDiretores.size(); i++) {
                std::string diretor = listaDiretores[i].second;

                int linhas = _tabela->rowCount();

                _tabela->insertRow(linhas);

                _tabela->setItem(
                    linhas, 0,
                    new QTableWidgetItem(QString::fromStdString(diretor)));
                _tabela->setItem(linhas, 1,
                                 new QTableWidgetItem(
                                     QString::number(listaDiretores[i].first)));
            }
        }
    } else {
        int idABuscar = texto.toInt();
        if (_categoria == filme) {
            try {
                Filme filme = Locadora::buscarFilme(idABuscar);

                _tabela->setItem(
                    0, 0,
                    new QTableWidgetItem(QString::fromStdString(filme.nome())));

                _tabela->setItem(0, 1,
                                 new QTableWidgetItem(QString::fromStdString(
                                     this->nomesDosDiretores(filme))));

                _tabela->setItem(
                    0, 2, new QTableWidgetItem(QString::number(idABuscar)));
            } catch (std::out_of_range oor) {
                Erro *janela = new Erro("Id inválido!");
                janela->setGeometry(500, 500, 200, 50);
                janela->setWindowTitle("Erro");
                janela->exec();
                delete janela;
            }
        } else {
            try {
                std::string diretor = Locadora::buscarDiretor(idABuscar);

                _tabela->setItem(
                    0, 0,
                    new QTableWidgetItem(QString::fromStdString(diretor)));
                _tabela->setItem(
                    0, 1, new QTableWidgetItem(QString::number(idABuscar)));
            } catch (std::out_of_range oor) {
                Erro *janela = new Erro("Id inválido!");
                janela->setGeometry(500, 500, 200, 50);
                janela->setWindowTitle("Erro");
                janela->exec();
                delete janela;
            }
        }
    }
}

void Principal::setFilme() {
    _tabela->clear();
    int initialCount = _tabela->rowCount();
    for (int i = 0; i < initialCount; i++) {
        _tabela->removeRow(0);
    }

    _categoria = filme;
    _tabela->setColumnCount(3);
    _tabela->setHorizontalHeaderLabels(
        QStringList({"Nome", "Diretores", "Id"}));
}

void Principal::setDiretor() {
    _tabela->clear();
    int initialCount = _tabela->rowCount();
    for (int i = 0; i < initialCount; i++) {
        _tabela->removeRow(0);
    }

    _categoria = diretor;
    _tabela->setColumnCount(2);
    _tabela->setHorizontalHeaderLabels(QStringList({"Nome", "Id"}));
}

std::string Principal::nomesDosDiretores(Filme filme) {
    std::set<ushort> idDiretores = filme.idDiretores();
    if (idDiretores.size() == 0) return "";

    std::string listaDiretores;
    for (auto it = idDiretores.begin(); it != idDiretores.end()--; it++) {
        listaDiretores.insert(0, ", " + Locadora::buscarDiretor(*it));
        // listaDiretores.insert(0, ", " + *it);
    }
    listaDiretores.insert(0,
                          "" + Locadora::buscarDiretor(*(idDiretores.end()--)));

    return listaDiretores;
}