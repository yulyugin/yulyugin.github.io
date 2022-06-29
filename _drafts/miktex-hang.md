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
MiKTeX-pdfTeX 4.10 (MiKTeX 22.3)
© 1982 D. E. Knuth, © 1996-2021 Hàn Thế Thành
TeX is a trademark of the American Mathematical Society.
using bzip2 version 1.0.8, 13-Jul-2019
compiled with curl version 7.72.0; using libcurl/7.72.0 Schannel
compiled with expat version 2.2.10; using expat_2.2.10
compiled with jpeg version 9.4
compiled with liblzma version 50020052; using 50020052
compiled with libpng version 1.6.37; using 1.6.37
compiled with libressl version LibreSSL 3.1.4; using LibreSSL 3.1.4
compiled with MiKTeX Application Framework version 4.4; using 4.4
compiled with MiKTeX Core version 4.12; using 4.12
compiled with MiKTeX Archive Extractor version 4.0; using 4.0
compiled with MiKTeX Package Manager version 4.7; using 4.7
compiled with uriparser version 0.9.4
compiled with xpdf version 4.02
compiled with zlib version 1.2.11; using 1.2.11
```

xelatex also hangs.

```
$ xelatex --version
MiKTeX-XeTeX 4.8 (MiKTeX 22.3)
© 1994-2008 SIL International, © 2009-2021 Jonathan Kew, © 2010-2012 Hàn Thế Thành, © 2012-2013 Khaled Hosny
TeX is a trademark of the American Mathematical Society
using bzip2 version 1.0.8, 13-Jul-2019
compiled with curl version 7.72.0; using libcurl/7.72.0 Schannel
compiled with expat version 2.2.10; using expat_2.2.10
compiled with fontconfig version 2.13.1; using 2.13.1
compiled with freetype2 version 2.10.3; using 2.10.3
compiled with graphite2 version 1.3.14; using 1.3.14
compiled with harfbuzz version 2.7.2; using 2.7.2
compiled with icu version 60.1; using 60.1
compiled with jpeg version 9.4
compiled with liblzma version 50020052; using 50020052
compiled with libpng version 1.6.37; using 1.6.37
compiled with libressl version LibreSSL 3.1.4; using LibreSSL 3.1.4
compiled with MiKTeX Application Framework version 4.4; using 4.4
compiled with MiKTeX Core version 4.12; using 4.12
compiled with MiKTeX Archive Extractor version 4.0; using 4.0
compiled with MiKTeX Package Manager version 4.7; using 4.7
compiled with pplib version v2.05 less toxic i hope
using teckit version 2.4
compiled with uriparser version 0.9.4
compiled with zlib version 1.2.11; using 1.2.11
```
