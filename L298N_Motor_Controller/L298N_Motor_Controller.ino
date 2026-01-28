/* 
 * Programme: Motor Controller L298N
 * Introduction: The purpose of this project was to create a programme to allow an L298N bridge to interface with an Arduino board and control the direction of an AC motor.
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  PIN NUMBER ASSIGNMENTS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const int enA = 9;              // PWM output to L298N, used to control motor's speed
const int potentiometer = A0;   // Analog A0 pin connected to potentiometer

// Digital Outputs connected to L298N
const int in1 = 7;            // Input direction 1 set to pin 7; when high while in2 is low, motor goes forward
const int in2 = 2;            // Input direction 2 set to pin 2; when high while in1 is low, motor goes in reverse
const int button = 4;         // Push-button used to toggle motor's direction
const int buttonLED = 13;     // Internal LED used to indicate button press reading

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Variable Declarations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int rotateDirection = 0;          // Controls motor's direction
int lastPotValue = -1;            // previous pot reading
int newPotValue = 0;              // current pot reading
int PWMOutput = 0;                // PWM value to be written to L298N via pin 9 (enA)
boolean pressed = false;          // Used to determine if push button has been pressed

void setup()
{
  Serial.begin(9600);

  // Output declarations
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(buttonLED, OUTPUT);

  // Input declarations
  pinMode(potentiometer, INPUT);
  pinMode(button, INPUT);

  // Set initial motor direction to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
}
  
void loop()
{
    newPotValue = analogRead(potentiometer);     // Read the voltage from the pot (10-bit ADC, 0 --> 1023)
    PWMOutput = (newPotValue / 1023.0) * 255;    // Scale the pot's value to a range of 0 --> 255
    analogWrite(enA, PWMOutput);              // Send PWM value to L298N's enable pin via Arduino's pin 9 (enA)
    
    // Print potentiometer reading only if the potValue has changed
    if (abs(newPotValue - lastPotValue) > 2)
    {
        Serial.print("Potentiometer Reading: ");
        Serial.println(newPotValue);
        Serial.println();

        lastPotValue = newPotValue;
    }
    
    // Check to see if the button has been pressed; if it has, toggle the value of 'pressed'
    if (digitalRead(button) == HIGH)
    {
      pressed = true;
    }

    while(digitalRead(button) == HIGH)    // Loop while the state of the button is still high
    {
      delay(10);                          // De-bounce delay to avoid multiple toggles
    }

    // If a button press is detected, change the motor's rotation direction to reverse
    if (pressed == true)
    {
        // Flash LED to indicate a button press was registered
        digitalWrite(buttonLED, HIGH);
        delay(200);
        digitalWrite(buttonLED, LOW);

        // Toggle direction
        rotateDirection = 1 - rotateDirection;    // Change the state of rotateDirection to be the complement of its current state
        pressed = false;                          // Change the state of button pressed back to low

        // Safety pause before direction change
        analogWrite(enA, 0);
        delay(100);

        if (rotateDirection == 1)   // When rotateDirection equals 1, change the motor's direction to reverse
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);

            // Print the state of rotate direction reading to the screen to verify connection and input validity
            Serial.println("Reverse motor rotation enabled");
            Serial.println();
            delay(100);
        }

        else    // When rotateDirection equals 0, change the motor's direction back to forward
        {
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);

            // Print the state of rotate direction reading to the screen to verify connection and input validity
            Serial.println("Forward motor rotation enabled");
            Serial.println();
            delay(100);
        }
    }
}