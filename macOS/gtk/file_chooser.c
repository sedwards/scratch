/* GTK file and directory selection dialog example */

/* Compile: gcc `pkg-config --cflags --libs gtk+-2.0` file_chooser.c -o test */

#include <gtk/gtk.h>
#include <string.h>

/* Type can be DIR or FILE. Returns a path or NULL. Free with g_free() is not NULL. */
gchar *get_dialog_path_selection(gchar *type, gchar *initial_dir, gchar *initial_file);

gchar *get_dialog_path_selection(gchar *type, gchar *initial_dir, gchar *initial_file)
{
    GtkWidget *dialog;
    gboolean ret = 0;
    int dlg_ret = 0;
    gchar *path;

    if( strstr(type, "DIR") )
    {
	dialog = gtk_file_chooser_dialog_new("Select directory",
	NULL,
	GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	NULL);

	/* Set initial directory. If it doesnt exist "/" is used. */
	ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), initial_dir);
	if( ! ret )
          ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "/");
    }
    else
    if( strstr(type, "FILE") )
    {
	dialog = gtk_file_chooser_dialog_new("Select file",
	NULL,
	GTK_FILE_CHOOSER_ACTION_OPEN,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	NULL);

	/* Set initial directory. If it doesnt exist "/" is used. */
	ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), initial_dir);
	if( ! ret )
          ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "/");

	/* It complains if the file doesnt exist, ignore it. */
	gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), initial_file);
    }
    else
    {
	printf("Path selection: Input TYPE error.\n");
	return NULL;
    }

    dlg_ret = gtk_dialog_run(GTK_DIALOG(dialog));

    if( dlg_ret == GTK_RESPONSE_ACCEPT )
    {
	path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    if( dlg_ret == GTK_RESPONSE_CANCEL )
    {
	printf("Path selection: Canceled.\n");
	path = NULL;
    }

    gtk_widget_destroy(dialog);
    
    return path;
}


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    gchar *path;

    path = get_dialog_path_selection("DIR", "/var/samba", "None");
    if( path!=NULL )
    {
	printf("Selected directory: %s\n", path);
	g_free(path);
    }

    path = get_dialog_path_selection("FILE", "/var/samba", "some_file.txt");
    if( path!=NULL )
    {
	printf("Selected file: %s\n", path);
	g_free(path);
    }

    gtk_main();

    return 0;
}
