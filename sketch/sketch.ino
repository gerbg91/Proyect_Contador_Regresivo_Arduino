#include <Config.h>
#include <EasyBuzzer.h>
#include <TM1637Display.h>

long tiempoContadorConstante = 10;
long tiempoContador = tiempoContadorConstante;
long tiempoIntervalo = 1000;
long tiempoAnterior = 0;
long tiempoActual = 0;
int valuePulsador = 0;
int frecuenciaHercios = 2000;

const int inputPulsador = 11;
const byte inputBuzzer = 5;

#define CLK 3
#define DIO 4

// Crea objeto display
TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
  // Realiza el brillo
  display.setBrightness(5);
  pinMode(inputPulsador, INPUT);
  Serial.begin(9600);
}

void loop() {
  valuePulsador = digitalRead(inputPulsador);
  if (valuePulsador == HIGH) {
    tiempoContador = tiempoContadorConstante;
    noTone(inputBuzzer);
  }

  if (tiempoContador >= 0) {
    tiempoActual = millis();
    if ((tiempoActual - tiempoAnterior) >= tiempoIntervalo) {
      muestraTiempo(tiempoContador);
      tiempoContador--;
      tiempoAnterior = tiempoActual;
    }
  }
}

void muestraTiempo(int tiempoContador) {
  display.showNumberDec(tiempoContador);
  if (tiempoContador == 0) {
    tone(inputBuzzer, frecuenciaHercios);
  }
}
