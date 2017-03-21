# C Grammar

[C99 Specification](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf)

## Choices of conception :

- trigraphs are not implemented
- break and continue are not implemented
- we should use a number/constant to make a global affectation (e.g int a = 3 works but int a = 3 + 3 doesn't )
- The %-alternate forms are not matched (<% %: ...)

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

- `\/\*.*\*\/`
- `\/\/[^\n]+`
- `(^|\n)#[^\n]+`

## Program
[Program]: #program

- _[declarationsList]_

## declarationsList
[declarationsList]: #declarationslist

- _[declarationsList]_ _[fonctionDeclaration]_
- _[declarationsList]_ _[variableDeclarationOrAffectationLitteral]_ `;`
- _[declarationsList]_ _[functionDefinition]_
- ε

## fonctionDeclaration
[fonctionDeclaration]: #fonctionDeclaration

- _[dataType]_ _[identifier]_ `(` _[declarationParametersList]_ `)` `;`

DataType = ArrayDataType | LiteralDataType
ArrayDataType = DataType "[" IntegerLiteral "]"

## dataType
[dataType]: #datatype

- `int32_t`
- `int64_t`
- `char`

## identifier
[identifier]: #identifier

- `[a-zA-Z_$][a-zA-Z_$0-9]*`

## declarationParametersList
[declarationParametersList]: #declarationParametersList

- _[nonEmptyDeclarationParametersList]_
- ε

## nonEmptyDeclarationParametersList
[nonEmptyDeclarationParametersList]: #nonEmptyDeclarationParametersList

- _[nonEmptyDeclarationParametersList]_ `,` _[declarationParameters]_
- _[declarationParameters]_

## declarationParameters
[declarationParameters]: #declarationParameters

- _[definitionParameters]_
- _[dataType]_
- _[dataType]_  `[` `]`

## definitionParameters
[definitionParameters]: #definitionParameters

- _[dataType]_ _[identifier]_
- _[dataType]_ _[identifier]_ `[` `]`

## variableDeclarationOrAffectationLitteral
[variableDeclarationOrAffectationLitteral]: #variableDeclarationOrAffectationLitteral

- _[variableDeclarationOrAffectationLitteral]_ `,` _[restOfVarDecAffLitteral]_
- _[dataType]_ _[restOfVarDecAffLitteral]_

## restOfVarDecAffLitteral
[restOfVarDecAffLitteral]: #restOfVarDecAffLitteral

- _[variableIdentifierArrayLiteral]_
- _[identifier]_ `=` _[LiteralExpression]_

## variableIdentifierArrayLiteral
[variableIdentifierArrayLiteral]: #variableIdentifierArrayLiteral

- _[identifier]_
- _[identifier]_ `[` _[integerLiteral]_ `]`

## integerLiteral
[integerLiteral]: #integerLiteral

- `[0-9]+`

## LiteralExpression
[LiteralExpression]: #LiteralExpression

- _[integerLiteral]_
- _[charLiteral]_

## charLiteral
[charLiteral]: #charliteral

-  `'` _[atomicChar]_ `'`

## atomicChar
[atomicChar]: #atomicChar

- _[sourceChar]_
- <code>&#92;</code> _[escapeSequence]_

## sourceChar
[sourceChar]: #sourcechar

- `[^\\'\n]`

## escapeSequence
[escapeSequence]: #escapesequence

- _[octalEscape]_
- `x` _[hexEscape]_
- _[escapeChar]_

## octalEscape
[octalEscape]: #octalescape

- `[0-3][0-7]{2}`
- `[0-7]{1,2}`

## hexEscape
[hexEscape]: #hexescape

- `[0-9a-fA-F]{2}`

## escapeChar
[escapeChar]: #escapechar

- `[abfnrtv\\'"?]`

## functionDefinition
[functionDefinition]: #functionDefinition

- _[dataType]_ _[identifier]_ `(` _[definitionParametersList]_ `)` _[bloc]_

## definitionParametersList
[definitionParametersList]: #definitionParametersList

- _[nonEmptyDefinitionParametersList]_
- ε

## nonEmptyDefinitionParametersList
[nonEmptyDefinitionParametersList]: #nonEmptyDefinitionParametersList

- _[nonEmptyDefinitionParametersList]_ `,` _[definitionParameters]_
- _[definitionParameters]_

## bloc
[bloc]: #bloc

- `{`insideBloc`}`

## insideBloc
[insideBloc]: #insidebloc

- _[insideBloc]_ _[variableDeclarationOrAffectation]_ `;`
- _[insideBloc]_ _[return]_
- _[insideBloc]_ _[instruction]_
- ε

## variableDeclarationOrAffectation
[variableDeclarationOrAffectation]: #variableDeclarationOrAffectation

- _[variableDeclarationOrAffectation]_ `,` _[restOfVarDecAff]_
- _[dataType]_ _[restOfVarDecAff]_

## restOfVarDecAff
[restOfVarDecAff]: #restOfVarDecAff

- _[variableIdentifierArrayLiteral]_
- _[identifier]_ `=` _[expression]_


## return
[return]: #return

- `return` _[expressionOrVoid]_ `;`

## expressionOrVoid
[expressionOrVoid]: #expressionOrVoid

- _[expression]_
- ε 

## expression
[expression]: #expression

- _[expression]_ _[OP]_ _[expression]_
- _[LiteralExpression]_
- _[variableAffectation]_
- _[varUpdate]_
- _[varIdentifier]_
- `(` _[expression]_ `)`
- `-` _[expression]_
- `+` _[expression]_
- `!` _[expression]_
- `~` _[expression]_
- _[functionCall]_
- _[identifier]_ `(` `)`

## op
[op]: #op

- `==`
- `!=`
- `<`
- `<=`
- `>`
- `>=`
- `<<`
- `>>`
- `=`
- `+`
- `-`
- `*`
- `/`
- `%`
- `+=`
- `-=`
- `*=`
- `/=`
- `%=`
- `<<=`
- `>>=`
- `&=`
- `^=`
- `|=`
- `|`
- `^`
- `&`
- `||`
- `&&`
- `,`

## variableAffectation
[variableAffectation]: #variableAffectation

- _[varIdentifier]_ `=` expression]_

## varIdentifier
[varIdentifier]: #varidentifier

- _[identifier]_
- _[identifier]_ `[` _[expression]_ `]`
- _[functionCall]_ `[` _[expression]_ `]`

## varUpdate
[varUpdate]: #varupdate

- _[varIdentifier]_ `++`
- _[varIdentifier]_ `--`
- `++` _[varIdentifier]_
- `--` _[varIdentifier]_

## functionCall
[functionCall]: #functioncall

- _[identifier]_ `(` _[functionCallParamsOrVoid]_ `)`

## functionCallParamsOrVoid
[functionCallParams]: #functioncallparams

- _[functionCallParams]_
- ε

## functionCallParams
[functionCallParams]: #functioncallparams

- _[functionCallParams]_ `,` _[expression]_
- _[expression]_

## instruction
[instruction]: #instruction

- _[expression]_ `;`
- _[bloc]_
- _[if]_
- _[while]_
- _[for]_
- `;`

## if
[if]: #if

- `if` `(` _[expression]_ `)` _[instruction]_  `else` _[instruction]_
- `if` `(` _[expression]_ `)` _[instruction]_

## while
[while]: #while

- `while` `(` _[expression]_ `)` _[instruction]_

## for
[for]: #for

- `for` `(`  _[expressionOrVoid]_ `;` _[expressionOrVoid]_  `;` _[expressionOrVoid]_ `)` _[instruction]_



















