#ifndef CHECKBOX_SEPARATED_HPP
#define CHECKBOX_SEPARATED_FLAG_HPP

#include <flags/checkbox_base.hpp>

class CheckboxSeparatedFlag : public CheckboxBase {
  public:
    using CheckboxBase::CheckboxBase;
    std::string as_string() override;
};

#endif
