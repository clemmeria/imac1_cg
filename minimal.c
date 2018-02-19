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



void resizeWindow(SDL_Event e){

    SDL_SetVideoMode(e.resize.w, e.resize.h, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    glViewport(0,0,e.resize.w, e.resize.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.,1.,-1.,1.);

}

void drawPoint(PointListe* listePoints){

	printf("Dessiner point !\n");
	PointListe tmp = (PointListe)malloc(sizeof(PointListe));
	tmp = *listePoints;


	while(tmp != NULL){
		
		glPointSize(10.0f);
		glBegin(GL_POINTS);;
		glColor3d(0,0,0);
		glVertex2f(coorX(tmp->x), coorY(tmp->y)); 
		glEnd();

		tmp = tmp->next;

	}

    

}

/*void drawLine(SDL_Event e, float tab[]){

	drawPoint(e);

    glPointSize(10.0f);

	printf("Dessiner ligne !\n");

	glBegin(GL_LINES);
	glColor3d(0,0,0);

	//Coordonnées du point précédement enregistré dans tabLine 
	glVertex2f(-1 + 2. * tab[0] / WINDOW_WIDTH, -(-1 +2. * tab[1] / WINDOW_HEIGHT));

  	//Coordonées du nouveau point cliqué
  	glVertex2f(-1 + 2. * e.button.x / WINDOW_WIDTH, -(-1 +2. * e.button.y / WINDOW_HEIGHT));
	glEnd();

}

void drawTriangle(SDL_Event e, float tab[]){

	drawPoint(e);
	
    glPointSize(10.0f);

	printf("Dessiner triangle !\n");

	glBegin(GL_TRIANGLES);
	glColor3d(0,0,0);

	//Coordonnées du point précédement enregistré dans tabLine 
	glVertex2f(-1 + 2. * tab[0] / WINDOW_WIDTH, -(-1 +2. * tab[1] / WINDOW_HEIGHT));

	//Coordonnées du point précédement enregistré dans tabLine 
	glVertex2f(-1 + 2. * tab[2] / WINDOW_WIDTH, -(-1 +2. * tab[3] / WINDOW_HEIGHT));

  	//Coordonées du nouveau point cliqué
  	glVertex2f(-1 + 2. * e.button.x / WINDOW_WIDTH, -(-1 +2. * e.button.y / WINDOW_HEIGHT));

	glEnd();

}*/

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
	glVertex2f(coorX(x1+50), coorY(0));
	glVertex2f(coorX(x1+50), coorY(400));  
	glVertex2f(coorX(x1), coorY(400)); 
	
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
				x1+=50;
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

void addPointToList(Point* point, PointListe* list){

	//printf("%f\n", tmp->next->x);

	if(*list!=NULL){

		PointListe tmp = (PointListe)malloc(sizeof(PointListe));
		tmp = *list;


		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = point;
		printf("X vaut %f\n", tmp->next->x);

	}else{
		*list = point;
		printf("X2 vaut %f\n", (*list)->x);
	}



}

void drawClean(){    

    glClearColor(1,1,0,1); // definir la couleur de nettoyage (Jaune)
    glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage

}

void reDraw(){

}

int main(int argc, char** argv) {


	PointListe listePoints;
	listePoints = (PointListe)malloc(sizeof(PointListe));
	if(listePoints!=NULL){
		listePoints=NULL;
	}else{
		exit(0);
	}

	char touche = 'p';
	float tabLine[3]={0,0,0}; // Toutes les cases valent 0
	float tabTriangle[5]={0,0,0,0,0}; // Toutes les cases valent 0
	
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
    glClearColor(1,1,0,1); // definir la couleur de nettoyage (Jaune)
    glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage

    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
    	//glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage
      
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
                    resizeWindow(e);
                    printf("Il y a redimmensionnement : %d , %d\n", e.resize.w, e.resize.h);
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:


                	switch(touche){

                		case 'p':
                			addPointToList(allocPoint(e.button.x, e.button.y, 0, 0, 0), &listePoints);
                			drawPoint(&listePoints);
                			break;

                		/*case 'l':

	                		if(tabLine[2] == 0){
	                			tabLine[0] = e.button.x;
	                			tabLine[1] = e.button.y;
	                			tabLine[2] = 1;
	                			drawPoint(e);
	                			printf("TabLine x=%f et y=%f\n", tabLine[0], tabLine[1]);
	                		}else{
	                			drawLine(e, tabLine);
	                			int i;
	                			for(i=0;i<3;i++){
	                				tabLine[i]=0;
	                			}
	                		}
	                		break;

	                	case 't':

	                		if(tabTriangle[4] == 0){
	                			tabTriangle[0] = e.button.x;
	                			tabTriangle[1] = e.button.y;
	                			tabTriangle[4] = 1;
	                			drawPoint(e);        
	                		}else if(tabTriangle[4]==1){
	                			tabTriangle[2] = e.button.x;
	                			tabTriangle[3] = e.button.y;
	                			tabTriangle[4] = 2;
	                			drawPoint(e);
	                		}else{
	                			drawTriangle(e, tabTriangle);
	                			int i;
	                			for(i=0;i<5;i++){
	                				tabTriangle[i]=0;
	                			}
	                		}
	                		break;*/
	    
                		default:
                			break;
                	}

                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Mouvement souris */
                case SDL_MOUSEMOTION:
                    //printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:

                    if(e.key.keysym.sym == 'q'){
                        loop=0;
                    }
                    else if(e.key.keysym.sym == ' '){
                    printf("Touche espace pressée\n");
                    drawQuad();
                    }

                    /* On determine ce que l'utilisateur souhaite dessiner et on l'enregistre dans 'touche' */
                    touche = e.key.keysym.sym;
                    printf("valeur de 'touche' (code = %c)\n", touche);
                    /********************************************************************/

                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    glClearColor(1,0,1,1);
                    break;

                 case SDL_KEYUP:

                 	if(e.key.keysym.sym == ' '){
                    printf("Touche espace relarchée\n");
                    drawClean();
                    drawPoint(&listePoints);
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
