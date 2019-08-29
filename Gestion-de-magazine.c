#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<dos.h>
#include<windows.h>
#include<time.h>

/////////////////////////////////////////////////////////////////

/// structures des paiement

//prototype de structure de paiement
typedef struct payment Payment;

//une liste chainée de paiements
typedef struct PaymentElement{
Payment *payment;
struct PaymentElement *next;
}PaymentElement;

/// Date
typedef struct{
int day;
int month;
int year;
}Date;

/// structures des produits
typedef struct product{
    int code;
    char *designation;
    double prixVente;
    double prixAchat;

}Product;

typedef struct productElement{
    Product *produit;
    struct productElement *next;

}productElement;

/// structures des clients
typedef struct client{
int code;
char *nom;
char *prenom;
char *tel;
}Customer;

typedef struct Listclient{
Customer *c;
struct Listclient *suiv;
}CustomerElement;


/////////////////////////////////////////////////////////////////

/// structures des ventes

//pour une ligne de commande
typedef struct Item{
int quantite;
double subTotal;
Product *product; // a un seul produit
}Item;

//pour une liste chainée de lignes de commande
typedef struct ItemElement{
Item *item;
struct ItemElement *next;
}ItemElement;

/////////////////////////////////////////////////////////////////

//une vente
typedef struct Sale{
int saleCode;
double total;
Date date;
ItemElement *itemsList; //une liste chainée de lignes de commande
Customer *customer; // appartient à un seul client
PaymentElement *payElement; // une vente a une liste chainée de paiement
}Sale;

//une liste chainée de vente
typedef struct SaleElement{
Sale *sale;
struct SaleElement *next;
}SaleElement;

/////////////////////////////////////////////////////////////////

/// structures des paiement

//un paiement
struct payment{
int paymentCode;
double amount;
char *type ;
Date date;
Sale *sale ; //apartient à une vente
};

///////////////////////////////////////////////////////////////// ///////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// Partie des produits

Product *createproduct(int c,char *des,double p,double q)
{
    Product *x;
    x = (Product*)malloc(sizeof(Product));
    x->code = c;
    x->designation = des;
    x->prixVente= p;
    x->prixAchat= q;
    return x;
}

void displayProduct(Product *L)
{
    printf("************************************ \n");
    printf("code produit : %d\n",L->code);
    printf("nom : %s\n",L->designation);
    printf("prix de vente : %0.2lf\n",L->prixVente);
	printf("prix d'achat : %0.2lf\n",L->prixAchat);
    printf("************************************ \n");
}

productElement *create_new_element(Product *p)
{
    productElement *X;
    X = (productElement*)malloc(sizeof(productElement));
    X->produit = p;
    X->next = NULL;
    return X;
}

Product *get_product(productElement *s,int c)
{
    productElement *pt;
    if(s != NULL)
    {
    pt = s;
    while(pt!=NULL &&  pt->produit->code!=c )
    {
        pt = pt->next;
    }
    if(pt!=NULL)
        return pt->produit;
     }
     return NULL;


}

void display_product_liste(productElement *s)
{
    productElement *c;
    c = s;
    if(c==NULL){
        printf("La liste des produits est vide !!!");
        getch();
    }
    while(c!=NULL)
    {
        displayProduct(c->produit);
        c = c->next;
    }
}

void add_product_liste(productElement **L,Product *p)
{
    productElement *C,*nv;
    nv = create_new_element(p);
    if(*L==NULL)
    {
        *L = nv;
        nv->produit = p;

    }
    else
    {
        C = *L;
        while(C->next !=NULL)
            C = C->next;

        C->next = nv;
        nv->produit = p;
    }
}

void delete_product_from_list(productElement **L,int code)
{
    productElement *c,*tmp;
    if(*L!=NULL){
    if((*L)->produit->code==code)
    {
    	c=*L;
    	*L=(*L)->next;
    	free(c);
	}
	else
	{
	c=*L;
    while(c!=NULL && c->produit->code!=code)
    {
        tmp=c;
        c=c->next;
    }
    if(c!=NULL){
    tmp->next = c->next;
    free(c);
    }
    else
        printf("Le code produit que vous enterez n'existe pas dans la liste !!!");
        getch();
    }
   	}
   	else
    {
        printf("Le code produit que vous enterez n'existe pas dans la liste !!!");
        getch();
    }
}

void modifierProduct(Product *cl)
{
Product *p;
char *des;
int code;
double a,b;
p=cl;
if(p!=NULL){
        printf("\nDonner le nouveau code de produit : ");
        scanf("%d",&code);
        p->code=code;
        printf("\nDonner la nouvelle designation : ");
        des=(char*)malloc(sizeof(char)*10);
        scanf("%s",des);
        p->designation=des;
        printf("\nDonner le nouveau prix de vente : ");
        scanf("%lf",&a);
        p->prixVente=a;
        printf("\nDonner le nouveau prix d'achat : ");
        scanf("%lf",&b);
        p->prixAchat=b;
       }
       else
       {
        printf("Le code produit que vous enterez n'existe pas dans la liste !!!");
        getch();
       }
}

void ModifierProductList(productElement *cl,int code)
{
Product *p=NULL;
p=get_product(cl,code);
modifierProduct(p);
}

///////////////////////////////////////////////////////////////// ///////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// Partie des clients

Customer *createClient(int c,char *nom,char *prenom,char *tel)
{
    Customer *x;
    x = (Customer*)malloc(sizeof(Customer));
    x->code = c;
    x->prenom = prenom;
    x->nom = nom;
    x->tel = tel;
    return x;
}

void afficherClient(Customer *L)
{
    printf("************************************ \n");
    printf("code client : %d \n",L->code);
    printf("nom : %s \n",L->nom);
    printf("prenom : %s\n",L->prenom);
    printf("Numero de telephone : %s\n",L->tel);
    printf("************************************ \n");
}

CustomerElement *create_ListClient(Customer *cl)
{
    CustomerElement *X;
    X = (CustomerElement*)malloc(sizeof(CustomerElement));
    X->c = cl;
    X->suiv = NULL;
    return X;
}

Customer *get_client(CustomerElement *s,int code)
{
    CustomerElement *pt;
    if(s != NULL)
    {
    pt = s;
    while(pt!=NULL && pt->c->code != code)
    {
        pt = pt->suiv;
    }

    if(pt!=NULL)
        return pt->c;
    }
        return NULL;
}

void afficher_Listclient(CustomerElement *s)
{
    CustomerElement *c;
    c = s;
    if(c==NULL){
        printf("La liste des clients est vide !!!");
        getch();
    }
    while(c!=NULL)
    {
        afficherClient(c->c);
        c = c->suiv;
    }
}

void ajouterclient_to_List(CustomerElement **L,Customer *p)
{
    CustomerElement *C,*tmp,*nv;
    nv = create_ListClient(p);
    if(*L==NULL)
    {
        *L = nv;
        nv->c = p;

    }
    else
    {
        C = *L;
        while(C !=NULL)
        {
            tmp = C;
            C = C->suiv;
        }

        tmp->suiv = nv;
        nv->c = p;
    }
}

void supprimerClient_List(CustomerElement **L,int code)
{
    CustomerElement *c,*tmp;
    if(*L!=NULL){
    if((*L)->c->code==code)
    {
    	c=*L;
    	*L=(*L)->suiv;
    	free(c);
	}
	else
	{
	c=*L;
    while(c!=NULL && c->c->code!=code)
    {
        tmp=c;
        c=c->suiv;
    }
    if(c!=NULL){
    tmp->suiv = c->suiv;
    free(c);
    }
    else
        printf("Le code de client que vous entrez n'existe pas dans la liste !!!");
        getch();
    }
   	}
   	 else
        printf("Le code de client que vous entrez n'existe pas dans la liste  !!!");
        getch();
}

void modifierClient(Customer *cl)
{
Customer *p;
char *nom,*prenom,*tel;
int code;
p=cl;
    if(p!=NULL){
        printf("\nDonner le nouveau code de client : ");
        scanf("%d",&code);
        p->code=code;
        printf("\nDonner le nouveau nom de client : ");
        nom=(char*)malloc(sizeof(char)*10);
        scanf("%s",nom);
        p->nom=nom;
        getchar();
        printf("\nDonner le nouveau prenom de client : ");
        prenom=(char*)malloc(sizeof(char)*10);
        scanf("%s",prenom);
        p->prenom=prenom;
        printf("\nDonner la nouvelle numero de telephone : ");
        tel=(char*)malloc(sizeof(char)*10);
        scanf("%s",tel);
        p->tel=tel;
       }
    else
        printf("Le code de client que vous entrez n'existe pas dans la liste !!!");
        getch();
}

void modifierInfoClient(CustomerElement *cl,int code)
{
Customer *p=NULL;
p=get_client(cl,code);
modifierClient(p);
}
///////////////////////////////////////////////////////////////// ///////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// Partie des ventes

/////////////////////////////ligne de commande

Item *createItem(int quantite,Product *p)
{
	Item *X;
    X = (Item*)malloc(sizeof(Item));
    X->quantite = quantite;
    X->product=p;
    X->subTotal=quantite*p->prixVente;
    return X;
}

ItemElement *create_List_Item(Item *cl)
{
    ItemElement *X;
    X = (ItemElement*)malloc(sizeof(ItemElement));
    X->item = cl;
    X->next = NULL;
    return X;
}

void ajouter_Item_to_List(ItemElement **L,Item *p)
{
    ItemElement *C,*tmp,*nv;
    nv = create_List_Item(p);
    if(*L==NULL)
    {
        *L = nv;
        nv->item = p;

    }
    else
    {
        C = *L;
        while(C !=NULL && C->item->product->code!=p->product->code)
        {
            tmp = C;
            C = C->next;
        }

        if(C==NULL){
        tmp->next = nv;
        nv->item = p;
		}
		else
		{
			C->item->quantite+=p->quantite;
		    C->item->subTotal=C->item->quantite*(C->item->product->prixVente);
		}
    }
}

void afficherItem(Item *L)
{
    printf("*************************************** \n");
    displayProduct(L->product);
    printf("quantite : %d \n",L->quantite);
    printf("subtotal : %0.2f \n",L->subTotal);
    printf("*************************************** \n");
}

void afficher_ListItem(ItemElement *s)
{
    ItemElement *c;
    c = s;
    while(c!=NULL)
    {
        afficherItem(c->item);
        c = c->next;
    }
}

Item *get_Item(ItemElement *s,int code)
{
    ItemElement *pt;
    if(s != NULL)
    {
    pt = s;
    while(pt!=NULL && pt->item->product->code!= code)
    {
        pt = pt->next;
    }
    if(pt!=NULL)
        return pt->item;
    }
        return NULL;
}

void supprimerItem_List(ItemElement **L,int code)
{
    ItemElement *c,*tmp;
    if(*L!=NULL){
    if((*L)->item->product->code==code)
    {
    	c=*L;
    	*L=(*L)->next;
    	free(c);
	}
	else
	{
	c=*L;
    while(c!=NULL && c->item->product->code!=code)
    {
        tmp=c;
        c=c->next;
    }
    if(c!=NULL){
    tmp->next = c->next;
    free(c);
    }
    }
   	}
}

void modifierItem(Item *cl)
{
Item *p;
int q;
p=cl;
if(p!=NULL){
        printf("\nDonner la nouvelle quantite : ");
        scanf("%d",&q);
        p->quantite=q;
        p->subTotal=p->quantite*(p->product->prixVente);
       }
}

void modifierItem_List(ItemElement *cl,int code)
{
Item *p=NULL;
p=get_Item(cl,code);
modifierItem(p);
}

/////////////////////////////sale

Sale *createSale(int code,Date date,ItemElement *itemList,Customer *cus)
{
	Sale *X;
	ItemElement *s;
    X = (Sale*)malloc(sizeof(Sale));
    X->saleCode=code;
    X->date=date;
    X->itemsList=itemList;
    X->customer=cus;
    X->payElement=NULL;
    X->total=0;
    s=X->itemsList;
    while(s!=NULL){
    	 X->total+=s->item->subTotal;
    	 s=s->next;
	}
    return X;
}

SaleElement *create_List_Sale(Sale *cl)
{
    SaleElement *X;
    X = (SaleElement*)malloc(sizeof(SaleElement));
    X->sale = cl;
    X->next = NULL;
    return X;
}

void ajouter_Sale_to_List(SaleElement **L,Sale *s)
{
    SaleElement *C,*tmp,*nv;
    nv = create_List_Sale(s);
    if(*L==NULL)
    {
        *L = nv;
        nv->sale = s;

    }
    else
    {
        C = *L;
        while(C !=NULL)
        {
            tmp = C;
            C = C->next;
        }
        tmp->next = nv;
        nv->sale = s;
	}
}

void afficherSale(Sale *L)
{
    printf("*********************************************************** \n");
    printf("code vente : %d \n",L->saleCode);
    printf("date : %d-%d-%d \n",L->date.day,L->date.month,L->date.year);
    afficherClient(L->customer);
    afficher_ListItem(L->itemsList);
    printf("total : %0.2lf\n",L->total);
    printf("*********************************************************** \n");
}

void afficher_ListSale(SaleElement *s)
{
    SaleElement *c;
    c = s;
    if(c==NULL)
    {
        printf("La liste des ventes est vide !!!");
        getch();
    }
    while(c!=NULL)
    {
        afficherSale(c->sale);
        c = c->next;
    }
}

Sale *get_Sale(SaleElement *s,int code)
{
    SaleElement *pt;
    if(s != NULL)
    {
    pt = s;
    while(pt!=NULL && pt->sale->saleCode!= code)
    {
        pt = pt->next;
    }

    if(pt!=NULL)
        return pt->sale;
    }
    return NULL;
}

void supprimerSale_List(SaleElement **L,int code)
{
    SaleElement *c,*tmp;
    if(*L!=NULL){
    if((*L)->sale->saleCode ==code)
    {
    	c=*L;
    	*L=(*L)->next;
    	free(c);
	}
	else
	{
	c=*L;
    while(c!=NULL && c->sale->saleCode!=code)
    {
        tmp=c;
        c=c->next;
    }
    if(c!=NULL){
    tmp->next = c->next;
    free(c);
    }
    else
    {
        printf("Le code de vente n'est pas valide !!!");
        getch();
    }
   	}
    }
   	else
    {
        printf("Le code de vente n'est pas valide !!!");
        getch();
}
}

void modifierSale(Sale *cl)
{
Sale *p;
int q;
Date e;
ItemElement *s;
p=cl;
if(p!=NULL){
     	printf("donnez le nouveau code de vente : ");
     	scanf("%d",&q);
     	p->saleCode=q;
     	printf("donnez la nouvelle Date (dd-mm-yy) : ");
        scanf("%d %d %d",&e.day,&e.month,&e.year);
        p->date=e;
       }
else
    {
        printf("Le code de vente n'est pas valide !!!");
        getch();
}
}

void modifierSale_List(SaleElement *cl,int code)
{
Sale *p=NULL;
p=get_Sale(cl,code);
modifierSale(p);
}
///////////////////////////////////////////////////////////////// ///////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// Partie des payements

Payment *createPayment(int c,char *s,Date d,Sale *sal)
{
    Payment *x;
    x=(Payment*)malloc(sizeof(Payment));
    double f;
    x->paymentCode=c;
    x->type=s;
    x->date=d;
    x->sale=sal;
    if(strcmp(x->type,"espece")==0) // paiement par espèce
    x->amount=x->sale->total;
    else if(strcmp(x->type,"cheque")==0)  // paiement par chèque
    x->amount=x->sale->total; // + précise les informations relatives au chèque (propriétaire du chèque, date d’effet).
    else if(strcmp(x->type,"en ligne")==0) // paiement par carte bancaire (en ligne)
    x->amount=x->sale->total; // + le client saisit le code de sa carte pour se connecter au serveur de paiement et valider le montant à payer.
    else // paiement par traite
    {
    	printf("Paiement par Traite : ");
    	scanf("%lf",&f);
    	x->amount-=f;
    	printf("Reste : %0.2lf \n",x->amount);
    	getch();
	}
	return x;
}

PaymentElement *create_List_Payment(Payment *p)
{
    PaymentElement *X;
    X = (PaymentElement*)malloc(sizeof(PaymentElement));
    X->payment = p;
    X->next = NULL;
    return X;
}

void ajouter_Payment_to_List(PaymentElement **L,Payment *s)
{
    PaymentElement *C,*tmp,*nv;
    nv = create_List_Payment(s);
    if(*L==NULL)
    {
        *L = nv;
        nv->payment = s;

    }
    else
    {
        C = *L;
        while(C !=NULL)
        {
            tmp = C;
            C = C->next;
        }
        tmp->next = nv;
        nv->payment = s;
	}
}

void afficherPayment(Payment *L)
{
    printf("*************************************************************************** \n");
    printf("code paiement : %d \n",L->paymentCode);
    printf("date : %d-%d-%d \n",L->date.day,L->date.month,L->date.year);
    printf("type : %s \n",L->type);
    printf("montant : %0.2lf\n",L->amount);
    afficherSale(L->sale);
    printf("*************************************************************************** \n");
}

void afficher_ListPayment(PaymentElement *s)
{
    PaymentElement *c;
    c = s;
    if(c==NULL)
    {
        printf("La liste des paiements est vide !!!");
        getch();
    }
    while(c!=NULL)
    {
        afficherPayment(c->payment);
        c = c->next;
    }
}


Payment *get_Payment(PaymentElement *s,int code)
{
    PaymentElement *pt;
    if(s != NULL)
    {
    pt = s;
    while(pt!=NULL && pt->payment->paymentCode!=code)
    {
        pt = pt->next;
    }
    if(pt!=NULL)
        return pt->payment;

    }
	return NULL;
}

void supprimer_PaymentList(PaymentElement **L,int code)
{
    PaymentElement *c,*tmp;
    if(*L!=NULL){
    if((*L)->payment->paymentCode ==code)
    {
    	c=*L;
    	*L=(*L)->next;
    	free(c);
	}
	else
	{
	c=*L;
    while(c!=NULL && c->payment->paymentCode!=code)
    {
        tmp=c;
        c=c->next;
    }
    if(c!=NULL){
    tmp->next = c->next;
    free(c);
    }
    else
    {
        printf("Le code de paiement n'est pas valide !!!");
        getch();
    }
    }
   	}
   	else
    {
        printf("Le code de paiement n'est pas valide !!!");
        getch();
    }
}

void modifierPayment(Payment *P)
{
Payment *p;
int q;
Date e;
double f;
char *h;
PaymentElement *s;
p=P;
if(p!=NULL){
     	printf("donnez le nouveau code de paiement : ");
     	scanf("%d",&q);
     	p->paymentCode=q;
     	printf("donnez la nouvelle Date (dd-mm-yy) : ");
        scanf("%d %d %d",&e.day,&e.month,&e.year);
        p->date=e;
        printf("donnez la nouvelle type de paiement : ");
        h=(char*)malloc(sizeof(char)*10);
        scanf("%s",h);
        p->type=h;
        if(strcmp(p->type,"espece")==0) // paiement par espèce
        p->amount=p->sale->total;
        else if(strcmp(p->type,"cheque")==0)  // paiement par chèque
        p->amount=p->sale->total; // + précise les informations relatives au chèque (propriétaire du chèque, date d’effet).
        else if(strcmp(p->type,"en ligne")==0) // paiement par carte bancaire (en ligne)
        p->amount=p->sale->total; // + le client saisit le code de sa carte pour se connecter au serveur de paiement et valider le montant à payer.
        else // paiement par traite
        {
    	printf("Paiement par Traite : ");
    	scanf("%lf",&f);
    	p->amount-=f;
    	printf("Reste : %0.2lf \n",p->amount);
    	getch();
     	}
       }
else
    {
        printf("Le code de paiement n'est pas valide !!!");
        getch();
    }
}

void modifierPayment_List(PaymentElement *p,int code)
{
Payment *s=NULL;
s=get_Payment(p,code);
modifierPayment(s);
}

///////////////////////////////////////////////////////////////// ///////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////

////////////////////////////////////Partie des fichiers

////////// remplaire une liste chaine par les informations déja existe sur un fichier "products"
void fichierversliste_Product(productElement **o)
{
       FILE *f;
       Product *x=(Product*)malloc(sizeof(Product));
       f=fopen("Products.txt","r+");
       while (!feof(f))
        {
              fscanf(f,"%d",&x->code);
              x->designation=(char*)malloc(sizeof(char)*10);
              fscanf(f,"%s",x->designation);
               //printf("%s\n",x->designation);
              fscanf(f,"%lf",&x->prixVente);
              fscanf(f,"%lf\n",&x->prixAchat);
           //    printf("%lf\n",x->prixAchat);
              add_product_liste(o,x);
        }
        fclose(f);
}

////////////////transformer les données de la liste des produits vers le fichier "products"
void listeversfichier_Product(productElement *o)
{
     FILE *f;
     f=fopen("Products.txt","w+");
     productElement *c;
     c=o;
     while(c!=NULL)
     {
            fprintf(f,"%d\n",c->produit->code);
            fprintf(f,"%s\n",c->produit->designation);
            fprintf(f,"%0.2lf\n",c->produit->prixVente);
            fprintf(f,"%0.2lf\n",c->produit->prixAchat);
            c=c->next;
     }
     fclose(f);
}

////////// remplaire une liste chaine par les informations déja existe sur un fichier "Customers"
void fichierversliste_Customer(CustomerElement **o)
{
       FILE *f;
       Customer *x=(Customer*)malloc(sizeof(Customer));
       f=fopen("Customers.txt","r");
       while (!feof(f))
        {
              fscanf(f,"%d",&x->code);
              x->nom =(char*)malloc(sizeof(char)*10);
              x->prenom =(char*)malloc(sizeof(char)*10);
              x->tel =(char*)malloc(sizeof(char)*10);
              fscanf(f,"%s",x->nom);
              fscanf(f,"%s",x->prenom);
              fscanf(f,"%s\n",x->tel);
              ajouterclient_to_List(o,x);
        }
        fclose(f);
}

////////////////transformer les données de la liste des produits vers le fichier "Custmers"
void listeversfichier_Customer(CustomerElement *o)
{
     FILE *f;
     f=fopen("Customers.txt","w+");
     CustomerElement *c;
     c=o;
     while(c!=NULL)
     {
            fprintf(f,"%d\n",c->c->code);
            fprintf(f,"%s\n",c->c->nom);
            fprintf(f,"%s\n",c->c->prenom);
            fprintf(f,"%s\n",c->c->tel);
            c=c->suiv;
     }
     fclose(f);
}



///////////////////////////////////////////////////////////////// ///////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////
//////////////////// le programme principale


//////////////
void msgbienvenue()
{
    int i;
    printf("\n\n\n\n\n");
    printf("\t\t");
  for (i = 0 ; i < 2 ; i++)
    {
        printf("\t\t\t\t");
        printf("                    \r");
        Sleep(300);
        printf("\t\t\t\t");
        printf("BIENVENUE !\r");
        Sleep(300);
    }
    system("cls");
}
////////////////
void afficher_menu()
{
    // Menu principal
    system("COLOR F9");
    msgbienvenue();
    printf("\n\n");
    printf("               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\n");
    printf("                 --------------------------------------------\n");
    printf("                    <-> La Gestion De Magazine <->\n");
    printf("                 --------------------------------------------\n");
    printf("                    [1] Gestion Des Produits\n");
    printf("                    [2] Gestion Des Clients\n");
    printf("                    [3] Gestion Des Ventes\n");
    printf("                    [4] Gestion Des Paiements\n");
    printf("                    [5] Quitter\n");
    printf("               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n\n");
    printf("                        Veuillez choisir votre choix :");
}
///////////////////////
void afficher_menu1()
{
    // Menu du Bus
    system("COLOR F0");
    printf("\n\n");
    printf("               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\n");
    printf("                 --------------------------------------------\n");
    printf("                          <-> LA GESTION Des Produits <->\n");
    printf("                 --------------------------------------------\n\n");
    printf("                    [1] Afficher tous les produits disponibles\n");
    printf("                    [2] Chercher d'un produit\n");
    printf("                    [3] Ajouter un nouveau produit\n");
    printf("                    [4] Mise a jour des information d'un produit\n");
    printf("                    [5] Supprimer un produit\n");
    printf("                    [6] Retour au menu principal \n\n\n");
    printf("               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n\n");
    printf("                        Veuillez choisir votre choix :");
}

/////////////////////
void afficher_menu2()
{
    // Menu du Bus
    system("COLOR F0");
    printf("\n\n");
    printf("               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\n");
    printf("                 --------------------------------------------\n");
    printf("                          <-> LA GESTION Des Clients <->\n");
    printf("                 --------------------------------------------\n\n");
    printf("                    [1] Afficher tous les clients\n");
    printf("                    [2] Chercher d'un client\n");
    printf("                    [3] Ajouter un nouveau client\n");
    printf("                    [4] Mise a jour des information d'un client\n");
    printf("                    [5] Supprimer un client\n");
    printf("                    [6] Retour au menu principal \n\n\n");
    printf("               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n\n");
    printf("                        Veuillez choisir votre choix :");
}

/////////////////////
void afficher_menu3()
{
    // Menu du Bus
    system("COLOR F0");
    printf("\n\n");
    printf("               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\n");
    printf("                 --------------------------------------------\n");
    printf("                          <-> LA GESTION Des Ventes <->\n");
    printf("                 --------------------------------------------\n\n");
    printf("                    [1] Afficher tous les ventes\n");
    printf("                    [2] Chercher d'un vente\n");
    printf("                    [3] Ajouter un nouveau vente\n");
    printf("                    [4] Mise a jour des information d'un vente\n");
    printf("                    [5] Supprimer un vente\n");
    printf("                    [6] Retour au menu principal \n\n\n");
    printf("               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n\n");
    printf("                        Veuillez choisir votre choix :");
}

/////////////////////
void afficher_menu4()
{
    // Menu du Bus
    system("COLOR F0");
    printf("\n\n");
    printf("               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\n");
    printf("                 --------------------------------------------\n");
    printf("                          <-> LA GESTION Des paiements <->\n");
    printf("                 --------------------------------------------\n\n");
    printf("                    [1] Afficher tous les paiements\n");
    printf("                    [2] Chercher d'un paiement\n");
    printf("                    [3] Ajouter un nouveau paiement\n");
    printf("                    [4] Mise a jour des information d'un paiement\n");
    printf("                    [5] Supprimer un paiement\n");
    printf("                    [6] Retour au menu principal \n\n\n");
    printf("               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n\n");
    printf("                        Veuillez choisir votre choix :");
}

///////////////

int main(){
   productElement *o=NULL; /// liste des produits
   CustomerElement *cu=NULL; /// liste des clients
   ItemElement *I=NULL; /// liste des lignes de commandes
   SaleElement *s=NULL; /// liste des ventes
   PaymentElement *P=NULL; /// liste des paiements

  int code;
   char c,a,b,d;
    LOOP:
    while(1)
    {
        afficher_menu();
        c = getch();
        while(c>'5' || c<'1')
            c = getch();
            // clear console
        system("cls");
         switch(c)
           {
            case '1':
                 {
                fichierversliste_Product(&o);
                 while(1)
                      {
                       afficher_menu1();

                        a = getch();
                        while(a>'6' || a<'1')
                        a = getch();

                         // clear console
                        system("cls");

                        switch(a)
                        {
                         case '1':
                           {
                           display_product_liste(o);
                            break;
                           }
                         case '2':
                           {
                            Product *find;
                            printf("Chercher d'un Produit :\n");
                            printf("Donnez le code de produit : ");
                            scanf("%d",&code);
                            find=get_product(o,code);
                            if(find!=NULL)
                            displayProduct(find);
                            else
                            printf("Ce Produit n'existe pas dans la liste !!!");
                            getch();
                            listeversfichier_Product(o);
                            break;
                           }
                         case '3':
                           {
                            Product *nv;
                            double pra,prv;
                            printf("Nouveau Produit : \n");
                            printf("Donnez le code de produit : ");
                            scanf("%d",&code);
                            printf("Donnez leur nom : ");
                            char *h=(char*)malloc(sizeof(char)*10);
                            scanf("%s",h);
                            printf("Donnez leur prix de vente : ");
                            scanf("%lf",&prv);
                            printf("Donnez leur prix de vente : ");
                            scanf("%lf",&pra);
                            nv = createproduct(code,h,prv,pra);
                            add_product_liste(&o,nv);
                            listeversfichier_Product(o);
                            break;
                           }
                         case '4':
                           {
                            printf("Mise a jour des information de produit :\n");
                            printf("Donnez le code de produit : ");
                            scanf("%d",&code);
                            ModifierProductList(o,code);
                            listeversfichier_Product(o);
                            break;
                           }
                            case '5':
                           {
                            printf("Supprimer un produit :\n");
                            printf("Donnez le code de produit : ");
                            scanf("%d",&code);
                            delete_product_from_list(&o,code);
                            listeversfichier_Product(o);
                            break;
                           }
                           case '6':
                                {
                                    goto LOOP;
                                    break;
                                }
                                }
                                printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
                                getchar();
                                system("cls");

                          }
                          }

                  case '2':
                 {
                 fichierversliste_Customer(&cu);
                  while(1)
                      {
                       afficher_menu2();

                        a = getch();
                        while(a>'6' || a<'1')
                        a = getch();

                         // clear console
                        system("cls");

                        switch(a)
                        {
                         case '1':
                           {
                           afficher_Listclient(cu);
                            break;
                           }
                         case '2':
                           {
                            Customer *cfind;
                            printf("Chercher d'un Client : \n");
                            printf("Donnez le code de client : ");
                            scanf("%d",&code);
                            cfind=get_client(cu,code);
                            if(cfind!=NULL)
                            afficherClient(cfind);
                            else
                            printf("Ce client n'existe pas dans la liste !!!");
                            getch();
                            listeversfichier_Customer(cu);
                            break;
                           }
                         case '3':
                           {
                            Customer *n;
                            printf("Nouveau Client : \n");
                            printf("Donnez le code de client: ");
                            scanf("%d",&code);
                            printf("Donnez leur nom : ");
                            char *h1=(char*)malloc(sizeof(char)*10);
                            scanf("%s",h1);
                            printf("Donnez leur prenom : ");
                            char *h2=(char*)malloc(sizeof(char)*10);
                            scanf("%s",h2);
                            printf("Donnez leur telephone : ");
                            char *h3=(char*)malloc(sizeof(char)*10);
                            scanf("%s",h3);
                            n = createClient(code,h1,h2,h3);
                            ajouterclient_to_List(&cu,n);
                            listeversfichier_Customer(cu);
                            break;
                           }
                         case '4':
                           {
                            printf("Mise a jour des information de client :\n");
                            printf("Donnez le code de client : ");
                            scanf("%d",&code);
                            modifierInfoClient(cu,code);
                            listeversfichier_Customer(cu);
                            break;
                           }
                            case '5':
                           {
                            printf("Supprimer un client : \n");
                            printf("Donnez le code de client : ");
                            scanf("%d",&code);
                            supprimerClient_List(&cu,code);
                            listeversfichier_Customer(cu);
                            break;
                           }
                           case '6':
                                {
                                    goto LOOP;
                                    break;
                                }
                                }
                                printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
                                getchar();
                                system("cls");

                          }
                 }

                case '3':
                        {
                   while(1)
                      {
                       afficher_menu3();

                        a = getch();
                        while(a>'6' || a<'1')
                        a = getch();

                         // clear console
                        system("cls");

                        switch(a)
                        {
                         case '1':
                           {
                            afficher_ListSale(s);
                            break;
                           }
                         case '2':
                           {
                            Sale *sfind;
                            printf("Chercher d'une vente :\n");
                            printf("Donnez le code de vente : ");
                            scanf("%d",&code);
                            sfind=get_Sale(s,code);
                            if(sfind!=NULL)
                            afficherSale(sfind);
                            else
                            printf("Ce vente n'existe pas dans la liste !!!");
                            getch();
                            break;
                           }
                         case '3':
                           {
                            Sale *x;
                            Item *u;
                            Customer *y;
                            ItemElement *j=NULL;
                            char ok='o';
                            int codee,quantite;
                            Product *pp;
                            Date d;
                            printf("Nouvelle Vente : \n");
                            printf("Donnez le code de vente: ");
                            scanf("%d",&code);
                            printf("Donnez la date (dd-mm-yy) : ");
                            scanf("%d %d %d",&d.day,&d.month,&d.year);
                            printf("Donnez le code de client : ");
                            scanf("%d",&codee);
                            y=get_client(cu,codee);
                            if(y!=NULL){
                                    while(ok!='n')
                                    {
                                    printf("Veuillez donner les commandes de cette vente :\n");
                                    printf("Donnez le code de produit : ");
                                    scanf("%d",&codee);
                                    pp=get_product(o,codee);
                                    if(pp!=NULL)
                                    {
                                        printf("Donnez la quantite de cette produit : ");
                                        scanf("%d",&quantite);
                                        u = createItem(quantite,pp);
                                        ajouter_Item_to_List(&j,u);
                                    }
                                    getchar();
                                    printf("Y-t-elle d'autres commandes ( o='oui' ou n='non' ) :");
                                    scanf("%c",&ok);
                                    }
                                    x= createSale(code,d,j,y);
                                    ajouter_Sale_to_List(&s,x);
                            }
                            else
                            {
                                printf("Vous avez entrez un code de client qui n'existe pas dans la liste des clients, veuillez l'ajoutez avant d'ajouter cette vente !!");
                                printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
                                getch();
                                goto LOOP;
                            }
                            break;
                           }
                         case '4':
                           {
                            printf("Mise a jour des information de vente :\n");
                            printf("Donnez le code de vente : ");
                            scanf("%d",&code);
                            modifierSale_List(s,code);
                            break;
                           }
                            case '5':
                           {
                            printf("Supprimer une vente : \n");
                            printf("Donnez le code de vente : ");
                            scanf("%d",&code);
                            supprimerSale_List(&s,code);
                            break;
                           }
                           case '6':
                                {
                                    goto LOOP;
                                    break;
                                }
                                }
                                printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
                                getchar();
                                system("cls");

                          }
           }

           case '4':
                 {
                 while(1)
                      {
                       afficher_menu4();

                        a = getch();
                        while(a>'6' || a<'1')
                        a = getch();

                         // clear console
                        system("cls");

                        switch(a)
                        {
                         case '1':
                           {
                            afficher_ListPayment(P);
                            break;
                           }
                         case '2':
                           {
                           	int code;
                            Payment *finnd;
                            printf("Chercher d'un paiement :\n");
                            printf("Donnez le code de paiement: ");
                            scanf("%d",&code);
                            finnd=get_Payment(P,code);
                            if(finnd!=NULL)
                            afficherPayment(finnd);
                            else
                            printf("Ce paiement n'existe pas dans la liste !!!");
                            getch();
                            break;
                           }
                         case '3':
                           {
                            Payment *h;
                            Sale *sal;
                            int co,cc,ci;
                            Sale *findd;
                            char *y,choix;
                            Date d;
                            printf("Nouveau Paiement : \n");
                            printf("Donnez le code de ce paiement : ");
                            scanf("%d",&co);
                            y=(char*)malloc(sizeof(char)*10);
                            printf("Donnez le type ce paiement : ");
                            scanf("%s",y);
                            printf("Donnez la date (dd-mm-yy) : ");
                            scanf("%d %d %d",&d.day,&d.month,&d.year);
                            printf("Donnez le code de vente liee a ce paiement : ");
                            scanf("%d",&cc);
                            findd=get_Sale(s,cc);
                            if(findd!=NULL)
                            {
                             h=createPayment(co,y,d,findd);
                             ajouter_Payment_to_List(&P,h);
                             printf("Ce paiement est il paye ? (o='oui' et n='non') ");
                             scanf("%c",&choix);
                             if(choix == 'o')
                              {
                                sal=get_Sale(s,findd->saleCode);
                                ajouter_Payment_to_List(&findd->payElement,sal);
                              }
                            }
                            else
                            {
                                printf("Vous avez entrez un vente qui n'existe pas dans la liste des ventes, veuillez l'ajoutez avant d'ajouter ce paiement !!");
                                printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
                                getch();
                                goto LOOP;
                            }
                            break;
                           }
                         case '4':
                           {
                            printf("Mise a jour des information d'un paiement :\n");
                            printf("Donnez le code de paiement : ");
                            scanf("%d",&code);
                            modifierPayment_List(P,code);
                            break;
                           }
                            case '5':
                           {
                            printf("Supprimer un paiement :\n");
                            printf("Donnez le code de paiement : ");
                            scanf("%d",&code);
                            supprimer_PaymentList(&P,code);
                            break;
                           }
                           case '6':
                                {
                                    goto LOOP;
                                    break;
                                }
                                }
                                printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
                                getchar();
                                system("cls");

                          }
                          }

        case '5':
                 {
                 exit(0);
                 break;
                 }

           }

    }

    printf("\nAppuyer sur ENTRER pour retourner au menu principal ...");
    getchar();
    system("cls");
    return 0;
}

