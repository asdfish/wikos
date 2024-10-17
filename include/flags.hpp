#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <classes.hpp>

#include <memory>
#include <vector>

extern std::vector<std::unique_ptr<Flag>> flags;

extern void flags_init(void);

#endif
