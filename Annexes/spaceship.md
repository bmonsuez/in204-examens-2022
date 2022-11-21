## C. L'opérateur généralisé de comparison `<=>` dit spaceship operator ?

### Présentation du problème

Si nous souhaitons implanter les opérations de comparaison, nous devons implanter l'ensemble des 6 opérateurs des comparaison :

```cpp
class comparable
{
public:
    bool operator == (const comparable&) const;
    bool operator != (const comparable&) const;

    bool operator <= (const comparable&) const;
    bool operator < (const comparable&) const;

    bool operator >= (const comparable&) const;
    bool operator > (const comparable&) const;
};
```

Cette écriture est redondante, peut générer des erreurs, nous n'avons aucune garantie que :

* `a < b` est vrai impose que `a > b` !

De plus, il n'existe pas de support pour les ordres partiels. Le seul moyen serait de dire que deux éléments ne sont pas comparables si et seulement si :

* `a <= b` est faux et `a >= b` est faux !

Ce qui n'est pas très satisfaisant.

### Solution du problème

C++20 introduit un nouvel opérateur de comparaison : 

```cpp
class comparable
{
public:
    std::strong_ordering operator <=>(const comparable&);
};
```

Cet opérateur permet de définir trois types d'ordre entre les éléments :

* un ordre total, dans ce cas l'opérateur `operator <=>` retourne une valeur ayant pour type  [`std::strong_ordering`](https://en.cppreference.com/w/cpp/header/strong_ordering),
* un ordre total mais où deux éléments égaux (on dira que les deux éléments sont équivalents) peuvent cependant être différents, dans ce cas l'opérateur `operator <=>` retourne une valeur ayant pour type [`std::weak_ordering`](https://en.cppreference.com/w/cpp/header/weak_ordering). Typiquement, un opérateur de comparaison qui ne tient pas compte des majuscules ou minuscules introduit un tel ordre.
* un ordre partiel, il existe des éléments qui ne sont pas comparables, dans ce cas l'opérateur `operator <=>` retourne une valeur ayant pour type  [`std::partial_ordering`](https://en.cppreference.com/w/cpp/header/partial_ordering). L'inclusion dans les ensembles introduit un tel ordre partiel.
  
En fait, cet opérateur remplace l'ensemble des 6 opérateurs précédents. Il n'est plus nécessaire d'écrire les 6 opérateurs. 

```cpp
    bool operator == (const comparable&) const;
    bool operator != (const comparable&) const;

    bool operator <= (const comparable&) const;
    bool operator < (const comparable&) const;

    bool operator >= (const comparable&) const;
    bool operator > (const comparable&) const;
```

Il suffit d'écrire le seul opérateur :

```cpp
    std::strong_ordering operator <=>(const comparable&);
```

Dans certains cas, il peut être cependant intéressant d'écrire l'opérateur testant l'égalité ou l'inégalité si l'implantation est beaucoup plus rapide. Attention cependant à ce que : `a <=> b == std::partial|weak|strong_ordering::equivalent` est équivalent à `a == b`.

Nous pouvons désormais écrire une opération de comparaison générique qui nous permet de savoir si une vue dénote une sous-vue d'une autre vue. Pour ce faire, il suffira de déterminer si les deux vues font référence au même containeur et si l'interval de l'une des vues est égal ou est inclut dans l'intervale de l'autre vue.

Ceci pour s'exprimer par le code suivant :

```cpp
template<class containerT>
class view
{
    ...
    // Spaceship operator
    std::partial_ordering operator <=> (const view<containerT>& another_view) const
    {
        if(m_container != another_view.m_container)
            return std::partial_ordering::unordered;
        if(m_first_index < another_view.m_first_index)
        {
            return m_last_index >= another_view.m_last_index ? 
                std::partial_ordering::greater:
                std::partial_ordering::unordered;
        }
        if(m_first_index == another_view.m_first_index)
        {
            return m_last_index == another_view.m_last_index ? 
                std::partial_ordering::equivalent:
                m_last_index > another_view.m_last_index ? 
                    std::partial_ordering::greater :
                    std::partial_ordering::less;
        }
        return m_last_index <= another_view.m_last_index ? 
            std::partial_ordering::less:
            std::partial_ordering::unordered;
    }
};
```

Il est désormais possible d'utiliser n'importe quel opérateur `<`, `<=`, `>`, `>=` avec des vues, le code appellera l'opérateur `<=>` pour déterminer si la vue est incluse dans une autre vue. De même il est possible d'utiliser directement l'opérateur `<=>` par exemple pour déterminer si deux vues sont comparables :

```cpp
    auto large_set_of_towns = create_view(towns, 1, 5);
    auto another_set_of_towns = create_view(towns, 0, 3);
    if((large_set_of_towns <=>another_set_of_towns ) != std::partial_ordering::unordered)
        std::cout << "Both views are comparable\n";
```




