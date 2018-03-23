// #include <iostream>
// #include <memory>
// #include <queue>
// #include <iostream>
// #include <set>

// #include "../../lexical_analyzer_generator/finite_automata/finite_automata.h"
// #include "../../lexical_analyzer_generator/finite_automata/state.h"
// #include "../../lexical_analyzer_generator/finite_automata/nfa.h"
// #include "../../lexical_analyzer_generator/finite_automata/dfa.h"
// #include "../../lexical_analyzer_generator/finite_automata/nfa_state.h"
// #include "../../lexical_analyzer_generator/finite_automata/dfa_state.h"
// #include "../../lexical_analyzer_generator/nfa_tools/regex_processor.h"

// #define EPSILON ""

// void draw_trans_table(std::shared_ptr<dfa> dfa)
// {


// }

// std::shared_ptr<nfa> build_complex_nfa()
// {
//     std::shared_ptr<char_set> eps, c_i, c_f, c_t, c_h, c_e, c_n, c_l, c_s, c_less,
//             c_bigger, c_equals, c_eq_bigger, c_let, c_dig, c_let_dig;
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
//     std::shared_ptr<char_set> char_set_0;
//     char_set_0->add_character('0');

//     std::shared_ptr<char_set> char_set_1;
//     char_set_1->add_character('1');

//     std::shared_ptr<char_set> eps;

//     std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, eps));
//     std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, char_set_0));
//     std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, char_set_1));
//     std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, INTERMEDIATE, eps));
//     std::shared_ptr<nfa_state> s6 = std::make_shared<nfa_state>(nfa_state (6, ACCEPTANCE, eps));

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

// std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, char inp)
// {
//     std::cout << "Character to transition with = " << inp << "\n";
//     std::set<std::shared_ptr<nfa_state>> reachable_states;
//     for (const auto &state : nfa_states)
//     {
//         std::vector<std::shared_ptr<nfa_state>> curr_reached = state->get_next_state(inp);
//         std::cout << "Base state = " << state->get_id() << "\n";
//         for (const auto &curr : curr_reached)
//         {
//             std::cout << "Reached state = " << curr->get_id() << "\n";
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
//                 for (auto x :curr->get_char_set()->get_characters())
//                     std::cout << x.first << " ";
//                 nfa_states_stack.push(curr);
//             }
//         }
//     }
//     return reachable_states;
// }

// std::shared_ptr<dfa> convert_nfa_dfa(const std::shared_ptr<nfa> &nfa_ptr) {

//     // Constructing all possible alphabet(could be sth like nfa->get_alphabet()).
//     char_set alphabet;
//     alphabet.add_character('a');
//     alphabet.add_character('b');

//     std::shared_ptr<dfa> dfa_ptr(new dfa());
//     std::set<std::shared_ptr<nfa_state>> vec;
//     vec.insert((std::shared_ptr<nfa_state> &&) nfa_ptr->get_start_state());
//     std::shared_ptr<dfa_state> init_dfa_state(new dfa_state(e_closure(vec),
//                                                               static_cast<state_id>(dfa_ptr->get_total_states())));
//     dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
//     dfa_ptr->set_start_state(init_dfa_state);
//     dfa_ptr->add_state(init_dfa_state);

//     std::shared_ptr<dfa_state> curr_state;
//     while ((curr_state = dfa_ptr->get_unmarked_state()) != nullptr) // get_next_state returns next unmarked state or null if no more unmarked states in dfa_ptr.
//     {
//         curr_state->set_marked(true);
//         std::cout << "Current State = " << curr_state->get_id() << std::endl;
//         std::cout << "Composing states = \n";
//         for (auto curr : curr_state->get_composing_nfa_states()) {
//             std::cout << curr->get_id();
//             std::cout << ", transitions on: ";
//             for (auto x : curr->get_char_set()->get_characters())
//                 std::cout << x.first << " ";
//             std::cout << "\n";
//         }
//         std::cout << std::endl;
//         // Iterating over characters from alphabet.
//         for (const auto &inp : alphabet.get_characters())
//         {
//             std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(), inp.first)),
//                                     static_cast<state_id>(dfa_ptr->get_total_states())));
//             if (new_state->equals(curr_state))
//             {
//                 curr_state->insert_transition(alphabet.get_string(inp.first), curr_state);
//                 continue;
//             }
//             std::cout << "New State = " << new_state->get_id() << std::endl;
//             for (auto curr : new_state->get_composing_nfa_states()) {
//                 std::cout << curr->get_id() << " ";
//             }
//             std::cout << std::endl;
//             if (!dfa_ptr->contains(new_state))
//             {
//                 dfa_ptr->add_state(new_state);
//                 dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
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
//             curr_state->insert_transition(alphabet.get_string(inp.first), new_state);
//             if (new_state->get_type() == ACCEPTANCE)
//             {
//                 dfa_ptr->add_acceptance_state(new_state);
//             }
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

// int main(int argc, char** argv) {
//    regular_expression regex = {"letter", "a-z"};
//    std::map <std::string,std::shared_ptr<nfa>> sym_table;
//    std::shared_ptr<nfa> my_nfa = evaluate_regex (regex, sym_table);
//     char_set cs(*my_nfa->get_start_state()->get_char_set());

//    if (my_nfa != nullptr)
//    {
//        my_nfa->visualize();
//        std::shared_ptr<char_set> c_s = my_nfa->get_alphabet();
//        for (auto const& c : c_s->get_characters())
//        {
//            std::cout << c.first << std::endl;
//        }
//        for (auto const& range : c_s->get_ranges())
//        {
//            std::cout << range->get_range_string() << std::endl;
//        }
//    }
// //    std::shared_ptr<nfa> nfa_ptr = build_nfa();
//     // std::shared_ptr<nfa> nfa_ptr = build_nfa1();
// //    nfa_ptr->visualize();
//     // std::shared_ptr<dfa> dfa_ptr = convert_nfa_dfa(nfa_ptr);
//     // std::cout << "# of produced dfa states = " << dfa_ptr->get_total_states() << "\n";
//     // dfa_ptr->visualize();
// //    draw_trans_table(my_dfa);
//     return 0;
// }
