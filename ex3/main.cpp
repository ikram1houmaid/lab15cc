
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Classe Noeud : represente un element de la liste chainee
class Noeud {
public:
    int cle;
    string valeur;
    Noeud* suivant;

    Noeud(int c, string v) {
        cle = c;
        valeur = v;
        suivant = nullptr;
    }
};

// Classe TableHachage
class TableHachage {
private:
    Noeud** table;
    int tailleTable;
    int nombreElements;

    // Fonction de hachage
    int fonctionHachage(int cle) const {
        return ((cle % tailleTable) + tailleTable) % tailleTable;
    }

    // Inserer sans declencher un nouveau redimensionnement
    void insererInterne(int cle, const string& valeur) {
        int indice = fonctionHachage(cle);

        Noeud* nouveau = new Noeud(cle, valeur);
        nouveau->suivant = table[indice];
        table[indice] = nouveau;

        nombreElements++;
    }

    // Redimensionner la table et redistribuer les elements
    void redimensionner() {
        int ancienneTaille = tailleTable;
        Noeud** ancienneTable = table;

        tailleTable = tailleTable * 2;
        table = new Noeud*[tailleTable];

        for (int i = 0; i < tailleTable; i++) {
            table[i] = nullptr;
        }

        nombreElements = 0;

        for (int i = 0; i < ancienneTaille; i++) {
            Noeud* courant = ancienneTable[i];

            while (courant != nullptr) {
                insererInterne(courant->cle, courant->valeur);

                Noeud* temp = courant;
                courant = courant->suivant;
                delete temp;
            }
        }

        delete[] ancienneTable;
    }

public:

    // Constructeur
    TableHachage(int taille = 5) {
        if (taille <= 0) {
            throw invalid_argument("La taille doit etre positive !");
        }

        tailleTable = taille;
        nombreElements = 0;

        table = new Noeud*[tailleTable];

        for (int i = 0; i < tailleTable; i++) {
            table[i] = nullptr;
        }
    }

    // Inserer une cle et une valeur
    void inserer(int cle, string valeur) {
        int indice = fonctionHachage(cle);

        Noeud* courant = table[indice];

        // Si la cle existe deja, modifier sa valeur
        while (courant != nullptr) {
            if (courant->cle == cle) {
                courant->valeur = valeur;
                cout << "Valeur mise a jour !" << endl;
                return;
            }

            courant = courant->suivant;
        }

        // Ajouter le nouveau noeud
        insererInterne(cle, valeur);

        cout << "Element insere avec succes !" << endl;

        // Redimensionnement si le taux de remplissage depasse 0.75
        if ((double)nombreElements / tailleTable > 0.75) {
            cout << "Redimensionnement de la table..." << endl;
            redimensionner();
        }
    }

    // Rechercher une valeur a partir de sa cle
    string rechercher(int cle) const {
        int indice = fonctionHachage(cle);

        Noeud* courant = table[indice];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                return courant->valeur;
            }

            courant = courant->suivant;
        }

        throw runtime_error("Cle introuvable dans la table !");
    }

    // Supprimer un element a partir de sa cle
    void supprimer(int cle) {
        int indice = fonctionHachage(cle);

        Noeud* courant = table[indice];
        Noeud* precedent = nullptr;

        while (courant != nullptr) {
            if (courant->cle == cle) {

                if (precedent == nullptr) {
                    table[indice] = courant->suivant;
                } else {
                    precedent->suivant = courant->suivant;
                }

                delete courant;
                nombreElements--;

                cout << "Element supprime avec succes !" << endl;
                return;
            }

            precedent = courant;
            courant = courant->suivant;
        }

        cout << "Cle introuvable !" << endl;
    }

    // Afficher toutes les cases de la table
    void afficher() const {
        cout << "\n===== CONTENU DE LA TABLE =====" << endl;

        for (int i = 0; i < tailleTable; i++) {
            cout << "Case [" << i << "] : ";

            Noeud* courant = table[i];

            if (courant == nullptr) {
                cout << "Vide";
            }

            while (courant != nullptr) {
                cout << "(" << courant->cle
                     << ", " << courant->valeur << ")";

                if (courant->suivant != nullptr) {
                    cout << " -> ";
                }

                courant = courant->suivant;
            }

            cout << endl;
        }

        cout << "Taille actuelle : " << tailleTable << endl;
        cout << "Nombre d'elements : " << nombreElements << endl;
    }

    // Destructeur
    ~TableHachage() {
        for (int i = 0; i < tailleTable; i++) {
            Noeud* courant = table[i];

            while (courant != nullptr) {
                Noeud* temp = courant;
                courant = courant->suivant;
                delete temp;
            }
        }

        delete[] table;
    }

    // Empecher les copies superficielles
    TableHachage(const TableHachage&) = delete;
    TableHachage& operator=(const TableHachage&) = delete;
};

// Programme principal
int main() {

    TableHachage th(5);

    int choix;
    int cle;
    string valeur;

    do {
        cout << "\n===== MENU TABLE DE HACHAGE =====" << endl;
        cout << "1. Inserer un element" << endl;
        cout << "2. Rechercher un element" << endl;
        cout << "3. Supprimer un element" << endl;
        cout << "4. Afficher la table" << endl;
        cout << "0. Quitter" << endl;

        cout << "Votre choix : ";
        cin >> choix;

        try {
            switch (choix) {

                case 1:
                    cout << "Donner la cle : ";
                    cin >> cle;

                    cout << "Donner la valeur : ";
                    cin >> valeur;

                    th.inserer(cle, valeur);
                    break;

                case 2:
                    cout << "Donner la cle a rechercher : ";
                    cin >> cle;

                    cout << "Valeur trouvee : "
                         << th.rechercher(cle) << endl;
                    break;

                case 3:
                    cout << "Donner la cle a supprimer : ";
                    cin >> cle;

                    th.supprimer(cle);
                    break;

                case 4:
                    th.afficher();
                    break;

                case 0:
                    cout << "Fin du programme." << endl;
                    break;

                default:
                    cout << "Choix invalide !" << endl;
            }

        } catch (const exception& e) {
            cout << "Exception : " << e.what() << endl;
        }

    } while (choix != 0);

    return 0;
}
