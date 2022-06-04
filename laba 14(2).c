#include <stdio.h>
#include <stdlib.h>

typedef struct prod {
    char prodname[30];
    float weight;
    float cost;
    int warranty;
    char model[30];
    int number;
    char seller[30];
    struct prod *next;
    struct prod *prev;
} prod;

typedef struct deque {
    prod *first;
    prod *last;
} deq;

void init_deque(deq *q) {
 q->first = q->last = NULL; //ініціалізація черги
}

void add_el(prod *t, deq *q) {
    //перевірка на наявність елементів черги
    if (q->first == NULL && q->last == NULL) {
            q->first = q->last = t;
            return;
            }
    t->next = q->first;
    q->first->prev = t;
    q->first = t;
}
//зчитування даних з файлу
void read_file(deq *q) {
    puts("");
    FILE* file;
    prod *p = malloc(sizeof(prod));
    file = fopen("E:\\save.txt", "rb");
    //перевірка наявності файлу
    if (file == NULL)
    {

        return;
    }
    while (fread(p, sizeof(prod), 1, file)) {
            p->prev = p->next = NULL;
            //додавання елементу в чергу
            add_el(p, q);
            p = malloc(sizeof(prod));
            }
    fclose(file);
}

void print(deq *q) {
    prod *p = q->first;
    printf("| Product's name | Weight | Cost | Warranty | Model | Number of products | Seller |\n");
    //перевірка на наяівність елементів черги
    while (p != NULL) {
            printf("| %14s | %4.2f | %5.2f | %d | %s | %d | %s |\n", p->prodname, p->weight, p->cost, p->warranty, p->model, p->number, p->seller);
        /*printf("Product's name: %s\n", p->prodname);
        printf("Weight: %3.2f kg\n", p->weight);
        printf("Cost: %5.2f\n", p->cost);
        printf("Warranty: %d\n", p->warranty);
        printf("Model: %s\n", p->model);
        printf("Number of products: %d\n", p->number);
        printf("Seller: %s\n", p->seller);
        printf("-------------------\n");*/
        p = p->next;
    }
}

int main()
{
    deq q;
    init_deque(&q);

    read_file(&q);

    print(&q);

    return 0;
}
