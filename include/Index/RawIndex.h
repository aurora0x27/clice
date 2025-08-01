#pragma once

#include "Contextual.h"
#include "AST/SymbolID.h"
#include "AST/SymbolKind.h"
#include "AST/RelationKind.h"
#include "AST/SourceCode.h"

namespace clice::index::memory {

using SymbolID = std::uint64_t;

struct Relation {
    /// The context of this relation.
    Contextual ctx;

    /// The relation kind of this relation.
    RelationKind kind;

    /// The range of this relation.
    LocalSourceRange range;

    /// A field to store extra information depend on kind.
    union {
        SymbolID target_symbol;
        LocalSourceRange definition_range;
    };
};

struct Symbol {
    /// The symbol id.
    SymbolID id;

    /// The symbol kind.
    SymbolKind kind;

    /// Whether this symbol is not visible to other tu.
    bool is_tu_local = false;

    /// Whether this symbol is defined in function scope.
    bool is_function_local = false;

    /// The symbol name.
    std::string name;

    /// All relations of this symbol.
    llvm::DenseSet<Relation> relations;
};

struct Occurrence {
    /// The context of this occurrence.
    Contextual ctx;

    /// The target symbol of this occurrence.
    SymbolID target_symbol;
};

/// The raw index directly generated by indexing the source file.
struct RawIndex {
public:
    Symbol& get_symbol(SymbolID ID) {
        /// If not found, create a new symbol and return it.
        auto [it, _] = symbols.try_emplace(ID, Symbol{.id = ID});
        return it->second;
    }

    void add_relation(Symbol& symbol, Relation relation, bool is_dependent = true) {
        relation.ctx = Contextual::from(is_dependent, 0);
        symbol.relations.insert(relation);
    }

    void add_occurrence(LocalSourceRange range, SymbolID target_symbol, bool is_dependent = true) {
        occurrences[range].emplace_back(Contextual::from(is_dependent, 0), target_symbol);
    }

public:
    /// The path of source file.
    std::string path;

    /// The content of source file.
    std::string content;

    /// All symbols in this index.
    llvm::DenseMap<SymbolID, Symbol> symbols;

    /// All occurrences in this index.
    llvm::DenseMap<LocalSourceRange, llvm::SmallVector<Occurrence, 1>> occurrences;
};

}  // namespace clice::index::memory
