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

- _[declarationsList]_ _[fctDec]_
- _[declarationsList]_ _[varDecAffLitteral]_ `;`
- _[declarationsList]_ _[fctDef]_
- ε

## fctDec
[fctDec]: #fctdec

- _[dataType]_ _[identifier]_ `(` _[decParametersList]_ `)` `;`

## dataType
[dataType]: #datatype

- `int32_t`
- `int64_t`
- `char`

## identifier
[identifier]: #identifier

- `[a-zA-Z_$][a-zA-Z_$0-9]*`

## decParametersList
[decParametersList]: #decparameterslist

- _[nonEmptyDecParametersList]_
- ε

## nonEmptyDecParametersList
[nonEmptyDecParametersList]: #nonemptydecparameterslist

- _[nonEmptyDecParametersList]_ `,` _[paramsDec]_
- _[paramsDec]_

## paramsDec
[paramsDec]: #paramsdec

- _[paramsDef]_
- _[dataType]_
- _[dataType]_  `[` `]`

## paramsDef
[paramsDef]: #paramsdef

- _[dataType]_ _[identifier]_
- _[dataType]_ _[identifier]_ `[` `]`

## varDecAffLitteral
[varDecAffLitteral]: #vardecafflitteral

- _[varDecAffLitteral]_ `,` _[suiteDecAffLitteral]_
- _[dataType]_ _[suiteDecAffLitteral]_

## suiteDecAffLitteral
[suiteDecAffLitteral]: #suitedecafflitteral

- _[varIdentifierTabLiteral]_
- _[identifier]_ `=` _[literalExpr]_

## varIdentifierTabLiteral
[varIdentifierTabLiteral]: #varidentifiertabliteral

- _[identifier]_
- _[identifier]_ `[` _[intLiteral]_ `]`

## intLiteral
[intLiteral]: #intliteral

- `[0-9]+`

## LiteralExpr
[LiteralExpr]: #literalexpr

- _[intLiteral]_
- _[charLiteral]_

## charLiteral
[charLiteral]: #charliteral

-  `'` _[charAtom]_ `'`

## charAtom
[charAtom]: #charatom

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

## fctDef
[fctDef]: #fctdef

- _[dataType]_ _[identifier]_ `(` _[defParametersList]_ `)` _[bloc]_

## defParametersList
[defParametersList]: #defparameterslist

- _[nonEmptyDefParametersList]_
- ε

## nonEmptyDefParametersList
[nonEmptyDefParametersList]: #nonemptydefparameterslist

- _[nonEmptyDefParametersList]_ `,` _[paramsDef]_
- _[paramsDef]_

## bloc
[bloc]: #bloc

- `{`insideBloc`}`

## insideBloc
[insideBloc]: #insidebloc

- _[insideBloc]_ _[varDecAff]_ `;`
- _[insideBloc]_ _[return]_
- _[insideBloc]_ _[instr]_
- ε

## varDecAff
[varDecAff]: #vardecaff

- _[varDecAff]_ `,` _[suiteDecAff]_
- _[dataType]_ _[suiteDecAff]_

## suiteDecAff
[suiteDecAff]: #suitedecaff

- _[varIdentifierTabLiteral]_
- _[identifier]_ `=` _[expr]_


## return
[return]: #return

- `return` _[exprOrVoid]_ `;`

## exprOrVoid
[exprOrVoid]: #exprorvoid

- _[expr]_
- ε 

## expr
[expr]: #expr

- _[expr]_ _[OP]_ _[expr]_
- _[LiteralExpr]_
- _[varAff]_
- _[varUpdate]_
- _[varIdentifier]_
- `(` _[expr]_ `)`
- `-` _[expr]_
- `+` _[expr]_
- `!` _[expr]_
- `~` _[expr]_
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

## varAff
[varAff]: #varaff

- _[varIdentifier]_ `=` expr]_

## varIdentifier
[varIdentifier]: #varidentifier

- _[identifier]_
- _[identifier]_ `[` _[expr]_ `]`

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

- _[functionCallParams]_ `,` _[expr]_
- _[expr]_

## instr
[instr]: #instr

- _[expr]_ `;`
- _[bloc]_
- _[if]_
- _[while]_
- _[for]_
- `;`

## if
[if]: #if

- `if` `(` _[expr]_ `)` _[instr]_  `else` _[instr]_
- `if` `(` _[expr]_ `)` _[instr]_

## while
[while]: #while

- `while` `(` _[expr]_ `)` _[instr]_

## for
[for]: #for

- `for` `(`  _[exprOrVoid]_ `;` _[exprOrVoid]_  `;` _[exprOrVoid]_ `)` _[instr]_



















