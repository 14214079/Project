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
#include <string.h>

void show_about(void)
{			

	GtkWidget *window1;
	GtkWidget *label;
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window1), "About MY_TE Text Editor");
	gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
	label = gtk_label_new ("TextEditor\nGtk / C\nVersion 1.0\n\nCopyRight\nAll Rights Reserved\n");
	gtk_container_add (GTK_CONTAINER (window1), label); 
	gtk_widget_show_all (window1);
}
void show_help(void)
{
	GtkWidget *window1;
	GtkWidget *label;
	char help[5000];
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window1), "Help - Text Editor");
	gtk_window_set_default_size(GTK_WINDOW(window1), 300, 300);
	strcpy(help,"\n\t\tCreate New file : \n\t GOTO File->New\n Open file from file manager :\n\t GOTO File->open ");
	strcat(help,"\0");
	label = gtk_label_new (help);
	gtk_container_add (GTK_CONTAINER (window1), label); 
	gtk_widget_show_all (window1);
}
