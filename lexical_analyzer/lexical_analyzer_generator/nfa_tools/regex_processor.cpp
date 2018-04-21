#include "regex_processor.h"

#include <iostream>

bool is_regex_operator (char c)
{
    return c == UNION_SYMBOL || c == STAR_SYMBOL || c == PLUS_SYMBOL;
}


STACK_OPERATOR convert_to_stack_operator(char c)
{
    switch (c)
    {
        case UNION_SYMBOL:
            return UNION;
        case STAR_SYMBOL:
            return STAR;
        case PLUS_SYMBOL:
            return PLUS;
        case LEFT_PAREN_SYMBOL:
            return LEFT_PAREN;
    }
}

/**
 * checks if o1 (new operator) is higher precdance than o2 (top of stack)
 */
bool is_lower_or_equal (STACK_OPERATOR o1, STACK_OPERATOR o2)
{
    if (o2 == LEFT_PAREN) return false;
    if ((o1 == STAR || o1 == PLUS) && (o2 == STAR || o2 == PLUS))
        return true; // equal
    else if ((o1 == STAR || o1 == PLUS))
        return false;
    else if (o1 == CONCAT && (o2 == STAR || o2 == PLUS || o2 == CONCAT))
        return true;
    else if (o1 == CONCAT)
        return false;
    // UNION Case always true
    return true;
}

bool perform_operation_on_stack (std::stack<STACK_OPERATOR> &operators,
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


enum STACK_TYPE
{
    VALUE,
    OPERATOR,
    NONE
};

std::shared_ptr <nfa> evaluate_regex (regular_expression regex,
                                      std::map <std::string,
                                              std::shared_ptr<nfa>> &sym_table)
{
    std::stack <std::shared_ptr<nfa>> values;
    std::stack <STACK_OPERATOR> operators;
    std::string regex_name = regex.name;
    std::string regex_line = regex.rhs;
    std::string temp;
    STACK_TYPE last_push_type = NONE;
    for (int i = 0; i < regex_line.length(); i++)
    {
        if (is_regex_operator(regex_line[i]) || regex_line[i] == LEFT_PAREN_SYMBOL)
        {
            while (regex_line[i] != LEFT_PAREN_SYMBOL && !operators.empty()
                   && is_lower_or_equal (convert_to_stack_operator(regex_line[i]), operators.top()))
            {
                if (!perform_operation_on_stack (operators, values))
                    return nullptr;
                else {
                    last_push_type = VALUE;
                }
                if (operators.empty()) break;
            }
            if (regex_line[i] == LEFT_PAREN_SYMBOL && last_push_type == VALUE && !values.empty()) operators.push(CONCAT);
            operators.push(convert_to_stack_operator(regex_line[i]));
            last_push_type = OPERATOR;
        }
        else if (regex_line[i] == RIGHT_PAREN_SYMBOL)
        {
            while (operators.top() != LEFT_PAREN)
            {
                if (!perform_operation_on_stack (operators, values))
                    return nullptr;
                else {
                    last_push_type = VALUE;
                }
                if (operators.empty()) return nullptr;
            }
            operators.pop(); // pop left paren
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
            if (!is_regex_operator(regex_line[i]) || regex_line[i] == ESC)
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
            last_push_type = VALUE;
        }
        else if (regex_line[i] == SPACE || (regex_line[i] == ESC))
        {
            if (regex_line[i] == ESC && (i < regex_line.length() - 1)
                && regex_line[i + 1] == LAMBDA)
            {
                if (last_push_type == VALUE && !values.empty()) operators.push(CONCAT);
                values.push(build_nfa(EPS));
                i++;
                last_push_type = VALUE;
            }
            else if (regex_line[i] == ESC && (i < regex_line.length() - 1))
            {
                if (last_push_type == VALUE && !values.empty()) operators.push(CONCAT);
                values.push(build_nfa(regex_line[++i]));
                last_push_type = VALUE;
            }
            else if (regex_line[i] == ESC)
            {
                return nullptr;
            }
            continue;
        }
        else
        {
            // char
            while (!is_regex_operator(regex_line[i]) && regex_line[i] != LEFT_PAREN_SYMBOL
                   && regex_line[i] != RIGHT_PAREN_SYMBOL && regex_line[i] != RANGE_SEP
                   && regex_line[i] != SPACE && regex_line[i] != ESC)
            {
                temp += regex_line[i++];
                if (i == regex_line.length())
                    break;
            }
            i--;
            if (sym_table.count(temp) == 0)
            {
                int temp_size = temp.length();
                std::shared_ptr<nfa> nfa1 = build_nfa(temp[0]); // nfa(1)
                char temp_last = temp[temp_size - 1];
                temp = temp.substr(1, temp_size - 2); // abcd* only concats abc
                for (auto const& c : temp)
                {
                    std::shared_ptr<nfa> nfa2 = build_nfa(c);
                    nfa1->concat(nfa2);
                }
                if ((last_push_type == VALUE && !values.empty())
                    || (last_push_type == OPERATOR
                       && (operators.top() == PLUS || operators.top() == STAR)))
                {
                    perform_operation_on_stack (operators, values);
                    operators.push(CONCAT);
                }
                values.push(nfa1);
                last_push_type = VALUE;
                if (temp_last != '\0' && temp_size - 1 != 0)
                {
                    operators.push(CONCAT);
                    std::shared_ptr<nfa> nfa_temp_last = build_nfa(temp_last);
                    values.push(nfa_temp_last);
                    last_push_type = VALUE;
                }

            }
            else
            {
                if (last_push_type == VALUE && !values.empty()) operators.push(CONCAT);
                std::shared_ptr<nfa> copy_nfa = sym_table[temp]->copy();
                values.push(copy_nfa);
                last_push_type = VALUE;
            }
            temp.clear();
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
