#ifndef COMPILER_JAVA_BYTECODE_H
#define COMPILER_JAVA_BYTECODE_H


#include <string>
#include <vector>
#include <fstream>

namespace java_bytecode {

	// *********************************************************
	// ************** DECLARATIONS *****************************
	// *********************************************************

	/**
	 * the generated code.
	 */
	std::vector<std::string> code_base;
	std::ofstream compiled_file("output.java");

	/**
 	 * to generate labels.
 	 */
	int next_instr = 0;

	std::string gen_label();
	void gen_code(std::string code);

	void backpatch(std::vector<std::string> &lists, std::string jump_target);
	std::vector<std::string> merge(std::vector<std::string> &list1, std::vector<std::string> &list2);

	// *********************************************************
	// ********************** UTILITIES ************************
	// *********************************************************


	/**
 	 * generates label from the current value of next_instruction (PC).
 	 */
	std::string gen_label()
	{
		return "L_" + std::to_string(next_instr++);
	}


	void backpatch(std::vector<std::string> &lists, std::string jump_target)
	{
		for (auto list : lists)
		{
			code_base[std::atoi(list.c_str())] += "L_" + jump_target;
		}
	}

	std::vector<std::string> merge(std::vector<std::string> &list1, std::vector<std::string> &list2)
	{
		std::vector<std::string> res;
		res.reserve(list1.size() + list2.size()); // preallocate memory
		res.insert(res.end(), list1.begin(), list1.end());
		res.insert(res.end(), list2.begin(), list2.end());
		return res;
	}

	/**
	 * generates code.
	 */
	void gen_code(std::string code)
	{
		// line by line
		code_base.push_back(code);
	}



	// *********************************************************
	// ********************** ACTIONS **************************
	// *********************************************************


}

#endif //COMPILER_JAVA_BYTECODE_H
