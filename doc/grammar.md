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
- sizeof
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

- _[DataTypeLiteral]_
- _[ArrayDataType]_

## DataTypeLiteral
[DataTypeLiteral]: #datatypeliteral

- `int32_t`
- `int64_t`
- `char`

## ArrayDataType
[ArrayDataType]: #ArrayDataType

- _[DataTypeLiteral]_ `[` `]`

## Identifier
[Identifier]: #identifier

- PCRE Regular Expression: `[a-zA-Z_$][a-zA-Z_$0-9]*`

## ParametersList
[ParametersList]: #parameterslist

- _[ParametersList]_ `,` _[Parameter]_
- _[Parameter]_

## Parameter
[Parameter]: #parameter

- _[DataTypeLiteral]_ _[Declarator]_
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
[Declarator]: #Declarator

- _[Identifier]_
- _[Identifier]_ `[` `]`
- _[Identifier]_ `[` _[Expression]_ `]`

For the fixed-size array declaration (third rule), the size can be any const expression.
We keep it as this in the grammar but using anything but a literal will throw a semantic error.

## FunctionDefinition
[FunctionDefinition]: #FunctionDefinition

- _[DataTypeLiteral]_ _[Identifier]_ `(` _[ParametersList]_ `)` _[Block]_

In the standard C, the return type can be any _[DataType]_ (such as `int`, `int *` or `struct {}`)
except for an array type with fixed or unknown array size (such as `int[]`, `int[5]`).

Since our language is a subset of C, only with a few primitive types and array types, it means
that the return type can be restricted to only _[DataTypeLiteral]_.

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

- _[DataTypeLiteral]_ _[VariableDeclaratorsList]_ `;`

## VariableDeclaratorsList
[VariableDeclaratorsList]: #variabledeclaratorslist

- _[VariableDeclaratorsList]_ `,` _[VariableDeclarator]_
- _[VariableDeclarator]_

## VariableDeclarator
[VariableDeclarator]: #variabledeclarator

- _[Declarator]_
- _[Declarator]_ `=` _[Expression]_

## Expression
[Expression]: #Expression

- _[Expression]_ _[Op]_ _[Expression]_
- _[VarUpdate]_
- _[LValue]_
- `(` _[Expression]_ `)`
- `-` _[Expression]_
- `+` _[Expression]_
- `!` _[Expression]_
- `~` _[Expression]_
- _[FunctionCall]_
- _[Identifier]_ `(` `)`
- _[LiteralExpression]_

## Op
[Op]: #Op

- One of: `,` `=` `*=` `/=` `%=` `+=` `-=` `<<=` `>>=` `&=` `^=` `|=` `||` `&&`
  `|` `^` `&` `==` `!=` `!=` `<` `>` `<=` `>=` `<<` `>>` `+` `-` `*` `/` `%`

Here is a table describing the properties of the various operators:

Operator                  | Name                      | Precedence | Associativity
--------------------------|---------------------------|------------|--------------
`,`                       | Sequence                  | 0          | left
`=`                       | Simple Assignment         | 1          | right
`*=`                      | Multiplication Assignment | 1          | right
`/=`                      | Division Assignment       | 1          | right
`%=`                      | Remainder Assignment      | 1          | right
`+=`                      | Addition Assignment       | 1          | right
`-=`                      | Subtraction Assignment    | 1          | right
`<<=`                     | Left Shift Assignment     | 1          | right
`>>=`                     | Right Shift Assignment    | 1          | right
`&=`                      | Bitwise And Assignment    | 1          | right
`^=`                      | Bitwise Xor Assignment    | 1          | right
<code>&#124;=</code>      | Bitwise Or Assignment     | 1          | right
<code>&#124;&#124;</code> | Logical Or                | 2          | left
`&&`                      | Logical And               | 3          | left
<code>&#124;</code>       | Bitwise Or                | 4          | left
`^`                       | Bitwise Xor               | 5          | left
`&`                       | Bitwise And               | 6          | left
`==`                      | Equality                  | 7          | left
`!=`                      | Inequality                | 8          | left
`<`                       | LessThan                  | 9          | left
`>`                       | GreaterThan               | 9          | left
`<=`                      | LessThanOrEqualTo         | 9          | left
`>=`                      | GreaterThanOrEqual        | 9          | left
`<<`                      | Left Shift                | 10         | left
`>>`                      | Right Shift               | 10         | left
`+`                       | Addition                  | 11         | left
`-`                       | Subtraction               | 11         | left
`*`                       | Multiplication            | 12         | left
`/`                       | Division                  | 12         | left
`%`                       | Remainder                 | 12         | left

## LValue
[LValue]: #lvalue

- _[Identifier]_
- _[Identifier]_ `[` _[Expression]_ `]`
- _[FunctionCall]_ `[` _[Expression]_ `]`

## VarUpdate
[VarUpdate]: #varupdate

- _[LValue]_ `++`
- _[LValue]_ `--`
- `++` _[LValue]_
- `--` _[LValue]_

## FunctionCall
[FunctionCall]: #functioncall

- _[Identifier]_ `(` _[FunctionCallParams]_ `)`
- _[Identifier]_ `(` `)`

## FunctionCallParams
[FunctionCallParams]: #functioncallparams

- _[FunctionCallParams]_ `,` _[Expression]_
- _[Expression]_

## Statement
[Statement]: #Statement

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

- `for` `(` _[ExpressionOrVoid]_ `;`  _[ExpressionOrVoid]_  `;` _[ExpressionOrVoid]_ `)` _[Statement]_
- `for` `(` _[VariableDeclaration]_ _[ExpressionOrVoid]_  `;` _[ExpressionOrVoid]_ `)` _[Statement]_

## ExpressionOrVoid
[ExpressionOrVoid]: #expressionorvoid

- _[Expression]_
- ε

## LiteralExpression
[LiteralExpression]: #LiteralExpression

- _[IntegerLiteral]_
- _[CharLiteral]_

## IntegerLiteral
[IntegerLiteral]: #IntegerLiteral

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
[SourceChar]: #SourceChar

- PCRE Regular Expression: `[^\\'\n]`

## EscapeSequence
[EscapeSequence]: #escapesequence

- _[OctalEscape]_
- `x` _[HexEscape]_
- `X` _[HexEscape]_
- _[ControlChar]_

## OctalEscape
[OctalEscape]: #octalescape

- PCRE Regular Expression: `[0-3][0-7]{2}`
- PCRE Regular Expression: `[0-7]{1,2}`

## HexEscape
[HexEscape]: #hexescape

- `[0-9a-fA-F]{2}`

## ControlChar
[ControlChar]: #controlchar

- One of: `a` `b` `f` `n` `r` `t` `v` <code>&#92;</code> `'` `"` `?`
