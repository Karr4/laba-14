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
    q->first = q->last = NULL;   //ініціалізація черги
}

void enter(prod *p) {
    //ввід даних елементу
    printf("Enter product's name: ");
    scanf("%s", p->prodname);
    printf("Enter weight(kg): ");
    scanf("%f", &(p->weight));
    printf("Enter product's cost: ");
    scanf("%f", &(p->cost));
    printf("Enter warranty(months): ");
    scanf("%d", &(p->warranty));
    printf("Enter product's model: ");
    scanf("%s", p->model);
    printf("Enter the number of pruduct's: ");
    scanf("%d", &(p->number));
    printf("Enter seller's name: ");
    scanf("%s", p->seller);
    p->next = p->prev = NULL;
}

void add_el(deq *q) {
        prod *new_el = malloc(sizeof(prod));
        enter(new_el);
        if (q->first == NULL) {
                q->first = q->last = new_el;
                puts("\n-------------------\n");
                return;
        }
        q->last->next = new_el;
        new_el->prev = q->last;
        q->last = new_el;
        puts("\n-------------------\n");
}

void save_file(deq *q){
    FILE *file;
    file = fopen("E:\\save.txt", "wb");
    prod *p = q->first;
    if (file == NULL) {
        puts("Oops...file does not exist\nNext time, create it beforehand\n");
        return;
    }
    while (p != NULL){
        fwrite(p, sizeof(prod), 1, file);
        p = p->next;
    }
    fclose(file);
}

int main()
{
    deq q;
    init_deque(&q);

    int n = 0;
    do{
        printf("Input N: ");
        scanf("%d", &n);
        if(n <= 0){
            printf("N must be natural.\n");
        }
    } while(n <= 0);

    for (int i = 0; i < n; i++){
        add_el(&q);
    }

    save_file(&q);

    return 0;
}
