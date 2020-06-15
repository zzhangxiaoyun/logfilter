//
// Created by xy on 20-6-15.
//

#include "Utils.h"
#include "FileUtils.h"
int main1() {


    list<string> tags = Utils::split("fdafda01|fdafda2|fdafda3|fd4|", "|");
    Utils::logList(&tags);



}