#pragma once

#include <filme.hpp>
#include <map>
#include <stdexcept>
#include <string>

using ushort = unsigned short;
using MapFilmes = std::map<ushort, Filme>;
using MapDiretores = std::map<ushort, std::string>;
using FilmeValor = std::pair<ushort, Filme>;
using DiretorValor = std::pair<ushort, std::string>;

class Locadora {
   public:
    Locadora() = delete;
    ~Locadora() = delete;
    Locadora(const Locadora&) = delete;
    Locadora(const Locadora&&) = delete;
    Locadora& operator=(const Locadora&) = delete;
    Locadora& operator=(const Locadora&&) = delete;

    static void adicionarFilme(Filme filme);
    static void adicionarDiretor(std::string diretor);

    static void editarFilme(ushort idFilme, Filme filmeAtualizado);
    static void editarDiretor(ushort idDiretor, std::string diretorAtualizado);

    static void removerFilme(ushort idFilme);
    static void removerDiretor(ushort idDiretor);

    static Filme buscarFilme(ushort idFilme);
    static std::string buscarDiretor(ushort idDiretor);

    static std::vector<FilmeValor> buscarTodosFilmes();
    static std::vector<DiretorValor> buscarTodosDiretores();

   private:
    static ushort _idFilmeAtual;
    static ushort _idDiretorAtual;
    static MapDiretores _diretores;
    static MapFilmes _filmes;
};