 #include "lexical_analyzer/lexical_analyzer.h"
 #include "lexical_analyzer_generator/lexical_analyzer_generator.h"
#include "tests/lexical_analyzer_generator/dfa_construction.h"
#include <iostream>
 #include <string.h>
 #include <fstream>
 #include <memory>

 void err_argc ();
 void err_option ();
 void err_no_file_exists (char *);
 void help ();
 bool file_exists (char *);
 void print_output (std::vector<token> &);
 void lex_generate_tokenize (char *, char *, std::vector<token> &);
 void lex_tokenize (char *, char *, std::vector<token> &);

 std::ofstream sym_tab_file;
 std::ofstream token_file;
 std::ofstream log_file;

 int main (int argc, char *argv[]) {
     if (argc > 5 || argc == 1 || argc == 3) {
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
     std::cout << "Currently there is one supported option with 2 variations:\n\n"
         << "--lex --- Performs lexical analysis only on the given source code using the given rules file.\n\n"
         << "\t-g --- A flag for building lexical analyzer generator transition table from <rules-file>"
         << "and use it in tokenizing the input source code file.\n\n"
         << "\t \" ./compiler --lex -g <rules-file> <source-code-file>. \"\n"
         << "\t \" ./compiler --lex <transition-table-file> <source-code-file>. \"\n\n"
         << "NOTE: This option will write its output in default files in the current directory.\n\n";
        
     return;
 }

 bool file_exists (char *file_name) {
     std::ifstream in_file(file_name);
     return in_file.good();
 }

 void lex_generate_tokenize (char *rules_file, char *code_file
                                             , std::vector<token> &token_vec) {
     lexical_analyzer_generator gen = lexical_analyzer_generator();
     auto combined_nfa = gen.get_lexical_analyzer_file(std::string(rules_file));
     auto dfa_ptr = convert_nfa_dfa(combined_nfa);
     auto min_dfa = minimize(dfa_ptr);
     min_dfa->visualize();
     draw_trans_table(min_dfa);

     // Continue.
 }

 void lex_tokenize (char *transition_table_file, char *code_file
                                     , std::vector<token> &token_vec) {
     if (!file_exists (transition_table_file)) {
         err_no_file_exists (transition_table_file);
     }

     if (!file_exists (code_file)) {
         err_no_file_exists (code_file);
     }

     std::shared_ptr<lexical_analyzer> lex = std::make_shared<lexical_analyzer>(
                                     lexical_analyzer (transition_table_file, code_file));

 //    std::vector<std::shared_ptr<dfa_state>> vec;
 //    vec = lex->get_dfa ()->get_dfa_states ();

 //    std::cout << "Number of states: " << vec.size () << std::endl;

 //    std::cout << "--------------------------" << std::endl;

 //     for (int i=0 ; i < vec.size () ; i++) {
 //        std::cout << "State ID: " <<vec[i]->get_id() << " State Type: "
 //                        << vec[i]->get_type() << " State Token Class: " << vec[i]->get_token_class () << std::endl;
 //     }

     lex->get_dfa ()->visualize ();
     token t;
     while (lex->get_next_token (t)) {
         token_vec.push_back (token (t));
     }
 }

 void print_output (std::vector<token> &token_vec) {
     for (auto t : token_vec) {
         if (t.token_class.empty ()) {
             log_file << "[UNMATCHED]" << '\t' <<
                 t.lexeme << '\t' << t.str_pos << '\n';
         } else {
             log_file << "[MATCHED]" << '\t' <<
                 t.lexeme << '\t' << t.token_class << '\t'
                     << t.str_pos << '\n';
             sym_tab_file << t.lexeme << '\t' << t.token_class << '\n';
             token_file << t.token_class << '\n';
         }
     }
 }
