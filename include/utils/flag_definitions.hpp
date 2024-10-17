#ifndef FLAG_DEFINITIONS_HPP
#define FLAG_DEFINITIONS_HPP

#include <flags/flag_base.hpp>

#include <memory>
#include <string>
#include <vector>

extern std::vector<std::unique_ptr<FlagBase>> flags;

extern void flags_define(void);
extern void flags_define_default(void);

#endif
