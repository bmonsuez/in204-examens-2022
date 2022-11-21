## 6. Exceptions

Le constructeur de la classe `view`:

```cpp
    view(container& container, int first_index, int second_index) ```
```

ne génère aucune erreur si jamais `first_index` est inférieur à zéro ou plus grand que l'indice du dernier élément dans le containeur. L'erreur se produira quand l'on essayera d'accéder aux itérateurs. Il en va de même pour `last_index` qui peut accepter une valeur inférieure à zéro, plus grande que l'indice du dernier élément dans le containeur ou plus petite que le premier indice `first_index`. Nous souhaitons détecter ces cas d'erreur et générer une exception `std::out_of_range` pour signaler l'erreur d'initialisation de la classe.

### Question 6.1

Modifier le constructeur pour qu'il vérifie la validité des indices `first_index` et `last_index`. Si les indices ne sont pas valides, il génère une exception de type `std::out_of_range`.

***Conseil***: la méthode `size` d'un containeur retourne le nombre d'éléments dans le containeur.

___
**Correction**:

En fait, `first_index` et `last_index` doivent être compris entre $0$ et le nombre d'éléments dans le containeur, soit `m_container.size() - 1`.

De plus `last_index == first_index - 1` si la vue est vide, sinon `last_index >= first_index` s'il y a au moins un élément dans la vue.

Ceci permet d'avoir le code suivant :

```cpp
    view(container& container, int first_index, int last_index):
        m_container(container), m_first_index(first_index), m_last_index(last_index)
    {
        if(m_first_index < 0 || m_first_index >= m_container.size())
            throw std::out_of_range("first index is out of range");
        if(m_last_index < 0 || m_last_index >= m_container.size())
            throw std::out_of_range("last index is out of range");
        if(m_last_index < m_first_index - 1)
            throw std::out_of_range("last index is located before first index");
    }
```

Dans le code proposé en correction, il est proposé d'utiliser la fonction `std::format`qui est désormais supporté par certains compilateurs qui offre une alternative à `printf` de C tout en n'en ayant pas les défauts. Ceci donne le code suivant :

```cpp
    view(container& container, 
        int first_index, int last_index):
        m_container(container),
        m_first_index(first_index),
        m_last_index(last_index)
    {
        if(m_first_index < 0 || m_first_index >= m_container.size())
            throw std::out_of_range(
                std::format("first index is expected to be inside [0..{}]: Got: {}" 
                m_container.size(), m_first_index));
        if(m_last_index < 0 || m_last_index >= m_container.size())
            throw std::out_of_range(
                std::format("last index is expected to be inside [0..{}]: Got: {}" 
                m_container.size(), m_last_index));
        if(m_last_index < m_first_index - 1)
            throw std::out_of_range(
                std::format("last index is expected to be greater than first index {}: Got: {}" 
                m_first_index, m_last_index));
    }
```

___
