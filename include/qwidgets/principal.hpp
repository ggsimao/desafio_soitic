#pragma once

#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QRegExpValidator>
#include <QTableWidget>
#include <QWidget>
#include <locadora.hpp>
#include <qwidgets/adicionar.hpp>
#include <qwidgets/erro.hpp>

using ushort = unsigned short;

class Principal : public QWidget {
    // Q_OBJECT

   public:
    Principal(QWidget* pai = nullptr);
    virtual ~Principal(){};

   private slots:
    void adicionar();
    void remover();
    void editar();
    void buscar();
    void setIdABuscar();
    void setFilme();
    void setDiretor();

   private:
    std::string nomesDosDiretores(Filme filme);

   private:
    Categoria _categoria = nulo;
    QLineEdit* _idWidget;
    QTableWidget* _tabela;
};