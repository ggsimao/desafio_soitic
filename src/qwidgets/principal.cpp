#include <qwidgets/principal.hpp>

Principal::Principal(QWidget *pai) : QWidget(pai) {
    auto *adi = new QPushButton("Adicionar", this);
    auto *edit = new QPushButton("Editar", this);
    auto *rem = new QPushButton("Remover", this);
    auto *busc = new QPushButton("Buscar", this);
    auto *texto = new QLabel("ID selecionado: ", this);
    auto *opcFilme = new QRadioButton("Filme", this);
    auto *opcDiretor = new QRadioButton("Diretor", this);
    this->_tabela = new QTableWidget(this);

    this->_idWidget = new QLineEdit("", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(adi, 0, 0);
    grid->addWidget(edit, 0, 1);
    grid->addWidget(rem, 0, 2);
    grid->addWidget(busc, 0, 3);
    grid->addWidget(texto, 0, 4);
    grid->addWidget(opcFilme, 1, 0);
    grid->addWidget(opcDiretor, 2, 0);
    grid->addWidget(this->_tabela, 1, 1, 2, 5);

    grid->addWidget(this->_idWidget, 0, 5);

    connect(adi, &QPushButton::clicked, this, &Principal::adicionar);
    connect(edit, &QPushButton::clicked, this, &Principal::editar);
    connect(rem, &QPushButton::clicked, this, &Principal::remover);
    connect(busc, &QPushButton::clicked, this, &Principal::buscar);
    connect(opcFilme, &QRadioButton::clicked, this, &Principal::setFilme);
    connect(opcDiretor, &QRadioButton::clicked, this, &Principal::setDiretor);

    this->_tabela->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    this->_idWidget->setValidator(
        new QRegExpValidator(QRegExp("[0-9]*"), this->_idWidget));
}

void Principal::adicionar() {
    Adicionar *janela = new Adicionar(this->_categoria);
    janela->setGeometry(500, 500, 100, 100);
    janela->setWindowTitle("Adicionar");
    janela->exec();
    delete janela;
}

void Principal::remover() {
    auto texto = this->_idWidget->text();

    if (texto.isEmpty()) {
        Erro *janela = new Erro("Insira um id.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else if (this->_categoria == nulo) {
        Erro *janela = new Erro("Escolha o que remover.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else {
        int idABuscar = texto.toInt();
        if (this->_categoria == filme) {
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

void Principal::editar() {}

void Principal::buscar() {
    auto texto = this->_idWidget->text();

    if (this->_categoria == nulo) {
        Erro *janela = new Erro("Escolha o que buscar.");
        janela->setGeometry(500, 500, 200, 50);
        janela->setWindowTitle("Erro");
        janela->exec();
        delete janela;
    } else if (texto.isEmpty()) {
        if (this->_categoria == filme) {
            std::vector<FilmeValor> listaFilmes = Locadora::buscarTodosFilmes();
            for (int i = 0; i < listaFilmes.size(); i++) {
                Filme filme = listaFilmes[i].second;

                this->_tabela->insertRow(i);
                this->_tabela->itemAt(i, 0)->setText(
                    QString::fromStdString(filme.nome()));

                this->_tabela->itemAt(i, 1)->setText(
                    QString::fromStdString(this->nomesDosDiretores(filme)));

                this->_tabela->itemAt(i, 2)->setText(
                    QString::number(listaFilmes[i].first));
                // this->_tabela->itemAt(i, 0)->text() = listaFilmes[i].second;
            }
        } else {
            // try {
            //     Locadora::removerDiretor(idABuscar);
            // } catch (std::out_of_range oor) {
            //     Erro *janela = new Erro("Id inválido!");
            //     janela->setGeometry(500, 500, 200, 50);
            //     janela->setWindowTitle("Erro");
            //     janela->exec();
            //     delete janela;
            // }
        }
    } else {
        int idABuscar = texto.toInt();
        if (this->_categoria == filme) {
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

    this->_tabela;
}

void Principal::setFilme() {
    this->_categoria = filme;
    this->_tabela->setColumnCount(3);
    this->_tabela->setHorizontalHeaderLabels(
        QStringList({"Nome", "Diretores", "Id"}));
}

void Principal::setDiretor() {
    this->_categoria = diretor;
    this->_tabela->setColumnCount(2);
    this->_tabela->setHorizontalHeaderLabels(QStringList({"Nome", "Id"}));
}

std::string Principal::nomesDosDiretores(Filme filme) { return ""; }