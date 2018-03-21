#include "lexical_analyzer_generator.h"

//#include <Windows.h>

#include <sstream>

#include "nfa_tools/lexical_rules.h"

#define PUNCT_CLAUSE_START '['
#define PUNCT_CLAUSE_END ']'
#define KEYWORD_CLAUSE_START '{'
#define KEYWORD_CLAUSE_END '}'
#define EXPRESSION_ASSIGN '='
#define DEFINITION_ASSIGN ':'

#define ESCAPE '\\'


std::string trim(std::string const& str)
{
    if(str.empty())
        return str;

    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}

std::vector <std::string> read_file (std::string rules_file)
{
  std::vector <std::string> file_lines;
  std::ifstream infile (rules_file);
  if (infile.is_open())
  {
    std::string line;
    while ( getline (infile,line) )
    {
      file_lines.push_back (trim(line));
    }
    infile.close();
  }
  return file_lines;
}

void handle_punctation_line (std::string line, lexical_rules &rules)
{
  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] == ESCAPE && i >= line.length() - 2)
    {
        //// TODO : ERROR ex : [\] or [
    }
    else if (line[i] == ESCAPE && i <= line.length() - 2)
    {
        rules.add_punct_char (line[i+1]);
    }
    else
    {
      rules.add_punct_char (line[i]);
    }
  }
  if (line[line.length() - 1] != PUNCT_CLAUSE_END)
  {
      //// TODO : ERROR
  }
}

void handle_keywords_line (std::string line, lexical_rules &rules)
{
  if (line[line.length() - 1] != KEYWORD_CLAUSE_END
      || line.length() <= 2);
      //// TODO : Error
  std::istringstream iss(line.substr(1,line.length() - 2));
  while (iss) {
      std::string word;
      iss >> word;
      rules.add_keyword(word);
  }
}

void handle_reg_def (std::string lhs, std::string rhs, lexical_rules &rules)
{

}

void handle_regex (std::string lhs, std::string rhs, lexical_rules &rules)
{
  regular_expression expression = {lhs, rhs};
  rules.add_regex (expression);
}


FILE* lexical_analyzer_generator::get_lexical_analyzer_file (std::string rules_file)
{
    //SetConsoleOutputCP( CP_UTF8 );
    std::vector<std::string> rules_file_lines = read_file (rules_file);
    lexical_rules rules = lexical_rules ();
    for (auto line : rules_file_lines)
    {
      if (line[0] == PUNCT_CLAUSE_START)
      {
          handle_punctation_line (line, rules);
      }
      else if (line[0] == KEYWORD_CLAUSE_START)
      {
        handle_keywords_line (line, rules);
      }
      else
      {
          bool invalid_line = false;
          for (int i = 0; i < line.length(); i++)
          {
            if (line[i] == DEFINITION_ASSIGN)
            {
                handle_reg_def (trim(line.substr(0, i)), trim(line.substr(i+1)),
                                rules);
            }
            else if (line[i] == EXPRESSION_ASSIGN)
            {
                handle_regex (trim(line.substr(0, i)), trim(line.substr(i+1)),
                              rules);
            }
          }
          if (invalid_line)
          {
            //// TODO : Error
          }
      }
    }
}
