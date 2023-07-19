#if 0
// gtk3
// https://developer.gnome.org/gtk3/stable/gtk3-GtkFileChooserNative.html
GtkFileChooserNative *native;
GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
gint res;

native = gtk_file_chooser_native_new ("Open File",
                                      parent_window,
                                      action,
                                      "_Open",
                                      "_Cancel");

res = gtk_native_dialog_run (GTK_NATIVE_DIALOG (native));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
    filename = gtk_file_chooser_get_filename (chooser);
    open_file (filename);
    g_free (filename);
  }

g_object_unref (native);
#endif

