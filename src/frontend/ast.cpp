#include "../../includes/mbs/frontend/ast.h"

// ------------ AST NODE -------------------- //
AstNode::AstNode(std::string name, const NodeType type)
    : name(std::move(name)),
      type(type) {
}

AstNode::~AstNode() = default;

// ------------ AST ROOT -------------------- //
AstRoot::AstRoot() : AstNode("Program", NodeType::PROGRAM) {
}

AstRoot::~AstRoot() = default;

void AstRoot::addNode(std::unique_ptr<AstNode> node) {
    m_astNodes.push_back(std::move(node));
}

// ------------ UNARY EXPR -------------------- //
UnaryExpr::UnaryExpr(std::unique_ptr<AstNode> expr, std::string op)
    : AstNode("UnaryExpr", NodeType::UNARY_EXPR),
      m_op(std::move(op)),
      m_expr(std::move(expr)) {
}

UnaryExpr::~UnaryExpr() = default;

RuntimeValue UnaryExpr::eval() {
    return {};
}

// ------------ BINARY EXPR -------------------- //
BinaryExpr::BinaryExpr(std::unique_ptr<AstNode> left, std::string op, std::unique_ptr<AstNode> right)
    : AstNode("BinaryExpr", NodeType::BINARY_EXPR),
      m_op(std::move(op)),
      m_left(std::move(left)),
      m_right(std::move(right)) {
}

BinaryExpr::~BinaryExpr() = default;

RuntimeValue BinaryExpr::eval() {
    return {};
}

// ------------ IDENTIFIER LIT -------------------- //
IdentifierExpr::IdentifierExpr(std::string ident)
    : AstNode("IdentifierExpr", NodeType::IDENTIFIER),
      m_ident(std::move(ident)) {
}

IdentifierExpr::~IdentifierExpr() = default;

RuntimeValue IdentifierExpr::eval() {
    return {};
}

// ------------ BOOLEAN LIT -------------------- //
BooleanLiteral::BooleanLiteral(const bool status)
    : AstNode("BooleanLiteral", NodeType::BOOLEAN_LITERAL),
      m_bool(status) {
}

BooleanLiteral::~BooleanLiteral() = default;

RuntimeValue BooleanLiteral::eval() {
    return {};
}

// ------------ NUMBER LIT -------------------- //
NumberLiteral::NumberLiteral(const double val)
    : AstNode("NumberLiteral", NodeType::NUMBER_LITERAL),
      m_val(val) {
}

NumberLiteral::~NumberLiteral() = default;

RuntimeValue NumberLiteral::eval() {
    return {};
}

// ------------ NULL LIT -------------------- //
NullLiteral::NullLiteral()
    : AstNode("NullLiteral", NodeType::NULL_LITERAL) {
}

NullLiteral::~NullLiteral() = default;

RuntimeValue NullLiteral::eval() {
    return {};
}

// ------------ STRING LIT -------------------- //
StringLiteral::StringLiteral(std::string val)
    : AstNode("StringLiteral", NodeType::NULL_LITERAL),
      m_val(std::move(val)) {
}

StringLiteral::~StringLiteral() = default;

RuntimeValue StringLiteral::eval() {
    return {};
}
