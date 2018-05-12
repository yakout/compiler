#ifndef COMPILER_JAVA_BYTECODE_H
#define COMPILER_JAVA_BYTECODE_H


#include <string>
#include <vector>
#include <fstream>
#include <map>

namespace java_bytecode {

	// *********************************************************
	// ************** DECLARATIONS *****************************
	// *********************************************************

	/**
	 * the generated code.
	 */
	std::vector<std::string> code_base;
	std::ofstream code_file("output.java");

	/**
 	 * to generate labels.
 	 */
	int next_instr = 0; // program counter
	int variables_count = 1; // variables index starts with 1

	std::map<std::string, std::pair<int, std::string>> symbol_table;

	std::string gen_label();
	void gen_code(std::string code);
    void write_code();

	void backpatch(std::vector<std::string> lists, std::string jump_target);
	std::vector<std::string> merge(std::vector<std::string> list1, std::vector<std::string> list2);


	std::map<std::string, std::string> instr_list = {
		{"+", "add"},
		{"-", "sub"},
		{"*", "mul"},
		{"/", "div"},
		{">",  "if_icmpgt"},
		{"<",  "if_icmplt"},
		{"==", "if_icmpeq"},
		{"!=", "if_icmpne"},
		{">=", "if_icmpge"},
		{"<=", "if_icmple"},
	};


	// *********************************************************
	// ********************** UTILITIES ************************
	// *********************************************************

	/**
	 * 
	 */
    bool lookup(std::string sym)
    {
        return (symbol_table.find(sym) != symbol_table.end());
    }

	/**
	 * 
	 */
	std::pair<int, std::string> get_lexeme(std::string lexeme)
	{
		return symbol_table[lexeme];
	}

	void add_type(std::string lexeme, std::pair<int, std::string> p)
	{
		symbol_table[lexeme] = p;
	}


	/**
 	 * generates label from the current value of next_instruction (PC).
 	 */
	std::string gen_label()
	{
		return std::to_string(next_instr) + ": ";
		next_instr++;
	}


	void backpatch(std::vector<std::string> lists, std::string jump_target)
	{
		for (auto list : lists)
		{
			code_base[std::atoi(list.c_str())] += jump_target + ": ";
		}
	}

	std::vector<std::string> merge(std::vector<std::string> list1, std::vector<std::string> list2)
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

    /**
     * METHOD_BODY
     */
    void INIT_CODE(std::vector<cfg_symbol> &stack)
    {

    }

    void STATEMENT_LIST_RECORD_METHOD_BODY(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 3].add_attribute("STATEMENT_LIST.nextlist", stack.back().get_attribute("nextlist"));
    }

    void M_RECORD_METHOD_BODY(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 1].add_attribute("M.instr", stack.back().get_attribute("instr"));
    }

    void METHOD_BODY_ACTION(std::vector<cfg_symbol> &stack)
    {
        backpatch(stack.back().get_attribute("STATEMENT_LIST.nextList"), stack.back().get_attribute("M.instr").front());
    }

    void FINALIZE_CODE(std::vector<cfg_symbol> &stack)
    {
        write_code();
    }


    /**
     * STATEMENT_LIST
     */

    void STATMENT_RECORD_STATEMENT_LIST(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-5].add_attribute("STATMENT.nexlist", stack.back().get_attribute("nexlist"));
    }

    void M_RECORD_STATEMENT_LIST(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-3].add_attribute("M.instr", stack.back().get_attribute("instr"));
    }

    void STATEMENT_LIST1_RECORD_STATEMENT_LIST(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("STATEMENT_LIST1.nextlist", stack.back().get_attribute("nextlist"));
    }

    void STATEMENT_LIST1_ACTION_STATEMENT_LIST(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        backpatch(stack.back().get_attribute("STATMENT.nextlist"), stack.back().get_attribute("M.instr").front());
        stack[top-1].add_attribute("nextlist", stack.back().get_attribute("STATEMENT_LIST.nextlist"));
    }

    /**
     * STATEMENT_LIST1
     */
    void STATEMENT_RECORD_STATEMENT_LIST1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-5].add_attribute("STATEMENT.nextlist", stack.back().get_attribute("nextlist"));
    }

    void M_RECORD_STATEMENT_LIST1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-3].add_attribute("M.instr", stack.back().get_attribute("instr"));
    }

    void STATEMENT_LIST1_RECORD_STATEMENT_LIST1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-3].add_attribute("M.instr", stack.back().get_attribute("instr"));
    }


    void STATEMENT_LIST1_ACTION_STATEMENT_LIST1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        backpatch(stack.back().get_attribute("STATMENT.nextlist"), stack.back().get_attribute("M.instr").front());
        stack[top-1].add_attribute("nextlist", stack.back().get_attribute("STATEMENT_LIST.nextlist"));
    };


    /**
     * STATEMENT
     */
    void IF_RECORD_STATEMENT(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("nextlist", stack.back().get_attribute("nextlist"));
    }

    void WHILE_RECORD_STATEMENT(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("nextlist", stack.back().get_attribute("nextlist"));
    }


    /**
     * DECLARATION
     */
    void PRIMITIVE_TYPE_RECORD_DECLARATION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-4].add_attribute("PRIMITIVE_TYPE.type", stack.back().get_attribute("type"));
    }

    void id_ACTION_DECLARATION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-2].add_attribute("id.lexval", stack.back().get_attribute("lexval"));
    }
    void DECLARATION_ACTION_DECLARATION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        std::string type = stack.back().get_attribute("PRIMITIVE_TYPE.type").front();

        std::string lexeme(stack.back().get_attribute("id.lexeme").front());

        if (lookup(lexeme)) {
            add_type(lexeme, std::make_pair(variables_count, type));
            variables_count++;
        }
        else
        {
            // VARIABLE ALREADY EXIST
        }
    }


    /**
     * PRIMITIVE_TYPE
     */
    void int_ACTION_PRIMITIVE_TYPE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 1].add_attribute("PRIMITIVE_TYPE.type", "int");
    }

    void float_ACTION_PRIMITIVE_TYPE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 1].add_attribute("PRIMITIVE_TYPE.type", "float");
    }


    /**
     * IF
     */
    void EXPRESSION_RECORD_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-16].add_attribute("EXPRESSION.falselist", stack.back().get_attribute("falselist"));
    }

    void M1_RECORD_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-12].add_attribute("M1.instr", stack.back().get_attribute("instr"));
    }

    void STATEMENT1_RECORD_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-12].add_attribute("STATEMENT1.nextlist", stack.back().get_attribute("nextlist"));
    }

    void GOTO_ACTION_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        gen_code("goto ");
        std::vector<std::string> v;
        v.push_back(std::to_string(code_base.size()));
        stack[top-9].add_attribute("goto.nextlist", v);
    }

    void M2_RECORD_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-4].add_attribute("M2.instr", stack.back().get_attribute("instr"));
    }

    void STATEMENT2_RECORD_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-2].add_attribute("STATEMENT2.nextlist", stack.back().get_attribute("nextlist"));
    }

    void IF_ACTION_IF(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        backpatch(stack.back().get_attribute("EXPRESSION.truelist"), stack.back().get_attribute("M1.instr").front());
        backpatch(stack.back().get_attribute("EXPRESSION.falselist"), stack.back().get_attribute("M2.instr").front());
        stack[top-1].add_attribute("nextlist", merge(stack.back().get_attribute("STATEMENT1.nextlist"),
                                                     stack.back().get_attribute("STATEMENT2.nextlist")));

        stack[top-1].get_attribute("nextlist").push_back(stack.back().get_attribute("goto.nextlist").front());
    }

    /**
     * WHILE
     */
    void M1_RECORD_WHILE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-12].add_attribute("M1.instr", stack.back().get_attribute("instr"));
    }

    void EXPRESSION_RECORD_WHILE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-8].add_attribute("EXPRESSION.nextlist", stack.back().get_attribute("nextlist"));
        stack[top-8].add_attribute("EXPRESSION.falselist", stack.back().get_attribute("falselist"));
    }

    void M2_RECORD_WHILE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-10].add_attribute("M2.instr", stack.back().get_attribute("instr"));
    }

    void STATEMENT_RECORD_WHILE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 2].add_attribute("STATEMENT.nextlist", stack.back().get_attribute("nextlist"));
    }


    void WHILE_ACTION_WHILE(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        gen_code("goto " + stack.back().get_attribute("M1.instr").front());

        backpatch(stack.back().get_attribute("EXPRESSION.truelist"), stack.back().get_attribute("M2.instr").front());
        backpatch(stack.back().get_attribute("STATEMENT.nextlist"), stack.back().get_attribute("M1.instr").front());

        stack[top-1].add_attribute("nextlist", stack.back().get_attribute("EXPRESSION.falselist"));
    }


    /**
     * ASSIGNMENT
     */
    void id_ACTION_ASSIGNMENT(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-5].add_attribute("id.lexval", stack.back().get_attribute("lexval"));
    }

    void EXPRESSION_RECORD_ASSIGNMENT(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-2].add_attribute("EXPRESSION.type", stack.back().get_attribute("type"));
    }

    void ASSIGNMENT_ACTION_ASSIGNMENT(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);

        std::string lexeme(stack.back().get_attribute("id.lexval").front());
        std::string type = stack.back().get_attribute("EXPRESSION.type").front();

        if(lookup(lexeme))
        {
            if(type == get_lexeme(lexeme).second)
            {
                if(type == "int")
                {
                    gen_code("istore " + std::to_string(get_lexeme(lexeme).first));
                }
                else if (type == "float")
                {
                    gen_code("fstore " + std::to_string(get_lexeme(lexeme).first));
                }
            }
            // TODO WE CAN DO CASTING HERE OR JUST REJECT IT.
        }
        else
        {
            // TODO throw that error variable is not declared yet;
        }
    }


    /**
     * FACTOR
     */
    void id_ACTION_FACTOR(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("id.lexval", stack.back().get_attribute("lexval"));
    }

    void FACTOR_ACTION_FACTOR_id(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        std::string lexeme = stack.back().get_attribute("id.lexval").front();
        stack[top-1].add_attribute("FACTOR.val", lexeme);

        if (lookup(lexeme)) {
            if (get_lexeme(lexeme).second == "int") {
                gen_code( "iload\t" + std::to_string(get_lexeme(lexeme).first) );
            } else if (get_lexeme(lexeme).second == "float") {
                gen_code( "fload\t" + std::to_string(get_lexeme(lexeme).first) );
            }
        } else {
            // TODO ERROR!
        }
    }

    void num_ACTION_FACTOR(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("num.lexval", stack.back().get_attribute("lexval"));
    }

    void FACTOR_ACTION_FACTOR_num(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("FACTOR.val", stack.back().get_attribute("num.lexval"));
    }

    void SIMPLE_EXPRESSION_RECORD(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-2].add_attribute("SIMPLE_EXPRESSION.val", stack.back().get_attribute("val"));
    }

    void FACTOR_ACTION_FACTOR_PAREN(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("FACTOR.val", stack.back().get_attribute("SIMPLE_EXPRESSION.lexval"));
    }


    /**
     * TERM1
     */
    void TERM1_IN_mulop(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-5].add_attribute("TERM1.in", stack.back().get_inherited_attribute("TERM1.in"));
    }

    void mulop_ACTION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-3].add_attribute("mulop.op", stack.back().get_attribute("lexval"));
    }

    void FACTOR_RECORD_TERM1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("FACTOR.val", stack.back().get_attribute("FACTOR.val"));
    }

    void TERM1_ACTION_mulop(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 1].add_inherited_attribute("TERM1.in",
                                          std::to_string(
                                                  std::atoi(stack.back().get_attribute("TERM1.in").front().c_str())
                                                  *
                                                  std::atoi(stack.back().get_attribute("FACTOR.val").front().c_str())
                                          )
        );
    }

    void TERM1_RECORD_TERM1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("TERM1.val", stack.back().get_attribute("TERM1.val"));
    }


    void TERM1_IN_eps(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-2].add_attribute("TERM1.in", stack.back().get_inherited_attribute("TERM1.in"));
    }

    void TERM1_ACTION_eps(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("TERM1.val", stack.back().get_attribute("TERM1.in"));
    }


    /**
     * TERM
     */
    void FACTOR_RECORD_TERM(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_inherited_attribute("TERM1.in", stack.back().get_attribute("FACTOR.val").front());
    }

    void TERM1_RECORD_TERM(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("TERM.val", stack.back().get_attribute("TERM1.val"));
    }


    /**
     * SIMPLE_EXPRESSION1
     */
    void SIMPLE_EXPRESSION1_IN_addop(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-5].add_attribute("SIMPLE_EXPRESSION1.in", stack.back().get_inherited_attribute("SIMPLE_EXPRESSION1.in"));
    }

    void addop_ACTION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 3].add_attribute("op", stack.back().get_attribute("op"));
    }

    void TERM_RECORD_SIMPLE_EXPRESSION1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("TERM.val", stack.back().get_attribute("TERM.val"));
    }

    void SIMPLE_EXPRESSION1_ACTION_addop(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top - 1].add_inherited_attribute("SIMPLE_EXPRESSION1.in",
                                          std::to_string(
                                                  std::atoi(stack.back()
                                                                    .get_attribute("SIMPLE_EXPRESSION1.in")
                                                                    .front().c_str())
                                                  +
                                                  std::atoi(stack.back().get_attribute("TERM.val").front().c_str())
                                          )
        );
    }

    void SIMPLE_EXPRESSION1_RECORD_SIMPLE_EXPRESSION1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("SIMPLE_EXPRESSION1.val", stack.back().get_attribute("SIMPLE_EXPRESSION1.val"));
    }

    void SIMPLE_EXPRESSION1_IN_eps(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-2].add_attribute("SIMPLE_EXPRESSION1.in", stack.back().get_inherited_attribute("SIMPLE_EXPRESSION1.in"));
    }

    void SIMPLE_EXPRESSION1_ACTION_eps(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("SIMPLE_EXPRESSION1.val", stack.back().get_attribute("SIMPLE_EXPRESSION1.in"));
    }


    /**
     * SIMPLE_EXPRESSION
     */
    void TERM_RECORD_SIMPLE_EXPRESSION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_inherited_attribute("SIMPLE_EXPRESSION1.in", stack.back().get_attribute("TERM.val").front()); // TODO:: front
    }

    void SIMPLE_EXPRESSION1_RECORD_SIMPLE_EXPRESSION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("SIMPLE_EXPRESSION.val", stack.back().get_attribute("SIMPLE_EXPRESSION1.val"));
    }

    /**
     * EXPRESSION1
     */
    void EXPRESSION1_IN_relop(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-5].add_attribute("EXPRESSION1.in", stack.back().get_inherited_attribute("EXPRESSION1.in"));
    }

    void relop_ACTION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-3].add_attribute("relop.lexval", stack.back().get_attribute("lexval"));
    }

    void SIMPLE_EXPRESSION_RECORD_EXPRESSION1(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("SIMPLE_EXPRESSION.val", stack.back().get_attribute("SIMPLE_EXPRESSION.val"));
    }

    void EXPRESSION1_ACTION_relop(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        instr_list[stack.back().get_attribute("relop.lexval").front()];
    }
    

    /**
     * EXPRESSION
     */
    void SIMPLE_EXPRESSION_RECORD_EXPRESSION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_inherited_attribute("EXPRESSION.in", stack.back().get_attribute("SIMPLE_EXPRESSION.val").front());
    }

    void EXPRESSION1_RECORD_EXPRESSION(std::vector<cfg_symbol> &stack)
    {
        int top = static_cast<int>(stack.size() - 1);
        stack[top-1].add_attribute("EXPRESSION.val", stack.back().get_attribute("EXPRESSION1.val"));
    }

}

#endif //COMPILER_JAVA_BYTECODE_H
