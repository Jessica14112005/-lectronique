const int analog0 = A0;
const int analog1 = A1;
const char lettres[16] = {'A','B','C','D','E','F','H','I','J','K','L','M','N','O','P','Q'};
const int id[16] = {73,56,29,41,85,17,64,92,38,59,24,47,68,12,33,76};
int start;
int modeleDebut;
bool final;

void setup()
{
  pinMode(analog0, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  while (Serial.available() > 0)
  {
    Serial.read();
  }
  final = false;
  Serial.println("Entrez le code correspondant a votre carte sur les interrupteurs et tapez 1 pour valider");
  while (Serial.available() <= 0) {}
  start = Serial.parseInt();
  if (start == 1)
  {
    modeleDebut = verif1();
    if (modeleDebut == -1)
    {
      Serial.println("Aucun modèle reconnu");
      delay(1000);
    }
    else
    {
      Serial.println("Modele " + String(modeleDebut) + " reconnu");
      delay(1000);
      Serial.println("Veuillez entrez votre carte");
      delay(1000);
      int inputCarte;
      float tensionCarte;
      inputCarte = analogRead(analog1);
	  tensionCarte = inputCarte * (5.0 / 1023.0);
      if (tensionCarte > 2.0394 and tensionCarte < 2.0806 and modeleDebut == 4)
      {
        Serial.println("Carte correspondante au modèle");
        delay(1500);
        final = principale();
      }
      else
      {
        Serial.println("Aucune correlation");
        delay(1000);
      }
    }
  }
  if (final == true)
  {
    Serial.println("Authentification finale terminee : ouverture du coffre BIMBAMBOUMMMM");
  }
  else
  {
    Serial.println("Authentification finale invalide : veuillez reessayer");
  }
}

int verif1()
{
  int input;
  float tol1=0.99;
  float tol2=1.01;
  float tension;
  input = analogRead(analog0);
  tension = input * (5.0 / 1023.0);
  if ((tension > 2.96*tol1 and tension < 2.96*tol2) || (tension > 4.00*tol1 and tension < 4.00*tol2))
  {
    return 1;
  }
  else if (tension > 3.59*tol1 and tension < 3.59*tol2)
  {
    return 2;
  }
  else if ((tension > 4.05*tol1 and tension < 4.05*tol2) || (tension > 3.85*tol1 and tension < 3.85*tol2) || (tension > 3.33*tol1 and tension < 3.33*tol2))
  {
    return 3;
  }
  else if ((tension >= 0.00*tol1 and tension <= 0.00*tol2) || (tension > 1.02*tol1 and tension < 1.02*tol2) || (tension > 1.76*tol1 and tension < 1.76*tol2))
  {
    return 4;
  }
  else if (tension > 3.68*tol1 and tension < 3.68*tol2)
  {
    return 5;
  }
  else if ((tension > 2.72*tol1 and tension < 2.72*tol2) || (tension > 2.22*tol1 and tension < 2.22*tol2) || (tension > 4.10*tol1 and tension < 4.10*tol2))
  {
    return 6;
  }
  else if ((tension > 3.77*tol1 and tension < 3.77*tol2) || (tension > 3.17*tol1 and tension < 3.17*tol2))
  {
    return 7;
  }
  else if (tension > 3.95*tol1 and tension < 3.95*tol2)
  {
    return 8;
  }
  else
  {
    return -1;
  }
}


bool principale()
{
  bool isTrue = false;
  const int modele[8] = {1,1,2,2,3,3,4,5};
  int modeleCarte;
  int nivSecu;
  
  // Serial.println("Entrez votre numero de modele de carte :");
  // while (Serial.available() <= 0) {}
  // modeleCarte = Serial.parseInt();
  nivSecu = modele[(modeleDebut)-1];
  Serial.println("Debut de l'authentification de niveau "+ String(nivSecu));

  if (nivSecu == 1 and MA1() == true)
  {
    if (MA3() == true)
    {
      isTrue = true;
    }
  }

  else if (nivSecu == 2 and MA1() == true)
  {
    if (MA4() == true)
    {
      isTrue = true;
    }
  }

  else if (nivSecu == 3 and MA2() == true)
  {
    if (MA5(lettres,id) == true)
    {
      isTrue = true;
    }
  }

  else if (nivSecu == 4 and MA2()== true )
  {
    if (MA3() == true)
    {
      if (MA4() == true)
      {
        isTrue = true;
      }
    }
  }

  else if (nivSecu == 5 and MA1() == true)
  {
    if (MA2() == true)
    {
      if (MA3() == true)
      {
        if (MA5(lettres,id) == true)
        {
          isTrue = true;
        }
      }
    }
  }
  return isTrue;
}

bool MA1()
{
  bool isTrue = false;
  char reponse;

  Serial.println("Initialisation de la MA1");
  Serial.println("");
  Serial.println("Question 1 : Quel est le nom de code de l'operation en cours ?");
  Serial.println("a) Strongbox 3000");
  Serial.println("b) Operation Cerberus");
  Serial.println("c) Operation Mercury");

  while (Serial.available() <= 0) {}
  reponse = Serial.read();
  if (reponse == 'a')
  {
    Serial.println("Question 2 : Quel est le lieu de naissance de votre superieur immediat ?");
    Serial.println("a) Londres");
    Serial.println("b) edimbourg");
    Serial.println("c) Belfast");

    while (Serial.available() <= 0) {}
    reponse = Serial.read();
    if (reponse == 'b')
    {
      Serial.println("Quel est le nom du premier animal de compagnie que vous avez eu ?");
      Serial.println("a) Max");
      Serial.println("b) Luna");
      Serial.println("c) Charlie");

      while (Serial.available() <= 0) {}
      reponse = Serial.read();
      if (reponse == 'c')
      {
        isTrue = true;
        Serial.println("Authentification 1 validee");
      }
      else
      {
        Serial.println("Authentification 1 echouee"); 
      }
    }
    else
    {
      Serial.println("Authentification 1 echouee"); 
    }
  }
  else
  {
    Serial.println("Authentification 1 echouee");
  }
  return isTrue;
}

bool MA2()
{
  const char x[16] = {'A','B','C','D','E','F','H','I','J','K','L','M','N','O','P','Q'};
  const int e[16] = {601,619,631,641,647,653,661,673,691,701,733,739,751,797,809,811};
  const int d[16] = {1273,103,883,653,467,641,1321,589,1039,953,745,919,1159,713,233,1063};
  bool isTrue;
  bool verif;
  int M,Mp,C;
  char xinput;

  Serial.println("Initialisation de la MA2");
  Serial.println("Identifiez-vous (lettre d'agent) :");
  while (Serial.available()<= 0) {}
  xinput = Serial.read();
  for (int i = 0; i < 16; i++)
  {
    if (xinput == x[i])
    {
      xinput = i;
      verif = true;
      break;
    }  
  }
  if (verif == false)
  {
    Serial.println("Identite invalide");
  }
  else
  {
    M = random(2882);
    C = chiffrer(M, e[xinput]);
    Serial.println("Message a dechiffrer :"+ String(C));
    //Serial.println(M);
    while (Serial.available() <= 0) {}
    delay(100);
    Mp = Serial.parseInt();
    Serial.println(M +""+ Mp);
    if (M == Mp)
    {
      Serial.println("Authentification 2 validee");
      isTrue = true;
    }
    else
    {
      Serial.println("Authentification 2 echouee");
    }
  }
}

bool MA3()
{
  bool isTrue = false;
  int retine;

  Serial.println("Initialisation de la MA3");
  Serial.println("Veuillez vous placer devant le capteur retinien");
  Serial.println("Scan de la retine en cours...");
  while (Serial.available()<= 0) {}
  retine = Serial.parseInt();
  if (retine == 1)
  {
    Serial.println("Authentification 3 validee");
    isTrue = true;
  }
  else
  {
    Serial.println("Authentification 3 echouee");
  }
  return isTrue;
}

bool MA4()
{
  bool isTrue = false;
  int doigt;

  Serial.println("Initialisation de la MA4");
  Serial.println("Veuillez placer votre doit sur le capteur d'empreinte digitale");
  Serial.println("Scan de l'empreinte digitale en cours...");
  while (Serial.available()<= 0) {}
  doigt = Serial.parseInt();
  if (doigt == 1)
  {
    Serial.println("Authentification 4 validee");
    isTrue = true;
  }
  else
  {
    Serial.println("Authentification 4 echouee");
  }
  return isTrue;
}

bool MA5(const char lettres[16],const int id[16])
{
  bool isTrue = false;
  char input1;
  int input2;

  Serial.println("Initialisation de la MA5");
  Serial.println("Identifiez-vous (lettre d'agent) :");
  while (Serial.available()<= 0) {}
  input1 = Serial.read();
  Serial.println("Veuillez renseigner votre Card ID :");
  while (Serial.available()<= 0) {}
  input2 = Serial.parseInt();

  for (int i = 0; i < 16; i++)
  {
    if (input1 == lettres[i] and input2 == id[i])
    {
      isTrue = true;
      break;
    }
  }
  return isTrue;
}

int chiffrer(int M,int e)
{
  int n;
  int C;
  n = 43*67;
  C = modeExp(M,e,n);
  return C;
}

int modeExp(int a, int e, int n)
{
  long long r;
  if (e<0)
  {
    Serial.println("cas invalide");
    return -1;
  }
  else
  {
    if (a==0 || n ==1)
    {
      r=0;
    }
    else
    {
      r=1;
      while (e>0)
      {
        r=(r*(a % n)) % n;
        e= e-1;
      }
    }
  }
  return r;
}
