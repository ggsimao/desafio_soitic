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
#include <string>
#include <variant>

using variant = std::variant<Filme, std::string>;

enum Categoria { nulo, filme, diretor };

class Adicionar : public QDialog {
   public:
    Adicionar(Categoria categoria, QDialog* pai = nullptr);
    virtual ~Adicionar(){};

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