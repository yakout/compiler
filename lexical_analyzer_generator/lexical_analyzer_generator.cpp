#include "lexical_analyzer_generator.h"

//#include <Windows.h>

#include <sstream>
#include <iostream>

#define PUNCT_CLAUSE_START '['
#define PUNCT_CLAUSE_END ']'
#define KEYWORD_CLAUSE_START '{'
#define KEYWORD_CLAUSE_END '}'
#define EXPRESSION_ASSIGN ':'
#define DEFINITION_ASSIGN '='

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



std::shared_ptr<nfa> build_punctations_nfa (std::string full_line, int order)
{
  std::string line;
  for (char c : full_line)
  {
    if (c != '\0' && c != SPACE && c != PUNCT_CLAUSE_START && c != PUNCT_CLAUSE_END)
      line += c;
  }
  std::shared_ptr<nfa> punct_nfa;
  bool first_nfa = true;
  for (int i = 0; i < line.length(); i++)
  {
    std::shared_ptr<nfa> cur_punct_nfa;
    if (line[i] == ESCAPE && i >= line.length() - 2)
    {
        //// TODO : ERROR ex : [\] or [
    }
    else if (line[i] == ESCAPE && i <= line.length() - 2)
    {
        std::shared_ptr<char_set> c_s(new char_set(line[i + 1]));
        std::shared_ptr<nfa>
          p_nfa(new nfa(c_s));
        cur_punct_nfa = p_nfa;
        cur_punct_nfa->set_acceptance_states_priority(order);
        cur_punct_nfa->set_acceptance_states_token_class(std::string() + line[i + 1]);
        i++;
    }
    else
    {
      std::shared_ptr<char_set> c_s(new char_set(line[i]));
      std::shared_ptr<nfa> p_nfa(new nfa(c_s));
      cur_punct_nfa = p_nfa;
      cur_punct_nfa->set_acceptance_states_priority(order);
      cur_punct_nfa->set_acceptance_states_token_class(std::string() + line[i]);
    }
    if (first_nfa)
    {
      first_nfa = false;
      punct_nfa = cur_punct_nfa;
    }
    else
    {
      punct_nfa->unify(cur_punct_nfa, false);
    }
  }
  if (line[line.length() - 1] != PUNCT_CLAUSE_END)
  {
      //// TODO : ERROR
  }
  return punct_nfa;
}

std::shared_ptr<nfa> build_keywords_nfa (std::string line, int order)
{
  if (line[line.length() - 1] != KEYWORD_CLAUSE_END
      || line.length() <= 2)
  {
      //// TODO : Error
  }
  std::shared_ptr<nfa> keywords_nfa;
  bool first_nfa = true;
  std::istringstream iss(trim(line.substr(1,line.length() - 2)));
  while (iss) {
      std::string word;
      iss >> word;
      if (word.length() == 0) continue;
      std::shared_ptr<char_set> c_s0(new char_set(word[0]));
      std::shared_ptr<nfa> nfa0(new nfa(c_s0));
      for (int i = 1; i < word.length(); i++)
      {
        std::shared_ptr<char_set> c_s(new char_set(word[i]));
        std::shared_ptr<nfa> nfa1(new nfa(c_s));
        nfa0->concat(nfa1);
      }
      nfa0->set_acceptance_states_priority(order);
      nfa0->set_acceptance_states_token_class(word);
      if (first_nfa)
      {
        keywords_nfa = nfa0;
        first_nfa = false;
      }
      else
      {
        keywords_nfa->unify(nfa0, false);
      }
  }
  return keywords_nfa;
}

std::shared_ptr<nfa> build_regex_nfa (std::string lhs, std::string rhs,
                                        std::map <std::string,
                                        std::shared_ptr<nfa>> &sym_table,
                                        int order)
{
    regular_expression regex = {lhs, rhs};
    std::shared_ptr<nfa> reg_def_nfa = evaluate_regex(regex, sym_table);
    sym_table[lhs] = reg_def_nfa;
    reg_def_nfa->set_acceptance_states_priority(order);
    reg_def_nfa->set_acceptance_states_token_class(lhs);
    return reg_def_nfa;
}


std::shared_ptr<nfa> build_combined_nfa (std::vector<std::string> rules_file_lines)
{
  std::map <std::string, std::shared_ptr<nfa>> sym_table;
  std::shared_ptr<nfa> combined_nfa;
  bool first_nfa = true;
  bool is_def;
    int order = 1;
    std::vector<std::pair<std::shared_ptr<nfa>, bool>> nfas;
  for (auto line : rules_file_lines)
  {
    std::shared_ptr<nfa> cur_nfa;
    if (line[0] == PUNCT_CLAUSE_START)
    {
        cur_nfa = build_punctations_nfa (line, order - 100);
        nfas.push_back({cur_nfa, false});
    }
    else if (line[0] == KEYWORD_CLAUSE_START)
    {
       cur_nfa = build_keywords_nfa (line, order - 100);
        nfas.push_back({cur_nfa, false});
    }
    else
    {
        bool invalid_line = false;
        for (int i = 0; i < line.length(); i++)
        {
          if (line[i] == DEFINITION_ASSIGN)
          {
              is_def = true;
              cur_nfa = build_regex_nfa (trim(line.substr(0, i)), trim(line.substr(i+1)),
                              sym_table, order);
              nfas.push_back({cur_nfa, true});
              break;
          }
          else if (line[i] == EXPRESSION_ASSIGN)
          {
              cur_nfa = build_regex_nfa (trim(line.substr(0, i)), trim(line.substr(i+1)),
                            sym_table, order);
              nfas.push_back({cur_nfa, false});
              break;
          }
        }
        if (invalid_line)
        {
          //// TODO : Error
        }
    }
    order++;
  }


    for (auto const& n : nfas)
    {
        std::shared_ptr<nfa> cur_nfa = n.first;
//        cur_nfa->visualize();
        bool is_def = n.second;

        if (first_nfa && !is_def)
        {
            combined_nfa = cur_nfa;
            first_nfa = false;
        }
        else
        {
            if (is_def){}
                // combined_nfa->unify(cur_nfa, false);
            else
                combined_nfa->unify(cur_nfa, false);
//            combined_nfa->visualize();
        }
    }
    return combined_nfa;
}


std::shared_ptr<nfa> lexical_analyzer_generator::get_lexical_analyzer_file (std::string rules_file)
{
//    SetConsoleOutputCP( CP_UTF8 );
    std::vector<std::string> rules_file_lines = read_file (rules_file);
    std::shared_ptr<nfa> combined_nfa = build_combined_nfa(rules_file_lines);

    // MOVE THIS LOGIC FROM HERE.
    for (auto s : combined_nfa->get_acceptance_states()) {
        if(s->get_type() != ACCEPTANCE)
        {
            s->set_type(ACCEPTANCE);
        }
    }
    // combined_nfa->visualize();
    return combined_nfa;
}
