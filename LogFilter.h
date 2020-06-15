//
// Created by xy on 20-6-15.
//

#include <string>
#include <list>
#include "FileUtils.h"

#ifndef LOGREAD_LOGFILTER_H
#define LOGREAD_LOGFILTER_H

using namespace std;

class LogFilter {
private:
    list<string> *loglines;
public:
    LogFilter(string logdir) {
        list<string> files = FileUtils::scanFiles((char*)logdir.data());
        list<string> *logfiles = FileUtils::filterLogFiles(&files);
        FileUtils::logList(logfiles);
        this->loglines = FileUtils::files2lines(logfiles);
    }

    ~LogFilter() {
        delete(loglines);
    }

    list<string>* filter(list<string> filterTags, list<string> ignores) {
        list<string> *filteredLogs = new list<string>;
        list<string>::iterator it;
        for (it = loglines->begin(); it != loglines->end(); ++it) {
            bool filter = LogFilter::filter(*it, filterTags, ignores);
            if (filter) {
                filteredLogs->push_back(*it);
            }
        }
        return filteredLogs;
    }

public:
    static bool filter(string line, list<string> filterTags, list<string> ignores) {
        bool filter = LogFilter::filter(line, filterTags);
        if (filter) {
            bool ignore = LogFilter::filter(line, ignores);
            if (ignore) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    }

    static bool filter(string line, list<string> filterTags) {
        list<string>::iterator it;
        for (it = filterTags.begin(); it != filterTags.end(); it++) {
            if (line.find(*it) != string::npos) {
                return true;
            }
        }
        return false;
    }
};


#endif //LOGREAD_LOGFILTER_H
