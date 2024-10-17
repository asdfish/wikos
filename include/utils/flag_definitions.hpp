#ifndef FLAG_DEFINITIONS_HPP
#define FLAG_DEFINITIONS_HPP

#include <flags/flag_base.hpp>

#include <memory>
#include <string>
#include <vector>

extern const std::vector<std::string> checks;
extern const std::vector<std::string> mumerical_abstract_domains;
extern const std::vector<std::string> optimization_levels;
extern const std::vector<std::string> procedural_analysis;
extern const std::vector<std::string> widening_strategies;
extern const std::vector<std::string> narrowing_strategies;
extern const std::vector<std::string> partitioning_type;
extern const std::vector<std::string> others;

extern std::vector<std::unique_ptr<FlagBase>> flags;

extern void flags_define(void);
extern void flags_define_default(void);

#endif