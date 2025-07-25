# Copyright 2025 The Silkworm Authors
# SPDX-License-Identifier: Apache-2.0

if(SILKWORM_WASM_API)
  add_compile_definitions(EVMC_LOADER_MOCK)
endif()
add_subdirectory(evmone/evmc)

add_library(
  evmone
  evmone/lib/evmone/advanced_analysis.cpp
  evmone/lib/evmone/advanced_analysis.hpp
  evmone/lib/evmone/advanced_execution.cpp
  evmone/lib/evmone/advanced_execution.hpp
  evmone/lib/evmone/advanced_instructions.cpp
  evmone/lib/evmone/baseline_analysis.cpp
  evmone/lib/evmone/baseline_execution.cpp
  evmone/lib/evmone/baseline_instruction_table.cpp
  evmone/lib/evmone/baseline_instruction_table.hpp
  evmone/lib/evmone/baseline.hpp
  evmone/lib/evmone/constants.hpp
  evmone/lib/evmone/delegation.cpp
  evmone/lib/evmone/delegation.hpp
  evmone/lib/evmone/eof.cpp
  evmone/lib/evmone/eof.hpp
  evmone/lib/evmone/execution_state.hpp
  evmone/lib/evmone/instructions_calls.cpp
  evmone/lib/evmone/instructions_opcodes.hpp
  evmone/lib/evmone/instructions_storage.cpp
  evmone/lib/evmone/instructions_traits.hpp
  evmone/lib/evmone/instructions_xmacro.hpp
  evmone/lib/evmone/instructions.hpp
  evmone/lib/evmone/tracing.cpp
  evmone/lib/evmone/tracing.hpp
  evmone/lib/evmone/vm.cpp
  evmone/lib/evmone/vm.hpp
  evmone/lib/evmone_precompiles/blake2b.cpp
  evmone/lib/evmone_precompiles/ripemd160.cpp
  evmone/lib/evmone_precompiles/sha256.cpp
  evmone/lib/evmone_precompiles/kzg.cpp
  evmone/lib/evmone_precompiles/bn254.cpp
  evmone/lib/evmone_precompiles/secp256k1.cpp
  evmone/lib/evmone_precompiles/bls.cpp
  evmone/test/state/host.cpp
  evmone/test/state/precompiles.cpp
  evmone/test/state/state.cpp
)
set_source_files_properties(evmone/lib/evmone/vm.cpp PROPERTIES COMPILE_DEFINITIONS PROJECT_VERSION="0.11.0")
target_include_directories(
  evmone
  PUBLIC evmone/include evmone/lib
  INTERFACE .
  PRIVATE ../..
)
target_link_libraries(
  evmone
  PUBLIC evmc intx::intx blst::blst
  PRIVATE ethash::keccak
)

if(MSVC)
  target_compile_options(evmone PRIVATE /EHsc /w)
else()
  target_compile_options(
    evmone
    PRIVATE -fno-exceptions
            # evmone uses vendor specific attributes without macro guards.
            # https://github.com/ethereum/evmone/blob/master/CMakeLists.txt#L62-L66
            $<$<CXX_COMPILER_ID:GNU>:-Wno-attributes>
            $<$<CXX_COMPILER_ID:Clang,AppleClang>:-Wno-unknown-attributes>
  )
endif()

if(SILKWORM_CORE_USE_ABSEIL)
  # Propagate SILKWORM_CORE_USE_ABSEIL to allow using Silkworm's preferred FlatHashMap.
  find_package(absl REQUIRED)
  target_compile_definitions(evmone PRIVATE SILKWORM_CORE_USE_ABSEIL)
  target_link_libraries(evmone PRIVATE absl::flat_hash_map)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/evmone/include
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/evmone/test/state
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/evmone/test
  FILES_MATCHING PATTERN "*.hpp"
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/evmone/lib/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.hpp"
)