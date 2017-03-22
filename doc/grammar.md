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
- 3 types, no operator overloading, struct, typeof ...

// TODO HEX

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

- `\/\*[\s\S]*\*\/`
- `\/\/[^\n]+`
- `(^|\n)#[^\n]+`

## Program
[Program]: #program

- _[declarationsList]_

## declarationsList
[declarationsList]: #declarationslist

- _[declarationsList]_ _[functionDeclaration]_
- _[declarationsList]_ _[variableDeclaration]_
- _[declarationsList]_ _[functionDefinition]_
- ε

## functionDeclaration
[functionDeclaration]: #functionDeclaration

- _[dataType]_ _[identifier]_ `(` _[parametersList]_ `)` `;`
- _[dataType]_ _[identifier]_ `(` `)` `;`

DataType = ArrayDataType | LiteralDataType
ArrayDataType = DataType "[" IntegerLiteral "]"

## dataType
[dataType]: #dataType

- _[dataTypeLiteral]_
- _[arrayDataType]_

## dataTypeLiteral
[dataTypeLiteral]: #dataTypeLiteral

- `int32_t`
- `int64_t`
- `char`

## arrayDataType
[arrayDataType]: #arrayDataType

- _[dataTypeLiteral]_ `[` `]`

## identifier
[identifier]: #identifier

- `[a-zA-Z_$][a-zA-Z_$0-9]*`

## parametersList
[parametersList]: #parametersList

- _[parametersList]_ `,` _[parameters]_
- _[parameter]_

## parameter
[parameter]: #parameter

- _[dataTypeLiteral]_ _[declarator]_
- _[dataType]_

## declarator
[declarator]: #declarator

- _[identifier]_
- _[identifier]_ `[` `]`
- _[identifier]_ `[` _[literalExpression]_ `]`
// TODO 3+3

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

- _[dataType]_ _[identifier]_ `(` _[parametersList]_ `)` _[bloc]_

## bloc
[bloc]: #bloc

- `{` insideBloc `}`

## insideBloc
[insideBloc]: #insidebloc

- _[insideBloc]_ _[variableDeclaration]_
- _[insideBloc]_ _[return]_
- _[insideBloc]_ _[instruction]_
- ε


## variableDeclaration
[variableDeclaration]: #variableDeclaration

- _[dataTypeLiteral]_ _[variableDeclaratorsList]_ `;`

## variableDeclaratorsList
[variableDeclaratorsList]: #variableDeclaratorsList

- _[variableDeclaratorsList]_ `,` _[variableDeclarator]_
- _[variableDeclarator]_

## variableDeclarator
[variableDeclarator]: #variableDeclarator

- _[declarator]_
- _[declarator]_ `=` _[expression]_

## return
[return]: #return

- `return` _[expression]_ `;`
- `return` `;`

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

op | prec | assoc
---| ---- | -----
, |  0   | right
= |  1   | right
*=|  1   | right
/=|  1   | right
%=|  1   | right
+=|  1   | right
-=|  1   | right
<<=|  1   | right
>>=|  1   | right
&=|  1   | right
^=|  1   | right
|=|  1   | right
&#124;&#124; | 2 | left
&& | 3 | left
&#124; | 4 | left
^ | 5 | left
& | 6 | left
== | 7 | left
!= | 8 | left
< | 9 | left
&#62; | 9 | left
<= | 9 | left
>= | 9 | left
<< | 10 | left
&#62;&#62; | 10 | left
+ | 11 | left
- | 11 | left
* | 12 | left
/ | 12 | left
% | 12 | left

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

## expressionOrVoid
[expressionOrVoid]: #expressionOrVoid

- _[expression]_
- ε










