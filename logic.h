#ifndef LOGIC_H
#define LOGIC_H

#include <QWidget>
#include <QHash>

class QString;

class Logic : public QWidget
{
    Q_OBJECT
  public:
    explicit Logic(QWidget *parent = 0);
    bool validateEmail(const QString &);
    bool saveUser(const QHash<QString, QString> &, const quint32 &);
};

#endif // LOGIC_H
