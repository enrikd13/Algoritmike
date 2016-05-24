int menu(){
	int next;
	system("cls");
	printf("\n\n\n\t\tPune Laboratori Nr. 1 - Algoritmike");
	printf("\n\n\t1 - Leximi i te dhenave nga nje file\n\t");
	printf("2 - Shtimi i nje artikulli te ri nga tastiera \n\t");
	printf("3 - Afishimi i karateristikave te stokut \n\t");
		printf("\t(a) - Stoku i disponueshem \n\t");
		printf("\t(b) - Stoku i disponueshem \n\t");
		printf("\t(c) - Stoku i disponueshem \n\n\t");
	printf("4 - Fshirja e nje artikulli \n\t");
	printf("5 - Kerkimi i nje artikulli\n\t");
		printf("\t(a) - Kerkimi sipas emrit, id, dhe/ose kategorise  \n\t");
		printf("\t(b) - Kerkimi sipas sasise  \n\t");
		printf("\t(c) - Kerkimi sipas cmimit \n\n\t");
	printf("6 - Menaxhimi i komandave te klientit \n\t");
	printf("7 - Furnizimi\n\t");
	printf("8 - Fshirja e stokut \n\t");
	printf("9 - Dalja nga programi. \n\t");
	scanf("%d", &next);
	return next;
}

void AddArticle( ListeArticles list , Article * a) { // Shtimi i artikullit ne fund
	ListeArticles leviz ;
	leviz=list;
	while (leviz->nextArticle!=list && leviz->nextArticle->PU >= a->PU){
		leviz = leviz->nextArticle;
	}
	a->nextArticle=leviz->nextArticle ;
	leviz->nextArticle = a;
}

void DisplayStock( ListeArticles list ){ // Printimi i listes
	if (list->nextArticle == list){
		printf("\n\n\n\tNuk ka artikuj te regjistruar\n");
		return ;
	}
	ListeArticles leviz ;
	leviz=list->nextArticle;
	printf("\n\tID\tArtikulli\tCmimi\t\tSasia\tKategoria\n");
	while(leviz != list){
		printf("\t%d\t%s\t%f\t%d\t%s\n",leviz->id, leviz->name, leviz->PU, leviz->quantity, leviz->category );
		leviz=leviz->nextArticle;
	}
}


void DeleteStock( ListeArticles list){
	ListeArticles leviz = list->nextArticle ;
	while(leviz != list){
		list->nextArticle = leviz->nextArticle;
		free(leviz);
		leviz=list->nextArticle;
	}
	list->nextArticle=list;
}

void DeleteArticle (ListeArticles list , int id_Article){
	ListeArticles leviz ;
	leviz=list->nextArticle;
	if(leviz->id==id_Article){
		list->nextArticle=list->nextArticle->nextArticle;
		return ;
	}
	while(leviz !=list){
		if(leviz->nextArticle->id==id_Article){
			leviz->nextArticle=leviz->nextArticle->nextArticle;
			break;
		}
		leviz=leviz->nextArticle;
	}
}

void ResearchArticleOnCriteria( ListeArticles list , int id , char *name, char *category){
	if (list->nextArticle == list){
		printf("\n\n\n\tNuk ka artikuj te regjistruar\n");
		return ;
	}
	ListeArticles leviz ;
	leviz=list->nextArticle;
	printf("\n\tID\tArtikulli\tCmimi\t\tSasia\tKategoria\n");
	while(leviz->nextArticle!=list->nextArticle){
		if ( (leviz->id == id || id == -1) && (strcmp(leviz->name, name)==0 || strcmp("UNDEFINED", name)==0 ) && (strcmp(leviz->category, category)==0 || (strcmp(category , "UNDEFINED") == 0) ) )
			printf("\t%d\t%s\t%f\t%d\t%s\n",leviz->id, leviz->name, leviz->PU, leviz->quantity, leviz->category );
		leviz=leviz->nextArticle;
	}
}

void ResearchOnQuantity(ListeArticles list , int qte_min , int qte_max){
	if (list->nextArticle == list){
		printf("\n\n\n\tNuk ka artikuj te regjistruar\n");
		return ;
	}
	ListeArticles leviz ;
	leviz=list->nextArticle;
	printf("\n\tID\tArtikulli\tCmimi\t\tSasia\tKategoria\n");
	while(leviz->nextArticle!=list->nextArticle){
		if ( leviz->quantity >= qte_min && leviz->quantity <= qte_max )
			printf("\t%d\t%s\t%f\t%d\t%s\n",leviz->id, leviz->name, leviz->PU, leviz->quantity, leviz->category );
		leviz=leviz->nextArticle;
	}
}

void ResearchOnPrize(ListeArticles list , int prize_min , int prize_max){
	if (list->nextArticle == list){
		printf("\n\n\n\tNuk ka artikuj te regjistruar\n");
		return ;
	}
	ListeArticles leviz ;
	leviz=list->nextArticle;
	printf("\n\tID\tArtikulli\tCmimi\t\tSasia\tKategoria\n");
	while(leviz->nextArticle!=list->nextArticle){
		if ( leviz->PU >= prize_min && leviz->PU <= prize_max )
			printf("\t%d\t%s\t%f\t%d\t%s\n",leviz->id, leviz->name, leviz->PU, leviz->quantity, leviz->category );
		leviz=leviz->nextArticle;
	}
}

void UpdateArticle (int id , int quantity, ListeArticles list, ListeArticles finished){
	if (list->nextArticle == list){
	printf("\n\n\n\tNuk ka artikuj te regjistruar\n");
	return ;
	}
	ListeArticles leviz ;
	leviz=list->nextArticle;
	while(leviz->nextArticle!=list->nextArticle){
		if ( leviz->id == id ){
			leviz->quantity+=quantity;
			break ;
		}
		leviz = leviz->nextArticle;
	}
	if (leviz->quantity <= 0){
		leviz->quantity = 0;
		DeleteArticle(list, id);
		AddArticle(finished, leviz);
		
	}
}

void SaleArticles (ListeRequests r, ListeArticles list, ListeArticles finished ){
	ListeRequests leviz ;
	leviz = r->nextRequest ;
	while (leviz -> nextRequest != r->nextRequest){
		UpdateArticle(leviz->idArticle, -abs(leviz->qte), list, finished);
		leviz=leviz->nextRequest;
	}
}

void Furniturep (ListeRequests r, ListeArticles list, ListeArticles finished ){
	ListeRequests leviz ;
	leviz = r->nextRequest ;
	while (leviz -> nextRequest != r->nextRequest){
		UpdateArticle(leviz->idArticle, abs(leviz->qte), list, finished);
		leviz=leviz->nextRequest;
	}
}

void AddRequest( ListeRequests list , Request * a) { 
	ListeRequests leviz ;
	leviz=list->nextRequest;
	while (leviz->nextRequest!=list->nextRequest){
		leviz = leviz->nextRequest;
	}
	a->nextRequest=leviz->nextRequest ;
	leviz->nextRequest = a;
	getche();
}

void DisplayRequest( ListeRequests list ){ 
	if (list->nextRequest == list){
		printf("\n\n\n\tNuk ka artikuj te regjistruar\n");
		return ;
	}
	ListeRequests leviz ;
	leviz=list->nextRequest;
	while(leviz->nextRequest!=list->nextRequest){
		printf("\t%d %d\n",leviz->idArticle, leviz->qte);
		leviz=leviz->nextRequest;
	}
}

void WriteFileListeArticles(ListeArticles list){
	char file[50];
	strcpy(file, list->name);
	strcat(file, ".txt");
	FILE * fp; fp=fopen(file, "w");
	if(!fp){printf("\n\n\n\tSkedari %s nuk mund te hapet ose nuk ekziston\n", file);
		return ;
	}
	ListeArticles leviz ;
	leviz=list->nextArticle;
	while(leviz !=list){
		fprintf(fp, "\t%d\t%s\t%f\t%d\t%s\n",leviz->id, leviz->name, leviz->PU, leviz->quantity, leviz->category );
		leviz=leviz->nextArticle;
	}
	fclose(fp);
}

void ReadFileListeArticles(ListeArticles list){
	char file[50];
	strcpy(file, list->name);
	strcat(file, ".txt");
	FILE * fp; fp=fopen(file, "r");
	if(!fp){printf("\n\n\n\tSkedari %s nuk mund te hapet ose nuk ekziston\n", file);
		return ;
	}
	ListeArticles leviz ;
	Article *ar1;
	leviz=list->nextArticle;
	while(!feof(fp)){
		ar1=(Article *)malloc(sizeof(Article));
		fscanf(fp, "\t%d\t%s\t%f\t%d\t%s\n",&ar1->id, ar1->name, &ar1->PU, &ar1->quantity, ar1->category );
		AddArticle(list , ar1);
	}
	printf("\n\tSkedari %s u lexua me sukses\n", file);
	fclose(fp);
}

void ReadFileRequest( ListeRequests list ) { // Shtimi i artikullit ne fund
	FILE * fp; fp=fopen("request.txt", "r");
	if(!fp){printf("\n\n\n\tSkedari request.txt nuk mund te hapet ose nuk ekziston\n");
		return ;
	}
	ListeRequests leviz ;
	leviz=list->nextRequest;
	Request * rq1;
	while (!feof(fp)){
		rq1=(Request *)malloc(sizeof(Request));
		fscanf(fp, "\n%d%d", &rq1->idArticle, &rq1->qte);
		AddRequest(list, rq1);
	}
	printf("\n\tSkedari i kerkesave u lexua me sukses\n");
	getche();
}

void testcircle(ListeArticles list){
	if (list == list->nextArticle ) printf("Lista bosh\n");
}

void DeleteRequest( ListeRequests list){
	ListeRequests leviz = list->nextRequest ;
	while(leviz != list){
		list->nextRequest = leviz->nextRequest;
		free(leviz);
		leviz=list->nextRequest;
	}
	list->nextRequest=list;
}