#include <gtk/gtk.h>

static GtkWidget *window;
static GtkWidget *parent;
static GtkBuilder *builder;

/* Simple GTK+2 variant of gtk_builder_add_from_resource() */
static guint builder_add_from_resource(GtkBuilder *builder
    , const gchar *resource_path
    , GError **error)
{
    GBytes *data;
    const gchar *buffer;
    gsize buffer_length;
    guint ret;

    g_assert(error && *error == NULL);

    data = g_resources_lookup_data(resource_path, 0, error);
    if (data == NULL) {
        return 0;
    }

    buffer_length = 0;
    buffer = g_bytes_get_data(data, &buffer_length);
    g_assert(buffer != NULL);

    ret = gtk_builder_add_from_string(builder, buffer, buffer_length, error);

    g_bytes_unref(data);

    return ret;
}


GtkWidget *
//CreateMenuBar (GtkWidget * parent)
CreateMenuBar ()
{
  GtkWidget *menu_bar, *hbox;
#if 0
  GtkWidget *menu_gFTP, *menu_Local, *menu_Remote, *menu_Bookmarks,
            *menu_Transfer, *menu_Log, *menu_Tools, *menu_Help;

  menubar = gtk_menu_new();

  menu_gFTP  = gtk_menu_item_new_with_label("gFTP");
  menu_Local = gtk_menu_item_new_with_label("Local");
  menu_Remote = gtk_menu_item_new_with_label("Remote");
  menu_Bookmarks = gtk_menu_item_new_with_label("Bookmarks");
  menu_Transfer = gtk_menu_item_new_with_label("Transfer");
  menu_Log = gtk_menu_item_new_with_label("Log");
  menu_Tools = gtk_menu_item_new_with_label("Tools");
  menu_Help = gtk_menu_item_new_with_label("Help");

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_gFTP);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Local);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Remote);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Bookmarks);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Transfer);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Log);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Tools);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Help);

  return menubar; 

    GtkBuilder *builder;
    GError *error;
    GtkWidget *config_widget;

    builder = gtk_builder_new();
    error = NULL;
    if (!builder_add_from_resource(builder, "./menu.ui", &error)) {
        g_warning("Could not build config ui: %s", error->message);
        g_error_free(error);
        g_object_unref(G_OBJECT(builder));
        return;
    }

    config_widget = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    g_object_unref(G_OBJECT(builder));

#endif
      GError *err = NULL;
      gchar *filename;

      builder = gtk_builder_new ();

      filename = g_build_filename ("/home/sedwards/source/scratch/portable-gtk-app", "menu.ui", NULL);
      gtk_builder_add_from_file (builder, filename, &err);
      g_free (filename);
      if (err)
	{
	  g_error ("ERROR: %s\n", err->message);
	  return NULL;
	}
      gtk_builder_connect_signals (builder, NULL);

      menu_bar = GTK_WIDGET (gtk_builder_get_object (builder, "menubar1"));
//      gtk_box_pack_start(GTK_BOX(hbox), menu_bar, FALSE, FALSE, 0);

  return (menu_bar);
}

#if GTK_MAJOR_VERSION == 4
static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show (window);
}
#endif

int main(int argc, char *argv[]) 
{
  GtkWidget *menu_bar, *frame, *hbox;

#if GTK_MAJOR_VERSION == 4
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

#else /* GTK_MAJOR_VERSION < 4 */
  gtk_init(&argc, &argv);

  g_printf("GTK+ version: %d.%d.%d\n", gtk_major_version, 
    gtk_minor_version, gtk_micro_version);
#endif

  g_printf("Glib version: %d.%d.%d\n", glib_major_version,
    glib_minor_version, glib_micro_version);    

#if 0
#if GTK_MAJOR_VERSION < 4
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#else
  window = gtk_window_new();
#endif
      g_signal_connect (window, "destroy", G_CALLBACK (gtk_widget_destroyed), &window);
#endif

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_title(GTK_WINDOW(window), "Submenu");

  //hbox = gtk_hbox_new(FALSE, 0);
  hbox = gtk_hbox_new (GTK_ORIENTATION_HORIZONTAL, 4);
  gtk_container_add(GTK_WINDOW(window), hbox);

  menu_bar = CreateMenuBar();
  gtk_box_pack_start(GTK_BOX(hbox), menu_bar, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

//   g_signal_connect(G_OBJECT(hbox), "activate",
//        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);


//  menu_bar = CreateMenuBar();
  //gtk_container_add (GTK_CONTAINER (frame), menu_bar);
//  gtk_widget_show(window);

//#if GTK_MAJOR_VERSION < 4
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}

