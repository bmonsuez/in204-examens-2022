## 3. Opérateurs de comparaison [Correction]

Nous souhaitons définir un opérateur qui détermine si deux object **view** désigne la même séquence d'un même vecteur d'entiers.

### Question 3.1

Proposer une implantation des deux opérateurs suivants :

```cpp
class view
{
...
public:
...
    bool operator == (const view&) const;
    bool operator != (const view&) const;
...
};
```

___

**Correction**:

Deux vues sont égales si et seulement si :

* elles font références au même vecteur, ie. l'adresse des deux vecteurs doivent être égaux.
* le premier et le dernier index définissant la vue sont égaux.

En conséquence de quoi, il est possible de réécrire l'opérateur égal comme suit :

```cpp
    bool operator == (const view& another_view) const
    {
        return &m_container == &another_view.m_container 
            && m_first_index == another_view.m_first_index
            && m_last_index == another_view.m_last_index;
    }
```

Pour les versions antérieures à C++20, il est nécessaire de définir l'opérateur `operator !=`:

```cpp
    bool operator != (const view& another_view) const
    {
        return &m_container != &another_view.m_container 
            || m_first_index != another_view.m_first_index
            || m_last_index != another_view.m_last_index;
    }
```

A partir de C++20, si l'opérateur `operator ==` est redéfini, alors le compilateur génère automatiquement l'opérateur `operator !=` en faisant la négation de l'opérateur `operator ==`.

___
