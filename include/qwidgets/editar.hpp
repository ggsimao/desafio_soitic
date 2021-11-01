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

class Editar : public QDialog {
   public:
    Editar(Categoria categoria, QDialog *pai = nullptr);
    virtual ~Editar(){};

    variant recuperarDado();

   private:
    variant _dado;
};