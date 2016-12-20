#define DEBUG_MM                //debug, e. g. don't hoover!

#define CONTACT_SENSOR_VIA_IRQ  //evaluate the contact sensorss via irq handler -&gt; faster



#define PORT_RECHTES_RAD_VORWAERTS    4
#define PORT_RECHTES_RAD_RUECKWAERTS  5
#define PORT_LINKES_RAD_VORWAERTS     7
#define PORT_LINKES_RAD_RUECKWAERTS   6

#define PORT_VENTILATOR              11

//#define PORT_CONTACTSENSORS          12 //pin 12 cant make use of irq
#define PORT_CONTACTSENSORS           2
#ifdef CONTACT_SENSOR_VIA_IRQ
#define IRQ_NMBR_CONTACTSENSOR        0  // Pin2 uses IRQ number 0
#endif

#define PORT_LIFE_LED                13

//State machine defines
#define STMA_STATE_MOVE_BACK        0xe0
#define STMA_STATE_START              20


#ifdef CONTACT_SENSOR_VIA_IRQ
 extern void irqh_immediate_move_back(void);
#endif
volatile unsigned char STMA_state_uc = STMA_STATE_START;

//-------------------------------------------------
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode( PORT_RECHTES_RAD_VORWAERTS,   OUTPUT);  //vorwaerts rechts
  pinMode( PORT_RECHTES_RAD_RUECKWAERTS, OUTPUT);  //rueckwaerts rechts
  pinMode( PORT_LINKES_RAD_RUECKWAERTS,  OUTPUT);  //rueckwaerts links
  pinMode( PORT_LINKES_RAD_VORWAERTS,    OUTPUT);  //vorwaerts links
  pinMode( PORT_VENTILATOR,              OUTPUT);  //Saugmotor

  pinMode(PORT_CONTACTSENSORS,           INPUT);   //vorderer kontaktsensor
#ifdef CONTACT_SENSOR_VIA_IRQ
  //pinMode(PORT_CONTACTSENSORS,           INPUT_PULLUP);   //vorderer kontaktsensor
  attachInterrupt( IRQ_NMBR_CONTACTSENSOR, irqh_immediate_move_back, FALLING);
#endif
 
  pinMode(PORT_LIFE_LED, OUTPUT);   //lifeled
 
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS,   LOW);
  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, LOW);
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  LOW);
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,    LOW);
 
  digitalWrite( PORT_VENTILATOR,              LOW);
 
  delay( 1000 );   //erst mal kurz warten...
}

//-------------------------------------------------
void saugen( boolean stat )
{
#ifndef DEBUG_MM   //nicht saugen im debugmodus
  digitalWrite( PORT_VENTILATOR, stat );   // Saugluefter EIN
  digitalWrite( PORT_VENTILATOR, stat );   // Saugluefter AUS
#endif
}

//-------------------------------------------------
void vorwaerts( void )
{
  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  LOW);   // turn the LED on (HIGH is the voltage level)
 
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS,   HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,    HIGH);   // turn the LED on (HIGH is the voltage level)
}

//-------------------------------------------------
void vorwaerts_kurve( signed char staerke_der_kurve_c )
{
  //positive werte = linkskurve
  //negative werte = rechtskurve
  //wertebereich: -100% .. +100%
#define MAX_PROZENT 100
 
  unsigned char counter_uc;
  boolean       wirkung_rechtes_rad_bl;
  boolean       wirkung_linkes_rad_bl;
 
  if ( staerke_der_kurve_c &gt; MAX_PROZENT )    staerke_der_kurve_c = MAX_PROZENT;
  if ( staerke_der_kurve_c &lt; -1*MAX_PROZENT ) staerke_der_kurve_c = -1*MAX_PROZENT;
 
  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, LOW);   
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  LOW);   

  //rechtskurve
  wirkung_rechtes_rad_bl = LOW;
  wirkung_linkes_rad_bl  = HIGH;
 
  if ( staerke_der_kurve_c &lt; 0 )
  {
    staerke_der_kurve_c *= -1;
    
    //linkskurve
    wirkung_rechtes_rad_bl = HIGH;
    wirkung_linkes_rad_bl  = LOW;
  }
    
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS, HIGH);   
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,  HIGH);   
 
  for ( counter_uc = 0; counter_uc &lt; MAX_PROZENT; counter_uc++ )
  {
    if ( counter_uc &gt; (MAX_PROZENT-staerke_der_kurve_c) )
    {
      digitalWrite( PORT_RECHTES_RAD_VORWAERTS, wirkung_rechtes_rad_bl);   
      digitalWrite( PORT_LINKES_RAD_VORWAERTS,  wirkung_linkes_rad_bl);   
 
      delay( 10 );
    }
  }  
}

//-------------------------------------------------
void vorwaerts_kurve_simple( signed char richtung_kurve_c )
{
  //positive werte = linkskurve
  //negative werte = rechtskurve
  //wertebereich: -1 .. +1
#define MAX_PROZENT 1
 
  unsigned char counter_uc;
  boolean       wirkung_rechtes_rad_bl;
  boolean       wirkung_linkes_rad_bl;
 
  if ( richtung_kurve_c &gt; MAX_PROZENT )    richtung_kurve_c = MAX_PROZENT;
  if ( richtung_kurve_c &lt; -1*MAX_PROZENT ) richtung_kurve_c = -1*MAX_PROZENT;
 
  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, LOW);   
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  LOW);   

  digitalWrite( PORT_RECHTES_RAD_VORWAERTS, HIGH);   
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,  HIGH);

  if ( richtung_kurve_c &gt; 0 )
    digitalWrite( PORT_RECHTES_RAD_VORWAERTS, LOW);

  if ( richtung_kurve_c &lt; 0 )
    digitalWrite( PORT_LINKES_RAD_VORWAERTS, LOW);
}

//-------------------------------------------------
void rueckwaerts( void )
{
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS,   LOW);   
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,    LOW);   

  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, HIGH);   
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  HIGH);   
}

//-------------------------------------------------
void rueckwaerts_kurve( signed char staerke_der_kurve_c )
{
  //positive werte = linkskurve
  //negative werte = rechtskurve
  //wertebereich: -100% .. +100%
#define MAX_PROZENT 100
 
  unsigned char counter_uc;
  boolean       wirkung_rechtes_rad_bl;
  boolean       wirkung_linkes_rad_bl;
 
  if ( staerke_der_kurve_c &gt; MAX_PROZENT )    staerke_der_kurve_c = MAX_PROZENT;
  if ( staerke_der_kurve_c &lt; -1*MAX_PROZENT ) staerke_der_kurve_c = -1*MAX_PROZENT;
 
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS, LOW);   
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,  LOW);   

  //rechtskurve
  wirkung_rechtes_rad_bl = LOW;
  wirkung_linkes_rad_bl  = HIGH;
 
  if ( staerke_der_kurve_c &lt; 0 )
  {
    staerke_der_kurve_c *= -1;
    
    //linkskurve
    wirkung_rechtes_rad_bl = HIGH;
    wirkung_linkes_rad_bl  = LOW;
  }
    
  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, HIGH);   
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  HIGH);   
 
  for ( counter_uc = 0; counter_uc &lt; MAX_PROZENT; counter_uc++ )
  {
    if ( counter_uc &gt; (MAX_PROZENT-staerke_der_kurve_c) )
    {
      digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, wirkung_rechtes_rad_bl);   
      digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  wirkung_linkes_rad_bl);   
 
      delay( 10 );
    }
  }  
}

//-------------------------------------------------
void rueckwaerts_kurve_simple( signed char richtung_kurve_c )
{
  //positive werte = linkskurve
  //negative werte = rechtskurve
  //wertebereich: -1 .. +1
#define MAX_PROZENT 1
 
  unsigned char counter_uc;
  boolean       wirkung_rechtes_rad_bl;
  boolean       wirkung_linkes_rad_bl;
 
  if ( richtung_kurve_c &gt; MAX_PROZENT )    richtung_kurve_c = MAX_PROZENT;
  if ( richtung_kurve_c &lt; -1*MAX_PROZENT ) richtung_kurve_c = -1*MAX_PROZENT;
 
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS, LOW);   
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,  LOW);  

  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, HIGH);   
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  HIGH);

  if ( richtung_kurve_c &lt; 0 )
    digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, LOW);

  if ( richtung_kurve_c &gt; 0 )
    digitalWrite( PORT_LINKES_RAD_RUECKWAERTS, LOW);
}

//-------------------------------------------------
void stoppen( void )
{
  digitalWrite( PORT_RECHTES_RAD_VORWAERTS,   LOW);   
  digitalWrite( PORT_LINKES_RAD_VORWAERTS,    LOW);

  digitalWrite( PORT_RECHTES_RAD_RUECKWAERTS, LOW);   
  digitalWrite( PORT_LINKES_RAD_RUECKWAERTS,  LOW);   
}

//-------------------------------------------------
void defect_stop_all( void )
{
  //nutzereingriff noetig!
  stoppen();
  saugen( LOW );
  digitalWrite(PORT_LIFE_LED, HIGH);  //lifeled dauerleuchten
  while( 1 ){ ;}
}

//-------------------------------------------------
void move_back( void )
{
  //rueckwaerts();
  rueckwaerts_kurve_simple( -1 );
  delay(400);                // wait
//  rueckwaerts();
//  delay(200);
}

//-------------------------------------------------
void eval_contact_sensor( void )
{
  unsigned char counter_defekt_uc = 0;
 
  while ( digitalRead(PORT_CONTACTSENSORS) == LOW )  //stopperkontakt betaetigt!
  {
    move_back();
    
    counter_defekt_uc++;
    
    if ( counter_defekt_uc &gt; 10 )
    {
      defect_stop_all();
    }
  }

}
//-------------------------------------------------
#ifdef CONTACT_SENSOR_VIA_IRQ
void irqh_immediate_move_back(void)
//interrupt handler
{
  digitalWrite(PORT_LIFE_LED, HIGH);  //lifeled

  stoppen();
 
  STMA_state_uc = STMA_STATE_MOVE_BACK;

  //delay(100);   //delay doesn'T work in irq handler routines
  digitalWrite(PORT_LIFE_LED, LOW);  //lifeled
 
}
#endif


//-------------------------------------------------
// the loop function runs over and over again forever
void loop() {
 
 
  saugen( HIGH );

  //digitalWrite(PORT_LIFE_LED, HIGH); //lifeled
 

    vorwaerts_kurve_simple(1); //dieser befehl bei einer wartezeit von ca. 2 Sek entspricht ca. 45 Grad
    delay(7000);
    vorwaerts();
    delay(1000);
    
    saugen( LOW );
    
    vorwaerts_kurve_simple(-1);
    delay(7000);
    vorwaerts();
    delay(1000);

    saugen( HIGH );
 
 
}﻿
