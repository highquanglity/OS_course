#pragma once
#ifndef EXTERNAL_CMD_H
#define EXTERNAL_CMD_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>

using namespace std;

void exeExternalCmd(const vector<string> &args);

#endif // EXTERNAL_CMD_H