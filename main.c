#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#define nb_cartes 13
#define nb_couleur 4
int TabValeur[nb_cartes] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1};///Définit la valeur des cartes
int TabCouleur[nb_couleur] = {3,4,5,6};///Définit la couleur de la carte à l'aide du code ASCII
struct carte
{
    int valeur; //
    int  couleur; //3 à 6 (trefle, carreau coeur et pique)
};
typedef struct carte CARTE;
struct player
{
    char nom[50];
    int jetons;
    CARTE C[100];
    char choix[50];///choix (mise ou check ou secouche...
    char comb[50];///
    CARTE  TabP[5];
    int scrate;
    int montant ;
    char rslt[50];
};
typedef struct player Player;
CARTE Jeu[52];

int gMax=52;
void InitJeu()
{
    int val, coul, i;
    i = 0;
    for (coul=0; coul<nb_couleur; coul++)
    {
        for (val=0; val<nb_cartes; val++)
        {
            Jeu[i].valeur = val;
            Jeu[i].couleur =coul;
            i++;
        }
    }
}
CARTE *Distribue(CARTE *pCarte)
{
    int indice ;
    CARTE aux;
    srand(time(NULL));
    indice = rand()%(gMax);

    *pCarte = Jeu[indice];
    aux=Jeu[indice];
    Jeu[indice] = Jeu[gMax];
    Jeu[gMax]=aux;
    gMax --;

    return pCarte;
}
void DistribueCarte(Player Play[],int nb)
{
    CARTE C ;
    int i,j;
    for (i=0; i<nb; i++)
    {
        for (j=0; j<2; j++)
        {
            Distribue(&C);
            Play[i].C[j].valeur=TabValeur[C.valeur];
            Play[i].C[j].couleur=TabCouleur[C.couleur];
            Play[i].jetons=500000;
        }
    }
}
void saisir(Player Play[],int nb)
{
    printf("donner votre nom : ");
    scanf("%s",Play[0].nom);
    DistribueCarte(Play,nb);

}
void affichier(Player play[],int nb)
{
    int i,j;

    printf("\nPlayer %s :  ",play[0].nom);
    for (j=0; j<2; j++)
        printf ("  %d%c | ",play[0].C[j].valeur, play[0].C[j].couleur);
    printf("\n");
    for (i=1; i<nb; i++)
    {
        printf("Player %d: ",i+1);
        for (j=0; j<2; j++)
        {

            printf ("  ** | ");
        }
        printf ("\n");
    }
}
void affichierFTR(CARTE d[],int n,char ch [])
{
    int i;
    printf ("\n\nVoici le %s : ",ch);
    for (i=0; i<n; i++)
    {
        printf("%d%c|",d[i].valeur,d[i].couleur);
    }
}
void partieturn(CARTE d[],int* n)
{
    CARTE c;
    Distribue(&c);
    d[(*n)].valeur=TabValeur[c.valeur];
    d[(*n)].couleur=TabCouleur[c.couleur];
    (*n)++;
    if((*n) == 4)
        affichierFTR(d,*n,"TURN");
    else
        affichierFTR(d,*n,"RIVIERE ");


}
void donneur(CARTE d[], int* n)
{
    int j=0;
    CARTE c ;
    while ( j<(*n))
    {
        Distribue(&c);
        d[j].valeur=TabValeur[c.valeur];
        d[j].couleur=TabCouleur[c.couleur];
        j++;
    }

    affichierFTR(d,*n,"FLOP");
}
int test(int val,CARTE d[],int i)
{
    int j;
    for( j=0; (j<i)&&(val!=d[j].valeur) ; j++);
    if (j<i)
        return 1;
    return 0 ;
}
int testB(int val,CARTE d[],int i)
{
    int j,nbOcc=0;
    for (j=0; (j<i)&& ( nbOcc!=2); j++)
    {
        if (d[j].valeur == val)
            nbOcc++;
    }
    if (nbOcc == 2)
        return nbOcc;
    return 0 ;
}
void affichierTableau(CARTE t[],int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf ("%d %c |",t[i].valeur,t[i].couleur);
    }

}
void sort(CARTE t[],int n)
{
    int test = 1;
    int i;
    CARTE temp;

    while ( test!=0 )
    {
        test = 0;
        for (i=0; i<n-1; i++)
        {
            if (t[i].valeur>t[i+1].valeur)
            {
                test =1;
                /// on echange les deux elements
                temp = t[i];
                t[i] = t[i+1];
                t[i+1] = temp;
            }
        }
    }

}
int suite (CARTE t[],int n)
{


    int k,i,j,test=1;
    CARTE  c;

    if (n==5)
    {
        for(j=0; (j<n-3)&&(test ==1 ); j++)
        {
            c=t[j];
            test=0;
            for(i=j+1; (i<n+j)&&(test==0); i++)
            {
                if(c.valeur+1==t[i].valeur)
                    c=t[i];
                else if (c.valeur == t[i].valeur)
                {

                    for (k=i; k<n; k++)
                        t[k]=t[k+1];

                    if(c.valeur+1==t[i].valeur)
                    {
                        c=t[i];

                    }
                    else
                        test=1;
                }

                else
                    test =1;
            }
        }
    }
    else
    {
        for(j=0; (j<n-3)&&(test ==1 ); j++)
        {
            c=t[j];
            test=0;
            for(i=j+1; (i<n+j-1)&&(test==0); i++)
            {
                if(c.valeur+1==t[i].valeur )
                    c=t[i];
                else if (c.valeur == t[i].valeur)
                {

                    for (k=i; k<n; k++)
                        t[k]=t[k+1];

                    if(c.valeur+1==t[i].valeur)
                    {
                        c=t[i];

                    }
                    else
                        test=1;
                }
                else
                    test =1;
            }
        }
    }


    if(test == 0)
        return 1;
    return 0;
}
int  Fsuite(CARTE c[],CARTE d[],int i)
{
    CARTE t[7];
    int j,k;
    for (j=0; j<2; j++)
        t[j]=c[j];
    for (k=0; k<i; k++)
    {
        t[j]=d[k];
        j++;

    }
    sort(t,i+2);

    if(suite(t,i+1))
        return 1;
    return 0;
}
int coul(int val, CARTE d[],int n)
{
    int j;
    int nbcoul=0;
    for (j=0; (j<n) ; j++)
    {
        if (val == d[j].couleur)
            nbcoul ++;
    }
    if (nbcoul >=3 )
        return nbcoul ;
    return 0;

}

int full(int val,CARTE d[],int n)
{
    int i,j;
    if (test(val,d, n))
    {
        for (i=0; i<n; i++)
        {
            for (j=i+1; j<n && d[i].valeur!= d[j].valeur; j++);
            if (j<n)
                return 1;
        }
    }
    return 0;
}
int testC(int val,CARTE d[],int i)
{
    int j,nbOcc=0;
    for (j=0; (j<i)&& ( nbOcc!=3); j++)
    {
        if (d[j].valeur == val)
            nbOcc++;
    }
    if (nbOcc == 3)
        return nbOcc;
    return 0 ;
}
int paire (CARTE c[],CARTE d[],int i)
{
    int j;
    if (c[0].valeur == c[1].valeur)
        return 1;
    else
    {
        for( j=0; (j<i)&&((c[0].valeur!=d[j].valeur) && (c[1].valeur!=d[j].valeur)); j++);
        if (j<i)
            return 1;
    }
    return 0;
}
int doublepaire(CARTE c[],CARTE d[],int i)
{
    int j,k;
    if (c[0].valeur == c[1].valeur)
    {
        for (j=0; j<i; j++ )
        {
            for(k=j+1; (k<i)&&(d[j].valeur!=d[k].valeur); k++);
            if (k<i)
                return 1;
        }

    }
    else
    {
        if ((test(c[0].valeur,d, i)!= 0 )&&(test(c[1].valeur, d, i)!=0))
            return 1;
    }
    return 0;

}
int couleur(CARTE c[],CARTE d[],int i)
{
    if (c[0].couleur == c[1].couleur)
    {
        if (coul(c[0].couleur, d,i)>=3)
            return 1;
    }
    else
    {
        if (coul(c[0].couleur, d,i )>=4 || coul(c[1].couleur, d,i) >=4)
            return 1;

    }

    return 0;
}
int brelan(CARTE c[],CARTE d[],int i)
{
    if (c[0].valeur == c[1].valeur)
    {
        if (test(c[0].valeur,d, i)!= 0 )
            return 1;
    }
    else
    {
        if ((testB(c[0].valeur,d, i)== 2)||(testB(c[1].valeur,d, i)==2))
            return 1;
    }
    return 0;
}
int fullhouse(CARTE c[], CARTE d[], int i)
{
    if (c[0].valeur == c[1].valeur)
    {
        if (full(c[0].valeur,d,i))
            return 1;
    }
    else
    {
        if((testB(c[0].valeur,d, i)== 2)&&(test(c[1].valeur, d, i)!=0))
            return 1;
        else if ((test(c[0].valeur, d, i)!=0)&& (testB(c[1].valeur,d, i)== 2))
            return 1;

    }
    return 0;
}
int carree(CARTE c[],CARTE d[],int i)
{
    if (c[0].valeur == c[1].valeur)
    {
        if ((testB(c[0].valeur,d, i)== 2))
            return 1;
    }
    else
    {
        if (testC(c[0].valeur,d,i)==3 || testC(c[1].valeur,d,i)==3)
            return 1;
    }
    return 0;
}
int recherche(Player play[],char com[],int nb)
{
    int i;
    if (strcmp(com,"paire")==0)
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"doublepaire")==0 || strcmp(play[i].comb,"brelan")==0 || strcmp(play[i].comb,"suite")==0 || strcmp(play[i].comb,"couleur")==0 || strcmp(play[i].comb,"full")==0 || strcmp(play[i].comb,"carre")==0)
                return 1;
        }
    }
    else if(strcmp(com,"doublepaire")==0)
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"brelan")==0 || strcmp(play[i].comb,"suite")==0 || strcmp(play[i].comb,"couleur")==0 || strcmp(play[i].comb,"full")==0 || strcmp(play[i].comb,"carre")==0)
                return 1;
        }
    }
    else if (strcmp(com,"brelan")==0)
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"suite")==0 || strcmp(play[i].comb,"couleur")==0 || strcmp(play[i].comb,"full")==0 || strcmp(play[i].comb,"carre")==0)
                return 1;
        }
    }
    else if (strcmp(com,"suite")==0)
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"couleur")==0 || strcmp(play[i].comb,"full")==0 || strcmp(play[i].comb,"carre")==0)
                return 1;
        }
    }
    else if(strcmp(com,"couleur")==0)
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"full")==0 || strcmp(play[i].comb,"carre")==0)
                return 1;
        }
    }
    else if (strcmp(com,"full"))
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"carre")==0)
                return 1;
        }
    }
    else if (strcmp(com,"carre"))
    {
        for(i=0; i<nb; i++)
        {
            if (strcmp(play[i].comb,"quinteflush")==0)
                return 1;
        }
    }
    return 0;
}
void FBDPC(char com[],CARTE c[],CARTE d[],int i)
{
    ///paire
    if (paire(c,d,i))
    {
        strcpy(com,"paire");
    }
    ///double paire
    if (doublepaire(c,d,i))
    {
        strcpy(com,"doublepaire");
    }


    ///Brelan
    if (brelan(c,d,i))
    {
        strcpy(com,"brelan");
    }
    ///suite

    if (i>=4)
    {
        if ((strcmp(com,"brelan")!=0)&& (strcmp(com,"doublepaire")!=0));
        {
            if(Fsuite(c,d,i))
                strcpy(com,"suite");

        }
    }

    ///couleur
    if (couleur(c,d,i))
        strcpy(com,"couleur");
    ///full house
    if(fullhouse(c,d,i))
        strcpy(com,"full");
    ///carre
    if (carree(c,d,i))
        strcpy(com,"carre");
    ///quinteflush
    if (i>=4)
    {
        if ((strcmp(com,"brelan")!=0)&& (strcmp(com,"doublepaire")!=0));
        {
            if(Fsuite(c,d,i)&& couleur(c,d,i) )
                strcpy(com,"quinteflush");

        }
    }

}
void remplir (CARTE tab[],CARTE c[],CARTE d[],int i )
{
    int j,k;
    for (j=0; j<2; j++)
        tab[j]=c[j];
    for (k=0; k<i; k++)
    {
        tab[j]=d[k];
        j++;

    }
    sort(tab,7);

}
void  remplirtab(Player p,CARTE tab[])
{
    int j,k;
    int i=0;
    for (j=0; j<7; j++)
    {
        if (p.C[0].valeur==tab[j].valeur|| p.C[1].valeur==tab[j].valeur)
        {
            p.TabP[i]=tab[j];
            i++;
        }
    }

    for (j=6; j>=0; j--)
    {
        for(k=0; k<i && i<5 &&tab[j].valeur!=p.TabP[k].valeur; k++);

        if(k>=i)
        {
            p.TabP[i]=tab[j];
            i++;
        }
        if (i==5)
            break;
    }
    sort( p.TabP,5);
    affichierTableau(p.TabP,i);

}
void dbpaire(Player p,CARTE tab[])
{
    int j,i,indice,k;
    for (j=0; j<2; j++)
        p.TabP[j]=p.C[j];

    for (i=0; i<7; i++)
    {

        for(k=0; k<j && tab[i].valeur!=p.TabP[k].valeur; k++);
        if(k>=j)
        {
            for(indice=i+1; indice<=6 && tab[i].valeur!=tab[indice].valeur; indice++);
            if (indice <=6)
            {
                p.TabP[j]=tab[i];
                j++;

                p.TabP[j]=tab[indice];
                break;
            }
        }
    }
    j++;
    for (indice=6; indice>=0; indice--)
    {
        for(k=0; k<j && j<5 &&tab[indice].valeur!=p.TabP[j].valeur; k++);

        if(k>=j)
        {
            p.TabP[j]=tab[indice];
            j++;
        }
        if (i==5)
            break;
    }
    sort( p.TabP,5);
    affichierTableau(p.TabP,5);



}
void fulltab(Player p,CARTE tab[])
{
    int j=2,i,k,indice;
    int nbocc=0;
    for (j=0; j<2; j++)
        p.TabP[j]=p.C[j];
    for(i=0; i<7 && nbocc!=3 ; i++)
    {
        if(p.TabP[0].valeur==tab[i].valeur)
            nbocc ++;
    }
    if (nbocc == 3)
    {
        p.TabP[j]=p.TabP[0];
        j++;
        for (i=0; i<7; i++)
        {

            for(k=0; k<j && tab[i].valeur!=p.TabP[k].valeur; k++);
            if(k>=j)
            {
                for(indice=i+1; indice<=6 && tab[i].valeur!=tab[indice].valeur; indice++);
                if (indice <=6)
                {
                    p.TabP[j]=tab[i];
                    j++;

                    p.TabP[j]=tab[indice];
                    break;
                }
            }
        }
    }
    else
    {
        printf("j=%d \n",j);
        for (i=0; i<7; i++)
        {
            nbocc=0;
            for(indice=i+1; indice<=6 && nbocc!=2 ; indice++)
            {
                if(tab[indice].valeur==tab[i].valeur)
                    nbocc ++;
            }
            if ( nbocc==2)
            {

                p.TabP[j]=tab[i];
                j++;
                p.TabP[j]=tab[i];
                j++;
                p.TabP[j]=tab[i];

                break;
            }
        }
    }
    affichierTableau(p.TabP,5);
    sort( p.TabP,5);
}
int rechercheindice(CARTE tab[],int n)
{
    int k,m,i=0,j=4;
    for(k=0; k<n; k++)
    {
        if (tab[k].valeur== tab[k+1].valeur)
        {
            for(m=k+1; m<n-1; m++)
                tab[m]=tab[m+1];
            n--;
        }
    }
    while (i<3)
    {
        if(tab[i].valeur == tab[j].valeur-4)
            return i;
        i++;
        j++;
    }
    return 0;
}
void fsuiteplay(Player p,CARTE tab[],int n)
{
    int i,j,k=0;
    i=rechercheindice(tab,n);
    if (i!=-1)
    {
        for (j=i; j<5+i; j++)
        {
            p.TabP[k]=tab[j];
            k++;
        }
    }
    affichierTableau(p.TabP,5);
    sort( p.TabP,5);


}
void funcoulour(Player p,CARTE tab[],int n)
{
    int coul,i,k,j;
    for (i=0; i<7; i++)
    {
        coul=0;
        for(j=i+1; j<7 && coul<4; j++)
        {
            if (tab[i].couleur == tab[j].couleur)
                coul++;
        }
        if (coul >=4)
            break;
    }
    k=0;
    for (j=0; j<7&& k!=5; j++)
    {
        if (tab[i].couleur==tab[j].couleur)
        {
            p.TabP[k]=tab[j];
            k++;
        }
    }
    affichierTableau(p.TabP,5);
    sort(p.TabP,5);
}
void remplirTabplayer(Player Play,CARTE t[],int i)
{
    CARTE tab[7];
    remplir(tab,Play.C,t,i);
    if (strcmp(Play.comb,"paire")==0)
    {
        remplirtab(Play,tab);
    }
    else if (strcmp(Play.comb,"doublepaire")==0)
    {
        if (Play.C[0].valeur != Play.C[1].valeur)
            remplirtab(Play,tab);
        else
            dbpaire(Play,tab);
    }
    else if (strcmp(Play.comb,"brelan")==0)
    {
        remplirtab(Play,tab);
    }
    else if (strcmp(Play.comb,"full")==0)
    {
        if (Play.C[0].valeur != Play.C[1].valeur)
            remplirtab(Play,tab);
        else
            fulltab(Play,tab);
    }
    else if (strcmp(Play.comb,"carre")==0)
    {
        remplirtab(Play,tab);
    }
    else if (strcmp(Play.comb,"suite")==0)
    {
        fsuiteplay(Play,tab,7);
    }
    else if (strcmp(Play.comb,"couleur")==0)

    {
        funcoulour(Play,tab,7);
    }



}
void JeuPoker()
{
    int choixjeton=100,somme=0,choixj=100,p,i=3,nbplayer;
    char com[50];
    Player Play[10];
    CARTE ftr[7];

    printf("\n");
    printf("\t\t********************************************************\n");
    printf("\t\t*\t\t\t\t\t\t\t*\n");
    printf("\t\t*%10c%c%c%c%5c%c%c%c%c%5c%4c%5c%c%c%c%5c%c%c%c\t*\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
    printf("\t\t*%10c%3c%5c%4c%5c%3c%6c%8c%4c \t*\n",177,177,177,177,177,177,177,177,177);
    printf("\t\t*%10c%3c%5c%4c%5c%2c%7c%8c%4c \t*\n",177,177,177,177,177,177,177,177,177);
    printf("\t\t*%10c%c%c%c%5c%4c%5c%c%8c%c%c%c%5c%c%c%c \t*\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
    printf("\t\t*%10c%8c%4c%5c%2c%7c%8c%c \t\t*\n",177,177,177,177,177,177,177,177);
    printf("\t\t*%10c%8c%4c%5c%3c%6c%8c%2c\t\t*\n",177,177,177,177,177,177,177,177);
    printf("\t\t*%10c%8c%c%c%c%c%5c%4c%5c%c%c%c%5c%3c\t*\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177);
    printf("\t\t*\t\t\t\t\t\t\t*\n");
    printf("\t\t********************************************************\n");
    printf("\n\n");

    InitJeu();
    do
    {
        printf(" Entrez le nombre de participants entre 2 et 10: ");
        scanf("%d",&nbplayer);
        if((nbplayer<2) || (nbplayer>10))
            printf("Donnee non valide\n");
    }
    while((nbplayer<2)||(nbplayer >10));
    saisir (Play,nbplayer);
    affichier(Play,nbplayer);
    donneur(ftr,&i);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    while(i<=5)
    {
        affichier(Play,nbplayer);
        printf("\n");
        printf("le player sont misent :");
        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
        for (p=0; p<nbplayer; p++)
        {

            FBDPC(com,Play[p].C,ftr,i);
            if (p==0)
            {
                if (strcmp(Play[0].choix,"secouche")!=0)
                {
                    if (i==5)///partie revier
                    {
                        do
                        {
                            printf("\nle player %s vous voulez {mise,secouche} : ",Play[0].nom);
                            scanf("%s",Play[0].choix);
                            if ((strcmp(Play[0].choix,"mise")!=0)&&(strcmp(Play[0].choix,"secouche")!= 0))
                            {
                                printf("SVP entre {mise ou check ,se couche} ");
                            }

                        }
                        while ((strcmp(Play[0].choix,"mise")!= 0)&&(strcmp(Play[0].choix,"secouche")!= 0));
                    }
                    else
                    {
                        do
                        {
                            printf("\nle player %s vous voulez {mise,check, secouche} : ",Play[0].nom);
                            scanf("%s",Play[0].choix);
                            if ((strcmp(Play[0].choix,"check")!= 0)&&(strcmp(Play[0].choix,"mise")!=0)&&(strcmp(Play[0].choix,"secouche")!= 0))
                            {
                                printf("SVP entre {mise ou check ,se couche} ");
                            }

                        }
                        while ((strcmp(Play[0].choix,"check")!= 0)&&(strcmp(Play[0].choix,"mise")!= 0)&&(strcmp(Play[0].choix,"secouche")!= 0));
                    }

                    if (strcmp(Play[0].choix,"mise")== 0)
                    {
                        do
                        {
                            printf("donne le montant : ");
                            scanf("%d",&choixj);
                        }
                        while ((choixj < choixjeton || choixj>Play[0].jetons));
                        Play[0].jetons=Play[0].jetons-choixj;
                        choixjeton=choixj;
                        somme=somme+choixjeton;
                    }

                    else if (strcmp(Play[0].choix,"check")== 0)
                    {
                        Play[0].jetons=Play[0].jetons-100;
                        printf ("le montant : 100 \n");
                        somme=somme+100;
                    }
                    strcpy(Play[0].comb,com);
                }
                strcpy(com,"");
            }
            else
            {
                if (strcmp(com,"quinteflush")==0)
                {
                    strcpy(Play[p].choix,"mise");
                    printf ("le Player %d : mise ",p+1);
                    if (strcmp(Play[p-1].choix,"mise")==0)
                    {
                        choixjeton =choixjeton+500;
                        Play[p].jetons=Play[p].jetons-(choixjeton);
                        printf(" et il donne : %d$\n",choixjeton);
                    }
                    else
                    {
                        choixjeton=rand()%(3000-choixjeton)+choixjeton;
                        Play[p].jetons=Play[p].jetons-choixjeton;
                        printf(" et il donne  : %d$\n",choixjeton);
                    }
                    strcpy(Play[p].comb,com);
                    somme=somme+choixjeton;
                    strcpy(com,"");
                }
                else if (strcmp(com,"carre")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        strcpy(Play[p].choix,"mise");
                        printf ("le Player %d : mise ",p+1);
                        if (strcmp(Play[p-1].choix,"mise")==0)
                        {
                            choixjeton =choixjeton+300;
                            Play[p].jetons=Play[p].jetons-(choixjeton);
                            printf(" et il donne : %d$\n",choixjeton);
                        }
                        else
                        {
                            choixjeton=rand()%(2500-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf(" et il donne  : %d$\n",choixjeton);
                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;
                    }
                    strcpy(com,"");
                }

                else if (strcmp(com,"full")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        strcpy(Play[p].choix,"mise");
                        printf ("le Player %d : mise ",p+1);
                        if (strcmp(Play[p-1].choix,"mise"))
                        {
                            choixjeton =choixjeton+250;
                            Play[p].jetons=Play[p].jetons-(choixjeton);
                            printf(" et il donne : %d$\n",choixjeton);
                        }
                        else
                        {
                            choixjeton=rand()%(2000-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf(" et il donne  : %d$\n",choixjeton);
                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;
                    }
                    strcpy(com,"");

                }
                else if (strcmp(com,"couleur")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        strcpy(Play[p].choix,"mise");
                        printf ("le Player %d : mise ",p+1);
                        if (strcmp(Play[p-1].choix,"mise")==0)
                        {
                            choixjeton= choixjeton+200;
                            Play[p].jetons=Play[p].jetons-(choixjeton);
                            printf(" et il donne : %d$\n",choixjeton);
                        }
                        else
                        {
                            choixjeton=rand()%(1000-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf(" et il donne  : %d$\n",choixjeton);
                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;
                    }
                    strcpy(com,"");

                }
                else if (strcmp(com,"suite")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        strcpy(Play[p].choix,"mise");
                        printf ("le Player %d : mise ",p+1);
                        if (strcmp(Play[p-1].choix,"mise"))
                        {
                            choixjeton=choixjeton+170;
                            Play[p].jetons=Play[p].jetons-(choixjeton);
                            printf("et il donne : %d$\n",choixjeton);
                        }
                        else
                        {
                            choixjeton=rand()%((choixj+150)-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf("et il donne  : %d$\n",choixjeton);
                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;
                    }
                    strcpy(com,"");
                }
                else if (strcmp(com,"brelan")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        strcpy(Play[p].choix,"mise");
                        printf ("le Player %d : mise ",p+1);
                        if (strcmp(Play[p-1].choix,"mise")!=0)
                        {
                            choixjeton=choixjeton+150;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf("et il donne : %d$\n",choixjeton);
                        }
                        else
                        {
                            choixjeton=rand()%((choixj+160)-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf("et il donne  : %d$\n",choixjeton);
                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;

                    }
                    strcpy(com,"");

                }

                else if (strcmp(com,"doublepaire")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        printf ("le Player %d : mise",p+1);
                        strcpy(Play[p].choix,"mise");
                        if (strcmp(Play[p-1].choix,"mise")==0)
                        {
                            choixjeton=choixjeton+100;
                            Play[p].jetons=Play[p].jetons-(choixjeton);
                            printf("et il donne : %d$\n",choixjeton);
                        }
                        else
                        {
                            choixjeton=rand()%((choixj+110)-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf("et il donne  : %d$\n",choixjeton);

                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;
                    }
                    strcpy(com,"");
                }

                else if (strcmp(com,"paire")==0)
                {
                    if (recherche(Play,com,nbplayer)&& i==5)
                    {
                        strcpy(Play[p].choix,"secouche");
                        printf ("le Player %d il dit: secouche \n",p+1);
                    }
                    else
                    {
                        strcpy(Play[p].choix,"mise");
                        printf ("le Player %d il dit mise ",p+1);

                        if (strcmp(Play[p-1].choix,"mise"))
                        {
                            choixjeton=choixjeton+50;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf("et il donne : %d$\n",choixjeton);

                        }
                        else
                        {
                            choixjeton=rand()%((choixj+60)-choixjeton)+choixjeton;
                            Play[p].jetons=Play[p].jetons-choixjeton;
                            printf(" et il donne  : %d$\n",choixjeton);
                        }
                        strcpy(Play[p].comb,com);
                        somme=somme+choixjeton;
                    }
                    strcpy(com,"");
                }



                else
                {
                    if(i==5)
                    {
                        printf ("le Player %d il dit : secouche \n",p+1);
                        strcpy(Play[p].choix,"secouche");
                    }
                    else
                    {
                        printf ("le Player %d il dit : check il donne 100 \n",p+1);
                        Play[p].jetons=Play[p].jetons-100;
                        somme=somme+100;

                    }
                }
            }


        }
        if (i<5)
        {
            partieturn(ftr,&i);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
        }
        else
            break;
    }
    printf ("\nsomme = %d\n", somme);

///chkoun rbeh ...

    for(p=0; p<nbplayer; p++)
    {
        if (strcmp(Play[p].choix,"secouche")!=0)
        {
            if (p==0)
                printf("player %s: ",Play[0].nom);
            else
                printf ("le player %d (%s) : ",p+1,Play[p].comb);

            remplirTabplayer(Play[p],ftr,i);
            printf ("\n");
        }
    }




}

void JeuRoulette()
{

    int cag =1000,sommeM,numM,bille, i ;
    printf ("le cagnotte : %d\n", cag);
    do
    {
        do
        {
            printf ("choisir un numero entre 0..49: ");
            scanf("%d", &numM);
            numM=ceil(numM);

        }
        while (numM<0 || numM>49);
        do
        {
            printf("misez un montant :");
            scanf("%d",&sommeM);
            sommeM=ceil(sommeM);
        }
        while(sommeM<=0 || sommeM>cag);
        cag=abs(cag-sommeM);
        srand(time(NULL)); ///pour éviter la redandence du numero
        bille=rand()% 50;
        bille = ceil(bille);
        printf("la roulette  tombe sur le numero  : %d\n",bille);

        if (bille == numM)
        {
            sommeM=sommeM*3;
            cag=cag+sommeM;
        }
        else if(((bille %2 ==0) && (numM %2==0))||((bille %2 !=0) && (numM %2!=0))) //bille%2==numM%2
        {
            sommeM= sommeM +(sommeM*1/2);
            sommeM=ceil(sommeM);
            cag=cag+sommeM;
        }
        printf("le cagnotte est : %d\n", cag );
        if (cag>0)
        {
            do
            {
                printf("vous voulez continue cette joue ? si oui tapez 1  si non tapez 0 :  " );
                scanf("%d",&i);
                i=ceil(i);
            }
            while (i<0 || i>1);
        }
    }
    while(cag>0 && i!=0);
}
void DistribueCarte1(Player Play[],int nb,int *n)
{
    CARTE C ;
    int i,j;
    for (i=0; i<nb; i++)
    {
        for (j=0; j<2; j++)
        {
            Distribue(&C);
            Play[i].C[j].valeur=TabValeur[C.valeur];
            Play[i].C[j].couleur=TabCouleur[C.couleur];
        }
    }
    (*n)=2;
}
void miser (Player Play [],int nbplayer)
{
    int i;
        srand(time(NULL));
    for(i=0; i<nbplayer ; i++)
    {
        if (i==0)
        {

            do
            {
                printf ("player %s combien vous voulez miser ? choisir une valeur entre 5$..50$: ",Play[0].nom);
                scanf("%d",&Play[0].montant);
            }
            while ((Play[0].montant<5)||(Play[0].montant >50));
            Play[0].jetons=Play[0].jetons-Play[0].montant ;

        }
        else
        {
            Play[i].montant=rand()%(50-5)+5;
            Play[i].jetons=Play[i].jetons-Play[i].montant;
            printf(" le player %d il miser   : %d$\n",i+1,Play[i].montant);
        }
    }
}
void saisir1(Player Play[],int nb)
{
    int i;
    for (i=0; i<nb; i++)
    {
        if (i==0)
        {
            printf("donner votre nom : ");
            scanf("%s",Play[0].nom);
        }
        Play[i].jetons=200;
    }


}
void affichierblk(Player play[],int nb)
{
    int i,j;

    printf("Player %s :",play[0].nom);
    for (j=0; j<2; j++)
        printf (" %d%c | ",play[0].C[j].valeur, play[0].C[j].couleur);
    printf("\n");
    for (i=1; i<nb; i++)
    {
        printf("Player %d: ",i+1);
        for (j=0; j<2; j++)
        {

            printf (" %d%c | ",play[i].C[j].valeur,play[i].C[j].couleur);
        }
        printf ("\n");
    }
}
void affichierblackjack (CARTE c[],int n)
{
    int j;
    printf("voici les cartes de blackjack : ");
    for (j=0; j<1; j++)
        printf("%d%c|",c[j].valeur,c[j].couleur);
    printf ("**\n\n");
}
void carteblackjack(CARTE c[],int n)
{
    int j=0;
    CARTE d ;
    while ( j<n)
    {
        Distribue(&d);
        c[j].valeur=TabValeur[d.valeur];
        c[j].couleur=TabCouleur[d.couleur];
        j++;
    }
    affichierblackjack(c,n);
}
void sommeCarte(Player Play[],int nbplayer,int n)
{
    int i,j,s;
    for (i=0; i<nbplayer; i++)
    {
        if (i==0)
            printf (" la somme de carte pour player %s : ",Play[i].nom);
        else
            printf (" la somme de carte pour player %d : ",i+1);
        s=0;
        Play[i].scrate=0;
        for (j=0; j<n; j++)
            if (Play[i].C[j].valeur==11 || Play[i].C[j].valeur== 12 || Play[i].C[j].valeur==13 )
                s+=10;
            else
                s+=Play[i].C[j].valeur;
        Play[i].scrate+=s;
        printf ("%d \n",s);
    }

}
void afficheCarte(CARTE c[],int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("%d%c | ",c[i].valeur,c[i].couleur);
    printf ("\n");
}
void distruber(CARTE c[],int *n)
{
    CARTE   d;
    Distribue(&d);
    c[(*n)].valeur=TabValeur[d.valeur];
    c[(*n)].couleur=TabCouleur[d.couleur];
    (*n)++;
    afficheCarte(c,(*n));
}
int sommeCarter(Player p,int n)
{
    int j,s;
    s=0;
    for (j=0; j<n; j++)
    {
        if (p.C[j].valeur==11 || p.C[j].valeur== 12 || p.C[j].valeur==13 )
            s+=10;
        else
            s+=p.C[j].valeur;

    }
    return s;
}
void MiserCarte(Player Play[],int nbplayer,int *n)
{
    char  j;
    int i,montant;

    do
    {
        printf("Vous voulez plus de cartes? tapez o ou n: ");

        do
        {
            j = getchar();
        }
        while (j!='o' &&j!='n');
        if (j=='o')
        {
            do
            {
                printf ("player %s combien vous voulez miser , choisir une valeur entre 5..%d: ",Play[0].nom,Play[0].jetons);
                scanf("%d",&montant);
            }
            while (montant<5||montant >Play[0].jetons);
            Play[0].jetons=Play[0].jetons-montant;
            Play[0].montant=Play[0].montant+montant;
            printf("Vous avez une autre carte maintenant.\n");
            printf("player %s :  ",Play[0].nom);
            distruber(Play[0].C,n);
            Play[0].scrate=sommeCarter(Play[0],*n);
            printf("vous avez une autre somme maintnenat : %d \n",Play[0].scrate);
            if (Play[0].scrate>21)
            {
                strcpy(Play[0].rslt,"BUST");
                printf ("le player %s : %s\n",Play[0].nom,Play[0].rslt);
            }

        }

    }
    while(Play[0].scrate<21 && j!='n'&& Play[0].jetons>5 );
    srand(time(NULL));
    for (i=1; i<nbplayer; i++)
    {
        (*n)=2;//taille de carte ;
        if (Play[i].scrate<17)
        {
            do
            {
                montant=rand()%(Play[i].jetons-5)+5;
                Play[i].jetons=Play[i].jetons-montant;
                Play[i].montant=Play[i].montant+montant;
                printf(" le player %d a  mise   : %d$\n",i+1,montant);
                printf("player %d :  ",i+1);
                distruber(Play[i].C,n);
                Play[i].scrate=sommeCarter(Play[i],*n);
                printf("le player %d a une autre somme maintnenat : %d \n",i+1, Play[i].scrate);
                if (Play[i].scrate>21)
                {
                    strcpy(Play[i].rslt,"BUST");
                    printf ("le player %d : %s\n",i+1,Play[i].rslt);
                }
             }
            while( Play[i].scrate<17 && strcmp(Play[i].rslt,"BUST")!=0 );

        }
        getch();
    }

}
int  sommeblckjack(CARTE c[],int n)
{
    int j,s;
    s=0;
    for (j=0; j<n; j++)
    {
        if (c[j].valeur==11 || c[j].valeur== 12 || c[j].valeur==13 )
            s+=10;
        else
            s+=c[j].valeur;

    }
    return s;
}
int  affichecarteblackjack(CARTE c[],int *n)
{
    int j,s=0;
    (*n)=2;
    printf("voici les cartes de blackjack : ");
    for(j=0; j<(*n); j++)
    {
        printf("%d%c|",c[j].valeur,c[j].couleur);
        if (c[j].valeur==11 || c[j].valeur== 12 || c[j].valeur==13 )
            s+=10;
        else
            s+=c[j].valeur;
    }
    printf("\n");
    printf("la somme de carte  black jack :%d\n",s);
    if(s<17)
    {
        do
        {
            printf("le black jack est une autre carte maintnenat: ");
            distruber(c,n);
            s=sommeblckjack(c,(*n));
            printf("la somme de carte  black jack maintnant :%d\n",s);
        }
        while (s<17);
    }
    return s;
}
void Win(Player Play[],int nb,int sb)
{
    int j,k=0 ;
    if (sb>21)
    {
        for(j=0; j<nb; j++)
        {
            if (strcmp(Play[j].rslt,"BUST")!=0)
            {
                if (j == 0)
                    printf("le player %s est win avec la somme de carte %d ",Play[j].nom,Play[j].scrate);
                else
                    printf("le player %d est win avec la somme de carte %d ",j+1, Play[j].scrate);
                printf ("\n");
            }

        }
    }
    else
    {
        for(j=0; j<nb; j++)
        {
            if (Play[j].scrate>=sb&&strcmp(Play[j].rslt,"BUST")!=0)
            {
                if (j == 0)
                    printf("le player %s est win avec la somme de carte %d ",Play[j].nom,Play[j].scrate);
                else
                    printf("le player %d est win avec la somme de carte %d ",j+1, Play[j].scrate);
                k++;
                printf ("\n");
            }

        }
        if (k==0)
            printf("le blackjack est win \n");
    }
}
void BlackJack()
{


    Player Play[6];
    CARTE c[10];
    int sommeblack,n,nbplayer;
    InitJeu();
    do
    {
        printf(" Entrez le nombre de participants entre 2 et 5: ");
        scanf("%d",&nbplayer);
        if((nbplayer<2) || (nbplayer>5))
            printf("Donnee non valide\n");
    }
    while((nbplayer<2)||(nbplayer >5));
    saisir1(Play,nbplayer);
    printf("les players ont mis%c :",130);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    miser(Play, nbplayer);
    DistribueCarte1(Play,nbplayer,&n);
    getch();
    printf("\nle donneur distribue les cartes : ");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    affichierblk(Play,nbplayer);
    getch();
    printf("\nle donneur a distribu%c les cartes de blackjack : ",130);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    carteblackjack(c,n);
    getch();
    printf ("les sommes des cartes pour chaque player :  ");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    sommeCarte(Play,nbplayer,n);
    getch();
    printf("\npartie  miser les cartes :");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    MiserCarte(Play,nbplayer,&n);
    printf("\nle donneur  Visible  le  cartes de blackjack : ");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    sommeblack=affichecarteblackjack(c,&n);
    printf("\n partie final qui est gagine: ");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178,176,177,178);
    printf("la somme de carte blackjack : %d\n",sommeblack);
    Win(Play,nbplayer,sommeblack);


}


int main()
{
    int x;
    do
    {


        printf ("\n\n");
        printf("\t\t\t***********************************\n");
        printf("\t\t\t*  -1- Jeu de Roulette            *\n");
        printf("\t\t\t*  -2- Jeu de Pocker              *\n");
        printf("\t\t\t*  -3- Jeu de BlackJack           *\n");
        printf("\t\t\t*  -4- Quitter                    *\n");
        printf("\t\t\t***********************************\n");
        do
        {

            printf ("   choisir votre Jeu :");
            scanf ("%d",&x);

        }
        while (x<1 || x>4);
        system("cls");
        switch(x)
        {
        case 1:
            printf(" \t\t\t Le Jeu De Roulette  \n");
            JeuRoulette();
            break;
        case 2:
            JeuPoker();
            break ;
        case 3:
            printf("\t\t\t Le jeu De BlackJack \n");
            BlackJack();
            break  ;
        default :
            printf("\t\t\t bye bye bye ... \n");

        }
        getch();
        system("cls");
    }
    while(x!=4);

    return 0;
}
