#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	char comment[40];
	int nbpts; 
	float *time; 
	float *value; 
} trace;

float Pa[] = { 0.5 , 0.01 , 0.05 };
float Pb[] = { 0.75 , 0.3 , 0.1 };

float file_dt;
int file_tmax ;

int menu(){//Menuja 
	int next;
	system("cls");
	printf("\n\n\n\t\tPune Laboratori Nr. 1 - Algoritmike");
	printf("\n\n\t1 - Kryej simulimin per nje interval kohe dhe shfaq rezultatin \n\t");
	printf("2 - Ruaj vlerat e llogaritura\n\t");
	printf("3 - Lexo te dhenat e matura nga eksperimenti \n\t");
	printf("4 - Lexo skedarin duke perdorur funksionin alternativ\n\t");
	printf("5 - Gjej gabimin e matjeve laboratorike me ato eksperimentale\n\t");
	printf("6 - Gjej gabimin per nje numer te limituar te dhenash\n\t");
	printf("7 - Dil nga programi\n\t");
	scanf("%d", &next);
	return next;
}

trace* createTrace(int nbpts){ // Krijimi i trace te ri dhe alokimi i memories per vektoret time & value me nbpts elemente
	trace * uneTrace = (trace*)malloc(sizeof(trace));
	uneTrace->time = (float*)malloc(nbpts*sizeof(float)); 
	uneTrace->value = (float*)malloc(nbpts*sizeof(float));
	uneTrace->nbpts=nbpts;
	return uneTrace;
}

int fileLength(char * filename){ // Gjen sa the dhena ka te ruajtura ne nje file, qe te beje alokimin e sakte te memories
	FILE *fp ;
	fp = fopen (filename, "r");
	if (!fp){
		printf("Skedari nuk mund te hapet");
		exit(1);	
	}
	int temp; char tmp_comment[50];
	fscanf(fp, "%s\n%d", tmp_comment, &temp);
	int i=0;
	float t1, t2, t3;
	while(!feof(fp)){
		fscanf(fp, "\n%f %f", &t1, &t2);
		if(i==0) t3=t1;
		if (i==1) file_dt=t1-t3 ;
		i++;
		}
	fclose(fp);
	file_tmax=(int)(i-2)*file_dt ;
	return i-1;
}


void simutrace (int tmax,float dt,float params[],trace *uneTrace){ // Llogaritja e vlerave te simuluara
    float v=0,w=0,dv=0,dw=0,t=0;
    int i=0;
    while (t<=tmax){
            dv=(params[0]-v)*(v-1)*v-w;
            dw=params[2]*(0.5*v-w-params[1]);
            v+=(dv*dt);
            w+=(dw*dt);
            uneTrace->time[i]=t;
            uneTrace->value[i]=v;
            i++;
            t+=dt;
    };
    uneTrace->nbpts=i;
    return;
}

void printTrace(trace uneTrace) { // Printimi i permbajtjes se nje trace
	printf("\t%s\n", uneTrace.comment);
	int i;
	for ( i = 0; i < uneTrace.nbpts; i++)
	{
		printf("\tt=%.1f\tv=%f\n", uneTrace.time[i], uneTrace.value[i]);
	}
	printf("\n\n\tLeximi u be me sukses ! \n\t U lexuan %d vlera", i);
}

char* saveTraceBin(trace uneTrace) { // Ruajtja e vlerave te trace tek skedari myfile.txt. 
	FILE *fp;
	char output[] = "myfile.txt";
	fp = fopen(output, "w");
	if (fp == NULL) { printf("Skedari nuk mund te hapet"); exit(1); }
	fprintf(fp, "%s \n%d", uneTrace.comment, uneTrace.nbpts);
	int i=0;
	for (i = 0; i < uneTrace.nbpts; ++i)
	{
		fprintf(fp, "\nt=%.2f\tv=%f", uneTrace.time[i] , uneTrace.value[i]);
	}
	fclose(fp);
	return output ;
}

void readTrace ( char * fileName , trace * uneTrace ){ // Leximi i skedarit fileName dhe ruajtja e te dhenave ne nje trace deklaruar tek main()
	FILE *fp ;
	fp = fopen (fileName, "r");
	if (!fp){
		printf("Skedari nuk mund te hapet"); exit(2);	
	}
	int temp;
	fscanf(fp, "%s\n%d", uneTrace->comment, &temp);
	printf("%s\t\n",uneTrace->comment );
	int i=0;
	while(!feof(fp)){
		fscanf(fp, "\n%f %f", &uneTrace->time[i], &uneTrace->value[i]);
		i++;
		}
	fclose(fp);
	return ;
}

trace* readTrace1 ( char * fileName ){ // Leximi i skedarit fileName dhe ruajtja e te dhenave ne nje trace lokal. funksioni kthen pointerin e ketij variabli lokal
	FILE *fp ;
	fp = fopen (fileName, "r");
	if (!fp){
		printf("Skedari nuk mund te hapet"); exit(3);	
	}
	int nbpts; char comment[50];
	fscanf(fp, "%s\n%d", comment, &nbpts);
	nbpts=fileLength(fileName);
	trace *uneTrace = createTrace(nbpts);
	strcpy(uneTrace->comment, comment);
	uneTrace->nbpts=nbpts;
	int i=0;
	while(!feof(fp)){
		fscanf(fp, "\n%f %f", &uneTrace->time[i], &uneTrace->value[i]);
		i++;
		}
	fclose(fp);
	uneTrace->nbpts=i-1;
	return uneTrace ; 
}

float errorTrace(trace uneTrace1, trace uneTrace2) { // gabimi mes dy trace
	float error=0;
    int i, nbpts;
	if (uneTrace1.nbpts!=uneTrace2.nbpts) printf ("\tSimulimi me matjen kane numer te ndryshem vlerash .\n\tGabimi do llogaritet vetem per minimumin e vlerave.\n\t");
    if(uneTrace1.nbpts<uneTrace2.nbpts)
    	nbpts = uneTrace1.nbpts ;
    else nbpts = uneTrace2.nbpts ;
    
    for( i=0;i<nbpts;i++){
        error+=uneTrace1.value[i]-uneTrace2.value[i];
    }
    error/=nbpts;
    error=fabs(error);
    error=sqrt(error);
    return error;
}
float errorTraceLimited(int n, trace uneTrace1, trace uneTrace2) { // gabimi mes n elementeve te para te dy trace
	float error=0;
    int i, nbpts;
	if (uneTrace1.nbpts< n || uneTrace1.nbpts< n) {
	printf ("\tSimulimi ose matja eksperimentale kane me pak se %d vlera te matura .\n");
	exit(3);
	}
    
    for( i=0;i<n;i++){
        error+=uneTrace1.value[i]-uneTrace2.value[i];
    }
    error/=n;
    error=fabs(error);
    error=sqrt(error);
    return error;
}

int main(){
	system(" color f0"); // ndryshimi i ngjyrave te terminalit 
	system(" title Pune Laboratori Nr. 1 - Enrik Doci - Klajdi Gjoka"); // titulli i dritares
	trace *simulim; // krijimi i pointer-to-trace . alokimi i memories behet me vone ne varesi te memories qe nevojitet duke perdorur funksionin createTrace()
	trace * cell ;
	int tmax, answer, parametrat, a1=0, a2=0; // Variabla qe duhen per te levizuar ne menu dhe kushte te tjera
	float dt ;
	char output[50];
	while(answer!=7){
		answer = menu();
		if (answer==1){
			printf("\tJepni tmax :");
			scanf("%d", &tmax);
			printf("\tJepni dt :");
			scanf("%f", &dt);
			simulim = createTrace((int)tmax/dt+1);
			printf ("\tJep emrin e eksperimentit: ");
    		scanf("%s", simulim->comment);
			printf("\n\tZgjidhni Parametrat qe do perdorni gjate simulimit\n\t1. Parametrat Pa\n\t2.Parametrat Pb");
			scanf("%d", &parametrat);
			if (parametrat == 1) simutrace(tmax, dt, Pa, simulim);
				else if (parametrat == 2) simutrace(tmax, dt, Pb, simulim);
					else printf("vlera gabim");
			printTrace(*simulim);
			a1=1; // Vetem pasi a1 u be true mund te punoje funksioni i ruajtjes se te dhenave ne file
			getche();
		}
		if (answer==2){
			if (!a1) {
				printf("\tFillimisht duhet te kryeni nje Simulim te ri (Pika 1)\n\t");
				getche();
				continue;
			}
			strcpy(output,saveTraceBin(*simulim));
			printf("\tSimulimet u ruajten ne skedarin %s\n\t", output);
			getche();
		}
		if (answer==3){
			cell = createTrace(fileLength("cell.txt"));
			readTrace("cell.txt", cell);
			printTrace(*cell);
			a2=1;  // vetem kur a2 behet true (lexohen te dhena nga cell.txt) mund te behet gjetja e gabimit 
			getche();
		}
		if (answer==4){
			cell = readTrace1("cell.txt");
			printTrace(*cell);
			a2=1;
			getche();
		}
		if (answer==5){
			if (!a2){
			printf("\tFillimisht duhet te lexoni skedarin me matjet labotratorike (Pika 3 ose 4)\n\t"); getche();
			continue;
			}
			printf("\tGabimi mes Matjeve Laboratorike dhe Simulimit eshte :\n\t");
			if (a1) free(simulim);
			simulim=createTrace(fileLength("cell.txt"));
			simutrace(file_tmax, file_dt, Pa, simulim);
			printf("%f - Per parametrat Pa\n\t", errorTrace(*cell, *simulim));
			simutrace(file_tmax, file_dt, Pb, simulim);
			printf("%f - Per parametrat Pb\n\t", errorTrace(*cell, *simulim));
			getche();
		}
		if (answer==6){
			if (!a2){
			printf("\tFillimisht duhet te lexoni skedarin me matjet labotratorike (Pika 3 ose 4)\n\t"); getche();
			continue;
			}
			if (a1) free(simulim); // lirojme vleren qe kemi alokuar momentalisht per trace simulim pasi do rialokojm vend tjeter
			simulim=createTrace(fileLength("cell.txt"));
			simutrace(file_tmax, file_dt, Pa, simulim);
			printf("\n\tGabimet ne nje interval per simulimin me parametra Pa jane:\n\t");
			printf("%f - Per 100 vlerat e para\n\t", errorTraceLimited(100, *cell, *simulim));
			printf("%f - Per 200 vlerat e para\n\t", errorTraceLimited(200, *cell, *simulim));
			printf("%f - Per 400 vlerat e para\n\t", errorTraceLimited(400, *cell, *simulim));
			printf("%f - Per 600 vlerat e para\n\t", errorTraceLimited(600, *cell, *simulim));
			printf("%f - Per 800 vlerat e para\n\t", errorTraceLimited(800, *cell, *simulim));
			free(simulim);
			simulim=createTrace(fileLength("cell.txt"));
			simutrace(file_tmax, file_dt, Pb, simulim);
			printf("\n\tGabimet ne nje interval per simulimin me parametra Pb jane:\n\t");
			printf("%f - Per 100 vlerat e para\n\t", errorTraceLimited(100, *cell, *simulim));
			printf("%f - Per 200 vlerat e para\n\t", errorTraceLimited(200, *cell, *simulim));
			printf("%f - Per 400 vlerat e para\n\t", errorTraceLimited(400, *cell, *simulim));
			printf("%f - Per 600 vlerat e para\n\t", errorTraceLimited(600, *cell, *simulim));
			printf("%f - Per 800 vlerat e para\n\t", errorTraceLimited(800, *cell, *simulim));
			getche();
		}
	}
return 1;
}
