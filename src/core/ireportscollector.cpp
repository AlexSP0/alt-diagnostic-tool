#include "ireportscollector.h"

IReportsCollector::IReportsCollector()
    : m_delimiter("")
    , m_startLine("")
    , m_endLine("")
{}

void IReportsCollector::setDelimiter(QString delimiter)
{
    m_delimiter = delimiter;
}

void IReportsCollector::setStartLine(QString str)
{
    m_startLine = str;
}

void IReportsCollector::setEndLine(QString str)
{
    m_endLine = str;
}
