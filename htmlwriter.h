/************************************************************************
  Program:		Network Sniffer
  File:			htmlwriter.h
  Description:	HtmlWriter class header file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#ifndef HTMLWRITER_H
#define HTMLWRITER_H

#include <QString>

/** Manages writing to a html log file. */
class HtmlWriter
{
public:
	HtmlWriter();

	/** Writes regular text to the document. Html special characters will be escaped. */
	void write(const QString &text);

	/** Writes html to the document. */
	void writeHtml(const QString &html);

	/** Writes a paragraph header to the document. */
	void writeHeader(const QString &text);

	/** Writes a paragraph to the document. */
	void writePar(const QString &text);

	/** Closes the html document. */
	void endDoc();

	/** Returns the html document as a string. */
	QString &getHtml() { return html; }

private:
	QString html;
};

#endif // HTMLWRITER_H
