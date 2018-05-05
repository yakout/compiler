> The semantic analyzer uses the syntax tree and the information in the symbol table to check the source program for semantic consistency with the language definition. It also gathers type information and saves it in either the syntax tree or the symbol table, for subsequent use during intermediate-code generation.




* Use a recursive-descent parser with one function for each nonterminal. The function for nonterminal A receives the inherited attributes of A as arguments and returns the synthesized attributes of A.

* Generate code on the fly, using a recursive-descent parser.

* Implement an SDT in conjunction with an LL-parser. The attributes are kept on the parsing stack, and the rules fetch the needed attributes from known locations on the stack.

