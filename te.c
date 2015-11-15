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
#include "save.c"
#include "menu.c"


			

GtkWidget *view; /* Text view widget */

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	return !save_if_modified();
}
			/* Gtk error message */
static void err_msg(const gchar *msg)
{
	GtkWidget *dialog; 
	dialog = gtk_message_dialog_new(GTK_WINDOW(window), 0, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog); 
}	
	/*  for error msg window with ok button will pop up*/

			/* main function */
int main(int argc, char *argv[])
{
	GtkWidget *box, *scroll, *widget;

	GtkAccelGroup *accel;
      
	gtk_init(&argc, &argv);  /* initialisation take filename as an argument*/

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
				/*  quit menu */
	g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event), window);
	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "MY_TE(untitled document)");
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500); 
	box = gtk_vbox_new(FALSE, 1); 
	gtk_container_set_border_width(GTK_CONTAINER(box), 1);		
	gtk_container_add(GTK_CONTAINER(window), box);
    
			
	accel = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel);
			/* Create a menu */
	main_menu = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", accel);
	gtk_item_factory_create_items(main_menu,sizeof(menu_def) / sizeof(*menu_def),menu_def, NULL);

			
	widget = gtk_item_factory_get_widget(main_menu, "<main>");

			/* put the menu in the menu container */
	gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);
	scroll = gtk_scrolled_window_new(NULL, NULL); /* put a scroll window widget */

			/* put the scroll window in the text container */
	gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);
  
			/* create the text view widget */
	view = gtk_text_view_new();

			/* create a buffer for the text view where everything gets stored */
	buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

			/* put the text widget in the scroll window */
	gtk_container_add(GTK_CONTAINER(scroll), view);

    
	gtk_widget_show_all(window); /* show all widgets in the window */

			/* error checking */
	g_set_printerr_handler(err_msg);

			/* load the file if a filename is specified */
	if(argc > 1)
		load_file(g_strdup(argv[1]));
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "download.jpeg",NULL);
    
			/* the main loop where the app waits for mouse n keyboard events */
	gtk_main();
	return 0;
}
