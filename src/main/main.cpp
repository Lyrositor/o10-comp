#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <optionparser.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

#include <comp/as/ast.h>
#include <comp/as/emit.h>
#include <comp/ast/to_json.h>
#include <comp/as/arch/x64/build_asm.h>
#include <comp/ir/build_ir.h>
#include <comp/ir/program.h>
#include <comp/exceptions.h>
#include <comp/parser.h>
#include <comp/dot/ast.h>
#include <comp/ir/to_dot.h>
#include <comp/dot/emit.h>

#include "error_handling.h"

enum Options { Analyse, Ast, Compile, File, Help, Ir, Optimise, Output, Unknown };

static const option::Descriptor kUsage[] = {
  {
    Unknown,
    0,
    "",
    "",
    option::Arg::None,
    "Usage: o10c [options] file\nOptions:"
  },
  {
    File,
    0,
    "",
    "",
    option::Arg::Optional,
    "  file \tThe C file to analyze or compile."
  },
  {
    Help,
    0,
    "h",
    "help",
    option::Arg::None,
    "  --help, -h \tDisplay this information."
  },
  {
    Compile,
    0,
    "c",
    "compile",
    option::Arg::None,
    "  --compile, -c \tCompile the provided file to the GNU Assembler format."
  },
  {
    Analyse,
    0,
    "a",
    "analyse",
    option::Arg::None,
    "  --analyse, -a \tStatically analyse the provided file."
  },
  {
    Optimise,
    0,
    "o",
    "optimise",
    option::Arg::None,
    "  --optimise, -o \tAttempt to optimise the generated code."
  },
  {
    Ast,
    0,
    "",
    "ast",
    option::Arg::None,
    "  --ast \tDisplay a JSON representation of the generated abstract syntax tree."
  },
  {
    Ir,
    0,
    "",
    "ir",
    option::Arg::None,
    "  --dot \tEmit a Dot representation of the generated intermediate representation."
  },
  {
    Output,
    0,
    "",
    "output",
    option::Arg::Optional,
    "  --output \tOutput path for the ASM file."
  },
  {0, 0, 0, 0, 0, 0}
};

int main_exit(int retcode, option::Option buffer[], option::Option options[]) {
  delete[] buffer;
  delete[] options;
  return retcode;
}

int main(int argc, char **argv) {
  // Skip program name argv[0] if present
  if (argc > 0) {
    argc--;
    argv++;
  }

  // Parse the command-line arguments
  option::Stats stats(kUsage, argc, argv);
  option::Option *options = new option::Option[stats.options_max];
  option::Option *buffer = new option::Option[stats.buffer_max];
  option::Parser parse(kUsage, argc, argv, options, buffer);

  if (parse.error()) {
    std::cerr << "o10c: fatal error: could not parse arguments" << std::endl;
    std::cerr << "compilation terminated." << std::endl;
    return main_exit(EXIT_FAILURE, buffer, options);
  }

  // Display an error message if requested or if no arguments were provided
  if (options[Help] || argc == 0) {
    option::printUsage(std::cout, kUsage);
    return main_exit(EXIT_SUCCESS, buffer, options);
  }

  // Notify the user of any unknown options
  for (option::Option *opt = options[Unknown]; opt; opt = opt->next()) {
    std::cerr << "o10c: warning: unknown option: " << opt->name << std::endl;
  }

  // Ensure the user has provided a valid filename
  if (parse.nonOptionsCount() == 0) {
    std::cerr << "o10c: fatal error: no input files" << std::endl;
    std::cerr << "compilation terminated." << std::endl;
    return main_exit(EXIT_FAILURE, buffer, options);
  }
  std::string filename(parse.nonOptions()[0]);
  if (parse.nonOptionsCount() > 1) {
    std::cerr << "o10c: warning: only '" << filename << "' will be processed";
    std::cerr << std::endl;
  }
  if (filename.substr(filename.length() - 2) != ".c") {
    std::cerr << "o10c: fatal error: invalid file extension" << std::endl;
    std::cerr << "compilation terminated." << std::endl;
    return main_exit(EXIT_FAILURE, buffer, options);
  }

  // Read the provided file
  std::ifstream ifs(filename);
  if (ifs.fail()) {
    std::cerr << "o10c: error: " << filename << ": " << strerror(errno);
    std::cerr << std::endl;
    std::cerr << "o10c: fatal error: no input files" << std::endl;
    std::cerr << "compilation terminated." << std::endl;
    return main_exit(EXIT_FAILURE, buffer, options);
  }
  std::string content(
    (std::istreambuf_iterator<char>(ifs)),
    (std::istreambuf_iterator<char>()));

  // Try to parse the provided file, then perform additional operations if
  // the user has requested them
  try {
    std::shared_ptr<comp::ast::Program> program_ast = comp::parser::parse(
      content);

    // Perform static analysis of the provided source file
    if (options[Analyse]) {
      // TODO(Lyrositor) Perform static analysis on program
    }

    // Display a JSON representation of the AST
    if (options[Ast]) {
      std::unique_ptr<rapidjson::Document> document = comp::ast::ProgramToJson(
        *program_ast);
      rapidjson::StringBuffer json_buffer;
      rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(json_buffer);
      document->Accept(writer);
      std::cout << json_buffer.GetString() << std::endl;
    }

    if (!(options[Compile] || options[Ir])) {
      return main_exit(EXIT_SUCCESS, buffer, options);
    }

    std::shared_ptr<comp::ir::Program> program_ir = comp::ir::BuildProgramIR(
      *program_ast);
    if (options[Ir]) {
      std::unique_ptr<comp::dot::ast::Graph> program_graph = comp::ir::ProgramToDot(
        *program_ir);
      comp::dot::EmitGraph(*program_graph, std::cout);
      std::cout << std::endl;
    }

    // Compile the provided source file to an assembly file
    if (options[Compile]) {
      std::string asm_filename = filename.substr(0, filename.size() - 1) + "asm";
      if (options[Output]) {
        if (options[Output].arg == NULL) {
          std::cerr << "o10c: fatal error: output file path not specified";
          std::cerr << std::endl;
          std::cerr << "compilation terminated." << std::endl;
          return main_exit(EXIT_FAILURE, buffer, options);
        }
        asm_filename = options[Output].arg;
      }
      std::ofstream ofs(asm_filename);
      if (ofs.fail()) {
        std::cerr << "o10c: error: " << asm_filename << ": " << strerror(errno);
        std::cerr << std::endl;
        std::cerr << "o10c: fatal error: failed to open output file";
        std::cerr << std::endl;
        std::cerr << "compilation terminated." << std::endl;
        return main_exit(EXIT_FAILURE, buffer, options);
      }

      // Optimise the generated code
      if (options[Optimise]) {
        // TODO(Lyrositor) Optimise the generated code
      }

      std::shared_ptr<comp::as::ast::Program>
        program_asm = comp::as::arch::x64::BuildProgram(*program_ir);
      comp::as::EmitProgram(*program_asm, ofs);
    }
  } catch (comp::SyntaxException &e) {
    PrintSyntaxException(e, content, filename);
    return main_exit(EXIT_FAILURE, buffer, options);
  } catch (std::exception &e) {
    PrintException(e);
    return main_exit(EXIT_FAILURE, buffer, options);
  }

  return main_exit(EXIT_SUCCESS, buffer, options);
}
