#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Point{
	float x,y; // Position 2D du point
	unsigned char r,g,b; // Couleur du point
	struct Point* next; // Point suivant à dessiner
}Point,*PointListe;

typedef struct Primitive{
	GLenum primitiveType;
	PointListe points;
	struct Primitive* next;
}Primitive, *PrimitiveListe;


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


/* Prototypes */
float coorX(float x);
float coorY(float y);



void resizeWindow(){

    glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.,1.,-1.,1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);

}

void drawPoint(PointListe* listePoints){

	printf("drawpoint appelé !\n");
	PointListe tmp = (PointListe)malloc(sizeof(PointListe));
	tmp = *listePoints;


	while(tmp != NULL){
		
		glPointSize(5.0f);
		glBegin(GL_POINTS);;
		glColor3d(tmp->r,tmp->g,tmp->b);
		glVertex2f(coorX(tmp->x), coorY(tmp->y)); 
		glEnd();

		tmp = tmp->next;

	}

}

void drawLine(PointListe* listePoints){

	printf("drawline appelé !\n");
	PointListe tmp = (PointListe)malloc(sizeof(PointListe));
	tmp = *listePoints;

	while(tmp != NULL){

		if(tmp->next != NULL){
			glBegin(GL_LINES);
			glColor3d(tmp->r,tmp->g,tmp->b);
			glVertex2f(coorX(tmp->x), coorY(tmp->y));
			glColor3d(tmp->next->r,tmp->next->g,tmp->next->b);
			glVertex2f(coorX(tmp->next->x), coorY(tmp->next->y));
			glEnd();
		}

		tmp = tmp->next;

	}

}

void drawTriangle(PointListe* listePoints){

	printf("drawtriangle appelé !\n");
	PointListe tmp = (PointListe)malloc(sizeof(PointListe));
	tmp = *listePoints;

	while(tmp != NULL){

		if(tmp->next != NULL){ // Si le point traité est suivi d'un autre dans la liste
			if(tmp->next->next != NULL){ // Si le point traité est suivi de deux autres point dans la liste
				glBegin(GL_TRIANGLES);
				glColor3d(tmp->r,tmp->g,tmp->b);
				glVertex2f(coorX(tmp->x), coorY(tmp->y));
				glColor3d(tmp->next->r,tmp->next->g,tmp->next->b);
				glVertex2f(coorX(tmp->next->x), coorY(tmp->next->y));
				glColor3d(tmp->next->next->r,tmp->next->next->g,tmp->next->next->b);
				glVertex2f(coorX(tmp->next->next->x), coorY(tmp->next->next->y));
				glEnd();
				tmp = tmp->next->next;
			}
		}

		tmp = tmp->next;

	}

}


float coorX(float x){
	return (-1 + 2. * x / WINDOW_WIDTH);
}

float coorY(float y){
	return -(-1 +2. * y / WINDOW_HEIGHT);
}

void drawUnQuad(c1, c2, c3, x1){

	glBegin(GL_QUADS);  
	glColor3d(c1,c2,c3);
	glVertex2f(coorX(x1), coorY(0));
	glVertex2f(coorX(x1+(WINDOW_WIDTH/8)), coorY(0));
	glVertex2f(coorX(x1+(WINDOW_WIDTH/8)), coorY(WINDOW_HEIGHT));  
	glVertex2f(coorX(x1), coorY(WINDOW_HEIGHT)); 
	
	glEnd();   


}

void drawQuad(){
	
	printf("Dessiner rectangle !\n");

	int c1,c2,c3;
	int x1 = 0;

	for(c1=0; c1<2; c1++){
		for(c2=0;c2<2;c2++){
			for(c3=0;c3<2;c3++){
				drawUnQuad(c1,c2,c3,x1);
				x1+=(WINDOW_WIDTH/8);
			}
		}
	}       		

}


Point* allocPoint(float x, float y, unsigned char r, unsigned char g, unsigned char b){

	Point* tmp;
	tmp = (Point*)malloc(sizeof(Point));
	if(tmp!=NULL){
		tmp->x = x;
		tmp->y = y;
		tmp->r = r;
		tmp->g = g;
		tmp->b = b;
		tmp->next = NULL;
	}

	printf("%f\n", tmp->x);

	return tmp;

}

void addPointToList(Point* point, PointListe *list){
	printf("adddpointtolist appelé \n");
	if(*list!=NULL){

		PointListe tmp = (PointListe)malloc(sizeof(PointListe));
		tmp = *list;


		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = point;

	}else{
		*list = point;
	}

}

void drawClean(){    

    glClearColor(0.9,0.9,0.9,1); // definir la couleur de nettoyage (Jaune)
    glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage

}

void changerCouleur(float x, char* tabCoul){

	int caseCoul = (int)((x/WINDOW_WIDTH)*8);

	
	switch(caseCoul){

		case 0:
			tabCoul[0] = 0;
			tabCoul[1] = 0;
			tabCoul[2] = 0;
			break;
		case 1:
			tabCoul[0] = 0;
			tabCoul[1] = 0;
			tabCoul[2] = 1;
			break;
		case 2:
			tabCoul[0] = 0;
			tabCoul[1] = 1;
			tabCoul[2] = 0;
			break;
		case 3:
			tabCoul[0] = 0;
			tabCoul[1] = 1;
			tabCoul[2] = 1;
			break;
		case 4:
			tabCoul[0] = 1;
			tabCoul[1] = 0;
			tabCoul[2] = 0;
			break;
		case 5:
			tabCoul[0] = 1;
			tabCoul[1] = 0;
			tabCoul[2] = 1;
			break;
		case 6:
			tabCoul[0] = 1;
			tabCoul[1] = 1;
			tabCoul[2] = 0;
			break;
		case 7:
			tabCoul[0] = 1;
			tabCoul[1] = 1;
			tabCoul[2] = 1;
			break;
		default:
			break;

	}

}


void deletePoints(PointListe* list){

	PointListe tmp;
	if(*list != NULL){
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	*list = NULL;
}

void deletePrimitive(PrimitiveListe* list){

	PrimitiveListe tmp;
	if(*list != NULL){
		tmp = *list; 
		*list = (*list)->next;
		deletePoints(&(tmp->points));
		free(tmp);
	}
	*list = NULL;
}

Primitive* allocPrimitive(GLenum primitiveType){
	
	Primitive *unePrimitive;
	unePrimitive = (Primitive*)malloc(sizeof(Primitive));
	if(unePrimitive != NULL){
		unePrimitive->primitiveType = primitiveType;
		unePrimitive->points = NULL;
		unePrimitive->next = NULL;
	}

	return unePrimitive;

}

void addPrimitive(Primitive* primitive, PrimitiveListe* list){

	printf("addprimitve appelé \n");
	// Ajout en tête de liste
	if(*list!=NULL){
		primitive->next = *list;
		*list = primitive;
	}else{
		printf("OK - add1\n");
		*list = primitive;
	}
}

void drawPrimitives(PrimitiveListe* list){
	printf("drawPrimitives appelé \n");

	PrimitiveListe tmp = (PrimitiveListe)malloc(sizeof(PrimitiveListe));
	tmp = *list;

	if(tmp!=NULL){
		if(tmp->next != NULL){
			// Fonction récursive pour dessiner d'abord les primitives en fin de liste
			drawPrimitives(&(tmp->next));
		}

		switch(tmp->primitiveType){

			case GL_POINTS :
				drawPoint(&(tmp->points));
				break;

			case GL_LINES :
				drawPoint(&(tmp->points));
				drawLine(&(tmp->points));
				break;

			case GL_TRIANGLES :
				drawPoint(&(tmp->points));
				drawTriangle(&(tmp->points));
				break;


			default:
				break;

		}
	}
	

}



int main(int argc, char** argv) {


	PointListe listePoints;
	listePoints = (PointListe)malloc(sizeof(PointListe));
	if(listePoints==NULL){
		exit(0);
	}

	PrimitiveListe listePrimitives;
	listePrimitives = (Primitive*)malloc(sizeof(Primitive));
	if(listePrimitives!=NULL){
		listePrimitives=NULL;
	}else{
		exit(0);
	}

	addPrimitive(allocPrimitive(GL_POINTS), &listePrimitives);

	char tabCoul[4]={0,0,0,'\0'};

	char touche = 'p';
	
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("TP1 : cmonannif", NULL);
    
    /* Boucle d'affichage */
    glClearColor(0.9,0.9,0.9,1); // definir la couleur de nettoyage (Jaune)
    glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage

    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
      
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) { // e.type = type d'evnt recu

                case SDL_VIDEORESIZE:
                	WINDOW_WIDTH = e.resize.w;
                	WINDOW_HEIGHT = e.resize.h;
                    resizeWindow();
                    drawClean();
                    drawPrimitives(&listePrimitives);
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:


                	switch(touche){

                		case 'p':
                			addPointToList(allocPoint(e.button.x, e.button.y, tabCoul[0], tabCoul[1], tabCoul[2]), &(listePrimitives->points));
                			drawPrimitives(&listePrimitives);
                			break;

                		case 'l':
                			addPointToList(allocPoint(e.button.x, e.button.y, tabCoul[0], tabCoul[1], tabCoul[2]), &(listePrimitives->points));
                			drawPrimitives(&listePrimitives);
                			break;

                		case 't':
                			addPointToList(allocPoint(e.button.x, e.button.y, tabCoul[0], tabCoul[1], tabCoul[2]), &(listePrimitives->points));
                			drawPrimitives(&listePrimitives);
                			break;

                		case ' ':
                			printf("Recherche de couleurs\n");
                			changerCouleur(e.button.x, tabCoul);
                			break;
	    
                		default:
                			break;
                	}


                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Mouvement souris */
                case SDL_MOUSEMOTION:
                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:

                	switch(e.key.keysym.sym){

                		case 'q' : 
                			deletePrimitive(&listePrimitives);
                        	loop=0;
                			break;

                		case ' ':
                			printf("Touche espace pressée\n");
	                    	drawQuad();
	                    	break;

	                    case 'd':
	                    	deletePrimitive(&listePrimitives);
	                    	addPrimitive(allocPrimitive(GL_POINTS), &listePrimitives);
	                		drawClean();
	                		break;

	                	case 'l':
	                		if(touche != 'l'){
	                			addPrimitive(allocPrimitive(GL_LINES), &listePrimitives);
	                		}
	                		break;

	                	case 'p':
	                		if(touche != 'p'){
	                			addPrimitive(allocPrimitive(GL_POINTS), &listePrimitives);
	                		}
	                		break;

	                	case 't':
	                		if(touche != 't'){
	                			addPrimitive(allocPrimitive(GL_TRIANGLES), &listePrimitives);
	                		}
	                		break;

	                	default:
	                		break;

                	}

                    /* On determine ce que l'utilisateur souhaite dessiner et on l'enregistre dans 'touche' */
                    if(e.key.keysym.sym != 'd'){
                    	touche = e.key.keysym.sym;
                    }

                    
                    printf("valeur de 'touche' (code = %c)\n", touche);
                    /********************************************************************/

                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    glClearColor(1,0,1,1);
                    break;

                 case SDL_KEYUP:

                 	if(e.key.keysym.sym == ' '){
                    printf("Touche espace relarchée\n");
                    drawClean();
                    drawPrimitives(&listePrimitives);
                    touche = 'p';
                    }

                 	break;

                default:
                    break;
            }

        }

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
