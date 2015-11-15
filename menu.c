/*
Copyright (C) <2015>  <Pritesh Holani>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include <gtk/gtk.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "help.c"
#include "find.c"
GtkWidget *view; /* TextView */

GdkAtom sel_atom = GDK_SELECTION_CLIPBOARD;
GtkItemFactory *main_menu; 
void show_help(void);
void show_about(void); 

#define MENU_NEW 1
#define MENU_OPEN 2
#define MENU_SAVE 3
#define MENU_SAVE_AS 4
#define MENU_QUIT 5
#define MENU_CUT 6
#define MENU_COPY 7
#define MENU_PASTE 8
#define MENU_USE_CLIPBOARD 9
#define MENU_SELECT_ALL 10
#define MENU_FIND 11
#define MENU_HELP 12
#define MENU_ABOUT 13

static void menu_show(gpointer data, guint action, GtkWidget *widget)
{
	GtkTextIter p; 
	switch(action) 
	{
		case MENU_NEW:
			if(save_if_modified()) 
			{
				/* get all the current tag table n put them in the new buffer */
				buf = gtk_text_buffer_new(gtk_text_buffer_get_tag_table(buf));
				gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), buf);
				g_object_unref(G_OBJECT(buf)); 
        		}
			break;
		case MENU_OPEN:
			if(save_if_modified()) 
        		{
					  /* call save if modified wen user opens a new file */
				buf = gtk_text_buffer_new(gtk_text_buffer_get_tag_table(buf));
				gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), buf);
				g_object_unref(G_OBJECT(buf));
				load_file(NULL);
			}
			break;
		case MENU_SAVE:
			save_file(filename);
			break;
		case MENU_SAVE_AS:
			save_file(NULL);
			break;
		case MENU_QUIT:
			if(save_if_modified())            /* call save if modified wen user opens a new file */
			gtk_widget_destroy(window);
			break;
		case MENU_CUT:
			gtk_text_buffer_cut_clipboard(buf,gtk_clipboard_get(sel_atom), TRUE);
			break;
		case MENU_COPY:
			gtk_text_buffer_copy_clipboard(buf,gtk_clipboard_get(sel_atom));
			break;
		case MENU_PASTE:
        				/* if null text is inserted at the current cursor position */
			gtk_text_buffer_paste_clipboard(buf,gtk_clipboard_get(sel_atom), NULL, TRUE);
			break;
		case MENU_FIND:
			textfind();
			break;

		case MENU_SELECT_ALL:
			gtk_text_buffer_get_start_iter(buf, &p);  /* get the starting pt of the buffer */
			gtk_text_buffer_place_cursor(buf, &p);    /* ignore the selection made by the mouse */
			gtk_text_buffer_get_end_iter(buf, &p);   /* get the ending pt of the buffer */
			gtk_text_buffer_move_mark_by_name(buf, "select all", &p);
			break;
		case MENU_HELP:
			show_help();
			break;
		case MENU_ABOUT:
        		show_about();
        		break;
        	default:      /* error checking */
			g_printerr("Menu action not defined : %u\n", action);
			break;
	}
}



/* actual menu creation */

GtkItemFactoryEntry menu_def[] = {
	{ (char *)"/_File", NULL, NULL, 0, (char *)"<Branch>", NULL },
	{ (char *)"/File/_New", (char *)"<control>N", menu_show, MENU_NEW, (char *)"<StockItem>", GTK_STOCK_NEW },
	{ (char *)"/File/_Open...", (char *)"<control>O", menu_show, MENU_OPEN, (char *)"<StockItem>", GTK_STOCK_OPEN },
	{ (char *)"/File/_Save", (char *)"<control>S", menu_show, MENU_SAVE, (char *)"<StockItem>", GTK_STOCK_SAVE },
	{ (char *)"/File/Save _As...", (char *)"<SHIFT><CONTROL>A", menu_show, MENU_SAVE_AS, (char *)"<StockItem>", GTK_STOCK_SAVE_AS },
	{ (char *)"/File/sep", NULL, NULL, 0, (char *)"<Separator>", NULL },
	{ (char *)"/File/_Quit", (char *)"<control>Q", menu_show, MENU_QUIT, (char *)"<StockItem>", GTK_STOCK_QUIT },
	{ (char *)"/_Edit", NULL, NULL, 0, (char *)"<Branch>", NULL },
	{ (char *)"/Edit/Cut", (char *)"<control>X", menu_show, MENU_CUT, (char *)"<StockItem>", GTK_STOCK_CUT },
	{ (char *)"/Edit/_Copy", (char *)"<control>C", menu_show, MENU_COPY, (char *)"<StockItem>", GTK_STOCK_COPY },
	{ (char *)"/Edit/_Paste", (char *)"<control>V", menu_show, MENU_PASTE, (char *)"<StockItem>", GTK_STOCK_PASTE },
	{ (char *)"/Edit/sep", NULL, NULL, 0, (char *)"<Separator>", NULL },
	{ (char *)"/Edit/Select All", (char *)"<control>A", menu_show, MENU_SELECT_ALL, NULL, NULL },
	{ (char *)"/_Search", NULL, NULL, 0, (char *)"<Branch>", NULL },
	{ (char *)"/Search/_Find",  (char *)"<control>F" , menu_show, MENU_FIND,(char *)"<StockItem>", GTK_STOCK_FIND },
	{ (char *)"/_Help", NULL, NULL, 0, (char *)"<Branch>", NULL },
	{ (char *)"/Help/_Contents", (char *)"<control>H", menu_show, MENU_HELP, (char *)"<StockItem>", GTK_STOCK_HELP },
	{ (char *)"/Help/sep", NULL, NULL, 0, (char *)"<Separator>", NULL },
	{ (char *)"/Help/_About",  NULL , menu_show, MENU_ABOUT, "<Item>" },
};
