
#include <iostream>
using namespace std;

// Classe Noeud : représente un élément de la liste
class Noeud {
public:
    int valeur;
    Noeud* suivant;

    Noeud(int v) {
        valeur = v;
        suivant = nullptr;
    }
};

// Classe ListeChainee
class ListeChainee {
private:
    Noeud* tete;
    int nbElements;

public:

    // Constructeur
    ListeChainee() {
        tete = nullptr;
        nbElements = 0;
    }

    // Ajouter un élément au début
    void ajouterDebut(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        nouveau->suivant = tete;
        tete = nouveau;

        nbElements++;
    }

    // Ajouter un élément à la fin
    void ajouterFin(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (tete == nullptr) {
            tete = nouveau;
        } else {
            Noeud* courant = tete;

            while (courant->suivant != nullptr) {
                courant = courant->suivant;
            }

            courant->suivant = nouveau;
        }

        nbElements++;
    }

    // Supprimer un élément par sa valeur
    void supprimer(int valeur) {
        if (tete == nullptr) {
            cout << "La liste est vide !" << endl;
            return;
        }

        // Suppression du premier élément
        if (tete->valeur == valeur) {
            Noeud* temp = tete;
            tete = tete->suivant;
            delete temp;
            nbElements--;

            cout << "Element supprime !" << endl;
            return;
        }

        // Recherche de l'élément
        Noeud* courant = tete;

        while (courant->suivant != nullptr &&
               courant->suivant->valeur != valeur) {
            courant = courant->suivant;
        }

        if (courant->suivant != nullptr) {
            Noeud* temp = courant->suivant;
            courant->suivant = temp->suivant;
            delete temp;
            nbElements--;

            cout << "Element supprime !" << endl;
        } else {
            cout << "Element introuvable !" << endl;
        }
    }

    // Afficher la liste
    void afficher() const {
        if (tete == nullptr) {
            cout << "La liste est vide." << endl;
            return;
        }

        Noeud* courant = tete;

        cout << "Liste : ";

        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }

        cout << "NULL" << endl;
    }

    // Retourner le nombre d'éléments
    int taille() const {
        return nbElements;
    }

    // Iterateur personnalise
    class Iterateur {
    private:
        Noeud* courant;

    public:
        Iterateur(Noeud* noeud) {
            courant = noeud;
        }

        // Acceder a la valeur
        int operator*() const {
            return courant->valeur;
        }

        // Passer au noeud suivant
        Iterateur& operator++() {
            if (courant != nullptr) {
                courant = courant->suivant;
            }
            return *this;
        }

        // Comparer deux iterateurs
        bool operator!=(const Iterateur& autre) const {
            return courant != autre.courant;
        }
    };

    // Retourner l'iterateur de debut
    Iterateur begin() const {
        return Iterateur(tete);
    }

    // Retourner l'iterateur de fin
    Iterateur end() const {
        return Iterateur(nullptr);
    }

    // Destructeur : liberer la memoire
    ~ListeChainee() {
        Noeud* courant = tete;

        while (courant != nullptr) {
            Noeud* temp = courant;
            courant = courant->suivant;
            delete temp;
        }

        tete = nullptr;
        nbElements = 0;
    }
};

// Programme principal
int main() {

    ListeChainee liste;

    // Ajouter des elements
    liste.ajouterDebut(10);
    liste.ajouterDebut(5);
    liste.ajouterFin(20);
    liste.ajouterFin(30);

    cout << "=== Affichage de la liste ===" << endl;
    liste.afficher();

    // Afficher la taille
    cout << "Taille de la liste : "
         << liste.taille() << endl;

    // Supprimer un element
    cout << "\n=== Suppression de 20 ===" << endl;
    liste.supprimer(20);
    liste.afficher();

    // Parcours avec l'iterateur personnalise
    cout << "\n=== Parcours avec iterateur ===" << endl;

    for (ListeChainee::Iterateur it = liste.begin();
         it != liste.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;

    cout << "\nFin du programme." << endl;

    return 0;
}
