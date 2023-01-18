#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(a, b) (((a)<(b))?(a):(b))

struct node
{
    char numar;
    char culoare;
    int rank;
    int valoare;
    struct node* next;

}*head;

struct node* adaugareLaInceput(struct node* lista, char numar, char culoare, int rank, int valoare)
{
    struct node* newcard = malloc(sizeof(struct node));
    newcard->numar = numar;
    newcard->culoare = culoare;
    newcard->rank = rank;
    newcard->valoare = valoare;
    newcard->next = NULL;
    newcard->next = lista;
    lista = newcard;
    return lista;
}
void initializare_pachet()
{
    head = NULL;
    char culori[4] = {'d', 'c', 'h', 's'};
    for(int i = 2; i <= 9; i++)
    {
        int rank = 15 - i;
        for(int j = 0; j <= 3; j++)
            head = adaugareLaInceput(head, (char)i + '0', culori[j], rank, i);
    }
    for(int j = 0; j <= 3; j++)
        head = adaugareLaInceput(head, 'T', culori[j], 5, 10);
    char cartis[5] = {'J', 'Q', 'K', 'A'};
    for(int i = 0; i <= 3; i++)
    {
        int rank = 4 - i;
        int valoare = 12 + i;
        for(int j = 0; j <= 3; j++)
            head = adaugareLaInceput(head, cartis[i], culori[j], rank, valoare);
    }
}
int dimensiune(struct node* lista)
{
    struct node* p = lista;
    int ct = 0;
    while(p)
    {
        ct++;
        p = p->next;
    }
    return ct;
}
void inversare()
{
    int dim = dimensiune(head);
    for(int i = 1; i <= dim / 2; i++)
    {
        struct node* st = head;
        struct node* dr = head;
        for(int j = 1; j < i; st = st->next, j++); //st parcurge cartile din jumatatea stanga a pachetului
        for(int j = 1; j <= dim - i; dr = dr->next, j++); //dr se incarca cu cartea de pe pozitia opusa in oglinda lui st
        char aux = st->culoare; //fac interschimbare intre campurile lui st si dr
        
        st->culoare = dr->culoare;
        dr->culoare = aux;

        aux = st->numar;
        st->numar = dr->numar;
        dr->numar = aux;

        int auxr = st->rank;
        st->rank = dr->rank;
        dr->rank = auxr;
        auxr = st->valoare;

        st->valoare = dr->valoare;
        dr->valoare = auxr;
    }
}
void intercalare()
{
    struct node* st = head;
    struct node* dr = head;
    int d = dimensiune(head) / 2 - 1;
    struct node* st2; 
    struct node* dr2;
    struct node* pvdr = head; //pvdr = ultima carte din jumatatea stanga a pachetului

    while(d)
    {
        pvdr = pvdr->next;
        d--;
    }
    dr = pvdr->next;
    while(dr->next != NULL)
    {
        st2 = st->next;
        dr2 = dr->next;
        pvdr->next = dr2;
        dr->next = st2;
        st->next = dr;
        st = st2;
        dr = dr2;
    }
}
void mongean()
{
    struct node* p = head;
    struct node* q = head->next;

    while(q)
    {
        p->next = q->next;
        q->next = head;
        head = q;
        p = p->next;
        if(p == NULL)
            break;
        q = p->next;
    }
}

struct node* AdaugareLaSfarsit(struct node* list , char nr, char cl, int rank, int val)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->numar = nr;
    newnode->culoare = cl;
    newnode->rank = rank;
    newnode->valoare = val;
    newnode->next = NULL;

    if(list == NULL)
        list = newnode;
    else
    { 
        struct node* t = list;
        while(t->next != NULL)
            t = t->next;
        t->next = newnode;
    }
    return list;
}
void freeList(struct node* list)
{
    struct node* t = list;
    struct node* x = list;

    while(t != NULL)
    {
        x = t;
        t = t->next;
        free(x);
    }

}
void npiles(int N, int v[101])
{
    struct node** subliste = (struct node**)malloc(101 * sizeof(struct node*));
    int dimSubpachet = dimensiune(head)/N;
    struct node* listItem = head;
    int subListCt = 0;
   
    while(listItem != NULL)
    {
        struct node* sublist = NULL;
        while(dimensiune(sublist) < dimSubpachet && listItem != NULL)
        {
           sublist = AdaugareLaSfarsit(sublist, listItem->numar, listItem->culoare, listItem->rank, listItem->valoare);
           listItem = listItem->next;
        }
        subliste[++subListCt] = sublist; // creez vectorul de subliste
    }

    freeList(head); //reconstruiesc lista head
    head = NULL;
    for(int i = 1; i <= N; i++)
    {
        struct node* p = subliste[v[i]]; 
        while(p != NULL)
        {
            head = AdaugareLaSfarsit(head, p->numar, p->culoare, p->rank, p->valoare);
            p = p->next;
        }
        freeList(subliste[v[i]]);
    }
    free(subliste);
}
struct node* moveFirstToEnd(struct node* lista)
{
    struct node* first = lista;
    struct node* last = lista;

    if(lista->next == NULL)
        return lista;

    while(last->next != NULL)
        last = last->next;
    lista = first->next;
    first->next = NULL;
    last->next = first;
    return lista;

}
struct node* removeFirstN(struct node* list, int N) //functie care sterge primele n noduri
{
    while(N){
        struct node* p = list;
        list = list->next;
        free(p);
        N--;
    }
    return list;
}
struct node* lipireListe(struct node* l1, struct node* l2)
{
    struct node* p1 = l1;
    while(p1->next != NULL)
        p1 = p1->next;
    p1->next = l2;
    return l1;
} 
struct rezultatRazboi
{
    int castigator;
    char carte;
};
struct rezultatRazboi razboi(struct node* player1, struct node* player2)
{
    char rank[14] = {'n', 'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    struct node* p1 = player1;
    struct node* p2 = player2;
    struct rezultatRazboi ret; 
    ret.carte = rank[0];
    int nrMaini = 0;
    int v1[14] = {0}; //vectori pentru calcularea scorului
    int v2[14] = {0};

    while(p1 != NULL && p2 != NULL && nrMaini < 100)
    {
        if(p1->rank < p2->rank)
        {
            p1 = moveFirstToEnd(p1);
            p1 = AdaugareLaSfarsit(p1, p2->numar, p2->culoare, p2->rank, p2->valoare);
            p2 = removeFirstN(p2, 1);
        }
        else if(p1->rank > p2->rank)
        {
            p2 = moveFirstToEnd(p2);
            p2 = AdaugareLaSfarsit(p2, p1->numar, p1->culoare, p1->rank, p1->valoare);
            p1 = removeFirstN(p1, 1);
        }
        else if(p1->rank == p2->rank)
        {
            struct node* listaR1 = NULL; //liste auxiliare cu cartile jucate in razboi
            struct node* listaR2 = NULL;
            int n = min(min((dimensiune(p1) - 1), p1->valoare), min((dimensiune(p2) - 1), p2->valoare)); //cate carti se vor juca 
            
            struct node* aux1 = p1;
            struct node* aux2 = p2;
            for(int i = 1; i <= n; i++)
            {
                listaR1 = adaugareLaInceput(listaR1, aux1->numar, aux1->culoare, aux1->rank, aux1->valoare);
                aux1 = aux1->next;
                listaR2 = adaugareLaInceput(listaR2, aux2->numar, aux2->culoare, aux2->rank, aux2->valoare);
                aux2 = aux2->next;
            }
            listaR1 = adaugareLaInceput(listaR1, aux1->numar, aux1->culoare, aux1->rank, aux1->valoare);
            listaR2 = adaugareLaInceput(listaR2, aux2->numar, aux2->culoare, aux2->rank, aux2->valoare);
        
            if(aux1->rank < aux2->rank)
            {
                p1 = lipireListe(p1, listaR1);
                p1 = lipireListe(p1, listaR2);
            }
            else if(aux1->rank > aux2->rank)
            {
                p2 = lipireListe(p2, listaR2);
                p2 = lipireListe(p2, listaR1);
            }
            p1 = removeFirstN(p1, n+1); 
            p2 = removeFirstN(p2, n+1);
        }
        nrMaini++;
    }
    if(p1 == NULL)
        ret.castigator = 2;
    else if(p2 == NULL)
        ret.castigator = 1;
    else{
        while(p1 != NULL)
        {
            v1[p1->rank]++; //populez vectorul de frecventa al scorului pt jucatorul1
            p1 = p1->next;
        }
        while(p2 != NULL)
        {
            v2[p2->rank]++; //si pentru jucatorul2
            p2 = p2->next;
        }
        for(int i = 1; i <= 13; i++)
        {
            if(v1[i] > v2[i])
            {
                ret.castigator = 1;
                ret.carte = rank[i];
                return ret;
            }
            else if(v1[i] < v2[i]){
                ret.castigator = 2;
                ret.carte = rank[i];
                return ret;
            }
        }
    }
    return ret;
}
void afisareAmestecare(FILE* file)
{
    struct node* p = head;
    while(p != NULL)
    {
        fprintf(file, "%c%c ", p->numar, p->culoare);
        p = p->next;
    }

}
void afisareRazboi(FILE* file)
{
    struct node* p = head;
    struct node* player1 = NULL;
    struct node* player2 = NULL;
    for(int i = 1; i <= dimensiune(head) / 2; i++)
    {
        player1 = AdaugareLaSfarsit(player1, p->numar, p->culoare, p->rank, p->valoare);
        p = p->next;
    }
    for(int i = 1; i <= dimensiune(head) / 2; i++)
    {
        player2 = AdaugareLaSfarsit(player2, p->numar, p->culoare, p->rank, p->valoare);
        p = p->next;
    }
    struct rezultatRazboi ret = razboi(player1, player2);
    if(ret.carte == 'n')
        fprintf(file, "%d", ret.castigator);
    else
        fprintf(file, "%d %c", ret.castigator, ret.carte);
}

int main()
{
    char string[30];
    char tipamestecare[30];
    initializare_pachet();
    FILE* file = fopen("in", "r");
    fscanf(file, "%s\n", string);
    
    if(strcmp(string, "amestecare") == 0 || strcmp(string, "razboi") == 0)
       {
           int nr;
           fscanf(file, "%d", &nr);
           for(int i = 1; i <= nr; i++)
           {
               fscanf(file, "%s", tipamestecare);
               
               if(strcmp(tipamestecare, "inversare") == 0)
                    inversare();
                else if(strcmp(tipamestecare, "intercalare") == 0)
                    intercalare();
                else if(strcmp(tipamestecare, "mongean") == 0)
                    mongean();
                else if(strcmp(tipamestecare, "npiles") == 0)
                {
                    int n;
                    int v[101];
                    fscanf(file, "%d", &n);
                    for(int i = 1; i <= n; i++)
                        fscanf(file, "%d", &v[i]);
                    npiles(n, v);
                }
           }
       } 
    fclose(file);
    file = fopen("out", "w");

    if(strcmp(string, "amestecare") == 0)
        afisareAmestecare(file);

    if(strcmp(string, "razboi") == 0)
        afisareRazboi(file);
        
    fclose(file);
    freeList(head);
}

