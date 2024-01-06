#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <glob.h>
#include <stdlib.h>
#include <thread>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "external_cmd.h"
#include "internal_cmd.h"
using namespace std;
#define BOLD_AQUA "\033[1;36m"
#define RESET_TEXT "\033[0m"

/**
 * @brief Get the current working directory.
 *
 * @return The current working directory as a string.
 * @example get_current_dir() -> "/home/username"
 */
string get_current_dir()
{
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
    {
        string result;
        result = current_dir;
        return result;
    }
    else
    {
        perror("getcwd");
        return string();
    }
}

/**
 * @brief Dsiplay the prompt with the current directory.
 */
void display_prompt()
{
    cout << BOLD_AQUA << get_current_dir() << RESET_TEXT << "$ ";
}

/**
 * Checks if the given string contains the "&&" substring.
 *
 * @param str The string to be checked.
 * @return True if the string contains "&&", false otherwise.
 * @example "ls && pwd" -> true
 */
bool find_special_character(const string &str, const string &chr)
{
    return str.find(chr) != string::npos;
}

/**
 * @brief Trims leading and trailing spaces from a string.
 *
 * @param str The string to be trimmed.
 * @example "  Hello World!  " -> "Hello World!";
 */
void trim(string &str)
{
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
}

/**
 * @brief Splits a string into a vector of strings based on a delimiter.
 *
 * @param command The input string to be split.
 * @param delimiter The delimiter string to split the input string on.
 * @return A vector of strings containing the split input string.
 * @example "ls -l" returns {"ls", "-l"}.
 */
vector<string> SplitCmd_char(const string &command, const string &delimiter)
{
    vector<string> tokens;
    string token;
    int start = 0;
    int end = command.find(delimiter);
    while (end != string::npos)
    {
        token = command.substr(start, end - start);
        trim(token);
        tokens.push_back(token);
        start = end + delimiter.length();
        end = command.find(delimiter, start);
    }
    token = command.substr(start, end);
    trim(token);
    tokens.push_back(token);
    return tokens;
}

/**
 * @brief Finds the positions of a specified character in a given string.
 *
 * This function searches for occurrences of a specified character in a given string
 * and returns a vector containing the positions of those occurrences.
 *
 * @param str The input string to search in.
 * @param specCharacter The character to search for.
 * @return A vector containing the positions of the specified character in the string.
 * @example get_delimeter_positions("ls && pwd", "&&") -> [3]
 */
vector<int> get_delimeter_positions(const string &str, const string &specCharacter)
{
    vector<int> positions;
    int pos = str.find(specCharacter, 0);
    while (pos != string::npos)
    {
        positions.push_back(pos);
        pos = str.find(specCharacter, pos + 1);
    }
    return positions;
}
/**
 * @brief Processes a command line string and returns a vector of tokens.
 *
 * This function takes a command line string as input and splits it into tokens based on spaces (' ') and apostrophes ('\'').
 * If the number of apostrophes is odd, it prints an error message and returns an empty vector.
 * If there are apostrophes in the command line string, it removes the tokens enclosed in apostrophes before splitting.
 * The resulting tokens are stored in a vector and returned.
 *
 * @param command The command line string to be processed.
 * @return A vector of tokens extracted from the command line string.
 * @example "ls -l" returns {"ls", "-l"}.
 * @example "mkdir "quang'nghiem" returns{"mkdir", "quang'nghiem"}
 * @example "mkdir 'quang"nghiem'" returns{"mkdir", "quang"nghiem"}
 */
vector<string> single_cmd_process(const string &command)
{
    vector<string> tokens;
    vector<int> Quote_pos, Dquote_pos, Space_pos;
    Quote_pos = get_delimeter_positions(command, "\'");
    Dquote_pos = get_delimeter_positions(command, "\"");
    Space_pos = get_delimeter_positions(command, " ");

    if (Quote_pos.size() == 0 && Dquote_pos.size() == 0)
    {
        tokens = SplitCmd_char(command, " ");
        return tokens;
    }
    else if (Quote_pos.size() != 0 && Dquote_pos.size() == 0)
    {
        if (Quote_pos.size() % 2 != 0)
        {
            cout << "Odd number of apostrophes" << endl;
            return tokens;
        }
        if (Space_pos[0] < Quote_pos[0] || Space_pos.size() - 1 > Quote_pos[Quote_pos.size() - 1])
        {
            string token1 = command.substr(0, Space_pos.at(0));
            trim(token1);
            tokens.push_back(token1);
        }
        else
        {
            cout << "Invalid command" << endl;
        }
        for (int i = 0; i < Quote_pos.size() - 1; i += 2)
        {
            string token2 = command.substr(Quote_pos.at(i) + 1, Quote_pos.at(i + 1) - Quote_pos.at(i) - 1);
            trim(token2);
            tokens.push_back(token2);
        }
        return tokens;
    }
    else if (Quote_pos.size() == 0 && Dquote_pos.size() != 0)
    {
        if (Dquote_pos.size() % 2 != 0)
        {
            cout << "Odd number of apostrophes" << endl;
            return tokens;
        }
        if (Space_pos[0] < Dquote_pos[0] || Space_pos.size() - 1 > Dquote_pos[Dquote_pos.size() - 1])
        {
            string token1 = command.substr(0, Space_pos.at(0));
            trim(token1);
            tokens.push_back(token1);
        }
        else
        {
            cout << "Invalid command" << endl;
        }
        for (int i = 0; i < Dquote_pos.size() - 1; i += 2)
        {
            string token2 = command.substr(Dquote_pos.at(i) + 1, Dquote_pos.at(i + 1) - Dquote_pos.at(i) - 1);
            trim(token2);
            tokens.push_back(token2);
        }
        return tokens;
    }
    else if (Quote_pos.size() != 0 && Dquote_pos.size() != 0)
    {
        if (Quote_pos.size() % 2 == 0 && Dquote_pos.size() % 2 == 0)
        {
            if (Quote_pos[0] > Dquote_pos[0] && Quote_pos[Quote_pos[Quote_pos.size() - 1] < Dquote_pos[Dquote_pos.size() - 1]])
            {
                if (Space_pos[0] < Dquote_pos[0] || Space_pos.size() - 1 > Dquote_pos[Dquote_pos.size() - 1])
                {
                    string token1 = command.substr(0, Space_pos.at(0));
                    trim(token1);
                    tokens.push_back(token1);
                }
                else
                {
                    cout << "Invalid command" << endl;
                }
                for (int i = 0; i < Dquote_pos.size() - 1; i += 2)
                {
                    string token2 = command.substr(Dquote_pos.at(i) + 1, Dquote_pos.at(i + 1) - Dquote_pos.at(i) - 1);
                    trim(token2);
                    tokens.push_back(token2);
                }
            }

            else if (Quote_pos[0] < Dquote_pos[0] && Quote_pos[Quote_pos[Quote_pos.size() - 1] > Dquote_pos[Dquote_pos.size() - 1]])
            {
                if (Space_pos[0] < Quote_pos[0] || Space_pos.size() - 1 > Quote_pos[Quote_pos.size() - 1])
                {
                    string token1 = command.substr(0, Space_pos.at(0));
                    trim(token1);
                    tokens.push_back(token1);
                }
                else
                {
                    cout << "Invalid command" << endl;
                }
                for (int i = 0; i < Quote_pos.size() - 1; i += 2)
                {
                    string token2 = command.substr(Quote_pos.at(i) + 1, Quote_pos.at(i + 1) - Quote_pos.at(i) - 1);
                    trim(token2);
                    tokens.push_back(token2);
                }
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        }
        else if (Quote_pos.size() % 2 == 0 && Dquote_pos.size() % 2 != 0)
        {
            if (Quote_pos[0] < Dquote_pos[0] && Quote_pos[Quote_pos.size() - 1] > Dquote_pos[Dquote_pos.size() - 1])
            {
                if (Space_pos[0] < Quote_pos[0] || Space_pos.size() - 1 > Quote_pos[Quote_pos.size() - 1])
                {
                    string token1 = command.substr(0, Space_pos.at(0));
                    trim(token1);
                    tokens.push_back(token1);
                }
                else
                {
                    cout << "Invalid command" << endl;
                }
                for (int i = 0; i < Quote_pos.size() - 1; i += 2)
                {
                    string token2 = command.substr(Quote_pos.at(i) + 1, Quote_pos.at(i + 1) - Quote_pos.at(i) - 1);
                    trim(token2);
                    tokens.push_back(token2);
                }
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        }
        else if (Quote_pos.size() % 2 != 0 && Dquote_pos.size() % 2 == 0)
        {
            if (Quote_pos[0] > Dquote_pos[0] && Quote_pos[Quote_pos.size() - 1] < Dquote_pos[Dquote_pos.size() - 1])
            {
                if (Space_pos[0] < Dquote_pos[0] || Space_pos.size() - 1 > Dquote_pos[Dquote_pos.size() - 1])
                {
                    string token1 = command.substr(0, Space_pos.at(0));
                    trim(token1);
                    tokens.push_back(token1);
                }
                else
                {
                    cout << "Invalid command" << endl;
                }
                for (int i = 0; i < Dquote_pos.size() - 1; i += 2)
                {
                    string token2 = command.substr(Dquote_pos.at(i) + 1, Dquote_pos.at(i + 1) - Dquote_pos.at(i) - 1);
                    trim(token2);
                    tokens.push_back(token2);
                }
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        }
        else
        {
            cout << "Invalid command" << endl;
        }

        return tokens;
    }
    tokens = SplitCmd_char(command, " ");
    return tokens;
}

/**
 * Checks if any of the strings in the given vector contains wildcard characters.
 * Wildcard characters include '*' and '?'.
 *
 * @param args The vector of strings to check.
 * @return True if any string contains wildcard characters, false otherwise.
 * @example {"ls", "file*"} -> true
 */
bool wcard_check(const vector<string> &args)
{
    return any_of(args.begin(), args.end(), [](const string &chr)
                       { return chr.find_first_of("*?") != string::npos; });
}

/**
 * Expands a wildcard pattern into a vector of matching file paths.
 *
 * @param pattern The wildcard pattern to expand.
 * @return A vector of file paths that match the wildcard pattern.
 * @example "file*" -> {"file1", "file2", "file3"}
 */
vector<string> expand_wcard(const string &pattern)
{
    glob_t glob_result;
    memset(&glob_result, 0, sizeof(glob_result));

    glob(pattern.c_str(), GLOB_TILDE | GLOB_BRACE, nullptr, &glob_result);

    vector<string> expanded(glob_result.gl_pathv, glob_result.gl_pathv + glob_result.gl_pathc);

    globfree(&glob_result);

    return expanded;
}

/**
 * Expands wildcard tokens in the given vector of strings.
 * Wildcard tokens are strings that contain '*' or '?' characters.
 * For each wildcard token, it expands it into multiple strings based on the wildcard pattern.
 * Non-wildcard tokens are added as-is to the expanded tokens vector.
 *
 * @param tokens The vector of strings containing wildcard and non-wildcard tokens.
 * @return The vector of expanded tokens, where wildcard tokens are expanded into multiple strings.
 * @example {"ls", "file*"} -> {"ls", "file1", "file2", "file3"}
 */
vector<string> expandWildcardTokens(const vector<string> &tokens)
{
    vector<string> expanded_tokens;
    expanded_tokens.reserve(tokens.size());

    for (const string &token : tokens)
    {
        if (token.find_first_of("*?") != string::npos)
        {
            vector<string> expanded = expand_wcard(token);
            expanded_tokens.insert(expanded_tokens.end(), expanded.begin(), expanded.end());
        }
        else
        {
            expanded_tokens.push_back(token);
        }
    }

    return expanded_tokens;
}

/**
 * Checks if the given character is present in the vector of strings.
 *
 * @param args The vector of strings to search in.
 * @param character The character to search for.
 * @return True if the character is found in the vector, false otherwise.
 * @example {"ls >> output.txt", ">>" } -> true
 */
bool handle_redirect_check(const vector<string> &args, const string &character)
{
    return any_of(args.begin(), args.end(), [character](const string &chr)
                       { return chr == character; });
}

/**
 * Executes a command and returns the output as a vector of strings.
 * Each element of the vector represents a line of the command output.
 *
 * @param args A vector of strings representing the command and its arguments.
 * @return A vector of strings containing the command output.
 */
vector<string> exeCmdOutput(const vector<string> &args)
{
    vector<string> result;
    stringstream command;

    for (const auto &word : args)
    {
        command << word << ' ';
    }

    FILE *pipe = popen((command.str() + " 2>/dev/null").c_str(), "r");
    if (pipe)
    {
        constexpr int buffer_size = 128;
        vector<char> buffer(buffer_size);

        while (fgets(buffer.data(), buffer_size, pipe) != nullptr)
        {
            result.emplace_back(buffer.data());
        }

        pclose(pipe);
    }
    else
    {
        cerr << "Error opening pipe." << endl;
    }

    return result;
}

/**
 * Checks if any string in the given vector contains the backtick character (`).
 *
 * @param args The vector of strings to check.
 * @return True if any string contains the backtick character, false otherwise.
 * @example {"echo", "`date`"} -> true
 */
bool InItalicCmd_check(const vector<string> &args)
{
    for (const auto &line : args)
    {
        if (!line.empty() && line[0] == '`')
        {
            return true;
        }
    }
    return false;
}

void exeSimpleCmd(string &command);

// Execute single command in form of vector<string>(with Italic Comma). Print result to Terminal
// Eg: {"echo","`date`"} => print: "Chu nhat" "ngay 16" "thang 7"....
/**
 * Executes a command with inline commands enclosed in backticks (`) and replaces them with their output.
 * The resulting command is then executed.
 *
 * @param args A vector of strings representing the command and its arguments.
 * @example {"echo", "`date`"} -> "echo Thu bay ngay 6 thang 1..."
 */
void GetItalicCommaCommandOutput(vector<string> &args)
{
    vector<string> out_command;
    vector<string> temp = args;

    string input = "";

    for (int i = 1; i < temp.size(); i++)
    {
        if (*temp[i].begin() == '`')
        {
            temp[i] = temp[i].substr(1, temp[i].length() - 2);
            vector<string> inline_command;
            inline_command.push_back(temp[i]);
            vector<string> temp_out = exeCmdOutput(inline_command);
            for (int i = 0; i < temp_out.size(); i++)
            {
                out_command.push_back(temp_out[i]);
            }
        }
        else
        {
            out_command.push_back(temp[i]);
        }
    }
    string output_string;
    output_string = "'";
    for (int i = 0; i < out_command.size() - 1; i++)
    {
        output_string += out_command[i] + " ";
    }
    output_string += out_command[out_command.size() - 1] + "'";
    trim(temp.front());
    trim(output_string);
    string output = temp.front() + " " + output_string;
    exeSimpleCmd(output);
}

/**
 * @brief Finds and erases a specific flag and its corresponding value from a vector of strings.
 *
 * This function searches for the specified flag in the vector of strings and removes it along with its corresponding value.
 * The flag and its value are expected to be consecutive elements in the vector.
 *
 * @param args The vector of strings to search and modify.
 * @param flag The flag to find and erase.
 * @return The erased value if the flag is found and has a corresponding value, an empty string otherwise.
 */
string find_and_erase(vector<string> &args, const string &flag)
{
    auto it = find(args.begin(), args.end(), flag);
    if (it != args.end() && it + 1 != args.end())
    {
        string file = *(it + 1);
        args.erase(it, it + 2);
        return file;
    }
    return string();
}

/**
 * Redirects the output of a command to a specified file.
 *
 * @param output_file The path of the output file.
 * @param append      Flag indicating whether to append to the file or truncate it.
 * @param command     The command to be executed.
 */
void redirect_output(const string &output_file, bool append, const string &command)
{

    FILE *pipe = popen((command + " 2>/dev/null").c_str(), "r");
    if (!pipe)
    {
        cerr << "Error executing command using popen." << endl;
        return;
    }
    ofstream outfile(output_file, append ? ios::app : ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error opening output file: " << output_file << endl;
        pclose(pipe);
        return;
    }

    streambuf *coutbuf = cout.rdbuf();

    cout.rdbuf(outfile.rdbuf());

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        cout << buffer;
    }

    cout.rdbuf(coutbuf);

    outfile.close();
    pclose(pipe);
}

/**
 * Handles the redirection of output for a given command.
 *
 * @param args The vector of command arguments.
 */
void handle_redirection(vector<string> &args)
{
    string output_file = args[args.size() - 1];
    trim(output_file);
    string command = args[0];
    trim(command);

    bool append = false;

    output_file = find_and_erase(args, ">");
    if (output_file.empty())
    {
        output_file = find_and_erase(args, ">>");
        append = true;
    }

    thread redirect_thread(redirect_output, output_file, append, command);

    redirect_thread.detach();
}

/**
 * Checks if a given character position is inside quotes in a string.
 *
 * @param str The input string.
 * @param pos_of_char The position of the character to check.
 * @return True if the character is inside quotes, false otherwise.
 * @example IsInsideQuotes("echo 'Hello World!'", 7) -> true
 */
bool IsInsideQuotes(const string &str, const int &pos_of_char)
{
    vector<int> DQuote_pos = get_delimeter_positions(str, "\"");
    vector<int> Quote_pos = get_delimeter_positions(str, "\'");
    if (DQuote_pos.size() == 0 && Quote_pos.size() == 0)
        return false;
    else
    {
        for (int i = 0; i < DQuote_pos.size(); i += 2)
        {
            if (pos_of_char > DQuote_pos[i] && pos_of_char < DQuote_pos[DQuote_pos.size() - 1])
                return true;
        }
        for (int i = 0; i < Quote_pos.size(); i += 1)
        {
            if (pos_of_char > Quote_pos[i] && pos_of_char < Quote_pos[Quote_pos.size() - 1])
                return true;
        }
        return false;
    }
}

/**
 * Executes a simple command.
 *
 * This function takes a command as input and performs the following steps:
 * 1. Processes the command to obtain individual arguments.
 * 2. Expands wildcard tokens in the arguments.
 * 3. Checks for redirection operators ('>' or '>>') and handles redirection if present.
 * 4. If the command is an italic comma command, retrieves the output of the command.
 * 5. If the command is "exit", terminates the program.
 * 6. If the command is not an internal command, executes it as an external command.
 *
 * @param command The command to be executed.
 */
void exeSimpleCmd(string &command)
{

    vector<string> args = single_cmd_process(command);
    args = expandWildcardTokens(args);
    if (handle_redirect_check(args, ">") || handle_redirect_check(args, ">>"))
    {
        handle_redirection(args);
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    else if (InItalicCmd_check(args))
    {
        GetItalicCommaCommandOutput(args);
    }
    else if (args[0] == "exit")
    {
        exit(0);
    }
    else if (!exeInternalCmd(args))
    {
        exeExternalCmd(args);
    }
}

/**
 * Splits a command string into substrings based on the given split positions.
 *
 * @param command The command string to split.
 * @param splitPositions The positions at which to split the command string.
 * @return A vector of substrings obtained by splitting the command string.
 * @example SplitCmd_pos("ls -l", {2}) -> {"ls", "-l"}
 */
vector<string> SplitCmd_pos(const string &command, const vector<int> &splitPositions)
{
    vector<string> result;
    int start = 0;

    for (int position : splitPositions)
    {
        if (position > start && position <= command.length())
        {
            result.push_back(command.substr(start, position - start));
            start = position + 2; // Move start to the next character after the delimiter
        }
    }

    if (start < command.length())
    {
        result.push_back(command.substr(start));
    }

    return result;
}

/**
 * Executes a command in the background.
 *
 * @param command The command to be executed.
 */
void exeBackgndCmd(const char *command)
{
    char *args[64];
    char *token = strtok(const_cast<char *>(command), " ");
    int i = 0;
    while (token != nullptr)
    {
        args[i++] = token;
        token = strtok(nullptr, " ");
    }
    args[i] = nullptr;

    pid_t pid = fork();

    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        cout << "[" << pid << "] " << command << endl;
    }
    else
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}
/**
 * Executes a pipe command by opening a pipe to execute the specified command and read its output.
 * It also opens a pipe to execute the specified executable and write input to it.
 *
 * @param tokens A vector of strings representing the command and executable tokens.
 * @return void
 */
void exePipeCmd(vector<string> tokens)
{
    string merge_tokens;
    if (tokens.size() < 2)
    {
        cout << "Error: Not enough arguments" << endl;
        return;
    }
    merge_tokens = tokens[0];
    for (int i = 1; i < tokens.size() - 1; i++)
    {
        merge_tokens += (" | " + tokens[i]);
    }
    FILE *commandPipe = popen(merge_tokens.c_str(), "r");
    if (!commandPipe)
    {
        cerr << "Error executing command: " << merge_tokens << endl;
        return;
    }

    FILE *executablePipe = popen(tokens[tokens.size() - 1].c_str(), "w");
    if (!executablePipe)
    {
        cerr << "Error executing executable: " << tokens[1] << endl;
        pclose(commandPipe);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), commandPipe) != nullptr)
    {
        fputs(buffer, executablePipe);
    }

    pclose(commandPipe);
    pclose(executablePipe);
}

/**
 * Executes complex commands based on the given command string.
 * Complex commands can include multiple commands separated by special characters like "&&", "|", and "&".
 * If the command contains "&&", it executes each command sequentially until one of them fails.
 * If the command contains "|", it executes each command and passes the output of one command as input to the next command.
 * If the command contains "&", it executes each command in the background.
 *
 * @param command The command string to be executed.
 */
void exeComplexCmds(string &command)
{

    if (find_special_character(command, "&&"))
    {
        vector<int> and_and_pos = get_delimeter_positions(command, "&&");

        vector<int> and_and_pos_not_in_quotes;
        vector<string> tokens;
        for (auto &it : and_and_pos)
        {
            if (!IsInsideQuotes(command, it))
            {

                and_and_pos_not_in_quotes.push_back(it);
            }
        }
        if (and_and_pos_not_in_quotes.size() == 0)
        {
            tokens.push_back(command);
        }
        else
        {
            tokens = SplitCmd_pos(command, and_and_pos_not_in_quotes);
        }
        for (auto &it : tokens)
        {
            trim(it);
            exeSimpleCmd(it);
        }
    }
    else if (find_special_character(command, "|"))
    {
        vector<int> pipe_pos = get_delimeter_positions(command, "|");
        vector<int> pipe_pos_not_in_quote;
        vector<string> tokens;
        for (auto &it : pipe_pos)
        {
            if (!IsInsideQuotes(command, it))
            {
                pipe_pos_not_in_quote.push_back(it);
            }
        }
        if (pipe_pos_not_in_quote.size() == 0)
        {
            tokens.push_back(command);
        }
        else
        {
            tokens = SplitCmd_pos(command, pipe_pos_not_in_quote);
        }
        for (auto it : tokens)
        {
            trim(it);
        }
        exePipeCmd(tokens);
    }
    else if (find_special_character(command, "&"))
    {
        vector<int> and_pos = get_delimeter_positions(command, "&");
        vector<int> and_pos_not_in_quote;

        vector<string> tokens;
        for (auto &it : and_pos)
        {
            if (!IsInsideQuotes(command, it))
            {
                and_pos_not_in_quote.push_back(it);
            }
        }
        if (and_pos_not_in_quote.size() == 0)
        {
            tokens.push_back(command);
        }
        else
        {
            tokens = SplitCmd_pos(command, and_pos_not_in_quote);
        }
        for (int i = 0; i < tokens.size()-1; i++)
        {
            trim(tokens[i]);
            exeBackgndCmd(tokens[i].c_str());
        }
        trim(tokens[tokens.size()-1]);
        exeSimpleCmd(tokens[tokens.size()-1]);
        int status;
        while (wait(&status) > 0)
        {
        }
    }

    else
    {
        exeSimpleCmd(command);
    }
}
