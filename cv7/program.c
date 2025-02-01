#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct tree {
    char value[SIZE];
    struct tree* left;
    struct tree* right;
};

// Функція для читання дерева
struct tree* read_tree() {
    char buffer[SIZE];
    memset(buffer, 0, SIZE);

    if (!fgets(buffer, SIZE, stdin) || buffer[0] == '\n') {
        return NULL;
    }

    struct tree* node = calloc(1, sizeof(struct tree));
    strncpy(node->value, buffer, SIZE);

    if (buffer[0] != '*') {
        node->left = read_tree();
        node->right = read_tree();
    }
    return node;
}

// Підрахунок листкових вузлів
int count_leaves(struct tree* node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return count_leaves(node->left) + count_leaves(node->right);
}

// Функція для запуску чатбота
void run_bot(struct tree* node, int first_call) {
    if (node->left == NULL && node->right == NULL) {
        printf("%s", node->value);
        printf("Koniec\n");
        return;
    }

    if (first_call) {
        printf("Odpovedajte 'a' pre prvu moznost alebo 'n' pre druhu moznost.\n");
    }
    printf("%s", node->value);

    char answer;
    int input_result = scanf(" %c", &answer);

    if (input_result == EOF) {
        // Якщо немає введеного символу
        printf("Koniec vstupu\n");
    } else if (answer == 'a') {
        run_bot(node->left, 0);
    } else if (answer == 'n') {
        run_bot(node->right, 0);
    } else {
        printf("Nerozumiem\n");
    }
}

// Очищення пам'яті дерева
void destroy_tree(struct tree* node) {
    if (node == NULL) return;
    destroy_tree(node->left);
    destroy_tree(node->right);
    free(node);
}

int main() {
    // Читання дерева
    struct tree* root = read_tree();

    // Виведення інформації про експерта
    int num_leaves = count_leaves(root);
    printf("Expert z bufetu to vie.\n");

    if (root == NULL) {
        printf("Chybna databaza\n");
        return 0;
    }
    printf("Pozna %d druhov ovocia a zeleniny.\n", num_leaves);

    // Запуск чатбота з першим викликом
    run_bot(root, 1);

    // Звільнення пам'яті
    destroy_tree(root);

    return 0;
}
