#include <filme.hpp>

Filme::Filme() {
    _nome = "";
    _idDiretores = std::set<ushort>();
}

Filme::Filme(std::string nome) : _nome(nome) {
    _idDiretores = std::set<ushort>();
}

Filme::Filme(std::string nome, ushort idDiretores...) : _nome(nome) {
    _idDiretores.insert(idDiretores);
}

Filme::Filme(std::string nome, std::vector<ushort> idDiretores) : _nome(nome) {
    for (const auto id : idDiretores) {
        _idDiretores.insert(id);
    }
}

Filme::Filme(std::string nome, std::set<ushort> idDiretores)
    : _nome(nome), _idDiretores(idDiretores) {}

std::set<ushort> Filme::idDiretores() { return _idDiretores; }

std::string Filme::nome() { return _nome; }