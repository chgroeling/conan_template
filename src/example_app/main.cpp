#include "spdlog/sinks/basic_file_sink.h"
#include <algorithm>
#include <cxxopts.hpp>
#include <fmt/core.h>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <stdarg.h>
#include <vector>

static const std::vector<std::string> kValidLogLevels = {"TRACE",   "DEBUG", "INFO",
                                                        "WARNING", "ERROR", "CRITICAL"};

std::string CreateCommaSeparatedString(const std::vector<std::string> &input_set) {
  std::ostringstream oss;
  for (auto it = input_set.begin(); it != input_set.end(); ++it) {
    if (it != input_set.begin()) {
      oss << ", ";
    }
    oss << *it;
  }
  return oss.str();
}

int main(int argc, const char *argv[]) {
  // Parse command line options
const std::string kLogLevelOption =
      fmt::format("Set the log level ({})", CreateCommaSeparatedString(kValidLogLevels));
 
  cxxopts::Options options("example_add", "Armv7-m  emulator");
  options.positional_help("<path>");

  // clang-format off
  options.add_options()
    ("h,help", "Print usage information.")
    ("version", "Print version information.")
    ("l,log", "Enable logging")
    ("log-level" , kLogLevelOption, cxxopts::value<std::string>()->default_value("INFO"))
    ("log-file", "Specify log file path.", cxxopts::value<std::string>())
  ;
  // clang-format on

  // parse positional arguments into vector filenames
  options.parse_positional({"path"});

  cxxopts::ParseResult result;

  try {
    result = options.parse(argc, argv);
  } catch (const cxxopts::exceptions::exception &x) {
    fmt::print(stderr, "example_add: {}\n", x.what());
    fmt::print(stderr, "usage: example_add [options] <path> \n");
    return EXIT_FAILURE;
  }

  // print out help if necessary
  if (result.count("help")) {
    fmt::print(stdout, "{}", options.help());
    return EXIT_SUCCESS;
  }

  // Print version information if necessary
  if (result.count("version")) {

    // Both versions are the same for now
    fmt::print(stdout, "Version: 0.0.0\n");
    return EXIT_SUCCESS;
  }

    // Check defined log levels
  std::string log_level = result["log-level"].as<std::string>();
  if (std::find(kValidLogLevels.begin(), kValidLogLevels.end(), log_level) ==
      kValidLogLevels.end()) {
    fmt::print(stderr, "Error: Invalid log level '{}'. Valid log levels are: {}\n", log_level,
               CreateCommaSeparatedString(kValidLogLevels));
    return EXIT_FAILURE;
  }

   if (result.count("log")) {
    if (result.count("log-file")) {
      std::string log_file = result["log-file"].as<std::string>();
      // Create a file sink for the global logger and point it to a specific file
      auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file, true);

      // Set the default logger to use the file sink
      spdlog::set_default_logger(std::make_shared<spdlog::logger>("global_logger", file_sink));
    }

    spdlog::set_pattern("[%H:%M:%S,%f] [%^%l%$] %v");

    if (log_level == "TRACE") {
      spdlog::set_level(spdlog::level::trace);
    } else if (log_level == "DEBUG") {
      spdlog::set_level(spdlog::level::debug);
    } else if (log_level == "INFO") {
      spdlog::set_level(spdlog::level::info);
    } else if (log_level == "ERROR") {
      spdlog::set_level(spdlog::level::err);
    } else if (log_level == "WARNING") {
      spdlog::set_level(spdlog::level::warn);
    } else if (log_level == "CRITICAL") {
      spdlog::set_level(spdlog::level::critical);
    }
  }
  spdlog::debug("Debug Message");
  spdlog::info("Info Message");
  fmt::print(stdout, "Hello World\n");
  return EXIT_SUCCESS;
}
