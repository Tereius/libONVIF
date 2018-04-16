#include "qstringCompare.h"

bool operator>(const QString &s1, int length) { return s1.size() > length; }
bool operator>=(const QString &s1, int length) { return s1.size() >= length; }
bool operator<(const QString &s1, int length) { return s1.size() < length; }
bool operator<=(const QString &s1, int length) { return s1.size() <= length; }