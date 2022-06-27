#include <stdio.h>
#include <stdlib.h>

typedef struct prod {
    char prodname[30];
    float cost;
    int warranty;
    float vol;
    float cur;
    float freq;
    int up_lim;
    int low_lim;
    float err;
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
        puts("Oops...file does not exist\nNext time, create it beforehand\n");
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
    float V = 0, I = 0;
    int T = 0;
    do{
        printf("Enter required voltage: ");
        scanf("%f", &V);
        if(V <= 0){
            printf("This number has to be natural\n");
        }
    } while(V <= 0);

    do{
        printf("Enter required current: ");
        scanf("%f", &I);
        if(I <= 0){
            printf("This number has to be natural\n");
        }
    } while(I <= 0);

    do{
        printf("Enter required warranty: ");
        scanf("%d", &T);
        if(T <= 0){
            printf("This number has to be natural\n");
        }
    } while(T <= 0);

    prod *p = q->first;
    printf("| Product's name |   Cost   | Warranty |  Voltage  | Current | Frequency | Upper limit | Lower limit | Error |\n");
    printf("+------------------------------------------------------------------------------------------------------------+\n");
    while (p != NULL) {
            if (p->vol == V && p->cur < I && p->warranty < T)
            {
                printf("| %14s |  %5.2f | %8d |   %5.2f  |   %5.2f  |   %5.2f  | %11d | %11d | %5.2f |\n", p->prodname, p->cost, p->warranty, p->vol, p->cur, p->freq, p->up_lim, p->low_lim, p->err);
                printf("+------------------------------------------------------------------------------------------------------------+\n");
            }

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
