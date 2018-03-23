#include "regex_processor.h"

#include <iostream>

bool is_operator (char c)
{
  return c == UNION || c == STAR || c == PLUS;
}


/**
 * checks if c1 (new operator) is higher precdance than c2 (top of stack)
 */

bool is_lower_or_equal (char c1, char c2)
{
  if ((c1 == STAR || c1 == PLUS) && (c2 == STAR || c2 == PLUS))
    return true; // equal
  else if ((c1 == STAR || c1 == PLUS))
    return false;
  else if (c1 == CONCAT && (c2 == STAR || c2 == PLUS || c2 == CONCAT))
    return true;
  else if (c1 == CONCAT)
    return false;
  /// UNION Case always true
  return true;
}

bool perform_operation_on_stack (std::stack<char> &operators,
                                 std::stack<std::shared_ptr<nfa>> &values)
{
  if (values.empty()) return false;
  std::shared_ptr<nfa> rhs_nfa = values.top();
  values.pop();
  std::shared_ptr<nfa> lhs_nfa;
  char op = operators.top();
  operators.pop();
  switch (op) {
    case CONCAT:
    if (values.empty()) return false;
    lhs_nfa = values.top();
    values.pop();
    lhs_nfa->concat(rhs_nfa);
    values.push(lhs_nfa);
    break;
    case UNION:
    if (values.empty()) return false;
    lhs_nfa = values.top();
    values.pop();
    lhs_nfa->unify(rhs_nfa);
    values.push(lhs_nfa);
    break;
    case STAR:
    rhs_nfa->star();
    values.push(rhs_nfa);
    break;
    case PLUS:
    rhs_nfa->plus();
    values.push(rhs_nfa);
    default:
    break;
  }
  return true;
}

std::shared_ptr<nfa> build_nfa(char lower, char upper)
{
  std::shared_ptr<char_set> c_s(new char_set());
  c_s->add_range(lower, upper);
  std::shared_ptr<nfa> nfa_c(new nfa(c_s));
  return nfa_c;
}


std::shared_ptr<nfa> build_nfa(char c)
{
  std::shared_ptr<char_set> c_s(new char_set());
  if (c != EPS)
    c_s->add_character(c);
  std::shared_ptr<nfa> nfa_c(new nfa(c_s));
  return nfa_c;
}

std::shared_ptr <nfa> evaluate_regex (regular_expression regex,
                                      std::map <std::string,
                                      std::shared_ptr<nfa>> &sym_table)
{
    std::stack <std::shared_ptr<nfa>> values;
    std::stack <char> operators;
    std::string regex_name = regex.name;
    std::string regex_line = regex.rhs;
    std::string temp = "";
    for (int i = 0; i < regex_line.length(); i++)
    {
        if (is_operator(regex_line[i]) || regex_line[i] == LEFT_PAREN)
        {
          while (regex_line[i] != LEFT_PAREN && !operators.empty()
                 && is_lower_or_equal (regex_line[i], operators.top()))
          {
            if (!perform_operation_on_stack (operators, values))
              return nullptr;
            if (operators.empty()) break;
          }
          operators.push(regex_line[i]);
        }
        else if (regex_line[i] == RIGHT_PAREN)
        {
          while (operators.top() != LEFT_PAREN)
          {
            if (!perform_operation_on_stack (operators, values))
              return nullptr;
            if (operators.empty()) return nullptr;
          }
          operators.pop();
        }
        else if (regex_line[i] == RANGE_SEP)
        {
          if (values.empty()) return nullptr;
          char lower;
          std::map <char, bool> mp = (values.top())->get_start_state()->get_char_set()->get_characters();
          if (mp.size() != 1) return nullptr;
          for (auto const& c : mp)
          {
            lower = c.first;
          }
          values.pop();
          char upper;
          while (i < regex_line.length() - 1 && regex_line[++i] == SPACE);
          if (i == regex_line.length()) return nullptr;
          if (!is_operator(regex_line[i]) || regex_line[i] == ESC)
          {
            if (regex_line[i] == ESC && i < regex_line.length() - 1)
            {
              if (regex_line[i + 1] == LAMBDA) return nullptr;
              upper = regex_line[++i];
            }
            else
            {
              upper = regex_line[i];
            }
          }
          if (lower > upper) return nullptr; // TODO : Throw Exception
          values.push (build_nfa(lower, upper));
        }
        else if (regex_line[i] == SPACE || (regex_line[i] == ESC))
        {
          if (regex_line[i] == ESC && (i < regex_line.length() - 1)
              && regex_line[i + 1] == LAMBDA)
              values.push(build_nfa (EPS));
          else if (regex_line[i] == ESC && (i < regex_line.length() - 1))
              values.push(build_nfa (regex_line[++i]));
          else if (regex_line[i] == ESC)
          {
            return nullptr;
          }
          continue;
        }
        else
        {
          // char
          while (!is_operator(regex_line[i]) && regex_line[i] != LEFT_PAREN
                 && regex_line[i] != RIGHT_PAREN && regex_line[i] != RANGE_SEP)
          {
            temp += regex_line[i++];
            if (i == regex_line.length())
                break;
          }
          if (sym_table.count(temp) == 0)
          {
            i--;
            std::shared_ptr<nfa> nfa1 = build_nfa(temp[0]); // nfa(1)

            std::shared_ptr<char_set> cs = nfa1->get_start_state()->get_char_set();
            std::cout << (cs == nullptr) << std::endl;
            temp = temp.substr(1, temp.length() - 1); // abcd* only concats abc
            for (auto const& c : temp)
            {
                std::shared_ptr<nfa> nfa2 = build_nfa(c);
                nfa1->concat(nfa2);
            }
            values.push(nfa1);
          }
          else
          {
            values.push(sym_table[temp]);
          }
        }
    }
    while (!operators.empty())
    {
      if (operators.top() == LEFT_PAREN)
          return nullptr;
          if (!perform_operation_on_stack (operators, values))
            return nullptr;
    }
    return values.top();
}
