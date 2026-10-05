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


// Calcul de la longueur de la liste
int length(Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}
// Ajouter un élément au début de la liste
Node* add_start(Node *head, int value) {
    Node *new = malloc(sizeof(Node));
    new->value = value;
    new->next = head; // le nouvel élément pointe vers l'ancien début
    return new;       // devient la nouvelle tête
}

// Ajouter un élément à la fin
Node* add_end(Node *head, int value) {
    Node *new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;

    if (head == NULL) return new; // liste vide

    Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new; // ajout à la fin
    return head;
}
// Supprimer le premier élément
Node* remove_first(Node *head) {
    if (head == NULL) return NULL;

    Node *temp = head;
    head = head->next; // on avance la tête
    free(temp);        // libération mémoire

    return head;
}

// Supprimer le dernier élément
Node* remove_last(Node *head) {
    if (head == NULL) return NULL;

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node *temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);  // libère le dernier
    temp->next = NULL;

    return head;
}
// Concaténer deux listes
Node* concat(Node *l1, Node *l2) {
    if (l1 == NULL) return l2;

    Node *temp = l1;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = l2; 
    return l1;
}
int main() {
    // Création de la liste initiale
    Node *list = create_list(5);

    printf("Liste initiale:\n");
    print_list(list);
    // Test ajout début
    printf("\n---- TEST AJOUT DEBUT ----\n");
    list = add_start(list, 0);
    print_list(list);

    // Test ajout fin
    printf("\n---- TEST AJOUT FIN ----\n");
    list = add_end(list, 6);
    print_list(list);
      // Test suppression début
    printf("\n---- TEST SUPPRESSION DEBUT ----\n");
    list = remove_first(list);
    print_list(list);

    // Test suppression fin
    printf("\n---- TEST SUPPRESSION FIN ----\n");
    list = remove_last(list);
    print_list(list);
     // Test concaténation
    printf("\n---- TEST CONCAT ----\n");
    Node *list2 = create_list(3);
    list = concat(list, list2);
    print_list(list);

    return 0;
}
