#include <stdio.h>
#include <string.h>
#define dim 50

struct dati
{
    int giorno;
    int ora;
    char partenza[20];
    char destinazione[20];
    int spese_carburante;
    int pagamento;
    float spese_autostrada;
} campione;

void nuovoViaggio(struct dati viaggio[], char nomefile[]);
void visualizza(char nomefile[], char appoggio[]);
void nuovoMese(struct dati viaggio[], char nomefile[]);
void totale(struct dati viaggio[], char nomefile[], char appoggio[], int scelta);

int main()
{
    int i, c, q, scelta;
    char nomefile[20];
    char appoggio[200];

    struct dati viaggio[dim];

    do
    {
        printf("\n\nCosa vuoi fare?");
        printf("\n1-Carica nuovo viaggio");
        printf("\n2-Inizia nuovo mese");
        printf("\n3-Visualizza elenco viaggi");
        printf("\n4-Visualizza entrate totali");
        printf("\n5-Visualizza spese totali");
        printf("\n6-Visualizza netto mensile");
        printf("\n0-Esci\n");
        scanf("%d", &scelta);

        switch(scelta)
        {
        case 0:
            break;
        case 1:
            nuovoViaggio(viaggio, nomefile);
            break;
        case 2:
            nuovoMese(viaggio, nomefile);
            break;
        case 3:
            visualizza(nomefile, appoggio);
            break;
        case 4:
            totale(viaggio, nomefile, appoggio, scelta);
            break;
        case 5:
            totale(viaggio, nomefile, appoggio, scelta);
            break;
        case 6:
            totale(viaggio, nomefile, appoggio, scelta);
            break;
        default:
            printf("\nNumero non valido, inserire un numero tra quelli del menu");
            break;
        }
    }
    while(scelta != 0);

    return 0;
}

void nuovoViaggio(struct dati viaggio[], char nomefile[])
{
    FILE *fp;
    int q, i;
    printf("\nScrivi il mese: ");
    scanf("%s", nomefile);
    strcat(nomefile, ".txt");

    fp = fopen(nomefile, "r");

    if(fp)
    {
        fclose(fp);

        printf("\nQuanti viaggi vuoi aggiungere? ");
        scanf("%d", &q);

        for(i = 0; i < q; i++)  		//caricamento struct
        {
            printf("\nGiorno: ");
            scanf("%d", &viaggio[i].giorno);

            printf("\nOra: ");
            scanf("%d", &viaggio[i].ora);

            printf("\nPartenza: ");
            scanf("%s", viaggio[i].partenza);

            printf("\nDestinazione: ");
            scanf("%s", viaggio[i].destinazione);

            printf("\nPagamento: ");
            scanf("%d", &viaggio[i].pagamento);

            printf("\nSpese carburante: ");
            scanf("%d", &viaggio[i].spese_carburante);

            printf("\nSpese autostrada: ");
            scanf("%f", &viaggio[i].spese_autostrada);
        }

        fp = fopen(nomefile, "a");
        for(i = 0; i < q; i++)
        {
            fprintf(fp, "\n%d %d %s %s %d %d %.2f", viaggio[i].giorno, viaggio[i].ora, viaggio[i].partenza, viaggio[i].destinazione, viaggio[i].pagamento, viaggio[i].spese_carburante, viaggio[i].spese_autostrada);		//scrittura su file i voti e i pesi
        }
        fclose(fp);
    }
    else
    {
        fclose(fp);
        printf("\nIl mese che hai cercato non esiste!");
    }
}

void nuovoMese(struct dati viaggio[], char nomefile[])
{
    FILE *fp;
    int q, i;

    printf("\nScrivi il mese: ");
    scanf("%s", nomefile);
    strcat(nomefile, ".txt");

    printf("\nQuanti viaggi vuoi aggiungere? ");
    scanf("%d", &q);

    for(i = 0; i < q; i++)  		//caricamento struct
    {
        printf("\nGiorno: ");
        scanf("%d", &viaggio[i].giorno);

        printf("\nOra: ");
        scanf("%d", &viaggio[i].ora);

        printf("\nPartenza: ");
        scanf("%s", viaggio[i].partenza);

        printf("\nDestinazione: ");
        scanf("%s", viaggio[i].destinazione);

        printf("\nPagamento: ");
        scanf("%d", &viaggio[i].pagamento);

        printf("\nSpese carburante: ");
        scanf("%d", &viaggio[i].spese_carburante);

        printf("\nSpese autostrada: ");
        scanf("%f", &viaggio[i].spese_autostrada);
    }

    fp = fopen(nomefile, "w");
    fprintf(fp, "G ORA PART DES $$ be aut");		//scrittura su file della prima riga del documento (legenda)

    for(i = 0; i < q; i++)
    {
        fprintf(fp, "\n%d %d %s %s %d %d %.2f", viaggio[i].giorno, viaggio[i].ora, viaggio[i].partenza, viaggio[i].destinazione, viaggio[i].pagamento, viaggio[i].spese_carburante, viaggio[i].spese_autostrada);		//scrittura su file i voti e i pesi
    }
    fclose(fp);
}

void visualizza(char nomefile[], char appoggio[])
{
    FILE *fp;
    printf("\nScrivi il mese: ");
    scanf("%s", nomefile);
    strcat(nomefile, ".txt");

    fp = fopen(nomefile, "r");
    if(fp)
    {
        printf("\n");
        while(!feof(fp))
        {
            fgets(appoggio, 200, fp);
            printf("%s", appoggio);
        }
    }
    else
    {
        printf("Il file che hai cercato non esiste! Riprova");
    }
    fclose(fp);
}

void totale(struct dati viaggio[], char nomefile[], char appoggio[], int scelta) {
    FILE *fp;
    int i = 0;
    int g;
    int tot_entrate = 0;
    float tot_spese = 0;
    float netto_mensile = 0;
    int z; //variabile richiesta soldi gia incassati
    int incassati;

    printf("\nScrivi il mese: ");
    scanf("%s", nomefile);
    strcat(nomefile, ".txt");

    fp = fopen(nomefile, "r");
    fgets(appoggio, 200, fp);        //la prima riga del file viene messa nell'array "appoggio"
    if (fp) {
        while (!feof(fp)) {
            fscanf(fp, "%d %d %s %s %d %d %f", &viaggio[i].giorno, &viaggio[i].ora, viaggio[i].partenza,
                   viaggio[i].destinazione, &viaggio[i].pagamento, &viaggio[i].spese_carburante,
                   &viaggio[i].spese_autostrada);
            i++;
        }
    }
    g = i; //"i" era il numero di viaggi prelevati
    for (i = 0; i < g; i++) {
        tot_entrate = tot_entrate + viaggio[i].pagamento;
        tot_spese = tot_spese + viaggio[i].spese_carburante + viaggio[i].spese_autostrada;
    }

    netto_mensile = tot_entrate - tot_spese;

    printf("\nViaggi effettuati questo mese: %d", g);

    if (scelta == 4) {
        printf("\n\nTotale entrate: %d euro", tot_entrate); //stampa a monitor del totale delle entrate
        printf("\n\nHai gia' incassato dei soldi? \n1-Si\n0-No\n");
        scanf("%d", &z);
        if (z == 1) {
            printf("Quanto hai gia' incassato?\n");
            scanf("%d", &incassati);
            incassati = tot_entrate - incassati;
            printf("Ti restano da incassare: %d euro", incassati);
        }
    } else if (scelta == 5) {
        printf("\n\nTotale spese: %.2f euro", tot_spese); //stampa a monitor del totale delle spese
    } else if (scelta == 6) {
        printf("\n\nNetto mensile: %.2f euro", netto_mensile); //stampa a monitor del netto mensile (entrate-uscite)
    }
    fclose(fp);

}