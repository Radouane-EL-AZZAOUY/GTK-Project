#include "./../../../include/global.h"
#include "./../../../include/widgets/button/link_button.h"

ViewConfig *configure_link_button_property(LinkButtonConfig *link_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!link_button_config || !property || !value)
        return NULL;

    // URI
    if (g_strcmp0(property, "uri") == 0)
        strcpy(link_button_config->uri, value);

    // Label
    if (g_strcmp0(property, "label") == 0)
        strcpy(link_button_config->label, value);

    // Tooltip
    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(link_button_config->tooltip, value);

    // Visited state
    if (g_strcmp0(property, "is_visited") == 0)
        link_button_config->is_visited = g_strcmp0(value, "true") == 0;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        link_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        link_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        link_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        link_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        link_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        link_button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(link_button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(link_button_config->text_color, value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            link_button_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            link_button_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            link_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            link_button_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            link_button_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            link_button_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            link_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            link_button_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_link_button_config(FILE *index, LinkButtonConfig *link_button_config)
{
    return init_generic_config(index, (void *)link_button_config, (ConfigurePropertyCallback)configure_link_button_property);
}

GtkWidget *create_link_button(LinkButtonConfig link_button_config)
{
    GtkWidget *link_button = gtk_link_button_new_with_label(link_button_config.uri, link_button_config.label);

    // Set tooltip
    gtk_widget_set_tooltip_text(link_button, link_button_config.tooltip);

    // Set visited state
    gtk_link_button_set_visited(GTK_LINK_BUTTON(link_button), link_button_config.is_visited);

    // Set dimensions
    if (link_button_config.dimensions.width > 0 && link_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(link_button, link_button_config.dimensions.width, link_button_config.dimensions.height);
    }

    // Set colors
    widget_set_colors(link_button, link_button_config.bg_color, link_button_config.text_color);

    widget_set_margins(link_button, link_button_config.margins);

        // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(link_button, link_button_config.hexpand);
    gtk_widget_set_vexpand(link_button, link_button_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(link_button, link_button_config.halign);
    gtk_widget_set_valign(link_button, link_button_config.valign);

    return link_button;
}

LinkButtonConfig *read_link_button_config_from_dialog()
{
    LinkButtonConfig *link_button_config_ptr = NULL;
    SAFE_ALLOC(link_button_config_ptr, LinkButtonConfig, 1);

    LinkButtonConfig link_button_config = DEFAULT_LINK_BUTTON;

    // URI
    const gchar *uri = read_config_value_as_string("uri_entry");
    strcpy(link_button_config.uri, uri);

    // Label
    const gchar *label = read_config_value_as_string("label_entry");
    strcpy(link_button_config.label, label);

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strcpy(link_button_config.tooltip, tooltip);

    // Visited state
    gboolean is_visited = read_config_value_as_boolean("visited_switch");
    link_button_config.is_visited = is_visited;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    link_button_config.dimensions.width = dimensions->width;
    link_button_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    link_button_config.margins.top = margins->top;
    link_button_config.margins.bottom = margins->bottom;
    link_button_config.margins.start = margins->start;
    link_button_config.margins.end = margins->end;

    // HAlign
    link_button_config.halign = read_align_config("halign_combo");

    // VAlign
    link_button_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    link_button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    link_button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(link_button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(link_button_config.text_color, text_color);

    memcpy(link_button_config_ptr, &link_button_config, sizeof(LinkButtonConfig));
    return link_button_config_ptr;
}

LinkButtonConfig *read_link_button_config_from_widget(GtkWidget *widget)
{
    LinkButtonConfig *link_button_config_ptr = NULL;
    SAFE_ALLOC(link_button_config_ptr, LinkButtonConfig, 1);

    LinkButtonConfig link_button_config = DEFAULT_LINK_BUTTON;

    // URI
    const gchar *uri = gtk_link_button_get_uri(GTK_LINK_BUTTON(widget));
    strcpy(link_button_config.uri, uri);

    // Label
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    strcpy(link_button_config.label, label);

    // Tooltip
    const gchar *tooltip = gtk_widget_get_tooltip_text(widget);
    strcpy(link_button_config.tooltip, tooltip);

    // Visited state
    gboolean is_visited = gtk_link_button_get_visited(GTK_LINK_BUTTON(widget));
    link_button_config.is_visited = is_visited;

    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    link_button_config.dimensions.width = allocation.width;
    link_button_config.dimensions.height = allocation.height;

    // Expand
    link_button_config.hexpand = gtk_widget_get_hexpand(widget);
    link_button_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    link_button_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    link_button_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    link_button_config.margins = margins;

    gchar *property_value = NULL;
    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(link_button_config.bg_color, property_value);

    // Text color
    property_value = read_text_color_from_widget(widget);
    if (property_value)
        strcpy(link_button_config.text_color, property_value);

    memcpy(link_button_config_ptr, &link_button_config, sizeof(LinkButtonConfig));

    return link_button_config_ptr;
}

gchar *write_link_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "link_button", tabs_number);

    // Get the GtkLinkButton from the view
    GtkLinkButton *link_button = GTK_LINK_BUTTON(view->widget);

    // Get the URI
    const gchar *uri = gtk_link_button_get_uri(link_button);
    if (g_strcmp0(uri, "\0") != 0) // Check if the URI is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "uri=\"%s\"\n", uri);
    }

    // Get the label text
    const gchar *label = gtk_button_get_label(GTK_BUTTON(link_button));
    if (g_strcmp0(label, "\0") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(link_button));
    if (tooltip && g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    // Check if the link button is visited
    gboolean is_visited = gtk_link_button_get_visited(link_button);
    if (is_visited != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_visited=\"%s\"\n", is_visited ? "true" : "false");
    }

    return "link_button";
}