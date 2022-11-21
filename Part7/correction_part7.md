## 7. Opérateur d'indexation

L'opérateur d'indexation est défini dans une classe comme:

```cpp
template<typename T>
class indexed
{
    T& operator[](int index) { ... }
    T operator[](int index) const { ... }
};
```

Il existe deux versions de l'opérateur, l'une définie comme opération constante retournant la valeur associée à l'index, l'autre définie comme opération non constante permettant de modifier la valeur en renvoyant une référence sur la zone mémoire servant à stocker la valeur.

### Question 7.1

Proposer un opérateur `operator []` pour la classe `view`.


<div style="background-color:#cdd">

**Correction**:

En fait, il suffit que nous vérifions que l'indice désigne bien une valeur présente dans la vue et ensuite nous appelons l'opérateur `operator [](int index)` du containeur de base en translatant l'indice fournit de `first_index`.

```cpp
template<view_container containerT>
class view
{
    ...
    reference operator[](int index) 
    { 
        if(index < 0 || index >= size())
            throw std::out_of_range("index is out of range");
        return m_container[index + m_first_index];
    }
    value_type operator[](int index) const 
    { 
        if(index < 0 || index >= size())
            throw std::out_of_range("index is out of range");
        return m_container[index + m_first_index];
    }
    ...
};
```

Le code proposé dans le répertoire associé utilise la fonction `std::format` pour donner des messages plus informatifs.

</div>