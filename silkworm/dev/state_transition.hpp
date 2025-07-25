// Copyright 2025 The Silkworm Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include <silkworm/core/execution/execution.hpp>
#include <silkworm/core/state/in_memory_state.hpp>

#include "expected_state.hpp"

namespace silkworm::cmd::state_transition {

class StateTransition {
  private:
    nlohmann::json test_data_;
    std::string test_name_;
    unsigned total_count_{};
    unsigned failed_count_{};
    bool terminate_on_error_{false};
    bool show_diagnostics_{false};

    void print_message(const ExpectedState& expected_state, const ExpectedSubState& expected_sub_state, const std::string& message);
    void print_error_message(const ExpectedState& expected_state, const ExpectedSubState& expected_sub_state, const std::string& message);
    void print_diagnostic_message(const ExpectedState& expected_state, const ExpectedSubState& expected_sub_state, const std::string& message);

  public:
    explicit StateTransition(const std::string& file_path) noexcept;
    explicit StateTransition(const std::string& json_str, bool terminate_on_error, bool show_diagnostics) noexcept;

    std::string name();
    std::string get_env(const std::string& key);
    bool contains_env(const std::string& key);
    std::vector<ExpectedState> get_expected_states();
    static evmc::address to_evmc_address(const std::string& address);
    Block get_block(InMemoryState& state, ChainConfig& chain_config);
    std::unique_ptr<InMemoryState> get_state();
    static std::unique_ptr<evmc::address> private_key_to_address(const std::string& private_key);
    Transaction get_transaction(const ExpectedSubState& expected_sub_state);
    void validate_transition(const Receipt& receipt, const ExpectedState& expected_state, const ExpectedSubState& expected_sub_state, const InMemoryState& state);
    void run();
  };
void sample_run(std::string json_str);

}  // namespace silkworm::cmd::state_transition
