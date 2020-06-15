//
// Created by xy on 20-6-15.
//
#include <string>
#include <list>

#include <fstream>
#include <string>
#include <iostream>
#include <list>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#ifndef LOGREAD_FILESUTILS_H
#define LOGREAD_FILESUTILS_H
using namespace std;

class FileUtils {
public:
    static void file2lines(string filename, list<string> *lines) {

        ifstream in(filename);
        string line;
        if (in) {
            while (getline(in, line)) {
                lines->push_back(line);
            }
        } else { // 没有该文件
            cout << "no such file" << endl;
        }
    }

    static list<string> scanFiles(char *dirPath) {
        std::list<string> files;
        DIR *dir = opendir(dirPath);
        if (dir == NULL) {
            std::cout << strerror(errno) << endl;
        }
        chdir(dirPath); //进入到当前读取目录
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            struct stat st;
            stat(ent->d_name, &st);
            if (S_ISDIR(st.st_mode)) {
//            std::cout << "dir, continue: " << ent->d_name << endl;
            } else {
                std::string filename(dirPath);
                filename.append("/").append(ent->d_name);
                files.push_back(filename);
            }
        }
        closedir(dir);
        chdir("..");
        return files;
    }


    static list<string>* filterLogFiles(list<string> *files) {
        files->sort();
        std::list<string> *logfiles = new std::list<string>;
        std::list<string>::iterator it;
        for (it = files->begin(); it != files->end(); ++it) {
            if ((*it).find("logcat_full.log") == string::npos) {
                continue;
            }
            logfiles->push_front(*it);
        }
        return logfiles;
    }

    static list<string>* files2lines(list<string> *files) {
        std::list<string> *lines = new std::list<string>;
        std::list<string>::iterator it;
        for (it = files->begin(); it != files->end(); ++it) {
            file2lines(*it, lines);
        }
        return lines;
    }

};

#endif //LOGREAD_FILESUTILS_H
