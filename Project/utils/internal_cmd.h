#pragma once
#ifndef INTERNAL_CMD_H
#define INTERNAL_CMD_H
#include <vector>
#include <string>

void handle_cd(const std::vector<std::string> &args);
void handle_pwd();
void handle_echo(const std::vector<std::string> &args);
void handle_help();
int handle_cat(std::vector<std::string> &args);
int exeInternalCmd(std::vector<std::string> &args);

#endif // INTERNAL_CMD_H