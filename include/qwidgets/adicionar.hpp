#pragma once

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <filme.hpp>
#include <string>
#include <variant>

using variant = std::variant<Filme, std::string>;

enum Categoria { nulo, filme, diretor };

class Adicionar : public QDialog {
   public:
    Adicionar(Categoria categoria, QDialog *pai = nullptr);
    virtual ~Adicionar(){};

    variant recuperarDado();

   private:
    bool _confirmadoSenaoCancelado;
    variant _dado;
};