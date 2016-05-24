#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"
#include "tp3.c"

int main()
{
	system(" color f0"); // ndryshimi i ngjyrave te terminalit 
	system(" title Pune Laboratori Nr. 1 - Enrik Doci - Klajdi Gjoka"); // titulli i dritares
	ListeArticles Liste_stock_dispo, Liste_stock_finished ;
	Article* ar1;
	ListeRequests Liste_Req , Liste_Req1;
	Liste_stock_dispo=(Article *)malloc(sizeof(Article));
	Liste_stock_dispo->nextArticle=Liste_stock_dispo ;strcpy(Liste_stock_dispo->name, "liste_disponible");
	Liste_stock_finished=(Article *)malloc(sizeof(Article));
	Liste_stock_finished->nextArticle=Liste_stock_finished ;strcpy(Liste_stock_finished->name, "liste_finished");
	Liste_Req = (ListeRequests)malloc(sizeof(Request));
	Liste_Req->nextRequest = Liste_Req ;

	int p , id_temp, min, max;
	char p_char ;
	char name[50], cat[50];
	while(p!=9){
		p=menu();
		system("cls");
		if (p==1){
			ReadFileListeArticles(Liste_stock_dispo);
			ReadFileListeArticles(Liste_stock_finished);
		}
		if (p==2){
			ar1=(Article *)malloc(sizeof(Article));
			printf("\tShtim i Artikullit te ri nga tastjera\n\n\tID, Emri, Pu, Sasi, Kategori : \n\t ");
			scanf("%d %s %f %d %s", &ar1->id, ar1->name, &ar1->PU, &ar1->quantity, ar1->category );
			AddArticle(Liste_stock_dispo , ar1);
		}
		if (p==3){
			scanf("%c", &p_char);
			if (p_char == 'a' || p_char == 'c'){
				printf("\n\tLista e artikujve disponibel :\n\n");
				DisplayStock(Liste_stock_dispo);
			}
			if (p_char == 'b' || p_char == 'c'){
				printf("\n\tLista e artikujve te mbaruar :\n");
				DisplayStock(Liste_stock_finished);
			}
		}

		if (p==5){
			scanf("%c", &p_char);
			printf("\n\tKerkimi i Artikujve\n");
			if (p_char == 'a' ){
				printf("\n\tJepni ID dhe/ose emertimin dhe/ose kategorine (-1 ose UNDEFINED) :\n\t");
				scanf("%d%s%s", &id_temp, name, cat);
				ResearchArticleOnCriteria(Liste_stock_dispo, id_temp, name, cat);
			}
			if (p_char == 'b' ){
				printf("\n\tJepni sasine minimale dhe maksimale : ");
				scanf("%d%d", &min, &max);
				ResearchOnQuantity(Liste_stock_dispo, min, max);
			}
			if (p_char == 'c' ){
				printf("\n\tJepni cmimin minimal dhe maksimal : ");
				scanf("%d%d", &min, &max);
				ResearchOnPrize(Liste_stock_dispo, min, max);
			}
		}		
		if (p==4){
			printf("\n\tJepni ID e artikullit qe doni te fshini: ");
			scanf("%d", &id_temp);
			DeleteArticle(Liste_stock_dispo, id_temp);
		}
		if (p==6){
			printf("\n\t\tKomandat e Perdoruesit\n");
			printf("\n\t1. Afishimi i listes re kerkesave (requests)\n");
			printf("\t2. Shtimi i requesti te ri\n");
			printf("\t3. Fshirja e listes Request\n");
			printf("\t4. Shitje me liste Request\n");
			printf("\t5. Update sasine e nje artikulli manualisht\n");
			scanf("%d", &p);
			if (p==1) DisplayRequest(Liste_Req);
			if (p==2){
				Liste_Req1 = (ListeRequests)malloc(sizeof(Request));
				printf("\n\tJep ID e artikullin dhe sasine: ");
				scanf("%d %d", &Liste_Req1->idArticle, &Liste_Req1->qte );
				AddRequest(Liste_Req, Liste_Req1);
			}
			if (p==3) DeleteRequest(Liste_Req);
			if (p==4) {SaleArticles(Liste_Req, Liste_stock_dispo, Liste_stock_finished);
				ReadFileRequest(Liste_Req);}
			if (p==5) {
				printf("\n\tJepni ID e artikullit dhe sasine qe doni ti hiqni(-x)/shtoni\n");
				scanf("%d%d", &min, &max);
				UpdateArticle(min, max, Liste_stock_dispo, Liste_stock_finished);
			}
		}
		if (p==7){
			ReadFileRequest(Liste_Req);
			getche();
			Furniturep(Liste_Req, Liste_stock_dispo, Liste_stock_finished);
		}
		if (p==8) DeleteStock(Liste_stock_dispo);
		if(p==11) DisplayRequest(Liste_Req);
		getche();
	}
	testcircle(Liste_stock_dispo);
	WriteFileListeArticles(Liste_stock_dispo);
	WriteFileListeArticles(Liste_stock_finished);
	return 0;
}