## 5. Patrons

La classe `view` est définie pour un containeur de type `std::vector<int>`. Cependant, cette classe peut aussi fonctionner avec un  containeur de type `std::vector<float>` ou même un `std::array<std::string>`.

### Question 5.1

Transformer la classe `view` en la paramétrant par le type du containeur qui stocke les éléments qui sont accédés par la classe `view`.

Pour rappel, le squelette de la classe est le suivant :

```cpp
class view
{
public:
    [ Définition du type container]
    ...
    using value_type = container::value_type;
    [ Définition des types iterator, const_iterator, size_type]
    ... 
private:
    container& m_container;
    int m_first_index;
    int m_last_index;

public:

    explicit view(container& vector);
    view(container& vector, int first_index, int last_index);
    ...
};
```

___

**Correction**:

En fait, l'intégralité du travail a déjà été fait dans la partie précédente, nous avons défini le type `container` comme étant un alias du type `std::vector<int>`. Si nous voulons désormais utiliser un autre type de containeur, il suffit de paramètrer la classe par le type de containeur que nous souhaitons et le l'alias de type `container` fait désormais référence au paramètre de type.

```cpp
template<typename containerT>
class view
{
public:
    using container=containerT; // C'est la seule modification à réaliser !
};
```

___

### Question 5.2

Dites parmi les définitions suivantes :

* Celles qui sont correctes,
* Celles qui ne compilent pas.

| Instantiation | Compile |
|-------|-------|
`view<std::vector<int>>`||
`view<std::array<int>>`||
`view<std::set<std::string>>`||
`view<int>`||
`view<int*>`||

___

**Correction**:

* `view<std::vector<int>>`: compile parce que `std::vector<int>` est bien un containeur qui supporte un accès indexé.
* `view<std::array<int>>`: compile parce que `std::array<int>` est bien un containeur qui supporte un accès indexé.
* `view<std::set<int>>`: ne compile pas parce que `std::array<int>` est bien un containeur mais ce containeur ne supporte un accès indexé.
* `view<int>`: ne compile pas parce que `int` n'est pas un containeur.
* `view<int*>`: ne compile pas parce que `int*` n'est pas un containeur.

___

### Question 5.3

Nous souhaitons définir en C++20 des contraintes sur le type containeur. Définisser la liste des types ainsi que la liste des fonctions que le containeur doit exposer que l'instantiation se déroule correctement.

Définissez à partir de cela un `concept` dénommé `view_container` qui s'assure que les fonctions sont bien présentes.

Pour vous aider, nous rappelons les fonctions dont vous avez besoin. Le containeur doit fournir les types suivants : `value_type`, `reference`, `const_reference`, `iterator`, `const_iterator`, `size_type`. Ce même containeur doit fournir les fonction `begin` et `end`, ces fonctions doivent retourner `iterator`, le concept associé au random access itérateur est `std::random_access_iterator`. Donc `std::random_access_iterator<iterator>` doit-être vrai.

Nous rappelons la syntaxe des `concept` dans l'exemple suivant qui expose les méthodes pour une valeur entière qui supporte l'addition.

```cpp
template<typename T>
concept addable = requires(T a, T b) 
    // Indique qu'il est possible de créer deux valeurs a & b 
    // ayant comme type T qui seront utilisées dans les clauses
    // suivantes.
{
    typename T::value_type; // Indique que 
        // le type value_type doit être présent dans 
        // la définition de T.
    { a + b } -> std::same_as<value_type>; // Indique que
        // l'expression a + b doit compiler et que la valeur 
        // résultat a pour type value_type.
    { a == b } -> std::convertible_to<bool>; // Indique que
        // l'expression a == b doit compiler et que la valeur 
        // résultat doit être convertible vers une valeur booléene.
    std::is_integral<T::value_type>;
        // indique que le type doit vérifier la contrainte std::is_integral
        // qui indique que le type est un entier.
};
```

___

**Correction**:

Nous souhaitons définir un concept qui s'assure que le containeur puisse bien être utilisé. Ce concept ne vas prendre que le containeur comme paramètre, ce sera le seul argument:

```cpp
template<typename T>
concept view_container = requires 
{

};
```

Pour cela, il faut que le containeur fournisse l'ensemble des types et des méthodes qu'on appelle. La première opération est de faire le recensement dans le code des types et ensuite des méthodes ou opérateurs appellés.

Pour les types, nous avons les types `value_type`, `reference`, `const_reference`, `iterator`, `const_iterator`, `size_type`.

```cpp
template<typename T>
concept view_container = requires
{
    typename T::value_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;
};
```

Ensuite, nous avons quelques contraintes sur les types. `iterator` doit être un random access iterator, cela signifie qu'il doit respecter l'exigence définie par `std::random_access_iterator<>`.

```cpp
template<typename T>
concept view_container = requires
{
    typename T::value_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;

    std::random_access_iterator<T::iterator>;
    std::random_access_iterator<T::const_iterator>;
};
```

Enfin, il faut s'assurer que les méthodes `begin` et `end` sont bien définis et retourne bien un `iterator`. Pour ce faire, nous supposons que `c` désigne une référence sur un containeur ayant comme type `T`, ce qui s'écrit par :

```cpp
template<typename T>
concept view_container = requires(T& c) 
{
...
};
```

et ensuite nous écrivons la clause que nous souhaitons vérifier :

```cpp
    { c.begin() } -> std::same_as<T::iterator>;
```

Ce qui nous donne :

```cpp
template<typename T>
concept view_container = requires(T& c) 
{
    typename T::value_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;

    requires std::random_access_iterator<T::iterator>;
    requires std::random_access_iterator<T::const_iterator>;

    { c.begin() } -> std::same_as<T::iterator>;
    { c.end() } -> std::same_as<T::iterator>;
};
```

Si nous voulons vérifier que quand le containeur est non-modifiable, les méthodes `begin` et `end`  retournent bien un `const_iterator`, il suffit d'ajouter :

* la création d'une référence constante,
* deux clause additionelles pour les méthodes `begin` et `end` appelées désormais pour un objet constant.

```cpp
template<typename T>
concept view_container = requires(T& c, const T& cc) 
{
    typename T::value_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;

    requires std::random_access_iterator<T::iterator>;
    requires std::random_access_iterator<T::const_iterator>;

    { c.begin() } -> std::same_as<T::iterator>;
    { c.end() } -> std::same_as<T::iterator>;

    { cc.begin() } -> std::same_as<T::const_iterator>;
    { cc.end() } -> std::same_as<T::const_iterator>;
};
```

Nous pouvons continuer à ajouter des contraintes. Nous allons utiliser l'opérateur `operator []` ainsi que la méthode `size`. En conséquence nous pouvons ajouter ces contraintes :

```cpp
template<typename T>
concept view_container = requires(T& c, const T& cc) 
{
    typename T::value_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;

    requires std::random_access_iterator<typename T::iterator>;
    requires std::random_access_iterator<typename T::const_iterator>;

    { c.begin() } -> std::same_as<typename T::iterator>;
    { c.end() } -> std::same_as<typename T::iterator>;

    { cc.begin() } -> std::same_as<typename T::const_iterator>;
    { cc.end() } -> std::same_as<typename T::const_iterator>;

    { c[0] } -> std::convertible_to<typename T::reference>;
    { cc[0] } -> std::convertible_to<typename T::value_type>;

    { cc.size() } -> std::convertible_to<typename T::size_type>;
};
```

___