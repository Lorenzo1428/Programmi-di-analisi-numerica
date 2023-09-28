#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double norma_infinita(double[], double[]);
int sgn(double);
double funzione_reale(int, double);
void presentazione_e_configurazione(double[]);
void applica_interpolazione(double[]);

int main()
{
    double informazioni[10] = {};

    presentazione_e_configurazione(informazioni);
    applica_interpolazione(informazioni);

    printf("\n\n");
    system("pause");

    return 0;
}

double norma_infinita(double V[], double I[])
{
    double norma = fabs(V[0]);

    for(int i = 0; i <= (((int)I[3]) - 1); i++)
    {
        if(norma < fabs(V[i]))
        {
            norma = fabs(V[i]);
        }
    }

    return norma;
}

int sgn(double x)
{
    if(x < 0)
    {
        return -1;
    }
    if(x == 0)
    {
        return 0;
    }
    if(x > 0)
    {
        return 1;
    }
}

double funzione_reale(int f, double x)
{
    switch(f)
    {
    case 1:

        return sin(x);

        break;
    case 2:

        return sin(3*x);

        break;
    case 3:

        return x*cos(x);

        break;
    case 4:

        if(x <= 0)
        {
            x = pow(10, -10);
        }

        return log(x);

        break;
    case 5:

        return exp(x);

        break;
    case 6:

        return pow(x, 5) + 3*pow(x, 4) + 2*pow(x, 3) - pow(x, 2) - 5*x + 1;

        break;
    case 7:

        return (((double)1)/(1 + pow(x, 2)));

        break;
    case 8:

        return fabs(x);

        break;
    case 9:

        return fabs(x)*sin(x);

        break;
    case 10:

        return sin(pow(x, 2));

        break;
    case 11:

        return fabs(sin(pow(x, 2)));

        break;
    case 12:

        return sgn(x);

        break;
    default:
        ;
    }
}

void presentazione_e_configurazione(double I[])
{
    int scelta = 0;

    printf("Il programma e' in grado di effettuare l'interpolazione polinomiale di Lagrange su alcune funzioni predefinite.\n");
    printf("Al termine del processo di interpolazione saranno presentati attraverso una visualizzazione grafica:\n\n");
    printf("1. il grafico esatto della funzione\n2. il grafico del polinomio di Lagrange o dell'approsimazione di Lagrange composita (lineare o quadratica)\n\n");
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

    printf("\nSelezionare la funzione che si preferisce tra le seguenti dodici:\n\n1.  f(x) = sin(x)\n2.  f(x) = sin(3x)\n3.  f(x) = xcos(x)\n4.  f(x) = ln(x)\n5.  f(x) = e^x\n");
    printf("6.  f(x) = x^5 + 3(x^4) + 2(x^3) - x^2 - 5x + 1\n7.  f(x) = 1/(1 + x^2)\n8.  f(x) = |x|\n9.  f(x) = |x|sin(x)\n10. f(x) = sin(x^2)\n11. f(x) = |sin(x^2)|\n12. f(x) = sgn(x)\n\n");
    scanf("%lf", &I[0]);

    if(!((1 <= ((int)I[0]))&&(((int)I[0]) <= 12)))
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    printf("\nInserire l'estremo sinistro dell'intervallo che si ha intenzione di considerare (a):  ");
    scanf("%lf", &I[1]);
    printf("\nInserire l'estremo destro dell'intervallo che si ha intenzione di considerare (b):  ");
    scanf("%lf", &I[2]);

    if(I[1] >= I[2])
    {
        printf("\n\nLa scelta degli estremi e' incompatibile.\n\n\n");
        system("pause");
        exit(0);
    }

    if((((int)I[0]) == 4)&&(I[1] <= 0))
    {
        I[1] = 0.1;
    }

    printf("\nN. Verranno esclusi o approssimati eventuali valori dell'intervallo che non appartengono al dominio della funzione.\n");
    printf("\nInserire il numero (N <= 50) dei sottointervalli della partizione uniforme dell'intervallo [%.2f, %.2f]:  ", I[1], I[2]);
    scanf("%lf", &I[3]);

    if((((int)I[3]) <= 0)||(((int)I[3]) >= 51))
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    printf("\nSelezionare l'interpolazione che si preferisce (1: semplice, 2: composita):  ");
    scanf("%d", &scelta);

    if(!((1 <= scelta)&&(scelta <= 2)))
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    switch(scelta)
    {
    case 1:

        I[4] = 0;

        break;
    case 2:

        printf("\nInserire il grado (n <= 2) del polinomio interpolatore dell'approsimazione di Lagrange composita\n(1: lineare, 2: quadratica):  ");
        scanf("%lf", &I[4]);

        if(!((1 <= ((int)I[4]))&&(((int)I[4]) <= 2)))
        {
            printf("\n\nInput non valido.\n\n\n");
            system("pause");
            exit(0);
        }

        break;
    default:
        ;
    }
}

void applica_interpolazione(double I[])
{
    double maxabs, sommatoria, produttoria;
    double nodi_di_interpolazione[10000] = {};
    double punti_medi[10000] = {};
    double nodi_e_punti_medi[10000] = {};
    double errori_punti_medi[10000] = {};
    FILE *fPointer1, *fPointer2;
    maxabs = sommatoria = 0.0;
    produttoria = 1;
    nodi_di_interpolazione[0] = I[1];

    for(int i = 1; i <= ((int)I[3]); i++)
    {
        nodi_di_interpolazione[i] =  nodi_di_interpolazione[i - 1] + ((I[2] - I[1])/((int)I[3]));
        punti_medi[i - 1] = (nodi_di_interpolazione[i - 1] + nodi_di_interpolazione[i])/((double)2);
    }

    for(int i = 0; i <= ((int)I[3]); i++)
    {
        nodi_e_punti_medi[2*i] = nodi_di_interpolazione[i];
        nodi_e_punti_medi[2*i + 1] = punti_medi[i];
    }

    maxabs = fabs(funzione_reale(((int)I[0]), I[1]));

    for(int i = 0; i <= 100000; i++)
    {
        if(maxabs < fabs(funzione_reale(((int)I[0]), I[1] + i*((I[2] - I[1])/100000))))
        {
            maxabs = fabs(funzione_reale(((int)I[0]), I[1] + i*((I[2] - I[1])/100000)));
        }
    }

    fPointer1 = fopen("comando.txt", "w");
    fPointer2 = fopen("dati.txt", "w");

    switch(((int)I[0]))
    {
    case 1:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] sin(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 2:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] sin(3*x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 3:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] x*cos(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 4:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] log(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 5:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] exp(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 6:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] (x**5 + 3*(x**4) + 2*(x**3) - x**2 - 5*x + 1), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 7:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] (1./(1 + x**2)), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 8:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] abs(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 9:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] abs(x)*sin(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 10:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] sin(x**2), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 11:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] abs(sin(x**2)), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    case 12:

        fprintf(fPointer1, "plot [%f:%f] [%f:%f] sgn(x), ", I[1], I[2], -(maxabs + 0.5), maxabs + 0.5);

        break;
    default:
        ;
    }

    switch(((int)I[4]))
    {
    case 0:

        for(int i = 0; i <= (((int)I[3]) - 1); i++)
        {
            for(int j = 0; j <= ((int)I[3]); j++)
            {
                for(int k = 0; k <= ((int)I[3]); k++)
                {
                    if(j != k)
                    {
                        produttoria *= ((punti_medi[i] - nodi_di_interpolazione[k])/(nodi_di_interpolazione[j] - nodi_di_interpolazione[k]));
                    }
                }

                sommatoria += funzione_reale(((int)I[0]), nodi_di_interpolazione[j])*produttoria;
                produttoria = 1;
            }

            errori_punti_medi[i] = sommatoria - funzione_reale(((int)I[0]), punti_medi[i]);
            sommatoria = 0;
        }

        printf("\nLa norma infinito del vettore degli errori sui punti medi e':  %f\n", norma_infinita(errori_punti_medi, I));
        fprintf(fPointer1, "(");

        for(int i = 0; i <= ((int)I[3]); i++)
        {
            fprintf(fPointer1, "(%f)", funzione_reale(((int)I[0]), nodi_di_interpolazione[i]));

            for(int j = 0; j <= ((int)I[3]); j++)
            {
                if(i != j)
                {
                    fprintf(fPointer1, "*((x-(%f))/(%f))", nodi_di_interpolazione[j], nodi_di_interpolazione[i] - nodi_di_interpolazione[j]);
                }
            }

            if(i != ((int)I[3]))
            {
                fprintf(fPointer1, " + ");
            }
        }

        fprintf(fPointer1, ")");

        break;
    case 1:

        for(int i = 0; i <= (((int)I[3]) - 1); i++)
        {
            errori_punti_medi[i] = (((punti_medi[i] - nodi_di_interpolazione[i])/(nodi_di_interpolazione[i + 1] - nodi_di_interpolazione[i]))*(funzione_reale(((int)I[0]), nodi_di_interpolazione[i + 1]) - funzione_reale(((int)I[0]), nodi_di_interpolazione[i])) + funzione_reale(((int)I[0]), nodi_di_interpolazione[i])) - funzione_reale(((int)I[0]), punti_medi[i]);
        }

        printf("\nLa norma infinito del vettore degli errori sui punti medi e':  %f\n", norma_infinita(errori_punti_medi, I));
        fprintf(fPointer1, "\"dati.txt\" with linespoints linetype 7 linecolor 6");

        for(int i = 0; i <= ((int)I[3]); i++)
        {
            fprintf(fPointer2, "%f, %f\n", nodi_di_interpolazione[i], funzione_reale(((int)I[0]), nodi_di_interpolazione[i]));
        }

        break;
    case 2:

        for(int i = 0; i <= (((int)I[3]) - 1); i++)
        {
            for(int j = i*2; j <= i*2 + 2; j++)
            {
                for(int k = i*2; k <= i*2 + 2; k++)
                {
                    if(j != k)
                    {
                        produttoria *= ((punti_medi[i] - nodi_e_punti_medi[k])/(nodi_e_punti_medi[j] - nodi_e_punti_medi[k]));
                    }
                }

                sommatoria += funzione_reale(((int)I[0]), nodi_e_punti_medi[j])*produttoria;
                produttoria = 1;
            }

            errori_punti_medi[i] = sommatoria - funzione_reale(((int)I[0]), punti_medi[i]);
            sommatoria = 0;
        }

        printf("\nLa norma infinito del vettore degli errori sui punti medi e':  %f\n", norma_infinita(errori_punti_medi, I));

        for(int i = 0; i <= (((int)I[3]) - 1); i++)
        {
            fprintf(fPointer1, "[%f:%f] (", nodi_di_interpolazione[i], nodi_di_interpolazione[i + 1]);

            for(int j = i*2; j <= i*2 + 2; j++)
            {
                fprintf(fPointer1, "(%f)", funzione_reale(((int)I[0]), nodi_e_punti_medi[j]));

                for(int k = i*2; k <= i*2 + 2; k++)
                {
                    if(j != k)
                    {
                        fprintf(fPointer1, "*((x-(%f))/(%f))", nodi_e_punti_medi[k], nodi_e_punti_medi[j] - nodi_e_punti_medi[k]);
                    }
                }

                if(j != i*2 + 2)
                {
                    fprintf(fPointer1, " + ");
                }
                if((j == i*2 + 2)&&(i != (((int)I[3]) - 1)))
                {
                    fprintf(fPointer1, "), ");
                }
            }
        }

        fprintf(fPointer1, ")");

        break;
    default:
        ;
    }

    fclose(fPointer1);
    fclose(fPointer2);

    system("start wgnuplot.exe -p comando.txt");
}
