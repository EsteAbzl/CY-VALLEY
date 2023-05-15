#include "joueur.h"
JOUEUR j1;

void deplacementJoueur(JOUEUR* pJoueur) {

  
static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
 
  
  int deplacement = 'm';
  int a = 0;
  while (a == 0) {
    deplacement = getchar();
    deplacement = toupper(deplacement);
    
    switch (deplacement) {
    case 'Z':
      pJoueur->posJoueur.y = pJoueur->posJoueur.y - 1;
      a = 0;
      break;
    case 'S':
      pJoueur->posJoueur.y = pJoueur->posJoueur.y + 1;
      a = 0;
      break;
    case 'Q':
      pJoueur->posJoueur.x = pJoueur->posJoueur.x - 1;
      a = 0;
      break;
    case 'D':
      pJoueur->posJoueur.x = pJoueur->posJoueur.x + 1;
      a = 0;
      break;
    default:
      a = 1;
    }

    //printf("\e[2J");
    printf("(%d,%d)", pJoueur->posJoueur.x, pJoueur->posJoueur.y);
    printf("\033[u\e[0m \e[45m\e[%d;%df\033[s \e[f", pJoueur->posJoueur.y, pJoueur->posJoueur.x);
  }

/*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);


  
}