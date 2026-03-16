/*========================== begin_copyright_notice ============================

Copyright (C) 2020-2021 Intel Corporation

SPDX-License-Identifier: MIT

============================= end_copyright_notice ===========================*/

#ifndef IGC_OPTIONS_H
#define IGC_OPTIONS_H

#include <llvm/Option/OptTable.h>

namespace IGC {
namespace options {
// Flags should not overlap with llvm::opt::DriverFlag.
constexpr unsigned FirstNonBuiltinFlagNum = 4;

enum Flags {
  // VC backend specific options.
  VCApiOption = (1 << FirstNonBuiltinFlagNum),
  VCInternalOption = (VCApiOption << 1),
  IgcmcApiOption = (VCInternalOption << 1),

  // Scalar IGC backend specific options.
  IGCApiOption = (IgcmcApiOption << 1),
  IGCInternalOption = (IGCApiOption << 1),
};

namespace api {

enum ID {
  OPT_INVALID = 0,
#if LLVM_VERSION_MAJOR >= 22
#define OPTION(PREFIX, NAME, ID, KIND, GROUP, ALIAS, ALIASARGS, FLAGS, VISIBILITY, PARAM, HELPTEXT, HELPTEXTSFORVARIANTS, METAVAR, VALUES, SUBCOMMANDIDS_OFFSET) OPT_##ID,
#else
#define OPTION(PREFIX, NAME, ID, KIND, GROUP, ALIAS, ALIASARGS, FLAGS, PARAM, HELPTEXT, METAVAR, VALUES) OPT_##ID,
#endif

#include "igc/Options/ApiOptions.inc"
  LastOption
#undef OPTION
};
} // namespace api

namespace internal {
enum ID {
  OPT_INVALID = 0,
#if LLVM_VERSION_MAJOR >= 22
#define OPTION(PREFIX, NAME, ID, KIND, GROUP, ALIAS, ALIASARGS, FLAGS, VISIBILITY, PARAM, HELPTEXT, HELPTEXTSFORVARIANTS, METAVAR, VALUES, SUBCOMMANDIDS_OFFSET) OPT_##ID,
#else
#define OPTION(PREFIX, NAME, ID, KIND, GROUP, ALIAS, ALIASARGS, FLAGS, PARAM, HELPTEXT, METAVAR, VALUES) OPT_##ID,
#endif

#include "igc/Options/InternalOptions.inc"
  LastOption
#undef OPTION
};
} // namespace internal

} // namespace options

const llvm::opt::OptTable &getApiOptTable();
const llvm::opt::OptTable &getInternalOptTable();
} // namespace IGC
#endif
