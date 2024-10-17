#include <classes.hpp>
#include <flags.hpp>

std::vector<std::unique_ptr<Flag>> flags;

void flags_init(void) {
  flags.push_back(std::make_unique<CheckboxFlag>("checks", std::vector<std::string> {
    "buffer overflow analysis",
    "division by zero analysis",
    "null pointer analysis",
    "assertion prover",
    "unaligned pointer analysis",
    "uninitialized variable analysis",
    "signed integer overflow analysis",
    "unsigned integer overflow analysis",
    "shift count analysis",
    "pointer overflow analysis",
    "pointer comparison analysis",
    "soundness analysis",
    "function call analysis",
    "dead code analysis",
    "double free analysis",
    "debugger",
    "memory watcher",
  }));
}
