void print_widget_names(GtkWidget* parent, int level) {
  for (int i=0; i < level; i++) { 
    g_print("    ");
  }
  level++;
  g_print("%s\n", gtk_widget_get_name(GTK_WIDGET(parent)));
  GtkWidget *widget = gtk_widget_get_first_child(GTK_WIDGET(parent));
  GtkWidget *next;
  if (widget != NULL) {
    print_widget_names(widget, level);
    while ((next = gtk_widget_get_next_sibling(widget)) != NULL) {
      widget = next;
      print_widget_names(widget, level);
    }
  }
}

