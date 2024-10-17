#ifndef CHECKBOX_ARRAY_FLAG_HPP
#define CHECKBOX_ARRAY_FLAG_HPP

#include <flags/checkbox_base.hpp>

class CheckboxArrayFlag : public CheckboxBase {
  public:
    using CheckboxBase::CheckboxBase;
    std::string as_string() override;
};

#endif
