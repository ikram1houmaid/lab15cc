
#include <iostream>
#include <stdexcept>
using namespace std;

class File {
private:
    int* elements;
    int capacite;
    int debut;
    int fin;
    int nbElements;

public:

    // Constructeur
    File(int taille = 5) {
        if (taille <= 0) {
            throw invalid_argument("La capacite doit etre positive !");
        }

        capacite = taille;
        elements = new int[capacite];

        debut = 0;
        fin = -1;
        nbElements = 0;
    }

    // Verifier si la file est vide
    bool estVide() const {
        return nbElements == 0;
    }

    // Verifier si la file est pleine
    bool estPleine() const {
        return nbElements == capacite;
    }

    // Ajouter un element dans la file
    void enfiler(int valeur) {
        if (estPleine()) {
            cout << "Erreur : la file est pleine !" << endl;
            return;
        }

        fin = (fin + 1) % capacite;
        elements[fin] = valeur;
        nbElements++;

        cout << valeur << " ajoute a la file." << endl;
    }

    // Retirer un element de la file
    int defiler() {
        if (estVide()) {
            throw runtime_error("Impossible de defiler : la file est vide !");
        }

        int valeur = elements[debut];

        debut = (debut + 1) % capacite;
        nbElements--;

        return valeur;
    }

    // Afficher les elements de la file
    void afficher() const {
        if (estVide()) {
            cout << "La file est vide." << endl;
            return;
        }

        cout << "Contenu de la file : ";

        for (int i = 0; i < nbElements; i++) {
            int position = (debut + i) % capacite;
            cout << elements[position] << " ";
        }

        cout << endl;
    }

    // Destructeur
    ~File() {
        delete[] elements;
        cout << "Memoire de la file liberee." << endl;
    }
};

// Programme principal
int main() {

    File f(5);

    int choix;
    int valeur;

    do {
        cout << "\n===== MENU DE GESTION DE FILE =====" << endl;
        cout << "1. Enfiler un element" << endl;
        cout << "2. Defiler un element" << endl;
        cout << "3. Afficher la file" << endl;
        cout << "4. Verifier si la file est vide" << endl;
        cout << "5. Verifier si la file est pleine" << endl;
        cout << "0. Quitter" << endl;

        cout << "Votre choix : ";
        cin >> choix;

        try {
            switch (choix) {

                case 1:
                    cout << "Donner une valeur : ";
                    cin >> valeur;
                    f.enfiler(valeur);
                    break;

                case 2:
                    valeur = f.defiler();
                    cout << "Element retire : " << valeur << endl;
                    break;

                case 3:
                    f.afficher();
                    break;

                case 4:
                    if (f.estVide())
                        cout << "La file est vide." << endl;
                    else
                        cout << "La file n'est pas vide." << endl;
                    break;

                case 5:
                    if (f.estPleine())
                        cout << "La file est pleine." << endl;
                    else
                        cout << "La file n'est pas pleine." << endl;
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
