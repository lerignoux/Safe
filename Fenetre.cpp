#include "Fenetre.h"

using namespace std;


/*******************************************************************
Initialisation de la fenetre
********************************************************************/

Fenetre::Fenetre() : QMainWindow()
{
  desktop = QApplication::desktop();
  setWindowTitle("Personnal Safe");
  this->setMinimumSize(200,400);
  this->move(desktop->width()-this->width(),desktop->height()-this->height());
  
  
  mainWidget = new QWidget;
  mainLayout = new QVBoxLayout();
  setCentralWidget(mainWidget);
  mainWidget->setLayout(mainLayout);
  
  passwordsAction = new QAction(tr("&passwords"), this);
  fileAction = new QAction(tr("&files"), this);
  
  menuBar()->addAction(passwordsAction);
  menuBar()->addAction(fileAction);
  
  connect(passwordsAction, SIGNAL(triggered()), this, SLOT(setPasswordsWidget()));
  connect(fileAction, SIGNAL(triggered()), this, SLOT(setFilesWidget()));

  makePasswordWidget();
  makeFilesWidget();
  mainLayout->addWidget(filesMainWidget);
  mainLayout->addWidget(passwordMainWidget);
  filesMainWidget->setVisible(false);

 
  icon = new QIcon(QString("./Sicon.png"));
  setWindowIcon(*icon);
  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setIcon(*icon);
  trayIcon->setToolTip(/*iconComboBox->itemText(index)*/QString(" Personnal Safe"));  
  trayIcon->show();
  
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activate()));

  processData();

  installEventFilter(this);
  
}

Fenetre::~Fenetre()
{  
}


/*******************************************************************
Gestion du daemon de password
********************************************************************/

void Fenetre::makePasswordWidget()
{
  passwordMainWidget = new QWidget;
  
  passwordMainLayout = new QVBoxLayout();
  passwordMainWidget->setLayout(passwordMainLayout);
  
  passList = new QListWidget(this);
  passList->setObjectName(QString::fromUtf8("password list"));
  
  passLabel = new QLineEdit(this);
  passLabel->setReadOnly(true);
  passLabel->setEchoMode(QLineEdit::Password);
  passLabel->setObjectName(QString::fromUtf8("password :"));
  
  passwordMainLayout->addWidget(passList);
  passwordMainLayout->addWidget(passLabel);

  
  QObject::connect(passList,SIGNAL(itemSelectionChanged()),this,SLOT(findPass()));
  
  copy = new QShortcut(QKeySequence(tr("Ctrl+C")), this); 
  QObject::connect(copy,SIGNAL(activated()),this,SLOT(copier()));
 
}

/* Affiche de widget de gestion de password */
void Fenetre::setPasswordsWidget()
{
  filesMainWidget->setVisible(false);
  passwordMainWidget->setVisible(true);
}


QByteArray Fenetre::passPopUp()
{
  QString stringPass;
  stringPass = QInputDialog::getText ( this, QString("Password"), QString("saisissez votre password"),QLineEdit::NoEcho, QString(), 0, Qt::WindowStaysOnTopHint);
  return stringPass.toUtf8();
}

void Fenetre::activate()
{
  if(isHidden())
  {
    showNormal();
    raise();
    activateWindow();
    this->move(desktop->width()-this->width(),desktop->height()-this->height());
  }
  else
  {
    hide();
  }
}

bool Fenetre::eventFilter(QObject* obj,QEvent* evt)
{
  if(evt->type()==QEvent::WindowStateChange&&isMinimized())
  {
    evt->ignore();
    activate();
    return true;
  }
  else return QMainWindow::eventFilter(obj,evt);
}



/* Traite le fichier de password */
void Fenetre::processData()
{
  QFile file(DEFAULTFILENAME);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  while (!file.atEnd())
  {
    QByteArray line = file.readLine();
    addPassTitle(line);
  }
}

/* Affiche la liste des passwords */
void Fenetre::addPassTitle(QByteArray line)
{
  int i=0;
  i = line.lastIndexOf(": ");
  line.resize(i);
  passList->addItem(QString(line));
}

/* trouve le password selectionné */
void Fenetre::findPass()
{
  int passPos=0;
  QFile file(DEFAULTFILENAME);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  for(int ii=0;ii<passList->currentRow();ii++)
  {
    QByteArray line = file.readLine();
  }
  QByteArray line = file.readLine();
  passPos = line.lastIndexOf(": ") + 1;
  line.chop(1);
  openPass = line.remove(0,passPos+1);
  cout << openPass.data() << endl;
  passLabel->setText(QString(openPass));
}

/* copie du password */
void Fenetre::copier()
{
  
  for (int ii = 0; ii< 255; ii++)
  {
    cout << " i = " << ii << " -" <<  (char) ii << "-" << endl ;
  }

  
  cout << "pass = " << openPass.data() << endl;
  decryptPass();
  cout << "pass = " << openPass.data() << endl;
  
//   cout << "test = " << QByteArray("58Fds9:").data() << " crypte en " << encrypt(QByteArray("58Fds9:")).data << " dec en " << decrypt(encrypt(QByteArray("58Fds9:"))).data() << endl;
  
  passLabel->selectAll();
  passLabel->setEchoMode(QLineEdit::Normal);
  passLabel->cut();
  passLabel->setEchoMode(QLineEdit::Password);
}

/* Décrypte le password sélectionné */
void Fenetre::decryptPass()
{
  openPass = decrypt(openPass);
  passLabel->setText(QString(openPass));
}



/*******************************************************************
Gestion des fichiers de password
********************************************************************/

/* création du widget de manipulation des fihiers */
void Fenetre::makeFilesWidget()
{
  filesMainWidget = new QWidget;
  filesMainLayout = new QVBoxLayout();
  filesMainWidget->setLayout(filesMainLayout);
  
  cryptButton = new QPushButton(QString("crypter le fichier"),this);
  QObject::connect(cryptButton,SIGNAL(clicked()),this,SLOT(cryptFile()));
  
  passFileLine = new QLineEdit(QString("fichier"),this);
  passFileLine->setText("passwords");
  
  filesMainLayout->addWidget(passFileLine);
  filesMainLayout->addWidget(cryptButton);
}

/* affiche le widget de gestion des fichiers */
void Fenetre::setFilesWidget()
{
  passwordMainWidget->setVisible(false);
  filesMainWidget->setVisible(true);
}

/* methode de cryptage d'un fichier de password.
 * Forme d'une ligne requise : Nom : Password \n
 * Une ligne de forme différente sera recopiée.
 */
void Fenetre::cryptFile()
{
  QString inputName = passFileLine->text();
  QFile infile(inputName);
  QFile outfile(inputName+".crypt");
  QByteArray line, encLine, pass, encPass;
  int passPos=0;
  
  QByteArray key = passPopUp();
  
  if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  
  if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  
  QTextStream out(&outfile);
  
  while (!infile.atEnd())
  {
    line = infile.readLine();
    if (line.lastIndexOf(": ") == 0)
    {
      out << line;
    }
    else
    {
      passPos = line.lastIndexOf(": ") + 1;
      pass = line;
      pass.chop(1);
      encPass = encrypt(pass.remove(0,passPos+1), key);
      encLine = line.replace(passPos+1,line.length()-(passPos+1),encPass);
      out << encLine.data() << endl;;
    }
  }
  return;
}


/*******************************************************************
Fonctions Cryptographiques
********************************************************************/

QByteArray Fenetre::encrypt(QByteArray pass)
{
  int keyIndex = 0;
  QByteArray key = passPopUp();
  for (int ii=0; ii<pass.length(); ii++)
  {
    pass[ii] = encrypt(pass.at(ii),key.at(keyIndex));
    keyIndex++;
    if (keyIndex == key.length()) keyIndex = 0;
  }
  return pass;
}

QByteArray Fenetre::encrypt(QByteArray pass,QByteArray mainKey)
{
  int keyIndex = 0;
  QByteArray key = mainKey;
  for (int ii=0; ii<pass.length(); ii++)
  {
    pass[ii] = encrypt(pass.at(ii),key.at(keyIndex));
    keyIndex++;
    if (keyIndex == key.length()) keyIndex = 0;
  }
  return pass;
}

QByteArray Fenetre::decrypt(QByteArray pass)
{
  int keyIndex = 0;
  QByteArray key = passPopUp();
  for (int ii=0; ii<pass.length();ii++)
  {
    pass[ii] = decrypt(pass.at(ii),key.at(keyIndex));
    keyIndex++;
    if (keyIndex == key.length()) keyIndex = 0;
  }
  return pass;
}

char Fenetre::encrypt(char dec, char key)
{
  // Normes pour les har : 
  // conversion entiere : 32 = ' ' -> 126 = '~'
  for (int index = 0 ; index < (int) key; index ++)
  {
    if ((int) dec == 126) dec = (char) 32;
    else dec++;
  }
  return dec;
}

char Fenetre::decrypt(char enc, char key)
{
  // Normes pour les har : 
  // conversion entiere : 32 = ' ' -> 126 = '~'
  for (int index = 0 ; index < (int) key; index ++)
  {
    if ((int) enc == 32) enc = (char) 126;
    else enc = enc-1;
  }
  return enc;
}
