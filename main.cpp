#include <gtk/gtk.h>
#include <iostream>

/**
*callback function of button
*@param w widget
*@param userdata
*/
void choosefile(GtkWidget *w, gpointer userdata) {
    std::cout<< " choosefile" << std::endl;
//    GtkWidget *widget = gtk_file_chooser_dialog_new(&"file choose", (GdkWindow*)userdata, GTK_FILE_CHOOSER_ACTION_OPEN, &"确定");


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

void initLogList(GtkWidget *logdirList) {
    for (int i = 0; i < 10; ++i) {
        GtkWidget *label1 = gtk_button_new_with_label("~/lgos/log3/.log/log/log/lk/log");
        gtk_button_set_alignment(GTK_BUTTON(label1), 0, 0);
        gtk_box_pack_start(GTK_BOX(logdirList), label1, FALSE, FALSE, 0);
    }
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

    // 内容布局
    GtkWidget *content2Hpaned = gtk_hpaned_new();
    gtk_box_pack_start(GTK_BOX(rootVbox), content2Hpaned, TRUE, TRUE, 0);

    // 内容左
    GtkWidget *content2LeftWin = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(content2LeftWin,230, 0);
    gtk_paned_add1(GTK_PANED(content2Hpaned), content2LeftWin);

    GtkWidget *content2LeftVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(content2LeftWin), content2LeftVBox);

    // 内容右
    GtkWidget *content2RightBox = gtk_scrolled_window_new(NULL, NULL);
    gtk_paned_add2(GTK_PANED(content2Hpaned), content2RightBox);

    //创建按钮
    GtkWidget *openLogDir = gtk_button_new_with_label("Open log dir");
    gtk_widget_set_size_request(openLogDir, 100, 0);
    //设置按钮样式
    gtk_button_set_relief(GTK_BUTTON(openLogDir), GTK_RELIEF_NORMAL);
    //将按钮加入到布局中
    gtk_box_pack_start(GTK_BOX(title0HBox), openLogDir, FALSE, FALSE, 0);
    //为按钮加入单击事件响应函数
    g_signal_connect(G_OBJECT(openLogDir), "clicked", G_CALLBACK(choosefile), mainWindow);

    // filter
    GtkWidget *filterLabel = gtk_label_new("filter tags:");
    gtk_box_pack_start(GTK_BOX(title0HBox), filterLabel, FALSE, FALSE, 0);

    GtkWidget *filterEdit = gtk_entry_new();
    gtk_widget_set_size_request(filterEdit, 600, 0);
    gtk_box_pack_start(GTK_BOX(title0HBox), filterEdit, TRUE, TRUE, 0);

    // remove tag
    GtkWidget *empty = gtk_label_new("");
    gtk_widget_set_size_request(empty, 82, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), empty, FALSE, FALSE, 0);

    GtkWidget *removeTagLabel = gtk_label_new("remove tags:");
    gtk_box_pack_start(GTK_BOX(title1HBox), removeTagLabel, FALSE, FALSE, 0);

    GtkWidget *removeTagEdit = gtk_entry_new();
    gtk_widget_set_size_request(removeTagEdit, 600, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), removeTagEdit, TRUE, TRUE, 0);

    // left log dir list
    initLogList(content2LeftVBox);

    // text
    GtkWidget *textView = gtk_text_view_new();
    gtk_widget_set_size_request(removeTagEdit, 600, 0);

    gtk_widget_modify_bg(textView, GTK_STATE_NORMAL, parseGdkColor(0x0, 0x0, 0x0));
    gtk_widget_override_color(textView, GTK_STATE_FLAG_NORMAL, parseGdkRgba(0xffff, 0xffff, 0xffff, 0xffff));


    gtk_container_add(GTK_CONTAINER(content2RightBox), textView);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), TRUE);


    //显示主窗口控件及其所有子控件
    gtk_widget_show_all(mainWindow);
    gtk_main();

    return 0;
}