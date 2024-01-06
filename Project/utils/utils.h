#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

void display_prompt();
std::vector<std::string> SplitCmd(const std::string &command);
std::string find_and_erase(std::vector<std::string> &args, const std::string &flag);
void redirect_output(const std::string &output_file, bool append, const std::string &command);
void handle_redirection(std::vector<std::string> &args);
bool IsInsideQuotes(const std::string &str, const int &pos_of_char);
void exeSimpleCmd(std::string &command);
std::vector<std::string> SplitCmd_pos(const std::string &command, const std::vector<int> &splitPositions);
void exeBackgndCmd(const char *command);
void exePipeCmd(std::vector<std::string> tokens);
void exeComplexCmds(std::string &command);

#endif // UTILS_H