#include <flags/checkbox_array_flag.hpp>
#include <flags/radiobox_flag.hpp>
#include <utils/flag_definitions.hpp>

const std::vector<std::string> checks = {
  "boa",
  "dbz",
  "nullity",
  "prover",
  "upa",
  "uva",
  "sio",
  "uio",
  "shc",
  "poa",
  "pcmp",
  "sound",
  "fca",
  "dca",
  "dfa",
  "dbg",
  "watch",
};

const std::vector<std::string> mumerical_abstract_domains = {
  "interval",
  "congruence",
  "interval-congruence",
  "dbm",
  "var-pack-dbm",
  "var-pack-dbm-congruence",
  "gauge",
  "gauge-interval-congruence",
  "apron-interval",
  "apron-octagon",
  "apron-polka-polyhedra",
  "apron-polka-linear-equalities",
  "apron-ppl-polyhedra",
  "apron-ppl-linear-congruences",
  "apron-pkgrid-polyhedra-lin-cong",
  "var-pack-apron-octagon",
  "var-pack-apron-polka-polyhedra",
  "var-pack-apron-polka-linear-equalities",
  "var-pack-apron-ppl-polyhedra",
  "var-pack-apron-ppl-linear-congruences",
  "var-pack-apron-pkgrid-polyhedra-lin-cong",
};

const std::vector<std::string> optimization_levels = {
  "basic",
  "none",
  "aggressive",
};

const std::vector<std::string> procedural_analysis = {
  "inter",
  "intra",
};

const std::vector<std::string> widening_strategies = {
  "widen",
  "join",
};

const std::vector<std::string> narrowing_strategies = {
  "auto",
  "narrow",
  "meet",
};

const std::vector<std::string> partitioning_type = {
  "none",
  "return",
  "manual",
};

const std::vector<std::string> others = {
  "globals-init",
  "no-init-globals",
  "no-liveness",
  "no-pointer",
  "no-widening-hints",
  "no-fixpoint-cache",
  "no-checks",
  "argc",
  "no-libc",
};

std::vector<std::unique_ptr<FlagBase>> flags;

void flags_define(void) {
  flags.push_back(std::make_unique<CheckboxArrayFlag>("-a=", "checks", checks));
  flags.push_back(std::make_unique<RadioboxFlag>("-d=", "mumerical_abstract_domains", mumerical_abstract_domains));
  flags.push_back(std::make_unique<RadioboxFlag>("--opt=", "optimization_levels", optimization_levels));
  flags.push_back(std::make_unique<RadioboxFlag>("--proc=", "procedural_analysis", procedural_analysis));
  flags.push_back(std::make_unique<RadioboxFlag>("--widening-strategy=", "widening_strategies", widening_strategies));
  flags.push_back(std::make_unique<RadioboxFlag>("--narrowing-strategy=", "narrowing_strategies", narrowing_strategies));
  flags.push_back(std::make_unique<RadioboxFlag>("--partitioning=", "partitioning_type", partitioning_type));
  /*flags.push_back(std::make_unique<CheckboxFlag>("--", "others", others));*/
}

void flags_define_default(void) {
  flags_define();
  for(unsigned int i = 0; i < flags.size(); i ++)
    flags[i]->set_default();
}
