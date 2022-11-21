## 1: Définition d'une classe **view** pour un vecteur d'entier [Correction]

Nous considérons dans un premier temps le squelette de classe suivant :

```cpp
#include<vector>

class view
{
private:
    std::vector<int>& m_container;  // Référence au container stockant les valeurs.
    int m_first_index;              // Index de la première valeur de la vue.
    int m_last_index;               // Index de la dernière valeur de la vue.

public:
    explicit view(std::vector<int>& vector);
    view(std::vector<int>& vector, int first_index, int last_index);
};
```

### 1. Les constructeurs

### Question 1.1

Expliquer à quoi correspondent les déclarations suivantes :

```cpp
    explicit view(std::vector<int>& vector);
    view(std::vector<int>& vector, int first_index, int last_index);
```

<div style="background-color:#cdd">

**Correction**:

```cpp
    explicit view(std::vector<int>& vector);
```

Ce constructeur crée une vue qui fait référence au vecteur `vector` et qui rend l'ensemble des éléments de vecteurs accessibles. Le mot clé `explicit` indique qu'il ne s'agit pas d'un constructeur de conversion, le compilateur ne peut pas utiliser automatiquement ce constructeur pour convertir un objet de type `std::vector<int>` en un objet de type `view`.

```cpp
    view(std::vector<int>& vector, int first_index, int last_index);
```

Ce constructeur crée une vue qui fait référence au vecteur `vector` et qui ne permet d'accéder qu'aux éléments situés entre l'indice `first_index`et l'indice `last_index`. Il s'agit d'un constructeur spécialisé qui permet de créer une vue limitée à une sous-séquence du vecteur `vector`.

</div>

### Question 1.2

Pour chacun des constructeurs précédents, compléter le code des constructeurs.

**Remarque** : Le code est minimaliste, on ne demande pas de vérifier si les paramètres `first_index` et `last_index` désignent des index valides vecteur.

<div style="background-color:#cdd">

**Correction**:

```cpp
    explicit view(std::vector<int>& vector): 
        m_container(vector), m_first_index(0), m_last_index(vector.size() - 1)
        {}
```

Le premier constructeur est relativement simple, le champ `m_container` fait référence au vecteur `vector`, le champ `m_first_index` est mis à zéro puisque le premier champ fait référence au premier indice du tableau soit $0$, le champ `m_last_index` fait référence au dernier indice du tableau, soit `vector.size() - 1`. 

```cpp
    view(std::vector<int>& vector, int first_index, int last_index);
        m_container(vector), m_first_index(first_index), m_last_index(last_index)
        {}
```

Le second constructeur est encore plus simple, le champ `m_container` fait référence au vecteur `vector`, les champs `m_first_index` et `m_last_index` sont initialisés avec les paramètres `first_index`et `last_index`.

***Remarque :***
Nous pouvons constater que le constructeur 
```cpp
    explicit view(std::vector<int>& vector): 
        m_container(vector), m_first_index(0), m_last_index(vector.size() - 1)
        {}
```

est un cas particulier du constructeur :

```cpp
    view(std::vector<int>& vector, int first_index, int last_index);
        m_container(vector), m_first_index(first_index), m_last_index(last_index)
        {}
```

Dans ce cas, il est possible de définir le premier constructeur en faisant un appel au deuxième constructeur :

```cpp
    explicit view(std::vector<int>& vector): view(vector, 0, vector.size() - 1) {}
    view(std::vector<int>& vector, int first_index, int last_index);
        m_container(vector), m_first_index(first_index), m_last_index(last_index)
        {}
```

</div>

### Question 1.3

Y-aurait-il besoin de compléter la liste des constructeurs. Expliquer pourquoi c'est nécessaire ou ce n'est pas nécessaire.

Si vous ajoutez un ou plusieurs constructeurs, écrivez le constructeur et son code.

<div style="background-color:#cdd">

**Correction**:

Quels sont les constructeurs habituels qui ne sont pas définis ? Le constructeur par défaut `view()` et le constructeur de recopie `view(const view&)`. 

La question qui va se poser, c'est de savoir si un constructeur par défaut a du sens. En fait, une vue `view` doit toujours faire référence à un vecteur `std::vector<int>`, donc elle ne peut pas être construite sans avoir la référence à ce vecteur. Il n'est donc pas possible d'avoir un constructeur par défaut.

Le seconde question, avons-nous besoin d'un constructeur de recopie et est-il nécessaire de le définir. Il n'y a aucune raison de ne pas avoir à recopier une vue. Donc, le constructeur de recopie est bien nécessaire. Par défaut C++ fournit un constructeur de recopier qui recopit l'ensemble des champs. En fait, c'est bien le comportement que nous souhaitons avoir, donc il n'est pas nécessaire d'implanter un constructeur de recopier mais nous pouvons utiliser celui fournit par défaut.

Cependant, si nous souhaitons fournir un constructeur de recopie, celui-ci ressemblera au constructeur suivant :

```cpp
    view(const view& another_view);
        m_container(another_view.m_container), 
        m_first_index(another_view.m_first_index), 
        m_last_index(another_view.m_last_index)
        {}
```

Au passage à partir de C++11, il est possible d'indiquer que nous souhaitons utiliser le constructeur généré par défault, au lieu d'écrire le code suivant, nous pouvons écrire :

```cpp
    view(const view&) = default;
```

Ceci est utile pour indiquer que nous souhaitons avoir un constructeur de recopie. Si par exemple, nous souhaitons interdice la copie pour un object `non_copiable_object`, il serait possible à partir de C++11 d'écrire :

```cpp
class non_copiable_object:
    non_copiable_object(const non_copiable_object&) = delete;
```

</div>