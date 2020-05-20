#include <stdio.h>
#include <stdlib.h>
typedef struct complex
{
    float a;
    float b; // 1 - int, 0 float

};

typedef struct matrix
{
    int stolb;
    int str;
    int type; // 1 - int, 0 float
    void* p;
} Matrix;// обЪявлена М типа м


void doub(float *x)
{

    *x=*x*2;
}

void zero(float *x)
{
   *x=0;
}
void map(Matrix *a,void f(float*))
{
    for (int i = 0; i < a->str; i++)
    {
        for (int j = 0; j < a->stolb; j++)
        {
            switch(a->type)
            {
         case 1:
            f(&(((struct complex*)a->p + (i*a->stolb) + j)->a));
            f(&(((struct complex*)a->p + (i*a->stolb) + j)->b));
            break;
            default:
            f( ((float*)a->p + (i*a->stolb) + j));
            break;
            }
        }
    }
}


void msum(Matrix *a)
{
    struct  complex cres;
    float fres=0;
    int sb = a->stolb;
    int st = a->str;
    cres.a=0;
    cres.b=0;

    switch(a->type)
    {

        case 1:
            for (int i = 0; i < st; i++)
            {
                for (int j = 0; j < sb; j++)
                    {
                        cres.a += ((struct complex*)a->p + (i*sb) + j)->a;
                        cres.b += ((struct complex*)a->p + (i*sb) + j)->b;
                    }
            }

            printf("summa elementov %f  + %f*i  ",cres.a,cres.b);
            break;
        default:

            for (int i = 0; i < st; i++)
            {
               for (int j = 0; j < sb; j++)
                    fres+= *((float*)a->p + (i*sb) + j) ;
            }
            printf("summa elementov: %f ",fres);
            break;
    }

}

void Matrix_set(Matrix *m)
{
    float x;

    switch(m->type)
    {

        case 1:
            for (int i = 0; i < m->str; i++)
            {

                for (int j = 0; j < m->stolb; j++)
                {

                    printf("Enter %dx%d componets of matrix >> ", i+1, j+1); // приглашение для ввода очередного элемента матрицы
                    scanf("%f",&x) ;
                    ((struct complex*)m->p + (i*m->stolb) + j)->a=x;
                    scanf("%f",&x) ;
                    ((struct complex*)m->p + (i*m->stolb) + j)->b=x;
                }

            }

            break;
       default:
            for (int i = 0; i < m->str; i++)
            {

                for (int j = 0; j < m->stolb; j++)
                {

                    printf("Enter %dx%d componets of matrix >> ", i+1, j+1); // приглашение для ввода очередного элемента матрицы
                    scanf("%f", (float*)m->p + (i*m->stolb) + j);
                }

            }

            break;
    }

}

Matrix *Matrix_new(int type, int sb,int st )
{
    Matrix *m;
    m = malloc(sizeof(Matrix));
    switch (type)
    {

        case 1:
            m->p = malloc(sizeof(struct complex)*sb*st);
            m->type = type;
            m->stolb = sb;
            m->str = st;
            break;
       default:
            m->p = malloc(sizeof(float)*sb*st);
            m->type = type;
            m->stolb = sb;
            m->str = st;
            break;
    }

    return m;
}
Matrix *Matrix_sum(Matrix *a, Matrix *b)

{
    int sb = a->stolb;
    int st = a->str;

    if (a->stolb != b->stolb || a->str!= b->str)

        {

        fprintf(stderr, "a size != b size sum can't be counted\n");
        return NULL;
        }

    if (a->stolb == b->stolb && a->str== b->str)

    {

    Matrix *res = Matrix_new(a->type, sb,st);

    switch(a->type)
        {

        case 1:
           for (int i = 0; i < st; i++)
            {

                for (int j = 0; j < sb; j++)
                {

                    ((struct complex*)res->p + (i*sb) + j)->a = ((struct complex*)a->p + (i*sb) + j)->a + ((struct complex*)b->p + (i*sb) + j)->a;
                    ((struct complex*)res->p + (i*sb) + j)->b = ((struct complex*)a->p + (i*sb) + j)->b + ((struct complex*)b->p + (i*sb) + j)->b;
                }

            }

            break;
        default:

             for (int i = 0; i < st; i++)
                    {

                for (int j = 0; j < sb; j++)
                    *((float*)res->p + (i*sb) + j) = *((float*)a->p + (i*sb) + j) + *((float*)b->p + (i*sb) + j);
                    }
            break;
        }

    return res;
    }

}
Matrix *transp(Matrix *a)
{

    Matrix *res = Matrix_new(a->type, a->str,a->stolb);
    switch(a->type){
        case 1:
           for (int i = 0; i < a->stolb; i++)
            {
                for (int j = 0; j < a->str; j++){
                    ((struct complex*)res->p + (i*a->stolb) + j)->a = ((struct complex*)a->p + (j*a->stolb) + i)->a;
                    ((struct complex*)res->p + (i*a->stolb) + j)->b = ((struct complex*)a->p + (j*a->stolb) + i)->b ;}
            }
            break;
        default:
             for (int i = 0; i < a->stolb; i++)
            {
                for (int j = 0; j < a->str; j++)
                    *((float*)res->p + (i*a->str) + j) = *((float*)a->p + (j*a->stolb) + i);
            }
            break;
    }
    return res;
}

void Matrix_print(Matrix *m)
{
    switch(m->type) {
        case 1:
            for (int i = 0; i < m->str; i++)
            {
                for (int j = 0; j < m->stolb; j++)
                  printf("%f  + %f*i  ", (((struct complex*)m->p + (i*m->stolb) + j)->a),(((struct complex*)m->p + (i*m->stolb) + j)->b));


                printf("\n");printf("\n");
            }
            break;
        default:
            for (int i = 0; i < m->str; i++)
            {
                for (int j = 0; j < m->stolb; j++)
                    printf("%f  ", *((float*)m->p + (i*m->stolb) + j));
                printf("\n");printf("\n");
            }
            break;
    }
}
Matrix *mul(Matrix *a, Matrix *b)
{




    if (a->stolb != b->str )
        {

        return NULL;
        }

     if (a->stolb == b->str )
        {

    Matrix *res = Matrix_new(a->type, b->stolb,a->str);



    switch(a->type)
    {
        case 1:
           for (int i = 0; i < res->str; i++)
            {
                for (int j = 0; j <res-> stolb; j++)
                    {
                        ((struct complex*)res->p + (i*res->stolb) + j)->a=0;
                ((struct complex*)res->p + (i*res->stolb) + j)->b=0;
                         for (int t = 0; t < a->stolb; t++)
                            {

                    ((struct complex*)res->p + (i*res->stolb) + j)->a += ((struct complex*)a->p + (i*a->stolb) + t)->a  *((struct complex*)b->p + (t*b->stolb) + j)->a-
                        ((struct complex*)a->p + (i*a->stolb) + t)->b  *((struct complex*)b->p + (t*b->stolb) + j)->b;
                    ((struct complex*)res->p + (i*res->stolb) + j)->b += ((struct complex*)a->p + (i*a->stolb) + t)->a * ((struct complex*)b->p + (t*b->stolb) + j)->b
                    +((struct complex*)b->p + (i*a->stolb) + t)->a * ((struct complex*)a->p + (t*b->stolb) + j)->b;
                            }
                    }
            }
            break;
        default:

             for (int i = 0; i <res->str; i++)
            {
                for (int j = 0; j < res->stolb; j++){

*((float*)res->p + (i*res->stolb) + j)=0;
                    for (int t = 0; t < a->stolb; t++)


                    *((float*)res->p + (i*res->stolb) + j) += *((float*)a->p + (i*a->stolb) + t) * *((float*)b->p + (t*b->stolb) + j);
           } }
            break;}


    return res;}
}


int main(void)

{

    int type;

    int sb, st;



    printf("For work with complex numbers choose 1, for work with float - 0 -> ");

    printf("\n");

    scanf("%d", &type);

    printf("vvedite kolvo stolbcov -> ");

    printf("\n");

    scanf("%d", &sb);

    printf("vvedite kolvo strok -> ");

    printf("\n");

    scanf("%d", &st);



    Matrix* m1 = Matrix_new(type, sb, st);

    Matrix_set(m1);

    printf("Matrix 1");

    printf("\n");

    Matrix_print(m1);

    printf("vvedite kolvo stolbcov -> ");

    printf("\n");

    scanf("%d", &sb);

    printf("vvedite kolvo strok -> ");

    printf("\n");

    scanf("%d", &st);



    Matrix* m2 = Matrix_new(type, sb, st);

    Matrix_set(m2);

    printf("Matrix 2");

    printf("\n");

    Matrix_print(m2);

    printf("Do you want to count sum? 1-yes, 0-no \n");

    scanf("%d", &st);

    if (st == 1) {

        Matrix* m3 = Matrix_sum(m1, m2);

        if (m3 != NULL) {

            printf("sum");

            printf("\n");

            Matrix_print(m3);

            free(m3->p);

        }

    }

    printf("Transpanirovat? 1-yes, 0-no \n");

    scanf("%d", &st);



    if (st == 1) {

        Matrix* m4 = transp(m1);

        printf("trans");

        printf("\n");

        Matrix_print(m4);

        free(m4->p);

    }



    printf("Do you want to count mul? 1-yes, 0-no \n");

    scanf("%d", &st);

    if (st == 1) {

        if (m1->stolb != m2->str) {

            printf("a stolb != b str  mul can't be counted \n");

        };



        if (m1->stolb == m2->str) {

            Matrix* m5 = mul(m1, m2);

            printf("Mult ");

            printf("\n");

            Matrix_print(m5);

            free(m5->p);

            printf("\n");

        }

    }

    msum(m1);

    printf("For zero choose 1, for double - 0 -> \n");

    scanf("%d", &st);

    switch (st) {

    case 1: {

        map(m1, zero);

        Matrix_print(m1);

        break;

    }

    default: {

        map(m1, doub);

        Matrix_print(m1);

    }

    }

    free(m1->p);

    free(m2->p);

}

