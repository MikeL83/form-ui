#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>
#include "logic.h"

Logic::Logic(QWidget *parent) : QWidget(parent)
{
}

bool Logic::validateEmail(const QString &email)
{
    if (!email.isEmpty()) {
        QRegExp rx("^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@[A-Za-z0-9-]"
                   "+(\\.[A-Za-z0-9-]+)*(\\.[A-Za-z]{2,4})$");
        if (rx.indexIn(email) == -1) {
            QMessageBox::warning(
                this, QApplication::applicationName(),
                tr("Given email is not valid (%1).\n"
                   "Please correct the email address.").arg(email));
            return false;
        }
    }
    return true;
}

bool Logic::saveUser(const QHash<QString, QString> &prefs,
                     const quint32 &magicNumber)
{
    // save given user preferences to a file

    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save User Details"), "/home", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
            qFatal("Cannot open file %s for writing: %s", qPrintable(fileName),
                   qPrintable(file.errorString()));
        }
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << magicNumber << "\n";
        out << prefs.value("firstname") << "\n";
        out << prefs.value("middlename") << "\n";
        out << prefs.value("lastname") << "\n";
        out << prefs.value("dateofbirth") << "\n";
        QStringList addressLines = prefs.value("address").split("\n");
        if (addressLines.count() == 1) {
            out << addressLines.at(0) << "\n";
            out << "\n";
            out << "\n";
        } else if (addressLines.count() == 2) {
            out << addressLines.at(0) << "\n";
            out << addressLines.at(1) << "\n";
            out << "\n";
        } else {
            out << addressLines.at(0) << "\n";
            out << addressLines.at(1) << "\n";
            out << addressLines.at(2) << "\n";
        }
        out << prefs.value("city") << "\n";
        out << prefs.value("state") << "\n";
        out << prefs.value("postcode") << "\n";
        out << prefs.value("company") << "\n";
        out << prefs.value("email") << "\n";
        out << prefs.value("designation") << "\n";
        out << prefs.value("mobile") << "\n";
        out << prefs.value("bio") << "\n";

        return true;

    } else {
        return false;
    }
}
