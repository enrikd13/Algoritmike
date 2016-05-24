typedef struct Article{
	int id ;
	char name[50] ;
	float PU ;
	int quantity ;
	char category [50] ;
	struct Article* nextArticle ;
}Article;

typedef Article* ListeArticles ;

typedef struct {
	int idArticle ;
	int qte ;
	struct Request* nextRequest ;
}Request;

typedef Request* ListeRequests ;