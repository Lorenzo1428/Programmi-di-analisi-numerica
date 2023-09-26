#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double funzione_reale(int, int, double);
void presentazione_e_configurazione(double []);
void applica_metodi(double []);

int main()
{
    double I[7] = {};

    presentazione_e_configurazione(I);
    applica_metodi(I);

    printf("\n");
    system("pause");

    return 0;
}

double funzione_reale(int f, int od, double x)
{
    switch(f)
    {
    case 1:

        switch(od)
        {
        case 0:

            return (pow(x, 2)) - 2;

            break;
        case 1:

            return 2*x;

            break;
        default:
            ;
        }

        break;
    case 2:

        switch(od)
        {
        case 0:

            return 5*(pow(x, 2)) - 2;

            break;
        case 1:

            return 10*x;

            break;
        default:
            ;
        }

        break;
    case 3:

        switch(od)
        {
        case 0:

            return 10*(pow(x, 2)) - 2;

            break;
        case 1:

            return 20*x;

            break;
        default:
            ;
        }

        break;
    case 4:

        switch(od)
        {
        case 0:

            return pow(x, 3);

            break;
        case 1:

            return 3*(pow(x, 2));

            break;
        default:
            ;
        }

        break;
    case 5:

        switch(od)
        {
        case 0:

            return (x + 1)*(x - 3)*(x - 10);

            break;
        case 1:

            return 3*(pow(x, 2)) - 24*x + 17;

            break;
        default:
            ;
        }

        break;
    case 6:

        switch(od)
        {
        case 0:

            return atan(x);

            break;
        case 1:

            return ((double)1)/(pow(x, 2) + 1);

            break;
        default:
            ;
        }

        break;
    case 7:

        switch(od)
        {
        case 0:

            return pow(x, 2) - x - 2;

            break;
        case 1:

            return 2*x - 1;

            break;
        default:
            ;
        }

        break;
    case 8:

        if(x < -2)
        {
            x = -2;
        }

        switch(od)
        {
        case 0:

            return sqrt(x + 2) - x;

            break;
        case 1:

            return (((double)1)/(2*sqrt(x + 2))) - 1;

            break;
        default:
            ;
        }

        break;
    case 9:

        if(0 == x)
        {
            x = pow(10, -10);
        }

        switch(od)
        {
        case 0:

            return 1 + (((double)2)/x) - x;

            break;
        case 1:

            return -(((double)2)/pow(x, 2)) - 1;

            break;
        default:
            ;
        }

        break;
    case 10:

        switch(od)
        {
        case 0:

            return fabs(cos(x));

            break;
        case 1:

            return -((sin(x)*cos(x))/(fabs(cos(x))));

            break;
        default:
            ;
        }

        break;
    case 11:

        switch(od)
        {
        case 0:

            return ((double)20) / (pow(x, 2) + 2*x + 10);

            break;
        case 1:

            return - (((double)40)*(x + 1)/pow(pow(x, 2) + 2*x + 10, 2));

            break;
        default:
            ;
        }

        break;
    case 12:

        switch(od)
        {
        case 0:

            return ((2*pow(x, 3) + 2)/(3*pow(x, 2) + 4));

            break;
        case 1:

            return ((6*x*(pow(x, 3) + 4*x - 2))/pow(3*pow(x, 2) + 4, 2));

            break;
        default:
            ;
        }

        break;
    default:
        ;
    }
}

void presentazione_e_configurazione(double informazioni[])
{
    int scelta = 0;

    printf("Il programma e' in grado di approssimare le radici di alcune funzioni predefinite.\nLa ricerca di tali radici e' realizzabile");
    printf(" tramite quattro diversi metodi numerici e al termine di essa sara'\npresentata una visualizzazione grafica dei dati.\n\n");
    printf("Procedere? (0: no, 1: si')  ");
    scanf("%d", &scelta);

    switch(scelta)
    {
    case 0:

        printf("\n\n");
        system("pause");
        exit(0);

        break;
    case 1:

        break;
    default:

        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    printf("\nSelezionare il metodo che si preferisce tra i seguenti quattro:\n\n1. Metodo di bisezione\n2. Metodo delle secanti\n3. Metodo delle tangenti\n4. Metodo del punto fisso\n\n");
    scanf("%d", &scelta);

    if((1 <= scelta) && (scelta <= 4))
    {
        informazioni[1] = scelta;
    }
    else
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    if((1 <= ((int)informazioni[1]))&&(((int)informazioni[1]) <= 3))
    {
         printf("\nSelezionare la funzione che si preferisce tra le seguenti dieci:\n\n1.  f(x) = x^2 - 2\n2.  f(x) = 5(x^2) - 2\n3.  f(x) = 10(x^2) - 2\n4.  f(x) = x^3");
         printf("\n5.  f(x) = (x + 1)(x - 3)(x - 10)\n6.  f(x) = arctg(x)\n7.  f(x) = x^2 - x - 2\n8.  f(x) = sqrt(x + 2) - x\n9.  f(x) = 1 + (2/x) - x\n10. f(x) = |cos(x)|\n\n");
         scanf("%d", &scelta);

         if((1 <= scelta) && (scelta <= 10))
         {
             informazioni[0] = scelta;
         }
         else
         {
             printf("\n\nInput non valido.\n\n\n");
             system("pause");
             exit(0);
         }

         printf("\nInserire l'estremo sinistro dell'intervallo che si ha intenzione di considerare (a):  ");
         scanf("%lf", &informazioni[2]);
         printf("\nInserire l'estremo destro dell'intervallo che si ha intenzione di considerare (b):  ");
         scanf("%lf", &informazioni[3]);

         if(informazioni[2] >= informazioni[3])
         {
             printf("\n\nLa scelta degli estremi e' incompatibile.\n\n\n");
             system("pause");
             exit(0);
         }

         printf("\nN. Verranno esclusi o approssimati eventuali valori dell'intervallo che non appartengono al dominio della funzione.\n");

         if((funzione_reale(informazioni[0], 0, informazioni[2])*funzione_reale(informazioni[0], 0, informazioni[3])) >= 0)
         {
             printf("\nIn accordo con il Teorema di esistenza degli zeri, le condizioni iniziali non sono sufficienti\nper l'esistenza di almeno uno zero.\n\n");
         }
    }
    else
    {
        printf("\nSelezionare la funzione che si preferisce tra le seguenti due:\n\n11.  f(x) = x^3 + 2(x^2) + 10x - 20\n12.  f(x) = x^3 + 4x - 2\n\n");
        scanf("%lf", &informazioni[0]);

        if((((int)informazioni[0]) < 11) || (((int)informazioni[0]) > 12))
        {
            printf("\n\nInput non valido.\n\n\n");
            system("pause");
            exit(0);
        }
    }

    if(1 == ((int)informazioni[1]))
    {
        printf("\nInserire una tolleranza (o precisione) reale positiva (epsilon):  ");
        scanf("%lf", &informazioni[4]);

        if(informazioni[4] <= 0)
        {
            printf("\n\nInput non valido.\n\n\n");
            system("pause");
            exit(0);
        }
    }
    else
    {
        printf("\nInserire un punto iniziale (x0):  ");
        scanf("%lf", &informazioni[5]);

        if((2 <= ((int)informazioni[1]))&&(((int)informazioni[1]) <= 3))
        {
            if((informazioni[5] < informazioni[2]) || (informazioni[5] > informazioni[3]))
            {
                printf("\n\nInput non valido.\n\n\n");
                system("pause");
                exit(0);
            }
        }

        printf("\nInserire una tolleranza (o precisione) reale positiva (epsilon):  ");
        scanf("%lf", &informazioni[4]);

        if(informazioni[4] <= 0)
        {
            printf("\n\nInput non valido.\n\n\n");
            system("pause");
            exit(0);
        }

        if((2 <= ((int)informazioni[1]))&&(((int)informazioni[1]) <= 4))
        {
            printf("\nInserire il massimo numero di iterazioni consentite (K):  ");
            scanf("%lf", &informazioni[6]);

            if(((int)informazioni[6]) <= 0)
            {
                printf("\n\nInput non valido.\n\n\n");
                system("pause");
                exit(0);
            }
        }
    }
}

void applica_metodi(double informazioni[])
{
    int contatore = 0;
    double an, bn, cn, cn1;
    FILE * fPointer1;
    FILE * fPointer2;
    an = informazioni[2];
    bn = informazioni[3];

    printf("\n*****************\n");

    switch((int)informazioni[1])
    {
    case 1:

        cn1 = ((an + bn)/((double)2));

        do
        {
            cn = cn1;

            if(funzione_reale(informazioni[0], 0, cn1) < 0)
            {
                an = cn1;
                cn1 = ((an + bn)/((double)2));
            }
            if(funzione_reale(informazioni[0], 0, cn1) == 0)
            {
                printf("\nSoluzione esatta trovata! Si tratta di: %.10f.\n", cn1);
                contatore++;
                break;
            }
            if(funzione_reale(informazioni[0], 0, cn1) > 0)
            {
                bn = cn1;
                cn1 = ((an + bn)/((double)2));
            }

            contatore++;
        }
        while(fabs(cn1 - cn) >= informazioni[4]);

        if(contatore > ((int)ceil((log(informazioni[4]/(informazioni[3] - informazioni[2]))/log(((double)1)/((double)2))))))
        {
            an = informazioni[2];
            bn = informazioni[3];

            cn1 = ((an + bn)/((double)2));

            for(int i = 1; i <= ((int)ceil((log(informazioni[4]/(informazioni[3] - informazioni[2]))/log(((double)1)/((double)2))))); i++)
            {
                cn = cn1;

                if(funzione_reale(informazioni[0], 0, cn1) < 0)
                {
                    an = cn1;
                    cn1 = ((an + bn)/((double)2));
                }
                if(funzione_reale(informazioni[0], 0, cn1) == 0)
                {
                    printf("\nSoluzione esatta trovata! Si tratta di: %.10f.\n", cn1);
                    break;
                }
                if(funzione_reale(informazioni[0], 0, cn1) > 0)
                {
                    bn = cn1;
                    cn1 = ((an + bn)/((double)2));
                }
            }
        }

        printf("\nIl massimo numero di iterazioni consentite e':  %d\n", ((int)ceil((log(informazioni[4]/(informazioni[3] - informazioni[2]))/log(((double)1)/((double)2))))));
        printf("\nIl numero di iterazioni necessarie alla verifica del criterio d'arresto e':  %d\n", contatore);
        printf("\nL'immagine tramite f della radice approssimata e':  f(%.10f) = %.10f\n", cn1, funzione_reale(informazioni[0], 0, cn1));

        break;
    case 2:

        cn1 = an - (((bn - an)*funzione_reale(informazioni[0], 0, an))/(funzione_reale(informazioni[0], 0, bn) - funzione_reale(informazioni[0], 0, an)));

        do
        {
            cn = cn1;

            if(funzione_reale(informazioni[0], 0, cn1) < 0)
            {
                an = cn1;
                cn1 = an - (((bn - an)*funzione_reale(informazioni[0], 0, an))/(funzione_reale(informazioni[0], 0, bn) - funzione_reale(informazioni[0], 0, an)));
            }
            if(funzione_reale(informazioni[0], 0, cn1) == 0)
            {
                printf("\nSoluzione esatta trovata! Si tratta di: %.10f.\n", cn1);
                contatore++;
                break;
            }
            if(funzione_reale(informazioni[0], 0, cn1) > 0)
            {
                bn = cn1;
                cn1 = an - (((bn - an)*funzione_reale(informazioni[0], 0, an))/(funzione_reale(informazioni[0], 0, bn) - funzione_reale(informazioni[0], 0, an)));
            }

            contatore++;
        }
        while((fabs(cn1 - cn) + fabs(funzione_reale(informazioni[0], 0, cn1))) >= informazioni[4]);

        if(contatore > ((int)informazioni[6]))
        {
            an = informazioni[2];
            bn = informazioni[3];

            cn1 = an - (((bn - an)*funzione_reale(informazioni[0], 0, an))/(funzione_reale(informazioni[0], 0, bn) - funzione_reale(informazioni[0], 0, an)));

            for(int i = 1; i <= ((int)informazioni[6]); i++)
            {
                cn = cn1;

                if(funzione_reale(informazioni[0], 0, cn1) < 0)
                {
                    an = cn1;
                    cn1 = an - (((bn - an)*funzione_reale(informazioni[0], 0, an))/(funzione_reale(informazioni[0], 0, bn) - funzione_reale(informazioni[0], 0, an)));
                }
                if(funzione_reale(informazioni[0], 0, cn1) == 0)
                {
                    printf("\nSoluzione esatta trovata! Si tratta di: %.10f.\n", cn1);
                    break;
                }
                if(funzione_reale(informazioni[0], 0, cn1) > 0)
                {
                    bn = cn1;
                    cn1 = an - (((bn - an)*funzione_reale(informazioni[0], 0, an))/(funzione_reale(informazioni[0], 0, bn) - funzione_reale(informazioni[0], 0, an)));
                }
            }
        }

        printf("\nIl massimo numero di iterazioni consentite e':  %d\n", ((int)informazioni[6]));
        printf("\nIl numero di iterazioni necessarie alla verifica del criterio d'arresto e':  %d\n", contatore);
        printf("\nL'immagine tramite f della radice approssimata e':  f(%.10f) = %.10f\n", cn1, funzione_reale(informazioni[0], 0, cn1));

        break;
    case 3:

        cn = cn1 = informazioni[5];

        do
        {
            cn = cn1;
            cn1 = cn - (funzione_reale(informazioni[0], 0, cn)/funzione_reale(informazioni[0], 1, cn));

            contatore++;
        }
        while((fabs(cn1 - cn) + fabs(funzione_reale(informazioni[0], 0, cn1))) >= informazioni[4]);

        if(contatore > ((int)informazioni[6]))
        {
            cn = cn1 = informazioni[5];

            for(int i = 1; i <= ((int)informazioni[6]); i++)
            {
                cn = cn1;
                cn1 = cn - (funzione_reale(informazioni[0], 0, cn)/funzione_reale(informazioni[0], 1, cn));
            }
        }

        printf("\nIl massimo numero di iterazioni consentite e':  %d\n", ((int)informazioni[6]));
        printf("\nIl numero di iterazioni necessarie alla verifica del criterio d'arresto e':  %d\n", contatore);
        printf("\nL'immagine tramite f della radice approssimata e':  f(%.10f) = %.10f\n", cn1, funzione_reale(informazioni[0], 0, cn1));

        break;
    case 4:

        fPointer1 = fopen("dati.txt", "w");

        switch(((int)informazioni[0]))
        {
        case 11:

            printf("\nRisolvere l'equazione f(x) = x^3 + 2(x^2) + 10x - 20 = 0 e' equivalente a risolvere l'equazione\ng(x) = 20 / (x^2 + 2x + 10) = x, ");
            printf("e a sua volta cio' e' equivalente a trovare i punti fissi di g.\n");
            printf("Si procedera' pertanto (iterativamente) alla risoluzione di g(x) = x.\n");

            cn = cn1 = informazioni[5];

            do
            {
                cn = cn1;
                cn1 = funzione_reale(informazioni[0] , 0, cn);

                fprintf(fPointer1, "%.10f\n", cn1);

                contatore++;
            }
            while(fabs(cn1 - cn) >= informazioni[4]);

            fclose(fPointer1);

            if(contatore > ((int)informazioni[6]))
            {
                fPointer1 = fopen("dati.txt", "w");

                cn = cn1 = informazioni[5];

                for(int i = 1; i <= ((int)informazioni[6]); i++)
                {
                    cn = cn1;
                    cn1 = funzione_reale(informazioni[0], 0, cn);

                    fprintf(fPointer1, "%.10f\n", cn1);
                }

                fclose(fPointer1);
            }

            printf("\nIl massimo numero di iterazioni consentite e':  %d\n", ((int)informazioni[6]));
            printf("\nIl numero di iterazioni necessarie alla verifica del criterio d'arresto e':  %d\n", contatore);

            break;
        case 12:

            printf("\nRisolvere l'equazione f(x) = x^3 + 4x - 2 = 0 e' equivalente a risolvere l'equazione\ng(x) = (2(x^3) + 2) / (3(x^2) + 4) = x, ");
            printf("e a sua volta cio' e' equivalente a trovare i punti fissi di g.\n");
            printf("Si procedera' pertanto (iterativamente) alla risoluzione di g(x) = x.\n");

            cn = cn1 = informazioni[5];

            do
            {
                cn = cn1;
                cn1 = funzione_reale(informazioni[0] , 0, cn);

                fprintf(fPointer1, "%.10f\n", cn1);

                contatore++;
            }
            while(fabs(cn1 - cn) >= informazioni[4]);

            fclose(fPointer1);

            if(contatore > ((int)informazioni[6]))
            {
                fPointer1 = fopen("dati.txt", "w");

                cn = cn1 = informazioni[5];

                for(int i = 1; i <= ((int)informazioni[6]); i++)
                {
                    cn = cn1;
                    cn1 = funzione_reale(informazioni[0], 0, cn);

                    fprintf(fPointer1, "%.10f\n", cn1);
                }

                fclose(fPointer1);
            }

            printf("\nIl massimo numero di iterazioni consentite e':  %d\n", ((int)informazioni[6]));
            printf("\nIl numero di iterazioni necessarie alla verifica del criterio d'arresto e':  %d\n", contatore);

            break;
        default:
            ;
        }

        break;
    default:
        ;
    }

    if((1 <= ((int)informazioni[1]))&&(((int)informazioni[1]) <= 3))
    {
        fPointer1 = fopen("dati.txt", "w");

        switch(((int)informazioni[0]))
        {
        case 1:

            fprintf(fPointer1, "plot [%.10f to %.10f] x**2 - 2", informazioni[2], informazioni[3]);

            break;
        case 2:

            fprintf(fPointer1, "plot [%.10f to %.10f] 5*(x**2) - 2", informazioni[2], informazioni[3]);

            break;
        case 3:

            fprintf(fPointer1, "plot [%.10f to %.10f] 10*(x**2) - 2", informazioni[2], informazioni[3]);

            break;
        case 4:

            fprintf(fPointer1, "plot [%.10f to %.10f] x**3", informazioni[2], informazioni[3]);

            break;
        case 5:

            fprintf(fPointer1, "plot [%.10f to %.10f] (x + 1)*(x - 3)*(x - 10)", informazioni[2], informazioni[3]);

        break;
        case 6:

            fprintf(fPointer1, "plot [%.10f to %.10f] atan(x)", informazioni[2], informazioni[3]);

            break;
        case 7:

            fprintf(fPointer1, "plot [%.10f to %.10f] x**2 - x - 2", informazioni[2], informazioni[3]);

            break;
        case 8:

            fprintf(fPointer1, "plot [%.10f to %.10f] sqrt(x + 2) - x", informazioni[2], informazioni[3]);

            break;
        case 9:

            fprintf(fPointer1, "plot [%.10f to %.10f] 1 + (2. / x) - x", informazioni[2], informazioni[3]);

            break;
        case 10:

            fprintf(fPointer1, "plot [%.10f to %.10f] abs(cos(x))", informazioni[2], informazioni[3]);

            break;
        default:
            ;
        }

        fclose(fPointer1);

        printf("\nVisualizzo il grafico di f nell'intervallo [%.4f, %.4f]...\n\n", informazioni[2], informazioni[3]);

        system("start wgnuplot.exe -p dati.txt");
    }
    else
    {
        fPointer2 = fopen("comando.txt", "w");
        fprintf(fPointer2, "plot \"dati.txt\" with linespoints linetype 7 linecolor 6");
        fclose(fPointer2);

        printf("\nVisualizzo la successione di punti ottenuta...\n\n");

        system("start wgnuplot.exe -p comando.txt");
    }
}
