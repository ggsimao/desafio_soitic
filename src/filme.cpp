#include <filme.hpp>

Filme::Filme() {
    this->_nome = "";
    this->_idDiretores = std::vector<ushort>();
}

std::vector<ushort> Filme::idDiretores() { return this->_idDiretores; }

std::string Filme::nome() { return this->_nome; }