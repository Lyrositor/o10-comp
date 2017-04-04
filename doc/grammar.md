# C Grammar

[C99 Specification](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf)

## Choices of conception :

- trigraphs are not implemented
- break, continue and goto are not implemented
- do..while and switch..case are not implemented
- inline and volatile are not implemented
- we should use a number/constant to make a global affectation (e.g int a = 3 works but int a = 3 + 3 doesn't )
- The %-alternate forms are not implemented (<% %: ...)
- no multidimensional arrays
- no sizeof
- 3 types, no struct, typeof ...

## white-space characters

Each keyword should be separated by at least one white-space character.

White-space characters are the following : 
- `space (' ')`
- `form feed ('\f')`
- `new-line ('\n')`
- `carriage return ('\r')`
- `horizontal tab ('\t')`
- `vertical tab ('\v')`

Moreover, comments are treated as a white-space characters:
They correspond to the following regular expressions (using PCRE notation):

- `/\*[\s\S]*\*/`
- `//[^\n]+`
- `(^|\n)#[^\n]+`

## Program
[Program]: #program

- _[DeclarationsList]_

## DeclarationsList
[DeclarationsList]: #declarationslist

- _[DeclarationsList]_ _[FunctionDeclaration]_
- _[DeclarationsList]_ _[VariableDeclaration]_
- _[DeclarationsList]_ _[FunctionDefinition]_
- ε

## FunctionDeclaration
[FunctionDeclaration]: #functiondeclaration

- _[DataType]_ _[Identifier]_ `(` _[ParametersList]_ `)` `;`
- _[DataType]_ _[Identifier]_ `(` `)` `;`

## DataType
[DataType]: #datatype

- _[IdentifierDataType]_
- _[ArrayDataType]_

## IdentifierDataType
[IdentifierDataType]: #identifierdatatype

- `int32_t`
- `int64_t`
- `char`
- `void`

## ArrayDataType
[ArrayDataType]: #arraydatatype

- _[IdentifierDataType]_ `[` `]`

## Identifier
[Identifier]: #identifier

- PCRE Regular Expression: `[a-zA-Z_$][a-zA-Z_$0-9]*`

## ParametersList
[ParametersList]: #parameterslist

- _[ParametersList]_ `,` _[Parameter]_
- _[Parameter]_

## Parameter
[Parameter]: #parameter

- _[IdentifierDataType]_ _[Declarator]_
- _[DataType]_

It means that there are two kinds of parameters: named and anonymous parameters.
For example, you can have the following function definition:

```c
void foo(int a[], int[]) {
  // ...
}
```

This functions takes two array pointers as parameters but only the first parameter is
used so the second one is an anonymous parameter. This can be used to implement to have
a given function signature without producing "unused variable" warnings.

## Declarator
[Declarator]: #declarator

- _[Identifier]_
- _[Identifier]_ `[` `]`
- _[Identifier]_ `[` _[Expression]_ `]`

For the fixed-size array declaration (third rule), the size can be any const expression.
We keep it as this in the grammar but using anything but a literal will throw a semantic error.

## FunctionDefinition
[FunctionDefinition]: #functiondefinition

- _[IdentifierDataType]_ _[Identifier]_ `(` _[ParametersList]_ `)` _[Block]_
- _[IdentifierDataType]_ _[Identifier]_ `(` `)` _[Block]_

In the standard C, the return type can be any _[DataType]_ (such as `int`, `int *` or `struct {}`)
except for an array type with fixed or unknown array size (such as `int[]`, `int[5]`).

Since our language is a subset of C, only with a few primitive types and array types, it means
that the return type can be restricted to only _[IdentifierDataType]_.

## Block
[Block]: #Block

- `{` _[BlockContent]_ `}`
- `{` `}`

## BlockContent
[BlockContent]: #blockcontent

- _[BlockContent]_ _[VariableDeclaration]_
- _[BlockContent]_ _[Statement]_
- _[VariableDeclaration]_
- _[Statement]_

## VariableDeclaration
[VariableDeclaration]: #variabledeclaration

- _[IdentifierDataType]_ _[VariableDeclaratorsList]_ `;`

## VariableDeclaratorsList
[VariableDeclaratorsList]: #variabledeclaratorslist

- _[VariableDeclaratorsList]_ `,` _[VariableDeclarator]_
- _[VariableDeclarator]_

## VariableDeclarator
[VariableDeclarator]: #variabledeclarator

- _[Declarator]_
- _[Declarator]_ `=` _[AssignmentExpression]_

## Expression
[Expression]: #expression

- _[Expression]_ `,` _[Expression]_
- _[AssignmentExpression]_

## AssignmentExpression
[AssignmentExpression]: #assignmentexpression

- _[Lvalue]_ `=` _[AssignmentExpression]_
- _[Lvalue]_ `*=` _[AssignmentExpression]_
- _[Lvalue]_ `/=` _[AssignmentExpression]_
- _[Lvalue]_ `%=` _[AssignmentExpression]_
- _[Lvalue]_ `+=` _[AssignmentExpression]_
- _[Lvalue]_ `-=` _[AssignmentExpression]_
- _[Lvalue]_ `<<=` _[AssignmentExpression]_
- _[Lvalue]_ `>>=` _[AssignmentExpression]_
- _[Lvalue]_ `&=` _[AssignmentExpression]_
- _[Lvalue]_ `^=` _[AssignmentExpression]_
- _[Lvalue]_ `|=` _[AssignmentExpression]_
- _[ConditionalExpression]_

## LValue
[LValue]: #lvalue

- _[Identifier]_
- _[Identifier]_ `[` _[Expression]_ `]`
- `(` _[LValue]_ `)`

## ConditionalExpression
[ConditionalExpression]: #conditionalexpression

- _[LogicalORExpression]_ `?` _[expression]_ `:` _[ConditionalExpression]_
- _[LogicalORExpression]_

## LogicalORExpression
[LogicalORExpression]: #logicalorexpression

- _[LogicalORExpression]_ `||` _[LogicalANDExpression]_
- _[LogicalANDExpression]_

## LogicalANDExpression
[LogicalANDExpression]: #logicalandexpression

- _[LogicalANDExpression]_ `&&` _[InclusiveORExpression]_
- _[InclusiveORExpression]_

## InclusiveORExpression
[InclusiveORExpression]: #inclusiveorexpression

- _[InclusiveORExpression]_ `|` _[ExclusiveORExpression]_
- _[ExclusiveORExpression]_

## ExclusiveORExpression
[ExclusiveORExpression]: #exclusiveorexpression

- _[ExclusiveORExpression]_ `^` _[ANDExpression]_
- _[ANDExpression]_

## ANDExpression
[ANDExpression]: #andexpression

- _[ANDExpression]_ `&` _[EqualityExpression]_
- _[EqualityExpression]_

## EqualityExpression
[EqualityExpression]: #equalityexpression

- _[EqualityExpression]_ `==` _[RelationalExpression]_
- _[EqualityExpression]_ `!=` _[RelationalExpression]_
- _[RelationalExpression]_

## RelationalExpression
[RelationalExpression]: #relationalexpression

- _[RelationalExpression]_ `>` _[ShiftExpression]_
- _[RelationalExpression]_ `<` _[ShiftExpression]_
- _[RelationalExpression]_ `>=` _[ShiftExpression]_
- _[RelationalExpression]_ `<=` _[ShiftExpression]_
- _[ShiftExpression]_

## ShiftExpression
[ShiftExpression]: #shiftexpression

- _[ShiftExpression]_ `>>` _[AdditiveExpression]_
- _[ShiftExpression]_ `<<` _[AdditiveExpression]_
- _[AdditiveExpression]_

## AdditiveExpression
[AdditiveExpression]: #additiveexpression

- _[AdditiveExpression]_ `+` _[MultiplicativeExpression]_
- _[AdditiveExpression]_ `-` _[MultiplicativeExpression]_
- _[MultiplicativeExpression]_

## MultiplicativeExpression
[MultiplicativeExpression]: #multiplicativeexpression

- _[MultiplicativeExpression]_ `*` _[UnaryExpression]_
- _[MultiplicativeExpression]_ `/` _[UnaryExpression]_
- _[MultiplicativeExpression]_ `%` _[UnaryExpression]_
- _[UnaryExpression]_

## UnaryExpression
[UnaryExpression]: #unaryexpression


- `+` _[UnaryExpression]_
- `-` _[UnaryExpression]_
- `~` _[UnaryExpression]_
- `!` _[UnaryExpression]_
- _[PrimaryExpression]_

## PrimaryExpression
[PrimaryExpression]: #primaryexpression

- _[VarUpdate]_
- _[CallExpression]_
- _[LValue]_
- `(` _[Expression]_ `)`
- _[LiteralExpression]_

## VarUpdate
[VarUpdate]: #varupdate

- _[LValue]_ `++`
- _[LValue]_ `--`
- `++` _[LValue]_
- `--` _[LValue]_

## CallExpression
[CallExpression]: #callexpression

- _[Identifier]_ `(` _[CallExpressionArguments]_ `)`
- _[Identifier]_ `(` `)`

## CallExpressionArguments
[CallExpressionArguments]: #callexpressionarguments

- _[CallExpressionArguments]_ `,` _[AssignmentExpression]_
- _[AssignmentExpression]_

## Statement
[Statement]: #statement

- _[ExpressionStatement]_
- _[ReturnStatement]_
- _[Block]_
- _[IfStatement]_
- _[WhileStatement]_
- _[ForStatement]_
- `;`

## ExpressionStatement
[ExpressionStatement]: #expressionstatement

- _[Expression]_ `;`

## ReturnStatement
[ReturnStatement]: #returnstatement

- `return` _[Expression]_ `;`
- `return` `;`

## IfStatement
[IfStatement]: #ifstatement

- `if` `(` _[Expression]_ `)` _[Statement]_  `else` _[Statement]_
- `if` `(` _[Expression]_ `)` _[Statement]_

## WhileStatement
[WhileStatement]: #whilestatement

- `while` `(` _[Expression]_ `)` _[Statement]_

## ForStatement
[ForStatement]: #forstatement

- `for` `(` _[ForInitializer]_ _[OptionalExpression]_  `;` _[OptionalExpression]_ `)` _[Statement]_

## ForInitializer
[ForInitializer]: #forinitializer

- _[Expression]_ `;`
- _[VariableDeclaration]_
- `;`

## OptionalExpression
[OptionalExpression]: #optionalexpression

- _[Expression]_
- ε

## LiteralExpression
[LiteralExpression]: #literalexpression

- _[IntegerLiteral]_
- _[CharLiteral]_

## IntegerLiteral
[IntegerLiteral]: #integerliteral

- PCRE Regular Expression: `[0-9]+`
- PCRE Regular Expression: `0[xX][0-9A-Fa-f]+`

## CharLiteral
[CharLiteral]: #charliteral

-  `'` _[CharAtom]_ `'`

## CharAtom
[CharAtom]: #charatom

- _[SourceChar]_
- <code>&#92;</code> _[EscapeSequence]_

## SourceChar
[SourceChar]: #sourcechar

- PCRE Regular Expression: `[^\\'\n]`

## EscapeSequence
[EscapeSequence]: #escapesequence

- _[OctalEscape]_
- `x` _[HexEscape]_
- `X` _[HexEscape]_
- _[ControlChar]_

## OctalEscape
[OctalEscape]: #octalescape

- PCRE Regular Expression: `[1-7]?[0-7]|[1-3][0-7]{2}`

## HexEscape
[HexEscape]: #hexescape

- `[0-9a-fA-F]{2}`

## ControlChar
[ControlChar]: #controlchar

- One of: `a` `b` `f` `n` `r` `t` `v` <code>&#92;</code> `'` `"` `?`
