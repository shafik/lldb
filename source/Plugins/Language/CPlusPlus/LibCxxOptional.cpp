//===-- LibCxxOptional.cpp -----------------------------------------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "LibCxx.h"
#include "lldb/DataFormatters/FormattersHelpers.h"

using namespace lldb;
using namespace lldb_private;

namespace {

class OptionalFrontEnd : public SyntheticChildrenFrontEnd {
public:
  OptionalFrontEnd(ValueObject &valobj) : SyntheticChildrenFrontEnd(valobj) {
    Update();
  }

  size_t GetIndexOfChildWithName(const ConstString &name) override {
    return formatters::ExtractIndexFromString(name.GetCString());
  }

  bool MightHaveChildren() override { return true; }
  bool Update() override;
  size_t CalculateNumChildren() override { return m_size; }
  ValueObjectSP GetChildAtIndex(size_t idx) override;

private:
  size_t m_size = 0;
  ValueObjectSP m_base_sp;
};
} // namespace

bool OptionalFrontEnd::Update() {
<<<<<<< HEAD
  m_elements.clear();

  ValueObjectSP engaged_sp(
      m_backend.GetChildMemberWithName(ConstString("__engaged_"), true));

  if (!engaged_sp) {
    return false;
  }

  uint64_t num_elements = engaged_sp->GetValueAsSigned(0);

  m_elements.assign(num_elements, ValueObjectSP());
=======
  ValueObjectSP engaged_sp(
      m_backend.GetChildMemberWithName(ConstString("__engaged_"), true));

  if (!engaged_sp)
    return false;

  m_size = engaged_sp->GetValueAsSigned(0);

>>>>>>> a7193dc7d... Addressing comments
  return false;
}

ValueObjectSP OptionalFrontEnd::GetChildAtIndex(size_t idx) {
  if (idx >= m_size)
    return ValueObjectSP();

  ValueObjectSP val_sp(
      m_backend.GetChildMemberWithName(ConstString("__engaged_"), true)
          ->GetParent()
          ->GetChildAtIndex(0, true)
          ->GetChildMemberWithName(ConstString("__val_"), true));

  if (!val_sp)
    return ValueObjectSP();

  CompilerType holder_type = val_sp->GetCompilerType();

  if (!holder_type)
    return ValueObjectSP();

  return val_sp->Clone(ConstString(llvm::formatv("Value").str()));
}

SyntheticChildrenFrontEnd *
formatters::LibcxxOptionalFrontEndCreator(CXXSyntheticChildren *,
                                          lldb::ValueObjectSP valobj_sp) {
  if (valobj_sp)
    return new OptionalFrontEnd(*valobj_sp);
  return nullptr;
}
