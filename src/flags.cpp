#include <flags.hpp>

const std::string check_header = "-a=";
const std::vector<std::string> check_names = {
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
};
const std::vector<std::string> check_values = {
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

const std::string numeric_abstract_domain_header = "-d=";
const std::vector<std::string> numeric_abstract_domain_values = {
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

extern const std::string entry_points_header = "--entry-points=";

extern const std::string jobs_header = "-j=";

extern const std::string optimization_header = "-opt=";
extern const std::vector<std::string> optimization_values = {
  "none",
  "basic",
  "aggressive",
};

const std::vector<std::string> miscellaneous = {
  "--globals-init",
  "--no-init-globals",
  "--no-liveness",
  "--no-pointer",
  "--no-widening-hints",
  "--no-fixpoint-cache",
  "--no-checks",
  "--argc",
  "--no-libc",
};
