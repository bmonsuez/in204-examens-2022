## Définition d'une sous-vue d'une vue

### Présentation du problème

Il est parfaitement possible d'écrire le code suivant :

```cpp
    std::array<std::string, 7> towns = {
         "Paris", "Londres", "Bruxelles", 
         "Lisbonne", "Madrid", "Berlin", "Rome"};

    view<std::array<std::string, 7>> large_set_of_towns(towns, 1, 5);
    view<view<std::array<std::string, 7>>> small_set_of_towns(large_set_of_towns, 2, 4);
```

Si nous considérons l'utilisation des fonctions **factory** [`create_view`](slices.md), l'écriture est nettement simplifiée puisque nous pouvons écrire le code suivant :

```cpp
    std::array<std::string, 7> towns = {
         "Paris", "Londres", "Bruxelles", 
         "Lisbonne", "Madrid", "Berlin", "Rome"};
    auto large_set_of_towns = create_view(towns, 1, 5);
    auto small_set_of_towns = create_view(large_set_of_towns, 2, 4);
```

Cette écriture est nettement plus naturelle que l'écriture précédente. Cependant, nous constatons une problème. En effet, nous avons notre deuxième vue `small_set_of_towns` fait référence à la première vue `large_set_of_towns` qui elle-même fait référence au containeur `towns`. Cependant, la seconde vue n'est qu'une vue du second containeur en plus réduit. De ce fait, la deuxième vue `small_set_of_towns` pourrait ne pas faire référence à la première vue `large_set_of_towns` mais directement au containeur `towns`.

### Solution

Nous pouvons surcharger la définition des fonctions `create_view` avec une version plus spécialisée. Supposons que nous définission deux versions de la fonction `create_view` tel que suit :

```cpp
template<class containerT>
view<containerT> create_view(containerT& container, int first_index, int last_index)
{
    return view<containerT>(container, first_index, last_index);
}

```cpp
template<class containerT>
view<containerT> create_view(view<containerT>& base_view, 
    int first_index, int last_index)
{
    auto base_index = base_view.get_first_index();
    return view<containerT>(base_view.get_container(), 
        first_index + base_index, last_index + base_index);
}
```

La seconde surcharge de la fonction est spécifique aux objets de types `view<containerT>`. Cette seconde surcharge ne crée pas une vue qui fait référence à la vue passée en argument mais une vue qui fait référence au containeur. Comment le compilateur va-t-il savoir que c'est la seconde et non pas la première surcharge qu'il doit utilisée en présence d'un objet de type `view<containerT>` ? Il ne faut pas oublier que le compilateur sélectionne toujours la surcharge la plus spécialisée, ie. celle qui est le plus proche du type de l'argument, en l'état `view<containerT>` est plus spécialisé que `containerT` qui peut-être n'importer quoi. En conséquence, le compilateur sélectionnera si l'objet est un argument de type `view<containerT>` toujours la seconde surcharge.

En conséquence, le code suivant :

```cpp
    std::array<std::string, 7> towns = {
         "Paris", "Londres", "Bruxelles", 
         "Lisbonne", "Madrid", "Berlin", "Rome"};
    auto large_set_of_towns = create_view(towns, 1, 5);
    auto small_set_of_towns = create_view(large_set_of_towns, 2, 4);
    std::cout << "Make reference to 'town'" << std::is_same_type<decltype(small_set_of_towns), view<std::array<std::string, 7>>> << std::endl;
```

retourne bien true pour les deux vues : `large_set_of_towns` and `small_set_of_towns`.

