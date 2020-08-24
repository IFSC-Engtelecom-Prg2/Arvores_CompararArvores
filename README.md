Escreva uma função que compare duas árvores de pesquisa binárias. Essa função deve retornar o seguinte:

* **2**: se as árvores forem idênticas (possuirem os mesmos valores e tiverem a mesma topologia)
* **1**: se as árvores possuirem os mesmos valores, porém topologias diferentes
* **0**: se as árvores não possuirem o mesmo conteúdo

Essa função está declarada assim em _questao.h_:

```c++
template <typename T> int compara_arvores(arvore<T> * a1, arvore<T> * a2);
```