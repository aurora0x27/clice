#pragma once

#include "AST/SymbolKind.h"
#include "AST/SourceCode.h"
#include "Index/Shared.h"

namespace clice::config {

struct HoverOptions {
    /// Strip doxygen info and merge with lsp info
    bool enable_doxygen_parsing = true;
    /// If set `false`, the comment will be wrapped
    /// in code block and keep ascii typesetting
    bool parse_comment_as_markdown = true;
    /// Show sugar type
    bool show_aka = true;
};

}  // namespace clice::config

namespace clice::feature {

struct HoverItem {
    enum class HoverKind : uint8_t {
        /// The typename of a variable or a type alias.
        Type,
        /// Size of type or variable.
        Size,
        /// Align of type or variable.
        Align,
        /// Offset of field in a class/struct.
        Offset,
        /// Bit width of a bit field.
        BitWidth,
        /// The index of a field in a class/struct.
        FieldIndex,
        /// The value of an enum item.
        EnumValue,
    };

    using enum HoverKind;

    HoverKind kind;

    std::string value;
};

/// Hover information for a symbol.
struct Hover {
    /// Title
    SymbolKind kind;
    std::string name;

    /// Extra information.
    std::vector<HoverItem> items;

    /// Raw document in the source code.
    std::string document;

    /// The full qualified name of the declaration.
    std::string qualifier;

    /// The source code of the declaration.
    std::string source;
};

/// Hover information for all symbols in the file.
struct Hovers {
    struct Occurrence {
        LocalSourceRange range;
        uint32_t index;
    };

    /// Hover information for all symbols in the file.
    std::vector<Hover> hovers;

    /// A map between the file offset and the index of the hover.
    std::vector<Occurrence> occurrences;
};

/// Generate the hover information for the given declaration(for test).
Hover hover(CompilationUnit& unit, const clang::NamedDecl* decl);

/// Generate the hover information for the symbol at the given offset.
Hover hover(CompilationUnit& unit, uint32_t offset);

/// Generate the hover information for all files in the given unit.
index::Shared<Hovers> indexHover(CompilationUnit& unit);

}  // namespace clice::feature

