#include <stdio.h>
#include <stdlib.h>

// Structure d'un maillon de la liste chaînée
typedef struct Node {
    int value;           // valeur stockée dans le maillon
    struct Node *next;   // pointeur vers le maillon suivant
} Node;

// Crétion d'un nouveau maillon
Node* create_node(int value) {
    Node *newNode = malloc(sizeof(Node)); // allocation mémoire

    if (newNode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}


// Création d'une liste contenant n entiers 
Node* create_list(int n) {
    Node *head = NULL; 
    Node *currentNode = NULL;

    for (int i = 1; i <= n; i++) {
        Node *newNode = create_node(i);

        if (head == NULL) {
            // premier élément de la liste
            head = newNode;
            currentNode = newNode;
        } else {
            // ajout à la fin
            currentNode->next = newNode;
            currentNode = newNode;
        }
    }
    return head;
}

// Affichage de la liste
void display_list(Node *head) {
    while (head != NULL) {
        printf("%p : %d\n", head, head->value);
        head = head->next;
    }
}


// Calcul de la longueur de la liste
int get_list_length(Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Ajouter un élément au début de la liste
Node* add_node_at_start(Node *head, int value) {
    Node *newNode = create_node(value);
    newNode->next = head; // le nouvel élément pointe vers l'ancien début
    return newNode;       // devient la nouvelle tête
}

// Ajouter un élément à la fin
Node* add_node_at_end(Node *head, int value) {
    Node *newNode = create_node(value);

    if (head == NULL){
	return newNode; // liste vide
    }

    Node *currentNode = head;
    while (currentNode ->next != NULL)
        currentNode = currentNode ->next;

    currentNode->next = newNode; // ajout à la fin
    return head;
}


// Supprimer le premier élément
Node* remove_first_node(Node *head) {
    if (head == NULL){
         return NULL;
    }
    Node *currentNode = head;
    head = head->next;         // on avance la tête
    free(currentNode);        // libération mémoire

    return head;
}

// Supprimer le dernier élément
Node* remove_last_node(Node *head) {
    if (head == NULL) {
	return NULL;
    }
    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node *currentNode = head;
    while (currentNode->next->next != NULL)
        currentNode = currentNode->next;

    free(currentNode->next);  // libère le dernier
    currentNode->next = NULL;

    return head;
}

// Concaténer deux listes
Node* concatenate_2_lists(Node *l1, Node *l2) {
    if (l1 == NULL){
	return l2;
    }

    Node *currentNode = l1;
    while (currentNode->next != NULL){
        currentNode = currentNode->next;
    }

    currentNode->next = l2; 
    return l1;
}

// Appliquer une fonction (ici : carré) à chaque élément
Node* map(Node *head) {
    Node *new_head = NULL;
    Node *currentNode = NULL;

    while (head != NULL) {
        Node *newNode = create_node(head->value*head->value);

        if (new_head == NULL) {
            new_head = newNode;
            currentNode = newNode;
        } else {
            currentNode->next = newNode;
            currentNode = newNode;
        }

        head = head->next;
    }
    return new_head;
}

int main() {
    // Création de la liste initiale
    Node *list = create_list(5);
    Node *list2 = create_list(3);

    printf("Liste initiale:\n");
    display_list(list);
    
    // Test ajout début
    printf("\n---- TEST AJOUT DEBUT ----\n");
    list = add_node_at_start(list, 0);
    display_list(list);

    // Test ajout fin
    printf("\n---- TEST AJOUT FIN ----\n");
    list = add_node_at_end(list, 6);
    display_list(list);

    // Test suppression début
    printf("\n---- TEST SUPPRESSION DEBUT ----\n");
    list = remove_first_node(list);
    display_list(list);

    // Test suppression fin
    printf("\n---- TEST SUPPRESSION FIN ----\n");
    list = remove_last_node(list);
    display_list(list);
    
    // Test concaténation
    printf("\n---- TEST CONCAT ----\n");
    list = concatenate_2_lists(list, list2);
    display_list(list);
    
    // Test map (carré)
    printf("\n---- TEST MAP (CARRE) ----\n");
    Node *square = map(list);
    display_list(square);

    return EXIT_SUCCESS;
}
