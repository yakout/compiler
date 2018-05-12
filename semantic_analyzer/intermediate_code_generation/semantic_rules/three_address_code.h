#ifndef COMPILER_THREE_ADDRESS_CODE_H
#define COMPILER_THREE_ADDRESS_CODE_H

#include <string>
#include <vector>
#include <fstream>


namespace three_address_code 
{
	// *********************************************************
	// ************** DECLARATIONS *****************************
	// *********************************************************

	/**
	 * the generated code.
	 */
	std::vector<std::string> code_base;
	std::ofstream code_file("code.asm");

	/**
	 * to generate labels.
	 */
	int next_instr = 0;

	std::string gen_label ();
	void gen_code(std::string code);

	void backpatch(std::vector<std::string> lists, std::string jump_target);
	std::vector<std::string> merge(std::vector<std::string> list1, std::vector<std::string> list2);

	// *********************************************************
	// ********************** UTILITIES ************************
	// *********************************************************

	void backpatch(std::vector<std::string> lists, std::string jump_target)
	{
		for (auto list : lists)
		{
			code_base[std::atoi(list.c_str())] += jump_target;
		}
	}

	/**
	 * merge two lists.
	 */
	std::vector<std::string> merge(std::vector<std::string> list1, std::vector<std::string> list2)
	{
		std::vector<std::string> res;
		res.reserve(list1.size() + list2.size()); // preallocate memory
		res.insert(res.end(), list1.begin(), list1.end());
		res.insert(res.end(), list2.begin(), list2.end());
		return res;
	}


	/**
 	 * generates label from the current value of next_instruction (PC).
 	 */
	std::string gen_label()
	{
		return std::to_string(next_instr++) + ": ";
	}

	/**
 	 * generates code.
 	 */
	void gen_code(std::string code)
	{
		// line by line
		code_base.push_back(gen_label() + code);
	}

	void write_code()
	{
		for (auto c : code_base)
		{
			code_file << c << std::endl;
		}
		code_file.close();
	}



	// *********************************************************
	// ********************** ACTIONS **************************
	// *********************************************************

	void finalize_action(std::vector<cfg_symbol> &stack)
	{
		write_code();
	}

	// =================== B -> true ================
	void B_action_true(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 1].add_attribute("truelist", std::to_string(next_instr));
		gen_code("goto ");
	}

	// =================== B -> false ================
	void B_action_false(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 1].add_attribute("falselist", std::to_string(next_instr));
		gen_code("goto ");
	}

	// =================== B -> E1 #E1 relop E2 #E2 @B  ================
	void E1_record_relop(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 4].add_attribute("E1.addr", stack.back().get_attribute("addr"));
	}

	void E2_record_relop(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 1].add_attribute("E2.addr", stack.back().get_attribute("addr"));
	}

	void B_action_relop(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 1].add_attribute("truelist", std::to_string(next_instr));
		stack[top - 1].add_attribute("falselist", std::to_string(next_instr + 1));

		gen_code(
			"if " 
			+ stack.back().get_attribute("E1.addr").front()
			+ " relop "
			+ stack.back().get_attribute("E2.addr").front()
			+ " goto "
			);

		gen_code(
			"goto "
			);
	}

	// =================== B -> B1 #B1 || M #M B2 #B2 @B ================

	void B1_record_or(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);

		stack[top - 7].add_attribute("B1.truelist", stack.back().get_attribute("truelist"));
		stack[top - 7].add_attribute("B1.falselist", stack.back().get_attribute("falselist"));
	}

	void M_record_or(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);

		stack[top - 3].add_attribute("M.instr", stack.back().get_attribute("instr"));
	}

	void B2_record_or(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);

		stack[top - 2].add_attribute("B2.truelist", stack.back().get_attribute("truelist"));
		stack[top - 7].add_attribute("B2.falselist", stack.back().get_attribute("falselist"));
	}

	void B_action_or(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);

		backpatch(stack[top - 1].get_attribute("B1.falselist"), stack.back().get_attribute("M.instr").front());

		stack[top - 1].add_attribute(
			"truelist",
			merge(stack[top - 1].get_attribute("B1.truelist"),
			 stack[top - 1].get_attribute("B2.truelist"))
			);

		stack[top - 1].add_attribute(
			"falselist", stack[top - 1].get_attribute("B2.falselist")
			);
	}


	// =================== S -> if ( B #B ) M #M S1 #S1 @S ================

	void B_record_if(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 6].add_attribute("B.truelist", stack.back().get_attribute("truelist"));
		stack[top - 6].add_attribute("B.falselist", stack.back().get_attribute("falselist"));
	}

	void M_record_if(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 3].add_attribute("M.instr", stack.back().get_attribute("instr"));
	}

	void S1_record_if(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);

		stack[top - 1].add_attribute("S1.nextlist", stack.back().get_attribute("nextlist"));
		stack[top - 1].add_attribute("S1.code", stack.back().get_attribute("code"));
	}

	void S_action_if(std::vector<cfg_symbol> &stack) 
	{
		int top = static_cast<int>(stack.size() - 1);

		backpatch(stack.back().get_attribute("B.truelist"), stack.back().get_attribute("M.instr").front());
		stack[top - 1].add_attribute(
			"nextlist",
			merge(stack.back().get_attribute("S1.nextlist"), stack.back().get_attribute("B.falselist"))
			);
		gen_code(stack.back().get_attribute("S1.code").front());
	}



	// =================== E -> 'num' ================

	void E_action_num(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 1].add_attribute("addr", "num");
	}


	// =================== M -> '\L' ================

	void M_action_eps(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);
		stack[top - 1].add_attribute("instr", std::to_string(next_instr));

	}

	// =================== S -> 'assign' ================

	void S_action_assign(std::vector<cfg_symbol> &stack)
	{
		int top = static_cast<int>(stack.size() - 1);

		stack[top - 1].add_attribute("code", "assign");
	}


} // namespace three_address_code



#endif //COMPILER_THREE_ADDRESS_CODE_H
