#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ALLOWED_DIM_MATRIX 100
#define MAX_ALLOWED_ITERATIONS 1000

double norma_Euclidea(double[], double[]);
double norma_infinita(double[], double[]);
int presentazione_e_configurazione(double[]);
int ottieni_matrici(double[][MAX_ALLOWED_DIM_MATRIX], double[], double[]);
int applica_Jacobi(double[][MAX_ALLOWED_DIM_MATRIX], double[], double[]);

int main()
{
    double A[MAX_ALLOWED_DIM_MATRIX][MAX_ALLOWED_DIM_MATRIX] = {};
    double B[MAX_ALLOWED_DIM_MATRIX] = {};
    double informazioni[6] = {};

    presentazione_e_configurazione(informazioni);
    ottieni_matrici(A, B, informazioni);
    applica_Jacobi(A, B, informazioni);

    system("start wgnuplot.exe -p comando.txt");
    printf("\n");
    system("pause");

    return 0;
}

double norma_Euclidea(double V[], double I[])
{
    double norma = 0.0;

    for(int i = 0; i <= (((int)I[3]) - 1); i++)
    {
        if(V[i] == V[i])
        {
            norma = norma + pow(V[i], 2);
        }
    }

    norma = sqrt(norma);

    return norma;
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

int presentazione_e_configurazione(double I[])
{
    int scelta, iterazioni;
    scelta = iterazioni = 0;
    double epsilon = 0.0;

    printf("\t\t\t****Risolutore di sistemi lineari mediante metodo di Jacobi****\t\t\t\n\n");
    printf("Il programma e' in grado di risolvere (mediante Jacobi e con approssimazione) qualsiasi sistema lineare che goda\n");
    printf("delle seguenti proprieta' sulla matrice dei coefficienti (A):\n\n");
    printf("-quadrata;\n-non singolare;\n-a diagonale strettamente dominante;\n-di ordine non superiore a %d.\n\n", MAX_ALLOWED_DIM_MATRIX);
    printf("Procedere? (0: no, 1: si')  ");
    scanf("%d", &scelta);

    if((0 == scelta) || (1 == scelta))
    {
        switch (scelta)
        {
        case 0:

            printf("\n\n");
            system("pause");
            exit(0);

        case 1:
            break;
        }
    }
    else
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    printf("\nSelezionare la norma che si preferisce (1: Euclidea, 2: Infinita):  ");
    scanf("%d", &scelta);

    if((1 == scelta) || (2 == scelta))
    {
        switch (scelta)
        {
        case 1:
            I[1] = 1;
            break;
        case 2:
            I[1] = 2;
            break;
        }
    }
    else
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    printf("\nSi preferisce far arrestare le iterazioni a priori o a posteriori? (1: a priori, 2: a posteriori)  ");
    scanf("%d", &scelta);

    if((1 == scelta) || (2 == scelta))
    {
        switch (scelta)
        {
        case 1:
            printf("\nInserire il massimo numero di iterazioni (minore o uguale a %d):  ", MAX_ALLOWED_ITERATIONS);
            scanf("%d", &iterazioni);

            if((1 <= iterazioni) && (iterazioni <= MAX_ALLOWED_ITERATIONS))
            {
                I[0] = iterazioni;
                I[2] = 0;
            }
            else
            {
                printf("\n\nInput non valido.\n\n\n");
                system("pause");
                exit(0);
            }
            break;
        case 2:
            printf("\nInserire una tolleranza (o precisione) reale positiva (epsilon):  ");
            scanf("%lf", &epsilon);

            if(0.0 < epsilon)
            {
                I[0] = 0;
                I[2] = epsilon;
            }
            else
            {
                printf("\n\nInput non valido.\n\n\n");
                system("pause");
                exit(0);
            }
            break;
        }
    }
    else
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }

    printf("\nSi preferisce inserire la matrice manualmente, mediante file o casualmente?\n(1: manualmente, 2: mediante file, 3: casualmente)  ");
    scanf("%lf", &I[5]);

    if((((int)I[5]) <= 0)||(((int)I[5]) >= 4))
    {
        printf("\n\nInput non valido.\n\n\n");
        system("pause");
        exit(0);
    }
}

int ottieni_matrici(double A[][MAX_ALLOWED_DIM_MATRIX], double B[], double I[])
{
    srand(time(0));
    int l1, l2, c;
    double sommatoria;
    double C[2600] = {};
    FILE *fP;
    l1 = l2 = c = 0;
    sommatoria = 0.0;

    switch(((int)I[5]))
    {
        case 1:

            printf("\nInserire l'ordine della matrice dei coefficienti (A):  ");
            scanf("%lf", &I[3]);

            if((1 <= (int)I[3]) && ((int)I[3] <= MAX_ALLOWED_DIM_MATRIX))
            {
                printf("\nInserire gli elementi della matrice dei coefficienti (A)...\n\n");

                for(int i = 0; i <= ((int)I[3] - 1); i++)
                {
                    for(int j = 0; j <= ((int)I[3] - 1); j++)
                    {
                        printf("A[%d][%d] = ", i + 1, j + 1);
                        scanf("%lf", &A[i][j]);
                    }
                }

                printf("\nInserire gli elementi del vettore dei termini noti (B)...\n\n");

                for(int i = 0; i <= ((int)I[3] - 1); i++)
                {
                    printf("B[%d] = ", i + 1);
                    scanf("%lf", &B[i]);
                }
            }
            else
            {
                printf("\n\nInput non valido.\n\n\n");
                system("pause");
                exit(0);
            }

            break;
        case 2:

            fP = fopen("matrice orlata.txt", "r");

            fscanf(fP, "%lf", &C[l2]);
            l2++;

            while(!feof(fP))
            {
                if(fgetc(fP) != '|')
                {
                    fscanf(fP, "%lf", &C[l2]);
                    l2++;
                }
                else
                {
                    fscanf(fP, "%lf", &B[l1]);
                    l1++;
                }
            }

            fclose(fP);

            I[3] = l1;

            for(int i = 0; i <= (((int)I[3]) - 1); i++)
            {
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    A[i][j] = C[i + c];
                    c++;
                }
            }

            break;
        case 3:

            printf("\nInserire l'ordine della matrice dei coefficienti (A):  ");
            scanf("%lf", &I[3]);

            if((1 <= (int)I[3]) && ((int)I[3] <= MAX_ALLOWED_DIM_MATRIX))
            {
                for(int i = 0; i <= (((int)I[3]) - 1); i++)
                {
                    for(int j = 0; j <= (((int)I[3]) - 1); j++)
                    {
                        if(i != j)
                        {
                            A[i][j] = 10*(((double)(rand() - rand()))/((double)rand()));
                            sommatoria += fabs(A[i][j]);
                        }
                    }

                    do
                    {
                        A[i][i] = 10*(((double)(rand() - rand()))/((double)rand()));
                    }
                    while(fabs(A[i][i]) <= sommatoria);

                    sommatoria = 0.0;

                    B[i] = 10*(((double)(rand() - rand()))/((double)rand()));
                }

                fP = fopen("matrice casuale.txt", "w");

                for(int i = 0; i <= (((int)I[3]) - 1); i++)
                {
                    for(int j = 0; j <= (((int)I[3]) - 1); j++)
                    {
                        fprintf(fP, "%.4f ", A[i][j]);
                    }

                    fprintf(fP, "| %.4f\n", B[i]);
                }

                fclose(fP);
            }
            else
            {
                printf("\n\nInput non valido.\n\n\n");
                system("pause");
                exit(0);
            }

            break;
        default:
            ;
    }

    for(int i = 0; i <= (((int)I[3]) - 1); i++)
    {
        for(int j = 0; j <= (((int)I[3]) - 1); j++)
        {
            if(i != j)
            {
                sommatoria += fabs(A[i][j]);
            }
        }

        if(sommatoria >= fabs(A[i][i]))
        {
            printf("\n\nLa matrice dei coefficienti (A) inserita non e' a diagonale strettamente dominante!\n\n\n");
            system("pause");
            exit(0);
        }

        sommatoria = 0;
    }

    I[4] = 1;
}

int applica_Jacobi(double A[][MAX_ALLOWED_DIM_MATRIX], double B[], double I[])
{
    int counter;
    double sommatoria, residuo;
    double ausiliare[MAX_ALLOWED_DIM_MATRIX] = {};
    double Xk[MAX_ALLOWED_DIM_MATRIX] = {};
    double VD[MAX_ALLOWED_DIM_MATRIX] = {};
    double AXk[MAX_ALLOWED_DIM_MATRIX] = {};
    double Rk[MAX_ALLOWED_DIM_MATRIX] = {};
    FILE *fP, *fP1;
    counter = 0;
    sommatoria = residuo = 0.0;

    fP1 = fopen("comando.txt", "w");
    fprintf(fP1, "plot \"dati.txt\" with linespoints linetype 7 linecolor 6");
    fclose(fP1);

    switch ((int)I[1])
    {
    case 1:

        fP = fopen("dati.txt", "w");

        if(0 != ((int)I[0]))
        {
            for(int i = 1; i <= ((int)I[0]); i++)
            {
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    for(int k = 0; k <= (((int)I[3]) - 1); k++)
                    {
                        if(j != k)
                        {
                            sommatoria += A[j][k]*Xk[k];
                        }
                    }

                    ausiliare[j] = (B[j] - sommatoria)/A[j][j];
                    sommatoria = 0.0;
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    Xk[j] = ausiliare[j];
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    AXk[j] = 0.0;
                    Rk[j] = 0.0;
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    for(int k = 0; k <= (((int)I[3]) - 1); k++)
                    {
                        AXk[j] += A[j][k]*Xk[k];
                    }
                }

                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    Rk[j] = AXk[j] - B[j];
                    //printf("\n%f\t%f\t%f\n", Rk[j], AXk[j], B[j]);
                }

                if(1 == ((int)I[4]))
                {
                    if(i <= 10)
                    {
                        switch (i)
                        {
                        case 1:
                            printf("\n*****************\n");
                            printf("\nPrima iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 2:
                            printf("\nSeconda iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 3:
                            printf("\nTerza iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 4:
                            printf("\nQuarta iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 5:
                            printf("\nQuinta iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 6:
                            printf("\nSesta iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 7:
                            printf("\nSettima iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 8:
                            printf("\nOttava iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 9:
                            printf("\nNona iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 10:
                            printf("\nDecima iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        }
                    }
                    else
                    {
                        printf("\n%d-esima iterazione:\n", i);

                        for(int j = 0; j <= (((int)I[3]) - 2); j++)
                        {
                            printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                        }

                        printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                        fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                        if(((int)I[0]) == i)
                        {
                            fclose(fP);
                            return 0;
                        }
                    }
                }
            }
            }
            else
            {
                do
                {
                    for(int j = 0; j <= (((int)I[3]) - 1); j++)
                    {
                        for(int k = 0; k <= (((int)I[3]) - 1); k++)
                        {
                            if(j != k)
                            {
                                sommatoria += A[j][k]*Xk[k];
                            }
                        }

                        ausiliare[j] = (B[j] - sommatoria)/A[j][j];
                        sommatoria = 0.0;
                    }
                    for(int i = 0; i <= (((int)I[3]) - 1); i++)
                    {
                        VD[i] = ausiliare[i] - Xk[i];
                    }
                    for(int i = 0; i <= (((int)I[3]) - 1); i++)
                    {
                        Xk[i] = ausiliare[i];
                    }
                    for(int j = 0; j <= (((int)I[3]) - 1); j++)
                    {
                        AXk[j] = 0.0;
                        Rk[j] = 0.0;
                    }
                    for(int j = 0; j <= (((int)I[3]) - 1); j++)
                    {
                        for(int k = 0; k <= (((int)I[3]) - 1); k++)
                        {
                            AXk[j] += A[j][k]*Xk[k];
                        }
                    }
                    for(int j = 0; j <= (((int)I[3]) - 1); j++)
                    {
                        Rk[j] = AXk[j] - B[j];
                    }

                    if(1 == ((int)I[4]))
                    {
                        counter++;

                        if(counter <= 10)
                        {
                            switch (counter)
                            {
                            case 1:
                                printf("\n*****************\n");
                                printf("\nPrima iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 2:
                                printf("\nSeconda iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 3:
                                printf("\nTerza iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 4:
                                printf("\nQuarta iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 5:
                                printf("\nQuinta iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 6:
                                printf("\nSesta iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 7:
                                printf("\nSettima iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 8:
                                printf("\nOttava iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 9:
                                printf("\nNona iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            case 10:
                                printf("\nDecima iterazione:\n");
                                for(int j = 0; j <= (((int)I[3]) - 2); j++)
                                {
                                    printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                                }
                                printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                                fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                                break;
                            }
                        }
                        else
                        {
                            printf("\n%d-esima iterazione:\n", counter);

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_Euclidea(Rk, I));
                            fprintf(fP, "%.10f\n", norma_Euclidea(Rk, I));

                        }
                    }
            }
            while(norma_Euclidea(VD, I) > I[2]);

            fclose(fP);

            }
            break;
    case 2:

        fP = fopen("dati.txt", "w");

        if(0 != ((int)I[0]))
        {
            for(int i = 1; i <= ((int)I[0]); i++)
            {
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    for(int k = 0; k <= (((int)I[3]) - 1); k++)
                    {
                        if(j != k)
                        {
                            sommatoria += A[j][k]*Xk[k];
                        }
                    }

                    ausiliare[j] = (B[j] - sommatoria)/A[j][j];
                    sommatoria = 0.0;
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    Xk[j] = ausiliare[j];
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    AXk[j] = 0.0;
                    Rk[j] = 0.0;
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    for(int k = 0; k <= (((int)I[3]) - 1); k++)
                    {
                        AXk[j] += A[j][k]*Xk[k];
                    }
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    Rk[j] = AXk[j] - B[j];
                }
                if(1 == ((int)I[4]))
                {
                    if(i <= 10)
                    {
                        switch (i)
                        {
                        case 1:
                            printf("\n*****************\n");
                            printf("\nPrima iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 2:
                            printf("\nSeconda iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 3:
                            printf("\nTerza iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 4:
                            printf("\nQuarta iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 5:
                            printf("\nQuinta iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 6:
                            printf("\nSesta iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 7:
                            printf("\nSettima iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 8:
                            printf("\nOttava iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 9:
                            printf("\nNona iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        case 10:
                            printf("\nDecima iterazione:\n");

                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }

                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            if(((int)I[0]) == i)
                            {
                                fclose(fP);
                                return 0;
                            }
                            break;
                        }
                    }
                    else
                    {
                        printf("\n%d-esima iterazione:\n", i);

                        for(int j = 0; j <= (((int)I[3]) - 2); j++)
                        {
                            printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                        }

                        printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                        fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                        if(((int)I[0]) == i)
                        {
                            fclose(fP);
                            return 0;
                        }
                    }
                }

            }
        }
        else
        {
            do
            {
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    for(int k = 0; k <= (((int)I[3]) - 1); k++)
                    {
                        if(j != k)
                        {
                            sommatoria += A[j][k]*Xk[k];
                        }
                    }

                    ausiliare[j] = (B[j] - sommatoria)/A[j][j];
                    sommatoria = 0.0;
                }
                for(int i = 0; i <= (((int)I[3]) - 1); i++)
                {
                    VD[i] = ausiliare[i] - Xk[i];
                }
                for(int i = 0; i <= (((int)I[3]) - 1); i++)
                {
                    Xk[i] = ausiliare[i];
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    AXk[j] = 0.0;
                    Rk[j] = 0.0;
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    for(int k = 0; k <= (((int)I[3]) - 1); k++)
                    {
                        AXk[j] += A[j][k]*Xk[k];
                    }
                }
                for(int j = 0; j <= (((int)I[3]) - 1); j++)
                {
                    Rk[j] = AXk[j] - B[j];
                }

                if(1 == ((int)I[4]))
                {
                    counter++;

                    if(counter <= 10)
                    {
                        switch (counter)
                        {
                        case 1:
                            printf("\n*****************\n");
                            printf("\nPrima iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                 printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 2:
                            printf("\nSeconda iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 3:
                            printf("\nTerza iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 4:
                            printf("\nQuarta iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 5:
                            printf("\nQuinta iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 6:
                            printf("\nSesta iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 7:
                            printf("\nSettima iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 8:
                            printf("\nOttava iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 9:
                            printf("\nNona iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        case 10:
                            printf("\nDecima iterazione:\n");
                            for(int j = 0; j <= (((int)I[3]) - 2); j++)
                            {
                                printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                            }
                            printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                            fprintf(fP, "%.10f\n", norma_infinita(Rk, I));

                            break;
                        }
                    }
                    else
                    {
                        printf("\n%d-esima iterazione:\n", counter);

                        for(int j = 0; j <= (((int)I[3]) - 2); j++)
                        {
                            printf("\nX[%d] = %.10f;", j + 1, Xk[j]);
                        }

                        printf("\nX[%d] = %.10f.\n\nR(X) = %.10f.\n\n", ((int)I[3]), Xk[(((int)I[3]) - 1)], norma_infinita(Rk, I));
                        fprintf(fP, "%.10f\n", norma_infinita(Rk, I));
                    }
                }
            }
            while(norma_infinita(VD, I) > I[2]);

            fclose(fP);
        }
        break;
    }
}
