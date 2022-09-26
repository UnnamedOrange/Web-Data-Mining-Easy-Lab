/* 1 */
%{
#include <parser/lex_interface.h>
%}

/* 2.0 */
%s PAGE
%s TITLE
%s TEXT

/* 2.1 */
title_pattern [^<]*
link_pattern "[["[^\[\]]*"]]"

/* 2.2 */
%%
"<page>" {
	BEGIN PAGE;
	return (int)t_page_begin;
}
"</page>" {
	BEGIN INITIAL;
	return (int)t_page_end;
}
<PAGE>"<title>" {
	BEGIN TITLE;
	return (int)t_unused;
}
<TITLE>"</title>" {
	BEGIN PAGE;
	return (int)t_unused;
}
<PAGE>"<text"[^<>]*">" {
	BEGIN TEXT;
	return (int)t_unused;
}
<TEXT>"</text>" {
	BEGIN PAGE;
	return (int)t_unused;
}

<TITLE>{title_pattern} {
	return (int)t_title;
}
<TEXT>{link_pattern} {
	return (int)t_link;
}

. |
[\t\n] {
	return (int)t_unused; // Suppress outputs.
}
%%

/* 3 */
int yyFlexLexer::yywrap(void)
{
	return 1;
}
