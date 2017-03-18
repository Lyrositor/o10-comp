# C Grammar

[C99 Specification](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf)

## sourceChar
[sourceChar]: sourcechar

- `[^\\'\n]`

## octalEscape
[octalEscape]: octalescape

- `[0-3][0-7]{2}`
- `[0-7]{1,2}`

## hexEscape
[hexEscape]: hexescape

- `[0-9a-fA-F]{2}`

## escapeChar
[escapeChar]: escapechar

- `[abfnrtv\\'"?]`

## intLiteral
[intLiteral]: #intliteral

- `[0-9]+`

## identifier
[identifier]: #identifier

- `[a-zA-Z_$][a-zA-Z_$0-9]*`

## charLiteral
[charLiteral]: #charliteral

-  `'` _[charAtom]_ `'`

## charAtom
[charAtom]: #charatom

- <code>&#92;</code> _[escapeSequence]_
- _[sourceChar]_

## escapeSequence
[escapeSequence]: #escapesequence

- _[octalEscape]_
- `x` _[hexEscape]_
- _[escapeChar]_

## Program
[Program]: #program

- _[declarationsList]_

## declarationsList
[declarationsList]: #declarationslist

- _[declarationsList]_ _[fctDec]_
- _[declarationsList]_ _[fctDef]_
- _[declarationsList]_ _[varDecAffLitteral]_ `;`
- ε

## dataType
[dataType]: #datatype

- [identifier]

## varDecAffLitteral
[varDecAffLitteral]: #vardecafflitteral

- _[varDecAffLitteral]_ `,` _[suiteDecAffLitteral]_
- _[dataType]_ _[suiteDecAffLitteral]_

## suiteDecAffLitteral
[suiteDecAffLitteral]: #suitedecafflitteral

- _[varIdentifierTabLiteral]_
- _[identifier]_ `=` _[literalExpr]_

## varDecAff
[varDecAff]: #vardecaff

- _[varDecAff]_ `,` _[suite]_
- _[dataType]_ _[suite]_

## suiteDecAff
[suiteDecAff]: #suitedecaff

- _[varIdentifierTabLiteral]_
- _[identifier]_ `=` _[expr]_

## varAff
[varAff]: #varaff

- _[varIdentifier]_ `=` expr]_

## varUpdate
[varUpdate]: #varupdate

- _[varIdentifier]_ `++`
- _[varIdentifier]_ `--`
- `++` _[varIdentifier]_
- `--` _[varIdentifier]_

## varIdentifier
[varIdentifier]: #varidentifier

- _[identifier]_
- _[identifier]_ `[` _[expr]_ `]`

## varIdentifierTabLiteral
[varIdentifierTabLiteral]: #varidentifiertabliteral

- _[identifier]_
- _[identifier]_ `[` _[intLiteral]_ `]`

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

## bloc
[bloc]: #bloc

- `{`insideBloc`}`

## insideBloc
[insideBloc]: #insidebloc

- _[insideBloc]_ _[instr]_
- _[insideBloc]_ _[varDec]_ `;`
- _[insideBloc]_ _[return]_
- ε

## paramsDec
[paramsDec]: #paramsdec

- _[paramsDef]_
- _[dataType]_
- _[dataType]_  `[` `]`

## nonEmptyDecParametersList
[nonEmptyDecParametersList]: #nonemptydecparameterslist

- _[nonEmptyDecParametersList]_ `,` _[paramsDec]_
- _[paramsDec]_

## decParametersList
[decParametersList]: #decparameterslist

- _[nonEmptyDecParametersList]_
- ε

## paramsDef
[paramsDef]: #paramsdef

- _[dataType]_ _[identifier]_
- _[dataType]_ _[identifier]_ `[` `]`

## nonEmptyDefParametersList
[nonEmptyDefParametersList]: #nonemptydefparameterslist

- _[nonEmptyDefParametersList]_ `,` _[paramsDef]_
- _[paramsDef]_

## defParametersList
[defParametersList]: #defparameterslist

- _[nonEmptyDefParametersList]_
- ε

## fctDec
[fctDec]: #fctdec

- _[dataType]_ _[identifier]_ `(` _[decParametersList]_ `)` `;`

## fctDef
[fctDef]: #fctdef

- _[dataType]_ _[identifier]_ `(` _[defParametersList]_ `)` _[bloc]_

## return
[return]: #return

- `return` _[exprOrVoid]_ `;`

## LiteralExpr
[LiteralExpr]: #literalexpr

- _[intLiteral]_
- _[charLiteral]_

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
- _[identifier]_ `(` _[insideList]_ `)`
- _[identifier]_ `(` `)`

## exprOrVoid
[exprOrVoid]: #exprorvoid

- _[expr]_
- ε 
