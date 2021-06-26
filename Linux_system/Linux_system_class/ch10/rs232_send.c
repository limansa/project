#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <menu.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "conntty.h"

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))



char *choices[] = {
                        "LED 0 ON", 	"LED 1 ON",	"LED 2 ON",	"LED 3 ON",
                        "LED 0 OFF", 	"LED 1 OFF",	"LED 2 OFF",	"LED 3 OFF",
                        "LED 0 BLINK", 	"LED 1 BLINK",	"LED 2 BLINK",	"LED 3 BLINK",
                        "Reset",
			(char *)NULL,
                  };
char choices_cmd[] = {
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x01
                  };
char choices_data[] = {
                        0x01,0x11,0x21,0x31,
                        0x02,0x12,0x22,0x32,
                        0x03,0x13,0x23,0x33,
                        0x00
                  };



int main()
{
	ITEM **my_items;
	char *cname,*cdata;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i, quit=0;
	int winh=10,winw=70,winx,winy;

	int fd;
	struct termios  oldtio, newtio;
        char data[2];
	
	/* Initialize curses */
	initscr(); 	//initialize curses	
	start_color();	//start color 
        cbreak();	//disable line buffering 
        noecho();	//switches off echoing
	//keypad(stdscr, TRUE); //open function keys like F1,F2.. 

	/* define the fg,bg for pair number you give */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], choices[i]);

	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Set menu option not to show the description */
	menu_opts_off(my_menu, O_SHOWDESC);

	/* Create the window to be associated with the menu */
	/* newwin(height,width,y,x) */
	winy=(LINES/2)-(winh/2); //center
	winx=(COLS/2)-(winw/2);
        my_menu_win = newwin(winh, winw, winy, winx);
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
	set_menu_format(my_menu, 5, 4);
	set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);

	mvaddstr(winy-1,winx+1,"Rs232 control panel:");

	attron(COLOR_PAIR(2));
	mvprintw(LINES - 2, 0, "Use Up and Down Arrows to select");
	mvprintw(LINES - 1, 0, "Press <ENTER> to run - Q to quit");
	attroff(COLOR_PAIR(2));

	refresh();


	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
	
        fd=com_init(fd,MODEMDEVICE,BAUDRATE,oldtio,newtio);
	while((c = wgetch(my_menu_win)) != 27)
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_RIGHT_ITEM);
				break;
			case 'q':
			case 'Q':
				quit=1;	
				break;
			case 10: /* Enter */
				cname=(char*)item_name(current_item(my_menu));
				move(winy+winh,0);
       				clrtoeol();
        			attron(COLOR_PAIR(1));
        			mvprintw(winy+winh, winx, "Item selected is : %s", cname);
        			attroff(COLOR_PAIR(1));
        			refresh();

				for(i = 0; i < n_choices; ++i)
				{
					if(choices[i]==cname)
					{
        					data[0]=choices_cmd[i];
        					data[1]=choices_data[i];
        					com_write(fd,data,2);
						break;
					}
				}
                               break;
		}
                wrefresh(my_menu_win);
		if(quit)break;
	}	

        com_close(fd,oldtio);

        unpost_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
        free_menu(my_menu);
        endwin();

}
