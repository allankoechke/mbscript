#ifndef MBSCRIPT_AST_H
#define MBSCRIPT_AST_H

#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include "../backend/runtime.h"

enum class NodeType: uint8_t {
    PROGRAM,
    STRING_LITERAL,
    NUMBER_LITERAL,
    BOOLEAN_LITERAL,
    NULL_LITERAL,
    IDENTIFIER,
    UNARY_EXPR,
    BINARY_EXPR,
};

struct AstNode {
    std::string name;
    NodeType type;

    AstNode(std::string name, NodeType type);
    virtual ~AstNode();
    virtual RuntimeValue eval() = 0;
    virtual std::string toString() = 0;
};

class AstRoot: AstNode {
public:
    AstRoot();
    ~AstRoot() override;

    void addNode(std::unique_ptr<AstNode> node);
    RuntimeValue eval() override { return {}; };
    std::string toString() override {
        std::stringstream oss;
        oss << "[\n";
        for (const auto& anode: m_astNodes) {
            oss << anode->toString();
        }
        oss << "\n]\n";

        return oss.str();
    }

private:
    std::pmr::vector<std::unique_ptr<AstNode> > m_astNodes;
};

struct UnaryExpr : AstNode {
    UnaryExpr(std::unique_ptr<AstNode> expr, std::string op);
    ~UnaryExpr() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "{ type: " << name;
        oss << ", op: " << m_op;
        oss << ", right: " << m_expr->toString();
        oss << " }";
        return oss.str();
    }

private:
    std::string m_op;
    std::unique_ptr<AstNode> m_expr;
};

struct BinaryExpr : AstNode {
    BinaryExpr(std::unique_ptr<AstNode> left, std::string op, std::unique_ptr<AstNode> right);
    ~BinaryExpr() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "\n{ ";
        oss << "\n\ttype: " << name;
        oss << ", \n\tleft: " << m_left->toString();
        oss << ", \n\top: " << m_op;
        oss << ", \n\tright: " << m_right->toString();
        oss << " \n}\n";
        return oss.str();
    }

private:
    std::string m_op;
    std::unique_ptr<AstNode> m_left, m_right;
};

struct IdentifierExpr : AstNode {
    explicit IdentifierExpr(std::string ident);
    ~IdentifierExpr() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "{ type: " << name << ", name: " << m_ident << " }";
        return oss.str();
    }

private:
    std::string m_ident;
};

struct BooleanLiteral : AstNode {
    explicit BooleanLiteral(bool status);
    ~BooleanLiteral() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "{ type: " << name << ", value: " << (m_bool ? "true" : "false") << " }";
        return oss.str();
    }

private:
    bool m_bool = false;
};

struct NumberLiteral : AstNode {
    explicit NumberLiteral(double val);
    ~NumberLiteral() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "{ type: " << name << ", value: " << m_val << " }";
        return oss.str();
    }

private:
    double m_val = 0.0;
};

struct NullLiteral : AstNode {
    explicit NullLiteral();
    ~NullLiteral() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "{ type: " << name << " }";
        return oss.str();
    }
};

struct StringLiteral : AstNode {
    explicit StringLiteral(std::string val);
    ~StringLiteral() override;
    RuntimeValue eval() override;
    std::string toString() override {
        std::stringstream oss;
        oss << "{ type: " << name << ", value: " << m_val << " }";
        return oss.str();
    }

private:
    std::string m_val;
};


#endif //MBSCRIPT_AST_H
