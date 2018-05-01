#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <memory>
#include <cstdlib>

#include "lexical_analyzer/lexical_tokenizer/lexical_tokenizer.h"
#include "syntax_analyzer/predictive_parser.h"
#include "lexical_analyzer/lexical_analyzer_generator/lexical_analyzer_generator.h"

void err_argc ();
void err_option ();
void err_no_file_exists (char *);
void help ();
bool file_exists (char *);
void print_output (std::vector<token> &);

void lex_generate_tokenize (char *, char *, std::vector<token> &);
void lex_tokenize (char *, char *, std::vector<token> &);

void parse_generate_tokenize (char *, char *, char *, std::vector<token> &);
void parse_tokenize (char *, char *, char *, std::vector<token> &);

std::ofstream sym_tab_file;
std::ofstream token_file;
std::ofstream log_file;

int main (int argc, char *argv[]) {
    if (argc > 6 || argc == 1 || argc == 3) {
        err_argc ();
    }
    std::vector<token> token_vec;

    if (!strcmp (argv[1], "--help")) {
        help ();
    } else if (!strcmp (argv[1], "--lex")) {
        if (argc == 5 && !strcmp (argv[2], "-g")) {
            lex_generate_tokenize (argv[3], argv[4], token_vec);
        } else if (argc == 4) {
            lex_tokenize (argv[2], argv[3], token_vec);
        } else {
            err_argc ();
        }
    } else if (!strcmp (argv[1], "--parse")) {
        if (argc == 6 && !strcmp (argv[2], "-g")) {
            parse_generate_tokenize (argv[3], argv[4], argv[5], token_vec);
        } else if (argc == 5) {
            parse_tokenize (argv[2], argv[3], argv[4],token_vec);
        } else {
            err_argc ();
        }
    } else {
        err_option ();
    }
    sym_tab_file.open ("symbol-table.txt");
    token_file.open ("token-file.txt");
    log_file.open ("compiler.log");

    print_output (token_vec);

    sym_tab_file.close ();
    token_file.close ();
    log_file.close ();
    return 0;
}

 void err_argc () {
     std::cout << "Invalid number of arguments.\n"
         << "Please enter \"./compiler --help\" "
         << "to know the supported options in this version.\n";
     exit (EXIT_FAILURE);
}
 
 void err_option () {
     std::cout << "Unsupported option.\n"
         << "Please enter \"./compiler --help\" "
         << "to know the supported options in this version.\n";
     exit (EXIT_FAILURE);
}
 
 void err_no_file_exists (char *file_name) {
     std::cout << file_name << ":  File doesn't exists.\n";
     exit (EXIT_FAILURE);
}

void help () {
    std::cout << "\n./compiler [OPTION] [FLAG] [ARG ...]\n\n" 
        << "Currently there is two supported options each with 2 variations:\n\n"
        << "--lex --- Performs lexical analysis only on the given source code using the given rules file.\n\n"
        << "\t-g --- A flag for building lexical analyzer generator transition table from <rules-file>"
        << "and use it in tokenizing the input source code file.\n\n"
        << "\t \" ./compiler --lex -g <rules-file> <source-code-file>. \"\n"
        << "\t \" ./compiler --lex <transition-table-file> <source-code-file>. \"\n\n"
        << "--parse --- Performs syntax analysis only on the given source code using the given grammar"
        << "file and the output token file from the lexical analyzer.\n\n"
        << "\t-g --- A flag for building lexical analyzer generator transition table from <rules-file>"
        << "and use it in tokenizing the input source code\n\t       file then use these tokens in parsing the" 
        << "<source-code-file> according to the given <cfg-file>\n\n"
        << "\t \" ./compiler --parse -g <rules-file> <source-code-file> <cfg-file>. \"\n"
        << "\t \" ./compiler --parse <transition-table-file> <source-code-file> <cfg-file>. \"\n\n"
        << "NOTE: This option will write its output in default files in the current directory.\n\n";
}

bool file_exists (char *file_name) {
    std::ifstream in_file(file_name);
    return in_file.good();
}

void lex_generate_tokenize (char *rules_file, char *code_file
                                            , std::vector<token> &token_vec) {
    if (!file_exists (rules_file)) {
        err_no_file_exists (rules_file);
    }

    if (!file_exists (code_file)) {
        err_no_file_exists (code_file);
    }

    lexical_analyzer_generator gen = lexical_analyzer_generator();
    auto combined_nfa = gen.get_lexical_analyzer_file(std::string(rules_file));
    std::shared_ptr<dfa> dfa_ptr(new dfa(combined_nfa));
    auto minimized_dfa = dfa_ptr->minimize();
    minimized_dfa->draw_trans_table();
    std::shared_ptr<lexical_tokenizer> lex = std::make_shared<lexical_tokenizer>(
                                lexical_tokenizer ("transition_table.txt", code_file));
    token t;
    while (lex->get_next_token (t)) {
        token_vec.push_back (token (t));
    }
}

void lex_tokenize (char *transition_table_file, char *code_file
                                    , std::vector<token> &token_vec) {
    if (!file_exists (transition_table_file)) {
        err_no_file_exists (transition_table_file);
    }

    if (!file_exists (code_file)) {
        err_no_file_exists (code_file);
    }

    std::shared_ptr<lexical_tokenizer> lex = std::make_shared<lexical_tokenizer>(
                                    lexical_tokenizer (transition_table_file, code_file));
    token t;
    while (lex->get_next_token (t)) {
        token_vec.push_back (token (t));
    }
}

void parse_generate_tokenize (char *rules_file, char *code_file, char *cfg_file
        , std::vector<token> &token_vec)
{
    lex_generate_tokenize(rules_file, code_file, token_vec);

    predictive_parser parser(cfg_file, token_vec);

    int err_cnt;
    if ((err_cnt = parser.parse()) == 0) {
        std::cout << "\033[32m" << "PARSING SUCCESS! NO ERRORS OCCURED." << std::endl;
    } else {
        std::cout << "\033[31m" << "PARSING ERRORS COUNT: " << err_cnt << std::endl;
    }

    // to restore the default color
    // std::cout << "\033[0m";

    parser.write_debug_stack("debug_stack.log");
    parser.write_derivations("actions_output.log");
}

void parse_tokenize (char *transition_table_file, char *code_file, char *cfg_file
        , std::vector<token> &token_vec)
{
    lex_tokenize(transition_table_file, code_file, token_vec);

    predictive_parser parser(cfg_file, token_vec);

    int err_cnt;
    if ((err_cnt = parser.parse()) == 0) {
        std::cout << "\033[32m" << "PARSING SUCCESS! NO ERRORS OCCURED." << std::endl;
    } else {
        std::cout << "\033[31m" << "PARSING ERRORS COUNT: " << err_cnt << std::endl;
    }

    parser.write_debug_stack("debug_stack.log");
    parser.write_derivations("actions_output.log");
}

void print_output (std::vector<token> &token_vec) {
    std::map<std::string, bool> sym_tab_map;
    log_file << std::left << std::setw (20) << "Match State" <<
        std::left << std::setw (40) << "Lexeme" << std::left << std::setw (30)
            << "Token Class" << "Position" << '\n';
    log_file << std::left << std::setw (20) << "-----------" <<
        std::left << std::setw (40) << "------" << std::left << std::setw (30)
            << "-----------" << "--------" << '\n';
    for (auto t : token_vec) {
        if (t.token_class.empty ()) {
            log_file << std::left << std::setw(20) << "[UNMATCHED]" <<
                std::left << std::setw(40) << t.lexeme << std::setw (30)
                << t.token_class << t.str_pos << '\n';
        } else {
            log_file << std::left << std::setw(20) << "[MATCHED]" <<
                std::left << std::setw(40) << t.lexeme << std::setw (30)
                << t.token_class << t.str_pos << '\n';
            if (!sym_tab_map[t.lexeme]) {
                sym_tab_file << std::left << std::setw(40) << t.lexeme << t.token_class << '\n';
                sym_tab_map[t.lexeme] = true;
            }
            token_file << t.token_class << '\n';
        }
    }
}
