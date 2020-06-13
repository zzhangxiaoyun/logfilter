#include <gtk/gtk.h>

/**
*callback function of button
*@param w widget
*@param userdata
*/
void hello_proc(GtkWidget *w, gpointer userdata) {

}

#define WIDTH 1000
#define HEIGHT 600

GdkColor *parseGdkColor(int red, int green, int blue) {
    GdkColor *color = new GdkColor();
    color->red = red;
    color->blue = blue;
    color->green = green;
    return color;
}

GdkRGBA *parseGdkRgba(int red, int green, int blue, int a) {
    GdkRGBA *color = new GdkRGBA();
    color->red = red;
    color->blue = blue;
    color->green = green;
    color->alpha = a;
    return color;
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    GtkWidget *mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(mainWindow, WIDTH, HEIGHT);
    gtk_container_set_border_width(GTK_CONTAINER(mainWindow), 5);

    //创建垂直布局
    GtkWidget *rootVbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(mainWindow), rootVbox);

    GtkWidget *title0HBox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(rootVbox), title0HBox, FALSE, FALSE, 0);

    GtkWidget *title1HBox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(rootVbox), title1HBox, FALSE, FALSE, 0);

    GtkWidget *scroll2HBox = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(rootVbox), scroll2HBox, TRUE, TRUE, 0);






    //创建按钮
    GtkWidget *openLogDir = gtk_button_new_with_label("Open log dir");
    gtk_widget_set_size_request(openLogDir, 100, 0);
    //设置按钮样式
    gtk_button_set_relief(GTK_BUTTON(openLogDir), GTK_RELIEF_NORMAL);
    //将按钮加入到布局中
    gtk_box_pack_start(GTK_BOX(title0HBox), openLogDir, FALSE, FALSE, 0);
    //为按钮加入单击事件响应函数
    g_signal_connect(G_OBJECT(openLogDir), "clicked", G_CALLBACK(hello_proc), NULL);

    // filter
    GtkWidget *filterLabel = gtk_label_new("filter tags:");
    gtk_box_pack_start(GTK_BOX(title0HBox), filterLabel, FALSE, FALSE, 0);

    GtkWidget *filterEdit = gtk_entry_new();
    gtk_widget_set_size_request(filterEdit, 600, 0);
    gtk_box_pack_start(GTK_BOX(title0HBox), filterEdit, FALSE, FALSE, 0);



    // remove tag
    GtkWidget *empty = gtk_label_new("");
    gtk_widget_set_size_request(empty, 82, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), empty, FALSE, FALSE, 0);

    GtkWidget *removeTagLabel = gtk_label_new("remove tags:");
    gtk_box_pack_start(GTK_BOX(title1HBox), removeTagLabel, FALSE, FALSE, 0);

    GtkWidget *removeTagEdit = gtk_entry_new();
    gtk_widget_set_size_request(removeTagEdit, 600, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), removeTagEdit, FALSE, FALSE, 0);


    // text
    GtkWidget *textView = gtk_text_view_new();
    gtk_widget_set_size_request(removeTagEdit, 600, 0);


    gtk_widget_modify_bg(textView, GTK_STATE_NORMAL, parseGdkColor(0x0, 0x0, 0x0));
    gtk_widget_override_color(textView, GTK_STATE_FLAG_NORMAL, parseGdkRgba(0xffff, 0xffff, 0xffff, 0xffff));




    gtk_container_add(GTK_CONTAINER(scroll2HBox), textView);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), TRUE);
    GtkWidget *statusbar = gtk_statusbar_new();
    gtk_container_add(GTK_CONTAINER(scroll2HBox), statusbar);




    //显示主窗口控件及其所有子控件
    gtk_widget_show_all(mainWindow);
    gtk_main();

    return 0;
}