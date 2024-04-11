# compilers-3
Implementing static semantics

Link to GitHub: https://github.com/jtfox142/compilers-3

I implemented local scoping rules in this project.

The tree created by my parser is passed into statSem, which implements static semantic rules on variable identifiers. As the project specification indicates to only focus on variables, all function identifiers are ignored. Produces "Program successfully passed static semantic check" for programs that pass all checks, produces an error message and exits otherwise.

The only bug that I know of is within my scanner. I still haven't tracked down the bug that causes it to have an aneurysm if there is a space after an opening brace, so if you want to give the parser/static semantic checker a chance to work make sure that all spaces after opening braces have been deleted.

Program can be compiled using the included makefile. Simply type "make". 

Program can be run using "./statSem [yourFileHere]". Example: "./statSem test.txt"