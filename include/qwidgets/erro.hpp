#pragma once

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <string>

class Erro : public QDialog {
   public:
    Erro(std::string mensagem, QDialog* pai = nullptr);
};