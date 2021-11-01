#pragma once

#include <assert.h>

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QVBoxLayout>
#include <filme.hpp>
#include <iostream>
#include <locadora.hpp>
#include <string>
#include <variant>
#include <qwidgets/adicionar.hpp>

using variant = std::variant<Filme, std::string>;

class Editar : public QDialog {
   public:
    Editar(Categoria categoria, ushort id, QDialog* pai = nullptr);
    virtual ~Editar(){};

    bool confirmadoSenaoCancelado();
    variant recuperarDado();

   private slots:
    void cancelar();
    void adicionar();
    void adicionarDiretor();

   private:
    bool _confirmadoSenaoCancelado;
    Categoria _categoria;
    std::vector<QLineEdit*> _idDiretores;
    QLineEdit* _nome;
    std::vector<ushort> _idsSalvos;
    std::string _nomeSalvo;
    QGridLayout* _grid;
};