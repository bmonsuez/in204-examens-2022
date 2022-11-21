## 2: Les données stockées au sein de la classe [Correction]


### Question 2.1

Est-il possible d'accéder aux champs `m_container`, `m_first_index` et `m_last_index`. Expliquer pourquoi ?

<div style="background-color:#cdd">

**Correction**:

L'ensemble des champs `m_container`, `m_first_index` et `m_last_index` est déclaré dans une section dite privée : `private`.

```cpp
class view
{
private:
    std::vector<int>& m_container;
    int m_first_index;
    int m_last_index;
...
}
```

De ce fait, seules les méthodes de la classe `view` peuvent accéder à ces champs. 

</div>

### Question 2.2

Proposer un moyen pour pouvoir accéder en lecture aux données stockés dans ces champs mais surtout pas en écriture.

**Conseils** : Penser aux méthodes d'accés.

<div style="background-color:#cdd">

**Correction**:

***Rappels relatifs à la définition des méthodes d'accès***:

Il est habituel de définir des méthodes d'accès qui renvoie la valeur du champ. Il existe deux manières de nommer ces méthodes, soit en ajoutant le préfixe `get` pour la méthode d'accès en lecteur et le préfixe `set` pour la méthode d'accès en écriture ou alors en appelant la méthode par le nom du champ, celle-ci renvoyant soit une référence sur le champ si l'accès est en lecture et écriture ou alors uniquement une copie de la valeur si le champ n'est accessible en lecture.

Ces méthodes sont bien entendues publiques (ou éventuellement protégées si nous ne souhaitons rendre ces champs visibles qu'aux classes héritant de la classe courante).

Par exemple, nous considérons vouloir accèder à un champ `name` defini dans une classe `named_object` en définissant des méthodes préfixées par `get`  et `set`.

```cpp
class named_object
{
private:
    std::string m_name;

public:
    std::string get_name() const { return m_name; }         // accès en lecture.
    void set_name(std::string aName ) { m_name = aName; }   // accès en écriture.
};
```

Il est possible de n'avoir qu'un accès en lecture (en ne définissant par la méthode préfixée par `set`) ou en écriture en ne définissant pas la méthode préfixée par `get`).

Si nous souhaitons accèder au champ `name` par une méthode dénommée `name` offrant un accès en lecture et en écriture, nous pouvons écrire ceci comme suit :

```cpp
class named_object
{
private:
    std::string m_name;

public:
    std::string name() const { return m_name; } // accès en lecture uniquement.
    std::string& name() { m_name = aName; }     // accès en lecture et écriture.
};
```

Dans ce cas nous définissons deux méthodes `name`, l'une étant constante `name() const`, l'autre n'étant pas constante `name()`. La première méthode retourne une copie du nome stockée dans l'objet. Le contenu du champ n'est pas modifiable. La seconde méthode retourne une référence sur le champ `m_name`, il est donc possible d'accèder au contenu du champ. Il est dés lors possible d'écrire le code suivant :

```cpp
int main()
{
    named_object no;
    no.name() = 'MyObject';
    std::cout << no.name() << std::end;
    return 0;
};
```

qui affichera 'MyObject' sur la console.

***Définition des méthodes d'accès pour la classe***  `view`

Dans le cas de la classe `view`, nous proposons d'utiliser les méthodes préfixées par `get` et `set`. Comme les champs ne sont pas a priori modifiables, nous ne définirons que des méthodes `get`.

```cpp
class view
{
private:
    ...
public:
    ...
    int get_first_index() const { return m_first_index; }
    int get_last_index() const { return m_last_index; }
    std::vector<int>& container() const { return m_container; }
};
```

</div>
