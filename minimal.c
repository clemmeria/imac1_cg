#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

//1.
// Inclure les librairies SDL et OpenGL

//2.
// 


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeWindow(SDL_Event e){

    SDL_SetVideoMode(e.resize.w, e.resize.h, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    glViewport(0,0,e.resize.w, e.resize.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.,1.,-1.,1.);

}

int drawObject(SDL_Event e){

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPointSize(10.0f);

	printf("Dessiner !\n");
	glBegin(GL_POINTS);
	glColor3ub(0,0,0);
	glVertex2f(-1 + 2. * e.button.x / WINDOW_WIDTH, -(-1 +2. * e.button.y / WINDOW_HEIGHT));
	//glEnd();

	return 0;

}

int main(int argc, char** argv) {



    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Desactiver le double buffering avant d'ouvrir la fenetre pour que le dessin persiste */
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("TP1 : cmonannif", NULL);
    
    /* Boucle d'affichage */
    glClearColor(1,1,0,1); // definir la couleur de nettoyage

    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
    	glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
        
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
                	drawObject(e);
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Mouvement souris */
                case SDL_MOUSEMOTION:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == 'q'){
                        loop=0;
                    }

                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    glClearColor(1,0,1,1);
                    break;

                default:
                    break;
            }

        }

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
