#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegExp>
#include <QTextDocument>

class myHighlighter : public QSyntaxHighlighter{
    Q_OBJECT
public:
    explicit myHighlighter(QTextDocument *parent=nullptr);
protected:
void  highlightBlock(const QString &text);
};
#endif // MYHIGHLIGHTER_H
