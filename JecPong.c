#include <ncurses.h>


/*   ejemplo de curses en C                         */
/*   compilación: gcc -Wall -o $1 $1.c  -lncurses   */
/*   autor Julio Espinoza                           */
/*   fecha:    Noviembre 2020                       */


typedef struct{short int x, y, puntos;} objetoPong;

void usleep(long);

#define DELAY 170000


int main(void) 
{
  objetoPong Pantalla; 

  
  int i,j;

  bool    delequedele=true;

  initscr();
  start_color();
  init_pair(1,COLOR_BLUE,COLOR_BLACK);
  keypad(stdscr,true);
  noecho();
  curs_set(0);

  getmaxyx(stdscr,Pantalla.y,Pantalla.x);
  objetoPong LadoIzquierdo  = {1,Pantalla.y/2,0};
  objetoPong LadoDerecho    = {Pantalla.x-2, Pantalla.y/2,0};
  objetoPong Pelota         = {Pantalla.x/2, Pantalla.y/2,0};


  mvprintw(11, 11, "Ponguito....  Presione Cualquier tecla para empezar.");
  mvprintw(12, 11, "              tecla P, pausa.");
  mvprintw(13, 11, "              ESC termina.");

  getch();
  erase();

  int next_x = 1, next_y =1;
  j=0;


  for (nodelay(stdscr,1); delequedele; usleep(4000)) 	
    {

        mvvline(0,Pantalla.x/2,ACS_VLINE,Pantalla.y);
        mvprintw(2,Pantalla.x/2-2,"%i | %i",LadoIzquierdo.puntos,LadoDerecho.puntos);
 

	    if (LadoIzquierdo.y<=1)            LadoIzquierdo.y=Pantalla.y-2;
	    if (LadoIzquierdo.y>=Pantalla.y-1) LadoIzquierdo.y=2;
	    if (LadoDerecho.y<=1)              LadoDerecho.y=Pantalla.y-2;
        if (LadoDerecho.y>=Pantalla.y-1)   LadoDerecho.y=2;


        switch (getch()) {
               case KEY_DOWN: LadoDerecho.y++; break;
               case KEY_UP:   LadoDerecho.y--; break;
               case 'q':      LadoIzquierdo.y--; break;
               case 'a':      LadoIzquierdo.y++; break;
               case 'p':      getchar(); break;
               case 0x1B:    endwin(); delequedele = false; break;
              }   
        erase();     
        mvprintw(Pelota.y,Pelota.x,"o");    
        for(i=-1;i<2;i++){
             mvprintw(LadoIzquierdo.y+i,LadoIzquierdo.x,"|");
             mvprintw(LadoDerecho.y+i,LadoDerecho.x,"|");        
             usleep(4000);
             }
      
        if (Pelota.x == 77)
           {
              if ((Pelota.y >= LadoDerecho.y -1 ) && (Pelota.y <= LadoDerecho.y+1))
                   {next_x=-1; beep();}
              else 
              {
                   LadoIzquierdo.puntos ++;
                   next_x= next_y = 1;
                   Pelota.x = Pantalla.x/2;
                   Pelota.y = Pantalla.y/2;
                   j = 50;
                   
              }
           }
        
        else if (Pelota.x == 2)
           {
              if ((Pelota.y >= LadoIzquierdo.y -1 ) && (Pelota.y <= LadoIzquierdo.y+1))
                   {next_x=1; beep();}
              else 
              {
                   LadoDerecho.puntos ++;
                   next_x= -1 ; next_y = 1;
                   Pelota.x = Pantalla.x/2;
                   Pelota.y = Pantalla.y/2;
                   j = 50;
                   
              }
           }


        if (Pelota.y == 23)  next_y=-1;
        if (Pelota.y == 0)   next_y=1;

        if (j > 8) 
            {
                Pelota.y =  Pelota.y + next_y;
                Pelota.x =  Pelota.x + next_x;
                j=0;
            }
        else
           j++;    
    }

    endwin();
}

