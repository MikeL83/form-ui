#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include <QLineEdit>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QString>
#include <QRegExp>
#include <QRegExpValidator>
#include <QCloseEvent>
#include <QDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QStringList>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QTextDocument>
#include <QDateEdit>
#include <QRadioButton>
#include <QDesktopServices>
#include <QUrl>
#include "logic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), MagicNumber(0x21091983), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logic = std::unique_ptr<Logic>{ new Logic };

    createActions();
    createMenus();
    createWidgets();
    createLayout();
    createConnections();

    QApplication::setApplicationName(tr("User preferences"));

    setWindowTitle(QApplication::applicationName());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::createWidgets()
{

    tabWidget = new QTabWidget;
    page1Layout = new QVBoxLayout;
    page2Layout = new QVBoxLayout;
    buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Close);
    firstNameLabel = new QLabel(tr("First name:"));
    firstNameEdit = new QLineEdit;
    firstNameEdit->setValidator(
        new QRegExpValidator(QRegExp("[\\D\\s]+"), this));
    firstNameEdit->setMaxLength(101);
    firstNameLabel->setBuddy(firstNameEdit);
    middleNameLabel = new QLabel(tr("Middle name:"));
    middleNameEdit = new QLineEdit;
    middleNameLabel->setBuddy(middleNameEdit);
    middleNameEdit->setValidator(
        new QRegExpValidator(QRegExp("[\\D\\s]+"), this));
    middleNameEdit->setMaxLength(101);
    lastNameLabel = new QLabel(tr("Last name:"));
    lastNameEdit = new QLineEdit;
    lastNameLabel->setBuddy(lastNameEdit);
    lastNameEdit->setValidator(
        new QRegExpValidator(QRegExp("[\\D\\s]+"), this));
    lastNameEdit->setMaxLength(101);
    dateOfBirthLabel = new QLabel(tr("Date of birth:"));
    dateOfBirthEdit = new QDateEdit;
    dateOfBirthLabel->setBuddy(dateOfBirthEdit);
    addressLabel = new QLabel(tr("Address:"));
    addressEdit = new QPlainTextEdit;
    addressLabel->setBuddy(addressEdit);
    cityLabel = new QLabel(tr("City:"));
    cityEdit = new QLineEdit;
    cityLabel->setBuddy(cityEdit);
    cityEdit->setValidator(new QRegExpValidator(QRegExp("[\\D\\s]+"), this));
    cityEdit->setMaxLength(51);
    stateLabel = new QLabel(tr("State:"));
    stateEdit = new QLineEdit;
    stateLabel->setBuddy(stateEdit);
    stateEdit->setValidator(new QRegExpValidator(QRegExp("[\\D\\s]+"), this));
    stateEdit->setMaxLength(51);
    companyLabel = new QLabel(tr("Company:"));
    companyEdit = new QLineEdit;
    companyLabel->setBuddy(companyEdit);
    companyEdit->setMaxLength(101);
    postcodeLabel = new QLabel(tr("Post code: "));
    postcodeEdit = new QLineEdit;
    postcodeLabel->setBuddy(postcodeEdit);
    postcodeEdit->setMaxLength(11);
    emailLabel = new QLabel(tr("Email: "));
    emailEdit = new QLineEdit;
    emailLabel->setBuddy(emailEdit);
    emailEdit->setValidator(new QRegExpValidator(
        QRegExp("^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@[A-Za-z0-9-]"
                "+(\\.[A-Za-z0-9-]+)*(\\.[A-Za-z]{2,4})$"),
        this));
    emailEdit->setMaxLength(101);
    designationLabel = new QLabel(tr("Designation: "));
    designationEdit = new QLineEdit;
    designationLabel->setBuddy(designationEdit);
    designationEdit->setMaxLength(101);
    bioLabel = new QLabel(tr("Bio: "));
    bioEdit = new QPlainTextEdit;
    bioLabel->setBuddy(bioEdit);
    mobileLabel = new QLabel(tr("Mobile: "));
    mobileEdit = new QLineEdit;
    mobileLabel->setBuddy(mobileEdit);
    mobileEdit->setValidator(
        new QRegExpValidator(QRegExp("[\\d\\s\\-\\+]+"), this));
    mobileEdit->setMaxLength(16);
    settingsLabel = new QLabel(tr("Settings: "));
    settingsEdit = new QLineEdit;
    radioButton1 = new QRadioButton(tr("&Yes"));
    radioButton2 = new QRadioButton(tr("&No"));

    contactEmail = new QPushButton(tr("Contact email"));
    contactEmail->setEnabled(false);
    contactCell = new QPushButton(tr("Contact mobile"));
    contactCell->setEnabled(false);
}

void MainWindow::createActions()
{

    loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcut(QKeySequence::Open);
    loadAction->setStatusTip(tr("Load user preferences"));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the dialog"));
}

void MainWindow::createConnections()
{
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadUser()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    connect(firstNameEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(middleNameEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(lastNameEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(cityEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(stateEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(postcodeEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(companyEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(emailEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(mobileEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(designationEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkCharacterLengthForFields(QString)));
    connect(bioEdit, SIGNAL(textChanged()), this,
            SLOT(checkCharacterLengthForMultiLineFields()));
    connect(addressEdit, SIGNAL(textChanged()), this,
            SLOT(checkCharacterLengthForMultiLineFields()));
    connect(dateOfBirthEdit, SIGNAL(dateChanged(QDate)), this,
            SLOT(changeDateOfBirth(QDate)));
    connect(radioButton1, SIGNAL(clicked()), this, SLOT(checkSettings()));
    connect(radioButton2, SIGNAL(clicked()), this, SLOT(checkSettings()));
    connect(contactEmail, SIGNAL(clicked()), this, SLOT(sendEmail()));
    connect(contactCell, SIGNAL(clicked()), this, SLOT(callCell()));
}

void MainWindow::createMenus()
{

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);
    separatorAction = fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void MainWindow::createLayout()
{

    page1Layout->addWidget(firstNameLabel);
    page1Layout->addWidget(firstNameEdit);
    page1Layout->addWidget(middleNameLabel);
    page1Layout->addWidget(middleNameEdit);
    page1Layout->addWidget(lastNameLabel);
    page1Layout->addWidget(lastNameEdit);
    page1Layout->addWidget(dateOfBirthLabel);
    page1Layout->addWidget(dateOfBirthEdit);
    page1Layout->addWidget(addressLabel);
    page1Layout->addWidget(addressEdit);
    page1Layout->addWidget(cityLabel);
    page1Layout->addWidget(cityEdit);
    page1Layout->addWidget(stateLabel);
    page1Layout->addWidget(stateEdit);
    page1Layout->addWidget(postcodeLabel);
    page1Layout->addWidget(postcodeEdit);
    page1Layout->addStretch(4);
    page1Layout->addWidget(buttonBox);

    QWidget *wd1 = new QWidget;
    wd1->setLayout(page1Layout);
    tabWidget->addTab(wd1, tr("Personal"));

    page2Layout->addWidget(companyLabel);
    page2Layout->addWidget(companyEdit);
    page2Layout->addWidget(emailLabel);
    page2Layout->addWidget(emailEdit);
    page2Layout->addWidget(designationLabel);
    page2Layout->addWidget(designationEdit);
    page2Layout->addWidget(bioLabel);
    page2Layout->addWidget(bioEdit);
    page2Layout->addWidget(mobileLabel);
    page2Layout->addWidget(mobileEdit);
    QHBoxLayout *layoutForSettings = new QHBoxLayout;
    layoutForSettings->addWidget(settingsLabel);
    layoutForSettings->addStretch(1);
    layoutForSettings->addWidget(radioButton1);
    layoutForSettings->addWidget(radioButton2);
    radioButton2->setChecked(true);
    QHBoxLayout *layoutForButtons = new QHBoxLayout;
    layoutForButtons->addStretch(2);
    layoutForButtons->addWidget(contactEmail);
    layoutForButtons->addWidget(contactCell);
    page2Layout->addLayout(layoutForSettings);
    page2Layout->addLayout(layoutForButtons);
    page2Layout->addStretch(4);

    QWidget *wd2 = new QWidget;
    wd2->setLayout(page2Layout);
    tabWidget->addTab(wd2, tr("Additional details"));

    tabWidget->setAttribute(Qt::WA_DeleteOnClose);
    setCentralWidget(tabWidget);
}

void MainWindow::accept()
{
    if (!checkRequiredFields()) {
        QMessageBox::warning(
            this, QApplication::applicationName(),
            tr("There's missing information from some of the required fields.\n"
               "Please fill all the necessary fields."));

        return;
    }
    if (!logic->validateEmail(emailEdit->text())) {
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("Save user details.");
    msgBox.setInformativeText("Do you want to save user data into a file.");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
        if (logic->saveUser(preferences, MagicNumber)) {
            break;
        } else {
            return;
        }
    case QMessageBox::Discard:
        break;
    case QMessageBox::Cancel:
        return;
    default:
        break;
    }
}

bool MainWindow::checkRequiredFields()
{
    // Check that required fields are not empty
    if (!firstNameEdit->text().trimmed().isEmpty() &&
        !lastNameEdit->text().trimmed().isEmpty() &&
        !dateOfBirthEdit->date().toString().isEmpty() &&
        !addressEdit->toPlainText().trimmed().isEmpty() &&
        !cityEdit->text().trimmed().isEmpty() &&
        !stateEdit->text().trimmed().isEmpty() &&
        !postcodeEdit->text().trimmed().isEmpty()) {
        return true;
    } else {
        return false;
    }
}

void MainWindow::checkCharacterLengthForFields(QString text)
{
    // validate each input fields that the given character amount
    // is within the limit
    if (QObject::sender() == firstNameEdit) {
        if (text.length() > 100) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the "
                                    "first name field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["firstname"] = text;
        }
    } else if (QObject::sender() == middleNameEdit) {
        if (text.length() > 100) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the "
                                    "middle name field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["middlename"] = text;
        }
    } else if (QObject::sender() == lastNameEdit) {
        if (text.length() > 100) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the last "
                                    "name field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["lastname"] = text;
        }
    } else if (QObject::sender() == cityEdit) {
        if (text.length() > 50) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the city "
                                    "field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["city"] = text;
        }
    } else if (QObject::sender() == stateEdit) {
        if (text.length() > 50) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (50) of the state "
                                    "field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["state"] = text;
        }
    } else if (QObject::sender() == postcodeEdit) {
        if (text.length() > 10) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (10) of the "
                                    "postcode field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["postcode"] = text;
        }
    } else if (QObject::sender() == companyEdit) {
        if (text.length() > 100) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the "
                                    "company field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["company"] = text;
        }
    } else if (QObject::sender() == emailEdit) {
        if (text.length() > 100) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the "
                                    "email field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["email"] = text;
        }
    } else if (QObject::sender() == designationEdit) {
        if (text.length() > 100) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (100) of the "
                                    "designation field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["designation"] = text;
        }
    } else if (QObject::sender() == mobileEdit) {
        if (text.length() > 15) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (15) of the "
                                    "mobile field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["mobile"] = text;
        }
    }
}

void MainWindow::checkCharacterLengthForMultiLineFields()
{
    // validate that the given character amount
    // is within the limit for multiline input fields
    if (QObject::sender() == addressEdit) {
        QStringList lines = addressEdit->toPlainText().split("\n");
        if (lines.at(0).length() > 200) {
            QMessageBox::warning(
                this, QApplication::applicationName(),
                tr("Maximum character limit (200) of the "
                   "address field (line 1) has been exceeded.\n"
                   "Please reduce the number of characters."));
            return;
        } else {
            preferences["address"] = lines.at(0) + "\n";
        }
        if (lines.count() > 1) {
            if (lines.at(1).length() > 200) {
                QMessageBox::warning(
                    this, QApplication::applicationName(),
                    tr("Maximum character limit (200) of the "
                       "address field (line 2) has been exceeded.\n"
                       "Please reduce the number of characters."));
                return;
            } else {
                preferences["address"] += lines.at(1) + "\n";
            }
        }
        if (lines.count() > 2) {
            if (lines.at(2).length() > 200) {
                QMessageBox::warning(
                    this, QApplication::applicationName(),
                    tr("Maximum character limit (200) of the "
                       "address field (line 3) has been exceeded.\n"
                       "Please reduce the number of characters."));
                return;
            } else {
                preferences["address"] += lines.at(2) + "\n";
            }
        }
    } else if (QObject::sender() == bioEdit) {
        if (bioEdit->toPlainText().length() > 400) {
            QMessageBox::warning(this, QApplication::applicationName(),
                                 tr("Maximum character limit (400) of the "
                                    "bio field has been exceeded.\n"
                                    "Please reduce the number of characters."));
        } else {
            preferences["bio"] = bioEdit->toPlainText();
        }
    }
}

void MainWindow::loadUser()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open User Details"), "/home", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly)) {
            qFatal("Cannot open file %s for reading: %s", qPrintable(fileName),
                   qPrintable(file.errorString()));
        }
        QTextStream in(&file);
        in.setCodec("UTF-8");
        quint32 magic;
        magic = in.readLine().toUInt();
        if (magic != MagicNumber) {
            qWarning("File %s is not recognized by this application.",
                     qPrintable(fileName));
            return;
        }
        preferences["firstname"] = in.readLine();
        firstNameEdit->setText(preferences.value("firstname"));
        preferences["middlename"] = in.readLine();
        middleNameEdit->setText(preferences.value("middlename"));
        preferences["lastname"] = in.readLine();
        lastNameEdit->setText(preferences.value("lastname"));
        preferences["dateofbirth"] = in.readLine();
        dateOfBirthEdit->setDate(
            QDate::fromString(preferences.value("dateofbirth"), "d.M.yyyy"));
        for (int k = 0; k < 3; ++k) {
            preferences["address"] += in.readLine() + "\n";
        }
        addressEdit->setPlainText(preferences.value("address"));
        preferences["city"] = in.readLine();
        cityEdit->setText(preferences.value("city"));
        preferences["state"] = in.readLine();
        stateEdit->setText(preferences.value("state"));
        preferences["postcode"] = in.readLine();
        postcodeEdit->setText(preferences.value("postcode"));
        preferences["company"] = in.readLine();
        companyEdit->setText(preferences.value("company"));
        preferences["email"] = in.readLine();
        emailEdit->setText(preferences.value("email"));
        preferences["designation"] = in.readLine();
        designationEdit->setText(preferences.value("designation"));
        preferences["mobile"] = in.readLine();
        mobileEdit->setText(preferences.value("mobile"));
        while (!in.atEnd()) {
            preferences["bio"] += in.readLine() + "\n";
        }
        bioEdit->setPlainText(preferences.value("bio"));
    }
}

void MainWindow::changeDateOfBirth(QDate date)
{
    if (preferences["dateofbirth"] != date.toString()) {
        preferences["dateofbirth"] = date.toString("d.M.yyyy");
    }
}

void MainWindow::checkSettings()
{
    // allow send an email or make a call if
    // the fields in question are non-empty.
    if (QObject::sender() == radioButton1) {
        if (!emailEdit->text().isEmpty()) {
            contactEmail->setEnabled(true);
        }
        if (!mobileEdit->text().isEmpty()) {
            contactCell->setEnabled(true);
        }
    } else {
        contactEmail->setEnabled(false);
        contactCell->setEnabled(false);
    }
}

void MainWindow::sendEmail()
{
    if (logic->validateEmail(emailEdit->text()))
        QDesktopServices::openUrl(QUrl("mailto:" + emailEdit->text()));
}

void MainWindow::callCell()
{
    if (!mobileEdit->text().isEmpty())
        QDesktopServices::openUrl(QUrl("skype:" + mobileEdit->text()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
