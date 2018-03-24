// #include <iostream>
// #include <memory>
// #include <queue>
// #include <iostream>
// #include <set>
// #include <climits>

// #include "../../lexical_analyzer_generator/finite_automata/finite_automata.h"
// #include "../../lexical_analyzer_generator/finite_automata/state.h"
// #include "../../lexical_analyzer_generator/finite_automata/nfa.h"
// #include "../../lexical_analyzer_generator/finite_automata/dfa.h"
// #include "../../lexical_analyzer_generator/finite_automata/nfa_state.h"
// #include "../../lexical_analyzer_generator/finite_automata/dfa_state.h"
// #include "../../lexical_analyzer_generator/nfa_tools/regex_processor.h"
// #include "../../lexical_analyzer_generator/lexical_analyzer_generator.h"

// #define EPSILON ""

// bool dead_state(const std::shared_ptr<dfa_state> &shared_ptr);

// void draw_trans_table(std::shared_ptr<dfa> dfa)
// {
//     std::shared_ptr<std::ofstream> out_file(new std::ofstream());
//     out_file->open("transition_table.txt");
//     *out_file << "Total\tStates:\t" << dfa->get_total_states() << "\n";
//     *out_file << "Start\tState(s):\t{" << dfa->get_start_state()->get_id() << "}\n";
//     *out_file << "Acceptance\tState(s):\t" << dfa->get_acceptance_states().size() << "\n";
//     for (auto acc_state : dfa->get_acceptance_states())
//     {
//         *out_file << "{" << acc_state->get_id() << "}\t" << acc_state->get_token_class() << "\n";
//     }
//     *out_file << "State\t";
//     for (auto inp_char : dfa->get_alphabet()->get_characters())
//     {
//         *out_file << inp_char.first << "\t";
//     }
//     for (auto inp_range : dfa->get_alphabet()->get_ranges())
//     {
//         *out_file << inp_range->get_range_string() << "\t";
//     }
//     *out_file << "\n";
//     for (auto state : dfa->get_dfa_states())
//     {
//         *out_file << "{" << state->get_id() << "}\t";
//         for (auto inp_char : dfa->get_alphabet()->get_characters())
//         {
//             auto target_state = state->get_next_state(inp_char.first);
//             if (target_state == nullptr)
//             {
//                 *out_file << "{-}\t";
//             }
//             else
//             {
//                 *out_file << "{" << target_state->get_id() << "}\t";
//             }
//         }
//         for (auto inp_range : dfa->get_alphabet()->get_ranges())
//         {
//             auto target_state = state->get_next_state(inp_range->get_range_string());
//             if (target_state == nullptr)
//             {
//                 *out_file << "{-}\t";
//             }
//             else
//             {
//                 *out_file << "{" << target_state->get_id() << "}\t";
//             }
//         }
//         *out_file << "\n";
//     }
// }

// std::shared_ptr<nfa> build_complex_nfa()
// {
//     std::shared_ptr<char_set> eps(new char_set()), c_i(new char_set()), c_f(new char_set()), c_t(new char_set()),
//             c_h(new char_set()), c_e(new char_set()), c_n(new char_set()), c_l(new char_set()), c_s(new char_set()),
//             c_less(new char_set()), c_bigger(new char_set()), c_equals(new char_set()), c_eq_bigger(new char_set()),
//             c_let(new char_set()), c_dig(new char_set()), c_let_dig(new char_set());
//     c_i->add_character('i');
//     c_f->add_character('f');
//     c_t->add_character('t');
//     c_h->add_character('h');
//     c_e->add_character('e');
//     c_n->add_character('n');
//     c_l->add_character('l');
//     c_s->add_character('s');
//     c_less->add_character('<');
//     c_bigger->add_character('>');
//     c_equals->add_character('=');
//     c_eq_bigger->add_character('=');
//     c_eq_bigger->add_character('>');
//     c_let->add_range('a', 'z');
//     c_dig->add_range('0', '9');

//     // States
//     std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, eps));
//     std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, c_i));
//     std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, c_f));
//     std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, ACCEPTANCE, eps)); // if
//     std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, c_t));
//     std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, INTERMEDIATE, c_h));
//     std::shared_ptr<nfa_state> s6 = std::make_shared<nfa_state>(nfa_state (6, INTERMEDIATE, c_e));
//     std::shared_ptr<nfa_state> s7 = std::make_shared<nfa_state>(nfa_state (7, INTERMEDIATE, c_n));
//     std::shared_ptr<nfa_state> s8 = std::make_shared<nfa_state>(nfa_state (8, ACCEPTANCE, eps)); // then
//     std::shared_ptr<nfa_state> s9 = std::make_shared<nfa_state>(nfa_state (9, INTERMEDIATE, c_e));
//     std::shared_ptr<nfa_state> s10 = std::make_shared<nfa_state>(nfa_state (10, INTERMEDIATE, c_l));
//     std::shared_ptr<nfa_state> s11 = std::make_shared<nfa_state>(nfa_state (11, INTERMEDIATE, c_s));
//     std::shared_ptr<nfa_state> s12 = std::make_shared<nfa_state>(nfa_state (12, INTERMEDIATE, c_e));
//     std::shared_ptr<nfa_state> s13 = std::make_shared<nfa_state>(nfa_state (13, ACCEPTANCE, eps)); // else
//     std::shared_ptr<nfa_state> s14 = std::make_shared<nfa_state>(nfa_state (14, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s15 = std::make_shared<nfa_state>(nfa_state (15, INTERMEDIATE, c_less));
//     std::shared_ptr<nfa_state> s16 = std::make_shared<nfa_state>(nfa_state (16, ACCEPTANCE, c_eq_bigger)); // <
//     std::shared_ptr<nfa_state> s17 = std::make_shared<nfa_state>(nfa_state (17, INTERMEDIATE, c_bigger));
//     std::shared_ptr<nfa_state> s18 = std::make_shared<nfa_state>(nfa_state (18, ACCEPTANCE, c_equals)); // >
//     std::shared_ptr<nfa_state> s19 = std::make_shared<nfa_state>(nfa_state (19, INTERMEDIATE, c_equals));
//     std::shared_ptr<nfa_state> s20 = std::make_shared<nfa_state>(nfa_state (20, ACCEPTANCE, eps)); // relop
//     std::shared_ptr<nfa_state> s21 = std::make_shared<nfa_state>(nfa_state (21, INTERMEDIATE, c_let));
//     std::shared_ptr<nfa_state> s22 = std::make_shared<nfa_state>(nfa_state (22, ACCEPTANCE, c_let_dig)); // id
//     std::shared_ptr<nfa_state> s23 = std::make_shared<nfa_state>(nfa_state (23, INTERMEDIATE, c_dig));
//     std::shared_ptr<nfa_state> s24 = std::make_shared<nfa_state>(nfa_state (24, ACCEPTANCE, c_dig)); // num

//     // Transitions
//     s0->insert_transition(EPSILON, s1);
//     s0->insert_transition(EPSILON, s4);
//     s0->insert_transition(EPSILON, s9);
//     s0->insert_transition(EPSILON, s14);
//     s0->insert_transition(EPSILON, s21);
//     s0->insert_transition(EPSILON, s23);
//     s1->insert_transition("i", s2);
//     s2->insert_transition("f", s3);
//     s4->insert_transition("t", s5);
//     s5->insert_transition("h", s6);
//     s6->insert_transition("e", s7);
//     s7->insert_transition("n", s8);
//     s9->insert_transition("e", s10);
//     s10->insert_transition("l", s11);
//     s11->insert_transition("s", s12);
//     s12->insert_transition("e", s13);
//     s14->insert_transition(EPSILON, s15);
//     s14->insert_transition(EPSILON, s17);
//     s14->insert_transition(EPSILON, s19);
//     s15->insert_transition("<", s16);
//     s16->insert_transition("=", s20);
//     s16->insert_transition(">", s20);
//     s17->insert_transition(">", s18);
//     s18->insert_transition("=", s20);
//     s19->insert_transition("=", s20);
//     s21->insert_transition("a-z", s22);
//     s22->insert_transition("a-z", s22);
//     s22->insert_transition("0-9", s22);
//     s23->insert_transition("0-9", s24);
//     s24->insert_transition("0-9", s24);

//     std::vector<std::shared_ptr<state>> acceptance_states;
//     acceptance_states.push_back(s3);
//     acceptance_states.push_back(s8);
//     acceptance_states.push_back(s13);
//     acceptance_states.push_back(s16);
//     acceptance_states.push_back(s18);
//     acceptance_states.push_back(s20);
//     acceptance_states.push_back(s22);
//     acceptance_states.push_back(s24);
//     std::shared_ptr<nfa> my_nfa(new nfa(s0, acceptance_states, 25));
//     return my_nfa;
// }

// std::shared_ptr<nfa> build_nfa1() {
//     std::shared_ptr<char_set> c_0(new char_set()), c_1(new char_set()), eps(new char_set),
//                 c_01(new char_set());
//     c_0->add_character('0');
//     c_1->add_character('1');
//     c_01->add_character('0');
//     c_01->add_character('1');


//     std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, eps));
//     std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, c_01));
//     std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, c_0));
//     std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, INTERMEDIATE, c_01));
//     std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, c_0));
//     std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, INTERMEDIATE, c_1));
//     std::shared_ptr<nfa_state> s6 = std::make_shared<nfa_state>(nfa_state (6, ACCEPTANCE, eps));

//     s6->set_token_class("HALLELUIAH");
//     s6->set_priority(1);

//     s0->insert_transition (EPSILON, s1);
//     s0->insert_transition (EPSILON, s2);
//     s0->insert_transition (EPSILON, s4);
//     s1->insert_transition (EPSILON, s2);
//     s1->insert_transition ("0", s3);
//     s1->insert_transition ("1", s3);
//     s2->insert_transition (EPSILON, s4);
//     s2->insert_transition ("0", s3);
//     s3->insert_transition ("1", s5);
//     s3->insert_transition (EPSILON, s6);
//     s3->insert_transition ("0", s4);
//     s4->insert_transition ("0", s4);
//     s4->insert_transition (EPSILON, s1);
//     s5->insert_transition (EPSILON, s6);
//     s5->insert_transition ("1", s4);


//     std::vector<std::shared_ptr<state>> acceptance_states;
//     acceptance_states.push_back(s6);
//     std::shared_ptr<nfa> my_nfa(new nfa(s0, acceptance_states, 7));
//     return my_nfa;
// }

// std::shared_ptr<nfa> build_nfa()
// {
//     std::shared_ptr<char_set> a_char_set(new char_set());
//     a_char_set->add_character('a');

//     std::shared_ptr<char_set> b_char_set(new char_set());
//     b_char_set->add_character('b');

//     std::shared_ptr<char_set> eps(new char_set());

//     std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, eps));
//     std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, a_char_set));
//     std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, b_char_set));
//     std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s6 = std::make_shared<nfa_state>(nfa_state (6, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s7 = std::make_shared<nfa_state>(nfa_state (7, INTERMEDIATE, a_char_set));
//     std::shared_ptr<nfa_state> s8 = std::make_shared<nfa_state>(nfa_state (8, INTERMEDIATE, b_char_set));
//     std::shared_ptr<nfa_state> s9 = std::make_shared<nfa_state>(nfa_state (9, INTERMEDIATE, b_char_set));
//     std::shared_ptr<nfa_state> s10 = std::make_shared<nfa_state>(nfa_state (10, ACCEPTANCE, eps));

//     s0->insert_transition (EPSILON, s1);
//     s0->insert_transition (EPSILON, s7);
//     s1->insert_transition (EPSILON, s2);
//     s1->insert_transition (EPSILON, s4);
//     s2->insert_transition ("a", s3);
//     s3->insert_transition (EPSILON, s6);
//     s4->insert_transition ("b", s5);
//     s5->insert_transition (EPSILON, s6);
//     s6->insert_transition (EPSILON, s1);
//     s6->insert_transition (EPSILON, s7);
//     s7->insert_transition ("a", s8);
//     s8->insert_transition ("b", s9);
//     s9->insert_transition ("b", s10);

//     std::vector<std::shared_ptr<state>> acceptance_states;
//     acceptance_states.push_back(s10);
//     std::shared_ptr<nfa> my_nfa(new nfa(s0, acceptance_states, 11));
//     return my_nfa;
// }

// std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, const char inp)
// {
//     std::set<std::shared_ptr<nfa_state>> reachable_states;
//     for (const auto &state : nfa_states)
//     {
//         std::vector<std::shared_ptr<nfa_state>> curr_reached = state->get_next_state(inp);
//         for (const auto &curr : curr_reached)
//         {
//             reachable_states.insert(curr);
//         }
//     }
//     return reachable_states;
// }

// std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, const std::string &inp)
// {
//     std::set<std::shared_ptr<nfa_state>> reachable_states;
//     for (const auto &state : nfa_states)
//     {
//         std::vector<std::shared_ptr<nfa_state>> curr_reached = state->get_next_state(inp);
//         for (const auto &curr : curr_reached)
//         {
//             reachable_states.insert(curr);
//         }
//     }
//     return reachable_states;
// }

// std::set<std::shared_ptr<nfa_state>> e_closure(const std::set<std::shared_ptr<nfa_state>> nfa_states)
// {
//     std::set<std::shared_ptr<nfa_state>> reachable_states = nfa_states;
//     std::stack<std::shared_ptr<nfa_state>> nfa_states_stack;
//     std::map<state_id, bool> visited;
//     for (const auto &state : nfa_states)
//     {
//         nfa_states_stack.push(state);
//         visited[state->get_id()] = true;
//     }
//     while (!nfa_states_stack.empty())
//     {
//         auto curr_nfa_state = static_cast<std::shared_ptr<nfa_state> &&>(nfa_states_stack.top());
//         nfa_states_stack.pop();
//         std::vector<std::shared_ptr<nfa_state>> vec = curr_nfa_state->get_next_state('\0');
//         for (const auto &curr : vec)
//         {
//             if (!visited[curr->get_id()])
//             {
//                 visited[curr->get_id()] = true;
//                 reachable_states.insert(curr);
//                 nfa_states_stack.push(curr);
//             }
//         }
//     }
//     return reachable_states;
// }

// std::shared_ptr<dfa> convert_nfa_dfa(const std::shared_ptr<nfa> &nfa_ptr) {
//     std::shared_ptr<dfa> dfa_ptr(new dfa());
//     dfa_ptr->set_alphabet(nfa_ptr->get_alphabet());
// //    std::cout << "ALPHABET: ";
// //    for (auto ch : dfa_ptr->get_alphabet()->get_characters()) {
// //        std::cout << ch.first << " ";
// //    }
// //    for (auto x : dfa_ptr->get_alphabet()->get_ranges()) {
// //        std::cout << x->get_range_string() << " ";
// //    }
// //    exit(0);
//     std::set<std::shared_ptr<nfa_state>> vec;
//     vec.insert((std::shared_ptr<nfa_state> &&) nfa_ptr->get_start_state());
//     std::shared_ptr<dfa_state> init_dfa_state(new dfa_state(e_closure(vec),
//                                                               static_cast<state_id>(dfa_ptr->get_total_states())));
//     dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
//     dfa_ptr->set_start_state(init_dfa_state);
//     dfa_ptr->add_state(init_dfa_state);

//     std::shared_ptr<dfa_state> curr_state;
//     while ((curr_state = dfa_ptr->get_unmarked_state()) != nullptr)
//     {
//         curr_state->set_marked(true);
// //        std::cout << "Current State = " << curr_state->get_id() << std::endl;
// //        for (auto curr : curr_state->get_composing_nfa_states()) {
// //            std::cout << curr->get_id() << " ";
// //        }
// //        std::cout << std::endl;
//         for (const auto &curr_char : dfa_ptr->get_alphabet()->get_characters())
//         {
//             std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(),
//                                                                               curr_char.first)),
//                                     static_cast<state_id>(dfa_ptr->get_total_states())));
//             if (new_state->get_composing_nfa_states().empty()) { // dead state
//                 continue;
//             }
//             if (new_state->equals(curr_state))
//             {
//                 curr_state->insert_transition(dfa_ptr->get_alphabet()->get_string(curr_char.first), curr_state);
//                 continue;
//             }
// //            std::cout << "New State = " << new_state->get_id() << std::endl;
// //            for (auto curr : new_state->get_composing_nfa_states()) {
// //                std::cout << curr->get_id() << " ";
// //            }
// //            std::cout << std::endl;
//             if (!dfa_ptr->contains(new_state))
//             {
//                 dfa_ptr->add_state(new_state);
//                 dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
//                 if (new_state->get_type() == ACCEPTANCE)
//                 {
//                     dfa_ptr->add_acceptance_state(new_state);
//                     int max_pri = INT_MAX;
//                     std::string token_class;
//                     for (auto s : new_state->get_composing_nfa_states())
//                     {
//                         if (s->get_token_class_priority() < max_pri)
//                         {
//                             token_class = s->get_token_class();
//                             max_pri = s->get_token_class_priority();
//                         }
//                     }
//                     new_state->set_token_class(token_class);
//                 }
//             }
//             else
//             {
//                 auto existing_states = dfa_ptr->get_dfa_states();
//                 for (auto st : existing_states)
//                 {
//                     if (st->equals(new_state))
//                     {
//                         new_state = st;
//                         break;
//                     }
//                 }
//             }
//             curr_state->insert_transition(dfa_ptr->get_alphabet()->get_string(curr_char.first), new_state);
//         }
//         for (const auto &curr_range : dfa_ptr->get_alphabet()->get_ranges())
//         {
//             std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(),
//                                                                               curr_range->get_range_string())),
//                                                                static_cast<state_id>(dfa_ptr->get_total_states())));
//             // dead state
//             if (new_state->get_composing_nfa_states().empty()) { // dead state
//                 continue;
//             }
//             if (new_state->equals(curr_state))
//             {
//                 curr_state->insert_transition(curr_range->get_range_string(), curr_state);
//                 continue;
//             }
// //            std::cout << "New State = " << new_state->get_id() << std::endl;
// //            for (auto curr : new_state->get_composing_nfa_states()) {
// //                std::cout << curr->get_id() << " ";
// //            }
// //            std::cout << std::endl;
//             if (!dfa_ptr->contains(new_state))
//             {
//                 dfa_ptr->add_state(new_state);
//                 dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
//                 if (new_state->get_type() == ACCEPTANCE)
//                 {
//                     dfa_ptr->add_acceptance_state(new_state);
//                     int max_pri = INT_MAX;
//                     std::string token_class;
//                     for (auto s : new_state->get_composing_nfa_states())
//                     {
//                         if (s->get_token_class_priority() < max_pri)
//                         {
//                             token_class = s->get_token_class();
//                             max_pri = s->get_token_class_priority();
//                         }
//                     }
//                     new_state->set_token_class(token_class);
//                 }
//             }
//             else
//             {
//                 auto existing_states = dfa_ptr->get_dfa_states();
//                 for (auto st : existing_states)
//                 {
//                     if (st->equals(new_state))
//                     {
//                         new_state = st;
//                         break;
//                     }
//                 }
//             }
//             curr_state->insert_transition(curr_range->get_range_string(), new_state);
//         }
//     }
//     return dfa_ptr;
// }


// std::shared_ptr<nfa> build_nfa2()
// {
//     std::shared_ptr<char_set> a_char_set(new char_set());
//     a_char_set->add_character('a');

//     std::shared_ptr<char_set> b_char_set(new char_set());
//     b_char_set->add_character('b');

//     std::shared_ptr<nfa> nfa1(new nfa(a_char_set, 1, 2));
//     std::shared_ptr<nfa> nfa2(new nfa(b_char_set, 3, 4));

//     nfa2->plus();
//     nfa1->unify(nfa2);
//     //nfa1->concat(nfa1);

//     return nfa1;
// }

// std::shared_ptr<nfa> build_nfa3()
// {
//   std::shared_ptr<char_set> a_char_set (new char_set());
//   a_char_set->add_character ('a');


//   std::shared_ptr<char_set> b_char_set (new char_set());
//   b_char_set->add_character ('b');
//   //// (a|b)* abb
//   std::shared_ptr <nfa> nfa_a1_ptr (new nfa(a_char_set));
//   std::shared_ptr <nfa> nfa_a2_ptr (new nfa(a_char_set));
//   std::shared_ptr<nfa> nfa_b1_ptr (new nfa(b_char_set));
//   std::shared_ptr<nfa> nfa_b2_ptr (new nfa(b_char_set));
//   std::shared_ptr<nfa> nfa_b3_ptr (new nfa(b_char_set));
//   nfa_a1_ptr->unify(nfa_b1_ptr);
//   nfa_a1_ptr->star();
//   nfa_a1_ptr->concat(nfa_a2_ptr);
//   nfa_a1_ptr->concat(nfa_b2_ptr);
//   nfa_a1_ptr->concat(nfa_b3_ptr);

//   return nfa_a1_ptr;
// }

// /// CHECK THIS AGAIN!
// bool equal_partitions(std::set<std::set<std::shared_ptr<dfa_state>>> part1,
//                       std::set<std::set<std::shared_ptr<dfa_state>>> part2) {
//     return part1 == part2;
// }
// bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
//                 const std::string &inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition) {
//     auto dest_state_1 = s1->get_next_state(inp);
//     auto dest_state_2 = s2->get_next_state(inp);
//     if (dest_state_1 == nullptr && dest_state_2 == nullptr) {
//         return true;
//     }
//     if (dest_state_1 == nullptr || dest_state_2 == nullptr) {
//         return false;
//     }
//     for (auto grp : partition)
//     {
//         bool found_s1, found_s2;
//         found_s1 = found_s2 = false;
//         for (const auto &state : grp)
//         {
//             if (state->get_id() == dest_state_1->get_id())
//                 found_s1 = true;
//             if (state->get_id() == dest_state_2->get_id())
//                 found_s2 = true;
//         }
//         if (found_s1 && found_s2)
//             return true;
//     }
//     return false;
// }

// bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
//                 const char inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition) {
//     auto dest_state_1 = s1->get_next_state(inp);
//     auto dest_state_2 = s2->get_next_state(inp);
//     if (dest_state_1 == nullptr && dest_state_2 == nullptr) {
//         return true;
//     }
//     if (dest_state_1 == nullptr || dest_state_2 == nullptr) {
//         return false;
//     }
// //    std::cout << "Dest#1: " << dest_state_1->get_id() << ", Dest #2: " << dest_state_2->get_id() << "\n";
//     for (auto grp : partition)
//     {
//         bool found_s1, found_s2;
//         found_s1 = found_s2 = false;
//         for (const auto &state : grp)
//         {
//             if (state->get_id() == dest_state_1->get_id())
//                 found_s1 = true;
//             if (state->get_id() == dest_state_2->get_id())
//                 found_s2 = true;
//         }
//         if (found_s1 && found_s2)
//             return true;
//     }
//     return false;
// }

// std::set<std::set<std::shared_ptr<dfa_state>>>
// make_partition(std::set<std::set<std::shared_ptr<dfa_state>>> partition,
//                const std::shared_ptr<char_set> &alphabet) {
//     std::set<std::set<std::shared_ptr<dfa_state>>> new_partition;
//     std::map<int, bool> partitioned;
//     for (auto group : partition)
//     {
//         for (const auto &state : group)
//         {
//             if (partitioned[state->get_id()])
//             {
//                 continue;
//             }
//             std::set<std::shared_ptr<dfa_state>> new_group;
//             new_group.insert(state);
//             partitioned[state->get_id()] = true;
//             for (const auto &s : group)
//             {
// //                std::cout << s->get_id() << "\n";
//                 if (!partitioned[s->get_id()])
//                 {
//                     bool same_grp = true;
//                     for (auto inp : alphabet->get_characters())
//                     {
// //                        std::cout << "----" << state->get_id() << "    " << s->get_id() << " input = " << inp.first << "\n";
//                         if (!same_group(state, s, inp.first, partition))
//                         {
//                             same_grp = false;
//                             break;
//                         }
//                     }
//                     if (same_grp)
//                     {
//                         for (const auto &range : alphabet->get_ranges())
//                         {
//                             if (!same_group(state, s, range->get_range_string(), partition))
//                             {
//                                 same_grp = false;
//                                 break;
//                             }
//                         }
//                     }
//                     if (same_grp && state->get_token_class() == s->get_token_class())
//                     {
//                         new_group.insert(s);
//                         partitioned[s->get_id()] = true;
//                     }
//                 }
//             }
//             new_partition.insert(new_group);
//         }
//     }
//     return new_partition;
// }

// std::shared_ptr<dfa> minimize(const std::shared_ptr<dfa> &dfa_ptr)
// {
//     // FIRST OF ALL MAKE A PARTITION OF ACC AND NON-ACC STATES
//     std::set<std::set<std::shared_ptr<dfa_state>>> partition;
//     std::set<std::shared_ptr<dfa_state>> non_acc_states, acc_states;
//     for (const auto &s : dfa_ptr->get_dfa_states())
//     {
//         if (s->get_type() != ACCEPTANCE)
//         {
//             non_acc_states.insert(s);
//         }
//         else
//         {
//             acc_states.insert(s);
//         }
//     }
//     partition.insert(acc_states);
//     partition.insert(non_acc_states);

//     // SECONDLY: PARTITION CURRENT PARTITION TO A NEW PARTITION
//     auto new_partition = make_partition(partition, dfa_ptr->get_alphabet());
//     std::cout << "Original\n";
//     for (auto group : partition) {
//         for (auto s : group) {
//             std::cout << s->get_id() << " ";
//         }
//         std::cout << "\n";
//     }
//     std::cout << "New\n";
//     for (auto group : new_partition) {
//         for (auto s : group) {
//             std::cout << s->get_id() << " ";
//         }
//         std::cout << "\n";
//     }
//     while (!equal_partitions(partition, new_partition))
//     {
//         partition = new_partition;
//         new_partition = make_partition(partition, dfa_ptr->get_alphabet());
//         std::cout << "Copy\n";
//         for (auto group : partition) {
//             for (auto s : group) {
//                 std::cout << s->get_id() << " ";
//             }
//             std::cout << "\n";
//         }
//         std::cout << "New\n";
//         for (auto group : new_partition) {
//             for (auto s : group) {
//                 std::cout << s->get_id() << " ";
//             }
//             std::cout << "\n";
//         }
//     }
//     // PARTITION IS THE FINAL PARTITION, CHOOSE A REPRESENTATIVE FOR EACH GROUP AND REMOVE DEAD STATES.
//     std::shared_ptr<dfa> min_dfa(new dfa());
//     min_dfa->set_alphabet(dfa_ptr->get_alphabet());
//     for (auto group : partition)
//     {
//         // Choose representative and modify transitions.
//         std::shared_ptr<dfa_state> grp_representative = *(group.begin());
// //        if (dead_state(grp_representative))
// //        {
// //            continue;
// //        }
//         std::map<std::string, std::shared_ptr<dfa_state>> new_transitions;
//         for (auto trans : grp_representative->get_transitions())
//         {
//             if (trans.second == nullptr) {
//                 continue;
//             }
//             std::shared_ptr<dfa_state> target_state;
//             for (auto grp : partition)
//             {
//                 bool found_target_state = false;
//                 for (auto s : grp)
//                 {
//                     if (s->get_id() == trans.second->get_id())
//                     {
//                         target_state = *(grp.begin());
//                         found_target_state = true;
//                         break;
//                     }
//                 }
//                 if (found_target_state)
//                     break;
//             }
// //            if (dead_state(target_state))
// //            {
// //                continue;
// //            }
//             new_transitions[trans.first] = target_state;
//         }
//         grp_representative->set_transitions(new_transitions);

//         // Modify ID.
//         grp_representative->set_id(static_cast<state_id>(min_dfa->get_total_states()));

//         for (const auto &s : group)
//         {
//             if (s->get_type() == START)
//             {
//                 grp_representative->set_type(START);
//                 min_dfa->set_start_state(grp_representative);
//             }
//         }
//         if (grp_representative->get_type() == ACCEPTANCE)
//         {
//             min_dfa->add_acceptance_state(grp_representative);
//         }
//         min_dfa->add_state(grp_representative);
//         min_dfa->set_total_states(min_dfa->get_total_states() + 1);
//     }
//     return min_dfa;
// }

// //bool dead_state(const std::shared_ptr<dfa_state> &s) {
// //    return s->get_char_set()->is_empty();
// //}

// //int main(int argc, char** argv) {
// ////    std::shared_ptr<nfa> nfa_ptr = build_nfa1();
// //////    std::shared_ptr<nfa> nfa_ptr = build_complex_nfa();
// ////    nfa_ptr->visualize();
// ////    std::shared_ptr<dfa> dfa_ptr = convert_nfa_dfa(nfa_ptr);
// ////    dfa_ptr->visualize();
// ////    std::shared_ptr<dfa> minimized_dfa = minimize(dfa_ptr);
// //////    for (const auto &curr : minimized_dfa->get_acceptance_states())
// //////    {
// //////        std::cout << curr->get_id() << " ";
// //////    }
// ////    minimized_dfa->visualize();
// ////    draw_trans_table(minimized_dfa);
// //
// //    // Integration i guess.
// ////    lexical_analyzer_generator gen = lexical_analyzer_generator();
// ////    gen.get_lexical_analyzer_file("rules.txt");
// //    return 0;
// //}

// int main(int argc, char** argv) {
//     // std::map <std::string,std::shared_ptr<nfa>> sym_table;
//     // regular_expression regex1 = {"letter", "a-z | A-Z"};
//     // std::shared_ptr<nfa> letter_nfa = evaluate_regex (regex1, sym_table);
//     // sym_table["letter"] = letter_nfa;
//     // regular_expression regex2 = {"digit", "0-9"};
//     // std::shared_ptr<nfa> digit_nfa = evaluate_regex (regex2, sym_table);
//     // sym_table["digit"] = digit_nfa ;
//     // regular_expression regex3 = {"id", "letter (letter|digit)*"};
//     // std::shared_ptr<nfa> id_nfa = evaluate_regex (regex3, sym_table);
//     // sym_table["id"] = id_nfa;
//     // regular_expression regex4 = {"digits", "digit+"};
//     // std::shared_ptr<nfa> digits_nfa = evaluate_regex (regex4, sym_table);
//     // sym_table["digits"] = digits_nfa;
//     //  regular_expression regex5 = {"num", "digit+ | digit+ . digits ( \\L | E digits)"};
//     //  std::shared_ptr<nfa> num_nfa = evaluate_regex (regex5, sym_table);
//     //  sym_table["num"] = num_nfa;
//     //
//     // regular_expression regex6 = {"relop", "\\=\\= | !\\= | > | >\\= | < | <\\="};
//     // std::shared_ptr<nfa> relop_nfa = evaluate_regex (regex6, sym_table);
//     // sym_table["num"] = relop_nfa;
//     //
//     // regular_expression regex7 = {"assign", "\\="};
//     // std::shared_ptr<nfa> assign_nfa = evaluate_regex (regex7, sym_table);
//     // sym_table["num"] = assign_nfa;
//     //
//     // regular_expression regex8 = {"addop", "\\+ | \\-"};
//     // std::shared_ptr<nfa> addop_nfa = evaluate_regex (regex8, sym_table);
//     // sym_table["num"] = addop_nfa;
//     //
//     // regular_expression regex9 = {"mulop", "\\* | /"};
//     // std::shared_ptr<nfa> mulop_nfa = evaluate_regex (regex9, sym_table);
//     // sym_table["num"] = mulop_nfa;
//     //
//     //
//     // letter_nfa->unify(digit_nfa);
//     // letter_nfa->unify(id_nfa);
//     // letter_nfa->unify(digits_nfa);
//     // letter_nfa->unify(num_nfa, false);
//     // letter_nfa->unify(relop_nfa, false);
//     // letter_nfa->unify(assign_nfa, false);
//     // letter_nfa->unify(mulop_nfa, false);
//     //
//     // if (letter_nfa != nullptr)
//     // {
//     //     letter_nfa->visualize();
//     // }
//     lexical_analyzer_generator gen = lexical_analyzer_generator();
//     auto combined_nfa = gen.get_lexical_analyzer_file("rules.txt");
//     for (auto s : combined_nfa->get_acceptance_states()) {
//         if(s->get_type() != ACCEPTANCE)
//         {
//             s->set_type(ACCEPTANCE);
//         }
//     }
// //    combined_nfa->visualize();

//     auto dfa_ptr = convert_nfa_dfa(combined_nfa);
// //    dfa_ptr->visualize();
//     for (auto s : dfa_ptr->get_acceptance_states()) {
//         std::cout << s->get_id() << " ";
//     }
//     std::cout << "\n";
//     auto min_dfa = minimize(dfa_ptr);
//     for (auto s : min_dfa->get_acceptance_states()) {
//         std::cout << s->get_id() << " ";
//     }
//     std::cout << "\n";
//     min_dfa->visualize();
//     draw_trans_table(min_dfa);
//     // std::shared_ptr<nfa> nf = build_keywords_nfa("{ if else while }");
//     // nf->visualize();
//     return 0;
// }
