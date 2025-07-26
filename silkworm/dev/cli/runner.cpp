// Copyright 2025 The Silkworm Authors
// SPDX-License-Identifier: Apache-2.0

// #include <filesystem>

// #include <CLI/CLI.hpp>

#include "../state_transition.hpp"
#include "test_data.hpp"

// void execute_test(const std::string& json_str, bool terminate_flag, bool diagnostics_flag);
using namespace silkworm::cmd::state_transition;
// namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // CLI::App app{"Executes Ethereum State Transition tests"};

    // // std::string path = fs::current_path().append("state_transition_sample1.json");
    // // app.add_option("path", path, "Path to test file or directory")
    // // ->check(CLI::ExistingPath);

    // // path =

    // bool terminate_flag = false;
    // app.add_flag("-t,--terminateOnError", terminate_flag, "Terminate execution on failure");

    // bool diagnostics_flag = true;
    // app.add_flag("-d,--diagnostics", diagnostics_flag, "Enable extended diagnostics output");

    // CLI11_PARSE(app, argc, argv)

    if (argc > 1 && argv == nullptr) {
        argv = nullptr;
    }

    try {
        // execute_test(json_str, terminate_flag, diagnostics_flag);
        sample_run(silkworm::test_data::kAddTestJson);

    } catch (const std::exception& e) {
        // code to handle exceptions of type std::exception and its derived classes
        const auto desc = e.what();
        std::cerr << "Exception: " << desc << std::endl;
    } catch (...) {
        // code to handle any other type of exception
        std::cerr << "An unknown exception occurred" << std::endl;
    }
}

// void execute_test(const std::string& json_str1, bool terminate_flag, bool diagnostics_flag) {

//     auto state_transition = StateTransition(json_str1, terminate_flag, diagnostics_flag);
//     state_transition.run();
// }
