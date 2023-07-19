void print_children_helper(GtkWidget* parent, int indent_size, int depth)
{
    for (int i = 0; i < depth * indent_size; i++)
        printf(" ");
    printf("%s\n", gtk_widget_get_name(parent));

    GList* children = NULL;
    if (GTK_IS_CONTAINER(parent))
        children = gtk_container_get_children(GTK_CONTAINER(parent));

    while (children != NULL)
    {
        print_children(children->data, indent_size, depth + 1);
        children = children->next;
    }
}

void print_children(GtkWidget* parent, int indent_size)
{
    print_children_helper(parent, indent_size, 0);
}

GtkWidget* find_child_by_name(GtkWidget* parent, const gchar* name)
{
    if (g_strcmp0(gtk_widget_get_name(parent), name) == 0)
        return parent;

    GList* children = NULL;
    if (GTK_IS_CONTAINER(parent))
        children = gtk_container_get_children(GTK_CONTAINER(parent));

    while (children != NULL)
    {
        GtkWidget* widget = find_child_by_name(children->data, name);

        if (widget != NULL)
            return widget;

        children = children->next;
    }

    return NULL;
}

GtkWidget* find_child_by_index(GtkWidget* parent, int depth, ...)
{
    va_list argp;
    va_start(argp, depth);

    for (int i = 0; i < depth; i++)
    {
        int index = va_arg(argp, int);

        GList* children = NULL;
        if (GTK_IS_CONTAINER(parent))
            children = gtk_container_get_children(GTK_CONTAINER(parent));

        for (int j = 0; j < index; j++)
            if (children != NULL)
                children = children->next;

        if (children != NULL)
            parent = children->data;
        else
            return NULL;
    }

    va_end(argp);
    return parent;
}

