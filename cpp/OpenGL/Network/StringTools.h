#pragma once

#include <string>
#include <vector>

std::string trimLeft(const std::string& input);
std::string trimRight(const std::string& input);
std::string trim(const std::string& input);
std::string toLower(const std::string& input);
std::string toUpper(const std::string& input);
std::vector<std::string> tokenize(const std::string& input, const std::string& delim);
bool endsWith(std::string_view str, std::string_view suffix);
bool startsWith(std::string_view str, std::string_view prefix);
