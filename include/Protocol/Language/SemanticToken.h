#pragma once

#include "../Basic.h"

namespace clice::protocol {

enum class SemanticTokenTypes : uint8_t {
    Number,
    /// extension: represent a character literal,
    Char,
    String,
    Operator,
    Keyword,
    Comment,
    /// extension: represent a preprocessor directive,
    /// e.g. `#include`, `#define`
    Directive,
    /// extension: represent a header file path,
    /// e.g. `<iostream>`
    HeaderPath,
    Macro,
    /// extension: represent a macro parameter,
    /// e.g. `X` in `#define FOO(X) X`
    MacroParameter,
    Namespace,
    Type,
    Struct,
    /// extension: represent a union,
    Union,
    Class,
    /// extension: represent a field,
    Field,
    Enum,
    EnumMember,
    Variable,
    Function,
    Method,
    Parameter,
    /// extension, represent a type template parameter,
    /// e.g. `T` in `template <typename T> class Foo {};`
    TypeTemplateParameter,
    /// extension, represent a non-type template parameter,
    /// e.g. `N` in `template <int N> class Foo {};`
    NonTypeTemplateParameter,
    /// extension, represent a template template parameter,
    /// e.g. `T` in `template <template <typename> class T> class Foo {};`
    TemplateTemplateParameter,
    /// extension: represent a class template,
    ClassTemplate,
    /// extension, represent a function template,
    FunctionTemplate,
    /// extension, represent a variable template,
    VariableTemplate,
    /// extension, represent a concept(since C++20),
    Concept,
    /// extension, represent a attribute(since C++11),
    Attribute,
    Unknown
};

enum SemanticTokenModifiers : uint32_t {
    Declaration = 1 << 0,
    Definition = 1 << 1,
    Const = 1 << 2,
    Constexpr = 1 << 3,
    Consteval = 1 << 4,
    Virtual = 1 << 5,
    PureVirtual = 1 << 6,
    Inline = 1 << 7,
    Static = 1 << 8,
    Deprecated = 1 << 9,
    Local = 1 << 10,
};

/// Client Capability:
/// - property name(optional): `textDocument.semanticTokens`
/// - property type: `SemanticTokensClientCapabilities` defined as follows:
struct SemanticTokensClientCapabilities {
    /// Whether implementation supports dynamic registration. If this is set to `true` the client
    bool dynamicRegistration = false;

    struct Requests {
        // FIXME:
    };

    /// The token types that the client supports.
    std::vector<String> tokenTypes;

    /// The token modifiers that the client supports.
    std::vector<String> tokenModifiers;

    /// The formats the client supports.
    /// formats: TokenFormat[];

    /// Whether the client supports tokens that can overlap each other.
    bool overlappingTokenSupport = false;

    /// Whether the client supports tokens that can span multiple lines.
    bool multilineTokenSupport = false;

    /// Whether the client allows the server to actively cancel a semantic token request.
    bool serverCancelSupport = false;

    /// Whether the client uses semantic tokens to augment existing syntax tokens.
    bool serverCancelSupports = false;
};

struct SemanticTokensLegend {
    /// The token types a server uses.
    std::vector<String> tokenTypes;

    /// The token modifiers a server uses.
    std::vector<String> tokenModifiers;
};

/// Server Capability:
/// - property name(optional): `textDocument.semanticTokens`
/// - property type: `SemanticTokensOptionss` defined as follows:
struct SemanticTokensOptions {
    /// The legend used by the server.
    SemanticTokensLegend legend;

    /// Server supports providing semantic tokens for a specific range.
    bool range = false;

    /// Server supports providing semantic tokens for a full document.
    bool full = false;
};

/// Request:
/// - method: `textDocument/semanticTokens/full`
/// - params: `SemanticTokensParams` defined as follows:
struct SemanticTokensParamsBody {
    /// The text document.
    TextDocumentIdentifier textDocument;
};

using SemanticTokensParams = Combine<
    // WorkDoneProgressParams,
    // PartialResultParams,
    SemanticTokensParamsBody>;

/// Response:
/// - result: `SemanticTokens` defined as follows:
struct SemanticTokens {
    /// An optional result id.
    String resultId;

    /// The actual tokens.
    std::vector<Integer> data;
};

}  // namespace clice::protocol
