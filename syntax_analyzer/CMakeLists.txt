cmake_minimum_required(VERSION 3.5)

set(SOURCE_FILES
        predictive_parser.h
        predictive_parser.cpp first_follow.h first_follow.cpp parsing_table.h parsing_table.cpp cfg.h cfg_production.cpp cfg_production.h cfg_symbol.cpp cfg_symbol.h cfg_rule.cpp cfg_rule.h cfg.cpp)

add_library(syntax SHARED ${SOURCE_FILES})
