#pragma once

#include <string>
#include <vector>

using ushort = unsigned short;

class Filme {
   public:
    Filme();
    Filme(std::string nome);
    Filme(std::string nome, ushort idDiretores...);
    ~Filme(){};

    std::vector<ushort> idDiretores();
    std::string nome();

   private:
    std::vector<ushort> _idDiretores;
    std::string _nome;
};