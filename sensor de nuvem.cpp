const int trigPin = 4;
const int echoPin = 3;
const int ledPin = 11;

// Velocidade do som em cm/µs (a 20°C)
const float VELOCIDADE_SOM = 0.0343;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(trigPin, LOW);
  digitalWrite(ledPin, LOW);
  
  Serial.println("=== DETECTOR DE NUVENS ATÉ 5 METROS ===");
  Serial.println("Mostrando distância em CM e METROS");
  delay(1000);
}

void loop() {
  // --- DISPARO ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // --- LEITURA COM TIMEOUT (6 metros = ~35ms) ---
  long duration = pulseIn(echoPin, HIGH, 35000);

  if (duration == 0) {
    Serial.println("Sem reflexo (muito longe ou nuvem fina)");
    digitalWrite(ledPin, LOW);
  } else {
    // --- CÁLCULO EM CM ---
    float distancia_cm = duration * VELOCIDADE_SOM / 2;
    
    // --- CONVERSÃO PARA METROS ---
    float distancia_m = distancia_cm / 100.0;

    // --- EXIBE AS DUAS UNIDADES ---
    Serial.print("Distância: ");
    Serial.print(distancia_cm, 1);
    Serial.print(" cm | ");
    Serial.print(distancia_m, 2);
    Serial.println(" m");

    // --- ACENDE LED SE ATÉ 5 METROS ---
    if (distancia_m <= 5.0) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }

  delay(600); // Leitura a cada ~0,6s

}

