#include <stdio.h>
#include <stdlib.h>

// Structure d'un maillon de la liste chaînée
typedef struct Node {
    int value;           // valeur stockée dans le maillon
    struct Node *next;   // pointeur vers le maillon suivant
} Node;

// Création d'une liste contenant n entiers 
Node* create_list(int n) {
    Node *head = NULL, *temp = NULL;

    for (int i = 1; i <= n; i++) {
        Node *new = malloc(sizeof(Node)); // allocation mémoire
        new->value = i;                   // affectation valeur
        new->next = NULL;                 // pas de suivant au départ

        if (head == NULL) {
            // premier élément de la liste
            head = new;
            temp = new;
        } else {
            // ajout à la fin
            temp->next = new;
            temp = new;
        }
    }
    return head;
}

// Affichage de la liste
void print_list(Node *head) {
    while (head != NULL) {
        printf("%p : %d\n", head, head->value);
        head = head->next;
    }
}


int main() {
    // Création de la liste initiale
    Node *list = create_list(5);

    printf("Liste initiale:\n");
    print_list(list);


    return 0;
}
