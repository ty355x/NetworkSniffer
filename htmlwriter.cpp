/************************************************************************
  Program:		Network Sniffer
  File:			htmlwriter.cpp
  Description:	HtmlWriter class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "htmlwriter.h"

HtmlWriter::HtmlWriter()
{
	writeHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
	writeHtml("<html>\n<head>\n");

	writeHtml("<title>");
	write("Network Sniffer Scan Report");
	writeHtml("</title>\n");
	writeHtml("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>\n");
	writeHtml("<style type='text/css'>\n");

	QString styleSheet =
		"body { font-family: arial, sans-serif; font-size: 10pt; }\n"
		"h3 { font-size: 12pt; }\n"
		"table { border: solid 1px silver; font-size: 10pt; border-collapse: collapse; }\n"
		"td, th { border: solid 1px silver; padding: 2px; }\n";

	write(styleSheet);
	writeHtml("</style>\n");
	writeHtml("</head>\n<body>\n");
}

void HtmlWriter::write(const QString &text)
{
	for (int i = 0; i < text.length(); i++)
	{
		QChar qc = text[i];
		ushort c = text[i].unicode();

		if (c == '<')
			writeHtml("&lt;");
		else if (c == '>')
			writeHtml("&gt;");
		else if (c == '&')
			writeHtml("&amp;");
		else if (c == '\"')
			writeHtml("&quot;");
		else
			html.append(qc);
	}
}

inline void HtmlWriter::writeHtml(const QString &html)
{
	this->html.append(html);
}

void HtmlWriter::writeHeader(const QString &text)
{
	writeHtml("<h3>");
	writeHtml(text);
	writeHtml("</h3>\n");
}

void HtmlWriter::writePar(const QString &text)
{
	writeHtml("<p>");
	writeHtml(text);
	writeHtml("</p>\n");
}

void HtmlWriter::endDoc()
{
	writeHtml("</body></html>");
}
