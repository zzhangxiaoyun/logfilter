#include <gtk/gtk.h>
#include <iostream>
#include "LogFilter.h"
#include "Utils.h"
#include <time.h>


/**
*callback function of button
*@param w widget
*@param userdata
*/


void choosefile(GtkWidget *w, gpointer userdata) {
    std::cout << " choosefile" << std::endl;

//    GtkWidget *widget = gtk_file_chooser_dialog_new(&"file choose", (GdkWindow*)userdata, GTK_FILE_CHOOSER_ACTION_OPEN, &"确定");

}

void notifyTextView(list<string> filterTags, list<string> ignoreTags, LogFilter *logFilter, GtkTextBuffer* buffer) {

    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    time_t fstart = clock();

    list<string> *filterLogs = logFilter->filter(filterTags, ignoreTags);

    time_t fend = clock();
    cout<<"filter it cost " << (int)((fend - fstart ) * 1000/CLOCKS_PER_SEC) <<" ms"<<endl;


    time_t pstart = clock();
    string logcontext = Utils::append(filterLogs);
    time_t pend = clock();
    cout<<"append it cost " << (int)((pend - pstart ) * 1000/CLOCKS_PER_SEC) <<" ms"<<endl;

    const gchar *strData = logcontext.data();

    gdk_threads_enter();
    gtk_text_buffer_set_text(buffer, strData,  strlen(strData));
    gdk_threads_leave();

    cout << "done" << endl;
}



void enterClicked(GtkWidget *w, gpointer userdata) {
    GtkWidget **gtkwidgets = (GtkWidget **)userdata;


    const gchar *filterText = gtk_entry_get_text(GTK_ENTRY(gtkwidgets[0]));
    list<string> filterTags = Utils::split(string(filterText), "|");
//    Utils::logList(&filterTags);

    const gchar *ignoreText = gtk_entry_get_text(GTK_ENTRY(gtkwidgets[1]));
    list<string> ignoreTags = Utils::split(string(ignoreText), "|");
//    Utils::logList(&ignoreTags);

    notifyTextView(filterTags, ignoreTags, (LogFilter*)gtkwidgets[2], (GtkTextBuffer*) gtkwidgets[3]);
}

#define WIDTH 1000
#define HEIGHT 600


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
    gtk_widget_set_size_request(content2LeftWin, 230, 0);
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

    GtkWidget *filterTagEdit = gtk_entry_new();
    gtk_widget_set_size_request(filterTagEdit, 600, 0);
    gtk_box_pack_start(GTK_BOX(title0HBox), filterTagEdit, TRUE, TRUE, 0);

    // ignore tag
    GtkWidget *empty = gtk_label_new("");
    gtk_widget_set_size_request(empty, 82, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), empty, FALSE, FALSE, 0);

    GtkWidget *ignoreTagLabel = gtk_label_new("ignore tags:");
    gtk_box_pack_start(GTK_BOX(title1HBox), ignoreTagLabel, FALSE, FALSE, 0);

    GtkWidget *ignoreTagEdit = gtk_entry_new();
    gtk_widget_set_size_request(ignoreTagEdit, 600, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), ignoreTagEdit, TRUE, TRUE, 0);


    // 确定按钮
    GtkWidget *enterButton = gtk_button_new_with_label("确定");
    gtk_widget_set_size_request(enterButton, 200, 0);
    gtk_box_pack_start(GTK_BOX(title1HBox), enterButton, FALSE, FALSE, 0);


    // left log dir list
    initLogList(content2LeftVBox);

    // text
    GtkWidget *textView = gtk_text_view_new();
    gtk_widget_set_size_request(ignoreTagEdit, 600, 0);


    gtk_widget_override_background_color(textView, GTK_STATE_FLAG_NORMAL, Utils::parseGdkRgba(0, 0, 0, 1));
    gtk_widget_override_background_color(textView, GTK_STATE_FLAG_SELECTED, Utils::parseGdkRgba(0, 0.4, 0.4, 1));
    gtk_widget_override_color(textView, GTK_STATE_FLAG_NORMAL, Utils::parseGdkRgba(1, 1, 1, 1));


    gtk_container_add(GTK_CONTAINER(content2RightBox), textView);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), TRUE);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));


    LogFilter *logFilter = new LogFilter("/home/xy/1b/.log");


    void* gtkwidgets[] = {filterTagEdit, ignoreTagEdit, logFilter, buffer};

    g_signal_connect(G_OBJECT(filterTagEdit), "activate", G_CALLBACK(enterClicked), gtkwidgets);
    g_signal_connect(G_OBJECT(ignoreTagEdit), "activate", G_CALLBACK(enterClicked), gtkwidgets);
    g_signal_connect(G_OBJECT(enterButton), "clicked", G_CALLBACK(enterClicked), gtkwidgets);


    //显示主窗口控件及其所有子控件
    gtk_widget_show_all(mainWindow);
    gtk_main();

    return 0;
}