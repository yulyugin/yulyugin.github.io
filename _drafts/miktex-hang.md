# MikTeX hang

```
\documentclass{standalone}
\usepackage{tikz}
\begin{document}
\begin{tikzpicture}
  \node {}l;
\end{tikzpicture}
\end{document}
```

Hangs when compiled with pdflatex.

Tried some other letters: o, m - error is reported correctly.

```
$ pdflatex --version
MiKTeX-pdfTeX 4.8 (MiKTeX 21.10)
© 1982 D. E. Knuth, © 1996-2021 Hàn Thế Thành
TeX is a trademark of the American Mathematical Society.
using bzip2 version 1.0.8, 13-Jul-2019
compiled with curl version 7.72.0; using libcurl/7.72.0 Schannel
compiled with expat version 2.2.10; using expat_2.2.10
compiled with jpeg version 9.4
compiled with liblzma version 50020052; using 50020052
compiled with libpng version 1.6.37; using 1.6.37
compiled with libressl version LibreSSL 3.1.4; using LibreSSL 3.1.4
compiled with MiKTeX Application Framework version 4.2.1; using 4.2.1
compiled with MiKTeX Core version 4.9; using 4.9
compiled with MiKTeX Archive Extractor version 4.0; using 4.0
compiled with MiKTeX Package Manager version 4.5; using 4.5
compiled with uriparser version 0.9.4
compiled with xpdf version 4.02
compiled with zlib version 1.2.11; using 1.2.11
```
