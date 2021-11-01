#include <locadora.hpp>

ushort Locadora::_idFilmeAtual = 0;
ushort Locadora::_idDiretorAtual = 0;
MapDiretores Locadora::_diretores = MapDiretores();
MapFilmes Locadora::_filmes = MapFilmes();

void Locadora::adicionarFilme(Filme filme) {
    Locadora::_filmes.insert(FilmeValor(Locadora::_idFilmeAtual++, filme));
}

void Locadora::adicionarDiretor(std::string diretor) {
    Locadora::_diretores.insert(
        DiretorValor(Locadora::_idDiretorAtual++, diretor));
}

void Locadora::editarFilme(ushort idFilme, Filme filmeAtualizado) {
    Locadora::_filmes.at(idFilme) = filmeAtualizado;
}

void Locadora::editarDiretor(ushort idDiretor, std::string diretorAtualizado) {
    Locadora::_diretores.at(idDiretor) = diretorAtualizado;
}

void Locadora::removerFilme(ushort idFilme) {
    Locadora::_filmes.at(
        idFilme);  // exceção se id inválido, mesma complexidade do find
    Locadora::_filmes.erase(idFilme);
}

void Locadora::removerDiretor(ushort idDiretor) {
    Locadora::_diretores.at(
        idDiretor);  // exceção se id inválido, mesma complexidade do find
    Locadora::_diretores.erase(idDiretor);
}

Filme Locadora::buscarFilme(ushort idFilme) {
    return Locadora::_filmes.at(idFilme);
}

std::string Locadora::buscarDiretor(ushort idDiretor) {
    return Locadora::_diretores.at(idDiretor);
}

std::vector<FilmeValor> Locadora::buscarTodosFilmes() {
    std::vector<FilmeValor> todosOsFilmes;
    for (const auto& f : Locadora::_filmes) {
        auto valor = FilmeValor(f.first, f.second);
        todosOsFilmes.push_back(valor);
    }
    return todosOsFilmes;
}

std::vector<DiretorValor> Locadora::buscarTodosDiretores() {
    std::vector<DiretorValor> todosOsDiretores;
    for (const auto& d : Locadora::_diretores) {
        auto valor = DiretorValor(d.first, d.second);
        todosOsDiretores.push_back(valor);
    }
    return todosOsDiretores;
}