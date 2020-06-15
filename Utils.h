//
// Created by xy on 20-6-15.
//
#include <string>
#include <list>
#include <iostream>
#include <gtk/gtk.h>


#ifndef LOGFILTER_UTILS_H
#define LOGFILTER_UTILS_H
using namespace std;

class Utils {
public:
    static list<string> split(string str, string spacer) {
        list<string> v;
        int pos1, pos2;
        int len = spacer.length();     //记录分隔符的长度
        pos1 = 0;
        pos2 = str.find(spacer);
        while (pos2 != string::npos) {
            v.push_back(str.substr(pos1, pos2 - pos1));
            pos1 = pos2 + len;
            pos2 = str.find(spacer, pos1);    // 从str的pos1位置开始搜寻spacer
        }
//        if (pos1 != str.length())  {
//        }
        if (str.length() > 0) {
            v.push_back(str.substr(pos1));
        }
        return v;
    }

    static string append(list<string> *lines) {
        string str;

        std::list<string>::iterator it;
        for (it = lines->begin(); it != lines->end(); ++it) {
            str += (*it + "\n");
//            str->append(*it).append("\n");
//            cout << "line:" << *it << endl;
        }
        return str;

    }

    static void logList(list<string> *list) {
        cout<< "count:" << list->size() << endl;
        std::list<string>::iterator it;
        for (it = list->begin(); it != list->end(); ++it) {
            cout << "line:" << *it << endl;
        }
    }

    static GdkRGBA *parseGdkRgba(double red, double green, double blue, double a) {
        GdkRGBA *color = new GdkRGBA();

        color->red = red;
        color->blue = blue;
        color->green = green;
        color->alpha = a;
        return color;
    }

    static void log(string msg) {
        cout << msg << endl;
    }


};


#endif //LOGFILTER_UTILS_H
