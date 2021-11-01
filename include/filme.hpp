#pragma once

#include <set>
#include <string>
#include <vector>

using ushort = unsigned short;

class Filme {
   public:
    Filme();
    Filme(std::string nome);
    Filme(std::string nome, ushort idDiretores...);
    Filme(std::string nome, std::vector<ushort> idDiretores);
    Filme(std::string nome, std::set<ushort> idDiretores);
    ~Filme(){};

    std::set<ushort> idDiretores();
    std::string nome();

   private:
    std::set<ushort> _idDiretores;
    std::string _nome;
};