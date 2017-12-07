//
// Created by jorge on 25-11-17.
//

#ifndef SIMILITUD_SIMILITUD_H
#define SIMILITUD_SIMILITUD_H

#endif //SIMILITUD_SIMILITUD_H

#include <string.h>
#define TAMAN_DIC 77455 //8606 //7746  // 77455
#define NUM_PIV 32
#define NUM_QUERYS 8606 //34 //860 //8606
#define MAX_LINE 28 //34 //860 //8606
//#define TAMAN_B 32

extern long int cuentaeditdist;

int min_antigua(int a, int b, int c){

    if(a<=b && a<=c)
    {
        return a;
    }
    else if(b<=a && b<=c)
    {
        return b;
    }
    return c;

}

int min(int a, int b)
{
    if (a<b)
        return a;
    return b;
}

int edit(char *s1, char *s2, int x1, int x2)
{
    //int N1; // = strlen(s1);
    int N2; // = strlen(s2);
    int i, j, retorno, corner, upper;
    int T[MAX_LINE+1];

    cuentaeditdist++;
    /*T = (int *)malloc(sizeof(int)*(N2+1));*/
    for ( i = 0; s2[(x2*MAX_LINE)+i]!= '\0'; i++ )
        T[i] = i;
    T[i]=i; /*1 mas*/
    N2=i;
    for ( i = 0; s1[(x1*MAX_LINE)+i]!= '\0' /*i < N1*/; i++ )
    {
        T[0] = i+1;
        corner = i;
        for ( j = 0; j < N2; j++ )
        {
            upper = T[j+1];
            if ( s1[(x1*MAX_LINE)+i] == s2[(x2*MAX_LINE)+j] )
                T[j+1] = corner;
            else
                T[j+1] = min(T[j], min(upper, corner)) + 1;
            corner = upper;
        }
    }
    retorno = T[N2];
    /*free(T);*/
    return retorno;
}

int edit_2011yantes (char *q, char *p, int x, int i)
{
    int j,ind_q,ind_p, pos=0, aux_dis;
    int min_iz,min_ar,min_di;
    int tam_q,tam_p;
    int encontrado_q,encontrado_p;
    char vector_aux[MAX_LINE], caldis[MAX_LINE*MAX_LINE];//MAX_LINE*MAX_LINE=784
    //vector_aux = (char *) malloc(sizeof(char)*MAX_LINE);
    //caldis = (char *) malloc(sizeof(char)*MAX_LINE*MAX_LINE);
    cuentaeditdist++;
    for (j = 0; j<MAX_LINE; j++)
        vector_aux[j] = j;


    ind_q = -1;
    encontrado_q = 0;
    encontrado_p = 0;
    for(j = 0; j<(MAX_LINE*MAX_LINE) && encontrado_q!= 1; j++)
    {
        //caldis[pos+j] = x;
        if (j%MAX_LINE == 0)
        {
            ind_q++;
            ind_p=-1;
        }
        ind_p++;
        if (j < MAX_LINE) //PRIMERA FILA
        {
            if (q[(x*MAX_LINE)+ind_q]== p[(i*MAX_LINE)+ind_p])//vector aux es de un elemento mas
                min_di = vector_aux[j] + 0;
            else
                min_di = vector_aux[j] + 1;
            if (j == 0)
                min_iz = vector_aux[j+1] + 1;
            else
                min_iz = caldis[(pos+j)-1] + 1;

            min_ar = vector_aux[j+1] + 1;

            caldis[pos+j] = (char)min_antigua(min_di,min_iz,min_ar);

            if (p[(i*MAX_LINE)+ind_p] == 0 && !encontrado_p){ // 0 == caracter nulo
                tam_p = ind_p - 1;
                encontrado_p = 1;
            }
        }
        else if(j%MAX_LINE == 0)//PRIMERA COLUMNA
        {
            if ( q[(x*MAX_LINE)+ind_q]== p[(i*MAX_LINE)+ind_p])//vector aux es de un elemento mas
                min_di = vector_aux[ind_q] + 0;
            else
                min_di = vector_aux[ind_q ] + 1;

            min_iz = vector_aux[ind_q + 1] + 1;

            min_ar = caldis[(pos+j)-MAX_LINE] + 1;

            caldis[pos+j] = (char)min_antigua(min_di,min_iz,min_ar);

        }
        else
        {
            if (q[(x*MAX_LINE)+ind_q]== p[(i*MAX_LINE)+ind_p])//vector aux es de un elemento mas
                min_di = caldis[(((pos+j) - MAX_LINE) - 1)] + 0;
            else
                min_di = caldis[(((pos+j) - MAX_LINE) - 1)] + 1;

            min_iz = caldis[(pos+j)-1] + 1;

            min_ar = caldis[(pos+j)-MAX_LINE] + 1;

            caldis[pos+j] = (char)min_antigua(min_di,min_iz,min_ar);
            if (encontrado_p == 1 && encontrado_q == 1 && (j+1)%tam_q==0)
            {
                j= j+(tam_q-j);
            }

        }
        if (q[(x*MAX_LINE)+ind_q] == 0 && !encontrado_q)
        {
            tam_q = ind_q - 1;
            encontrado_q = 1;
        }
    }//FIN FOR j


    aux_dis = caldis[pos + (tam_q*MAX_LINE)+tam_p];

    //free(caldis);
    //free(vector_aux);

    return aux_dis;

} /*end edit*/

/*int edit (char *p1, char *p2)
{
  int c[1000];
  int pcc;
  int nc;
  int j;
  int i;
  char cc;
  int m = strlen (p1);
   nc = m;
  p1--;
  for (j = 0; j <= m; j++)
    c[j] = j;
  for (i = 0; cc = p2[i]; i++)
    {
      pcc = i;
      nc = i + 1;
      for (j = 1; j <= m; j++)
	{
	  if (c[j] < nc)
	    nc = c[j];
	  pcc += (cc != p1[j]);
	  if (pcc <= nc)
	    nc = pcc;
	  else
	    nc++;
	  pcc = c[j];
	  c[j] = nc;
	}
    }
  return (int) nc;
}*/


void ordearr(unsigned int* array,int inf, int sup)
{
    int elem_div=array[sup];
    int temp;
    int i = inf - 1;
    int j = sup;
    int cont = 1;
    if (inf >= sup)
        return;

    while (cont)
    {
        while (array[++i] < elem_div);
        while (array[--j] > elem_div);
        if (i < j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else
            cont = 0;
    }

    temp = array[i];
    array[i] = array[sup];
    array[sup] = temp;
    ordearr (array, inf, i - 1);
    ordearr(array, i + 1, sup);
}
