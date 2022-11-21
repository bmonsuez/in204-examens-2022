## A. Pourquoi utiliser une fonction `create_view` ?

### Présentation du problème

Nous avons vu dans le code donné en correction que nous avons déclarons les vues comme suit :

```cpp
    std::vector<int> ints = {1, 2, 3, 4, 5, 6, 7 };
    std::array<std::string, 7> towns = {
         "Paris", "Londres", "Bruxelles", 
         "Lisbonne", "Madrid", "Berlin", "Rome"};
    ...
    view<std::vector<int>> v2(ints, 3, 5);
    print_view(v2);
    view<std::array<std::string, 7>> v3(towns , 3, 5);
    print_view(v3);
```

Ce qui n'est absolument pas satisfaisant puisque l'écriture nécessite de connaître le type du containeur auquel la vue fait référence.

Ce que l'on aimerait avoir, c'est de pouvoir créer une vue et que ce soit la compilateur qui nous fournisse automatiquement le type de la vue.

### Solution

Pour ce faire, nous allons utiliser une fonction qui va fabriquer un objet de type `view`, le type sera déterminé automatiquement en fonction du containeur qui est passé en argument à la fonction `create_view`. Désormais l'entête de la fonction sera de la forme:

```cpp
template<class containerT>
view<containerT> create_view(containerT& container, int first_index, int last_index)
{
    return view<containerT>(container, first_index, last_index);
}
```

Il est désormais possible de réécrire le code précédent en :

```cpp
    std::vector<int> ints = {1, 2, 3, 4, 5, 6, 7 };
    std::array<std::string, 7> towns = {
         "Paris", "Londres", "Bruxelles", 
         "Lisbonne", "Madrid", "Berlin", "Rome"};
    ...
    auto v2 = create_view(ints, 3, 5);
    print_view(v2);
    auto v3 = create_view(towns , 3, 5);
    print_view(v3);
```

Ce qui est nettement plus simple.

Nous ne sommes obligés d'avoir une seule fonction `create_view`, nous pouvons définir plusieurs surcharges :

```cpp
template<class containerT>
view<containerT> create_view(containerT& container)
{
    return view<containerT>(container);
}

template<class containerT>
view<containerT> create_view(containerT& container, int first_index)
{
    return view<containerT>(container, first_index, container.size() - first_index);
}

template<class containerT>
view<containerT> create_view(containerT& container, int first_index, int last_index)
{
    return view<containerT>(container, first_index, last_index);
}
```

Les fonctions `create_view` sont des fonctions **factory** qui simplifient la construction des vues en enlevant une partie de la complexité relative à la détermination des types.
