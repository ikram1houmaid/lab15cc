
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Classe Pile generique
template <typename T>
class Pile {
private:
    T* elements;
    int capacite;
    int sommetIndex;

    // Agrandir la capacite du tableau
    void agrandir() {
        int nouvelleCapacite = capacite * 2;

        T* nouveauTableau = new T[nouvelleCapacite];

        for (int i = 0; i <= sommetIndex; i++) {
            nouveauTableau[i] = elements[i];
        }

        delete[] elements;

        elements = nouveauTableau;
        capacite = nouvelleCapacite;
    }

public:

    // Constructeur
    Pile(int taille = 5) {
        if (taille <= 0) {
            throw invalid_argument("La capacite doit etre positive !");
        }

        capacite = taille;
        sommetIndex = -1;

        elements = new T[capacite];
    }

    // Empiler un element
    void empiler(T element) {
        if (sommetIndex == capacite - 1) {
            agrandir();
        }

        elements[++sommetIndex] = element;

        cout << "Element empile : " << element << endl;
    }

    // Depiler un element
    T depiler() {
        if (estVide()) {
            throw runtime_error("Impossible de depiler : pile vide !");
        }

        return elements[sommetIndex--];
    }

    // Consulter le sommet sans supprimer
    T sommet() const {
        if (estVide()) {
            throw runtime_error("La pile est vide !");
        }

        return elements[sommetIndex];
    }

    // Verifier si la pile est vide
    bool estVide() const {
        return sommetIndex == -1;
    }

    // Inverser la pile
    void inverser() {
        int debut = 0;
        int fin = sommetIndex;

        while (debut < fin) {
            T temp = elements[debut];

            elements[debut] = elements[fin];
            elements[fin] = temp;

            debut++;
            fin--;
        }

        cout << "La pile a ete inversee !" << endl;
    }

    // Afficher la pile
    void afficher() const {
        if (estVide()) {
            cout << "La pile est vide." << endl;
            return;
        }

        cout << "Pile (sommet vers base) : ";

        for (int i = sommetIndex; i >= 0; i--) {
            cout << elements[i] << " ";
        }

        cout << endl;
    }

    // Destructeur
    ~Pile() {
        delete[] elements;
    }

    // Interdire la copie superficielle
    Pile(const Pile&) = delete;
    Pile& operator=(const Pile&) = delete;
};

// Programme principal
int main() {

    try {

        // Test avec les entiers
        cout << "\n===== TEST AVEC INT =====" << endl;

        Pile<int> p1;

        p1.empiler(10);
        p1.empiler(20);
        p1.empiler(30);

        p1.afficher();

        cout << "Sommet : " << p1.sommet() << endl;

        cout << "Element depile : " << p1.depiler() << endl;

        p1.afficher();

        p1.inverser();
        p1.afficher();


        // Test avec les chaines de caracteres
        cout << "\n===== TEST AVEC STRING =====" << endl;

        Pile<string> p2;

        p2.empiler("Bonjour");
        p2.empiler("C++");
        p2.empiler("Template");

        p2.afficher();

        cout << "Sommet : " << p2.sommet() << endl;

        cout << "Element depile : " << p2.depiler() << endl;

        p2.afficher();


        // Test avec les nombres decimaux
        cout << "\n===== TEST AVEC DOUBLE =====" << endl;

        Pile<double> p3;

        p3.empiler(10.5);
        p3.empiler(20.75);
        p3.empiler(30.25);

        p3.afficher();

        cout << "Sommet : " << p3.sommet() << endl;

        cout << "Element depile : " << p3.depiler() << endl;

        p3.afficher();


        // Test de l'exception
        cout << "\n===== TEST EXCEPTION =====" << endl;

        Pile<int> p4;

        cout << "Tentative de depilement..." << endl;

        p4.depiler();

    }
    catch (const exception& e) {
        cout << "Exception : " << e.what() << endl;
    }

    return 0;
}
