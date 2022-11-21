## 4. Containeur

Nous souhaitons que la classe `view` soit un containeur. Nous rappellons rapidement les types et comportements que doit définir un containeur :

| Type | Description |
|------|-------------|
`value_type` | Type des valeurs stockées dans le containeur  (T) |
`reference`  | Type référence des valeurs stockées dans le containeur (T&) |
`const_reference`  | Type référence non modifiable des valeurs stockées dans le containeur (const T&) |
`iterator` | Itérateur référençant les valeurs stockées dans le containeur et autorisant la modification de celles-ci |
`const_iterator` | Itérateur référençant les valeurs stockées dans le containeur mais ne permettant pas de modifier le contenu du containeur. |
`size_type` | Type permettant d'exprimer le nombre d'éléments stockés dans le containeur (unsigned long) |

| Expression | Type de retour | Description |
|------------|----------------|-------------|
| `c.begin()` | `(const_)iterator` | Itérateur référençant le premier élément stocké dans le containeur |
| `c.end()` | `(const_)iterator` | Itérateur référençant l'élément dénotant que la fin de la séquence |
| `c.empty()` | `bool` | Aucun élément dans le containeur |
| `c.size()` | `size_type` | Nombre d'éléments dans le containeur. |

### Question 4.1

Nous souhaitons simplifier l'écriture et ne pas avoir à systématiquement recopier notre containeur d'origine qui est `std::vector<int>`, surtout que nous allons prochainement généraliser la classe à d'autres containeurs. Pour ce faire, nous souhaitons que la classe `view` expose un alias de type public qui se dénomme : `container`. Définissez ce type dans la classe `view` afin qu'il désigne le type `std::vector<int>`. 

Remplacer ensuite toutes les références à `std::vector<int>` par une référence à l'alias de type `container`.

**Rappel**: Pour définir un alias de type dans une classe, par exemple dans une classe `number` un type `float_type` qui est égal à `double` comme suit:

```cpp
class number:
{
public:
    using float_type = double;

    float_type zero() const { return 0.0; }
};
```

___

**Correction**:

Il suffit de définir le type `container` comme :

```cpp
class view:
{
public:
    using container = std::vector<int>;
private:
    ...
};
```

et ensuite de remplacer toutes les occurrences de `std::vector<int>` dans la classe `view` par l'alias de type `container`, ce qui nous donne le code suivant :

```cpp
class view
{
public:
    using container=std::vector<int>;

private:
    container& m_container;
    int m_first_index;
    int m_last_index;

public:

    explicit view(container& container):
        view(container, 0, (int)container.size()-1)
        {}
    view(container& container, 
        int first_index, int last_index):
        m_container(container),
        m_first_index(first_index),
        m_last_index(last_index)
    {}

    view(const view&) = default; 

    int get_first_index() const { return m_first_index; }
    int get_last_index() const { return m_last_index; }
    container& get_container() const { return m_container; }

    bool operator == (const view& another_view) const
    { ... }
    bool operator != (const view& another_view) const
    { ... }
};
```

___

### Question 4.2

Les types des containeurs sont déjà définis dans le containeur `std::vector<int>`. Ainsi, il est possible de définir le type `value_type` en faisant référence au type `value_type` défini dans `std::vector<int>`.

```cpp
class view
{
public:
    ...
    using value_type = container::value_type;

private:
    container& m_container;
    int m_first_index;
    int m_last_index;
    ...
public:
    ...
};
```

Introduisez l'ensemble des types nécessaires en n'hésitant pas à faire référence aux types présents dans le `std::vector<int>`. Utilisez l'alias `container` en lieu et place de `std::vector<int>`, en effet cela évitera d'avoir à réécrire le code quand on généralisera le type à d'autres containeurs.

___

**Correction**:

Comme l'intégralité des types sont déjà présents dans la classe `std::vector<int>`, il est possible de faire directement référence aux types en définissant de nouveaux alias de types.

```cpp
class view
{
public:
    using container = std::vector<int>;
    using value_type = typename container::value_type;
    using reference = typename container::reference;
    using const_reference = typename container::const_reference;

    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;
    using size_type = typename container::size_type;

private:
    container& m_container;
    int m_first_index;
    int m_last_index;
    ...
public:
    ...
};
```
___

### Question 4.3

Maintenant que les alias de types sont définis nous pouvons générer les méthodes que doit implanter un containeur tel que définit précédemment. Commencer par définir les méthodes `empty()` et `size()`.

Ensuite proposer une écriture des méthodes `begin()` et `end()`. (Ne pas oublier que le containeur peut-être accessible en lecture ou en lecture et en écriture.)

___

**Correction**:

Nous débutons par les méthodes `empty()` et `size()` qui sont les plus simples. Le nombre d'éléments dans la vue `[first_index , last_index]` est égal à `last_index - first_index + 1`. Nous constatons que si la vue est vide, `last_index == first_index - 1`. Ce qui nous définit la condition pour tester si la vue contient des éléments ou aucun élément.

```cpp
class view
{
    ...
public:
    ...
    bool empty() const { return m_last_index < m_first_index; }
    size_type size() const { return (size_type)(m_last_index + 1 - m_first_index); }
    ...
};
```

La méthode `begin` retourne l'itérateur sur le premier élément de la séquence, soit l'élément ayant pour indice `first_index`. Il suffit donc d'avancer l'itérateur de début renvoyé par le containeur `m_container` par l'indice `first_index`.

```cpp
class view
{
    ...
public:
    ...
    iterator begin() { return m_container.begin() + m_first_index; }
};
```

Attention, **la vue peut-être déclarée constante**, dans ce cas, elle ne peut pas autoriser de **modification du contenu de la vue (ou plus exactement du containeur référencé par la vue)**, il faudra donc retourner non pas un `iterator` mais un `const_iterator`.

```cpp
class view
{
    ...
public:
    ...
    iterator begin() { return m_container.begin() + m_first_index; }
    const_iterator begin() const { return m_container.begin() + m_first_index; }
};
```

Pour la méthode `end`, celle-ci doit retourner l'itérateur marquant la fin de la séquence, c'est-à-dire l'itérateur qui est obtenu après l'itérateur référençant le dernier élément de la vue. L'itérateur référençant le dernier élément de la vue est l'itérateur de début renvoyé par le containeur `m_container` augmenté de l'indice `last_index`. L'itérateur suivant est celui obtenu en incrémentant une fois de plus le précédent itérateur.

```cpp
class view
{
    ...
public:
    ...
    iterator end() { return m_container.begin() + m_last_index + 1; }
    const_iterator end() const { return m_container.begin() + m_last_index + 1; }
};
```

___

### Compléments

En fait, les types et méthodes que nous avons définis ne forment qu'un sous-ensemble des méthodes et types que doivent fournir un containeur. La liste complète des méthodes et types que doit définir un containeur est défini sur la page [C++ named requirements: Container](https://en.cppreference.com/w/cpp/named_req/Container).

Nous constatons qu'il manque la définition du type `difference_type`, les fonctions `a.swap(b)`, `swap(a, b)`et enfin `a.max_size()`. L'implantation de ces types et méthodes ne posent pas de problèmes :

```cpp
class view
{
public:
    ...
    using difference_type = typename container::difference_type;
    ...
public:
    size_type max_size() const { return size(); }    
    void swap(view& another_view)
    {
        std::swap(m_container, another_view.m_container);
        std::swap(m_first_index, another_view.m_first_index);
        std::swap(m_last_index, another_view.m_last_index);
    }
};

namespace std
{
    void swap(view& first_view, view& second_view)
    {
        first_view.swap(second_view);
    }
}

```

Cependant, l'implantation de certaines exigences peut poser problème, comme notamment le fait qu'un constructeur par défaut doit être fourni, ce qui n'a pas de sens, sauf à accepter que l'on puisse créer un containeur vide quand on crée une vue par défaut.

C'est effectivement là où l'on commence à sentir les limites de certaines exigences et la nécessité d'avoir plus de liberté. Il est vrai qu'avec les exigences que nous avons définies, quasiment tous les algorithmes qui manipulent un containeur peuvent être utilisés, mais pas tous, et ce ne sera qu'au moment de la compilation qu'il sera possible de le savoir.
