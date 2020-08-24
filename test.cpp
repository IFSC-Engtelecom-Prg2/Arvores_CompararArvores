//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include <libs/arvore.h>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;
using prglib::arvore;

class TesteQuestao: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }

    shared_ptr<arvore<long>> copia(shared_ptr<arvore<long>> a) {
        list<long> l;

        a->listePreOrder(l);
        auto r = new arvore<long>(l);
        return shared_ptr<arvore<long>>(r);
    }

    shared_ptr<arvore<long>> gera_arvore(long size) {
        int n;
        list<long> l;

        while (size-- > 0) {
            l.push_back(rand() % 10000);
        }

        auto a = new arvore<long>(l);
        return shared_ptr<arvore<long>>(a);
    }
};

TEST_F(TesteQuestao, Nulo)
{
    try {
        if (compara_arvores<long>(nullptr, nullptr) != 2) {
            FAIL() << "comparação entre duas arvores nulas deve retornar valor 2";
            return;
        }
        auto a = gera_arvore(10);
        if (compara_arvores<long>(nullptr, a.get()) or compara_arvores<long>(a.get(), nullptr)) {
            FAIL() <<"comparação entre uma árvore nula e outra válida deve retornar 0";
        }

    } catch (...) {
        FAIL() <<"exceção inesperada ao comparar árvores nulas";
    }
}

TEST_F(TesteQuestao, Raiz)
{
    try {
        unique_ptr<arvore<long>> a1(new arvore<long>(10));
        unique_ptr<arvore<long>> a2(new arvore<long>(5));
        unique_ptr<arvore<long>> a3(new arvore<long>(5));
        auto a4 = gera_arvore(2);

        int r = compara_arvores<long>(a1.get(), a2.get());
        if (r != 0) {
            FAIL() <<"comparação entre duas arvores diferentes deve retornar 0, mas sua função retornou "+to_string(r);
            return;
        }

        r = compara_arvores<long>(a2.get(), a3.get());
        if (r != 2) {
            FAIL() <<"comparação entre duas arvores idênticas deve retornar 2, mas sua função retornou "+to_string(r);
            return;
        }

        r = compara_arvores<long>(a1.get(), a4.get());
        if (r > 0) {
            FAIL() <<"comparação entre duas arvores com topologias diferentes deve ser false";
            return;
        }
    } catch (...) {
        FAIL() <<"exceção inesperada ao comparar árvores";
    }
}

TEST_F(TesteQuestao, Normal)
{
    auto a1 = gera_arvore(50);
    auto a2 = gera_arvore(50);
    auto a3 = copia(a1);

    try {
        int r = compara_arvores<long>(a1.get(), a2.get());
        if (r > 0) {
            FAIL() <<"comparação entre duas arvores diferentes deve ser 0, mas sua função retornou "+to_string(r);
            return;
        }

        r = compara_arvores<long>(a1.get(), a3.get());
        if (r != 2) {
            FAIL() <<"comparação entre duas arvores idênticas deve ser 2, mas sua função retornou "+to_string(r);
            return;
        }

        auto a = a3->balanceia();
        r = compara_arvores<long>(a1.get(), a);
        if (r != 1) {
            FAIL() <<"comparação entre duas arvores com mesmos valores, mas topologias diferentes, deve ser 1, mas sua função retornou "+to_string(r);
            return;
        }
    } catch (...) {
        FAIL() <<"exceção inesperada ao comparar árvores";
    }
}

TEST_F(TesteQuestao, Degenerada)
{
    auto a1 = gera_arvore(50);
    list<long> l;

    a1->listeInOrder(l);
    auto a2 = shared_ptr<arvore<long>>(new arvore<long>(l));
    auto a3 = copia(a2);

    try {
        int r = compara_arvores<long>(a1.get(), a2.get());
        if (r != 1) {
            FAIL() <<"comparação entre duas arvores com mesmos valores, mas topologias diferentes, deve ser 1, mas sua função retornou "+to_string(r);
            return;
        }

        r = compara_arvores<long>(a2.get(), a3.get());
        if (r != 2) {
            FAIL() <<"comparação entre duas arvores idênticas, mesmo que degeneradas, deve ser 2, mas sua função retornou "+to_string(r);
            return;
        }

        auto a = a3->balanceia();
        r = compara_arvores<long>(a2.get(), a);
        if (r != 1) {
            FAIL() <<"comparação entre duas arvores com mesmos valores, mas topologias diferentes, deve ser 1, mas sua função retornou "+to_string(r);
            return;
        }
    } catch (...) {
        FAIL() <<"exceção inesperada ao comparar árvores";
    }
}

