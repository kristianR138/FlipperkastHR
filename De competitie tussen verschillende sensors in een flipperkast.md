Naam: Kristian Rumsa
Klas: 1TIC
# Hoofdstuk 1 Inleiding

## Hoofdstuk 1.1 Introductie

Sensors kunnen allerlei dingen detecteren, zoals geluiden, bewegingen en objecten. Nog een voorbeld van een detecteerbaar object is een metalen bal in een flipperkast. Om een functionerende flipperkast te bouwen is er een onderdeel nodig die een bal detecteerd en een signaal verder stuurt naar andere onderdelen.

## Hoofdstuk 1.2 Eisen

Dit onderzoek moet een sensor opleveren die:
- Een metalen speelbal van 12 mm diameter en een massa van 7 gram kunnen detecteren.
- Een speelbal binnen 200 ms detecteren.
- Een speelbal minimaal 99 keer detecteren wanneer de speelbal 100 keer langskomt.

# Hoofdstuk 2 Ondezoek

Er is een keuze tussen drie sensoren:
##### Hoofdstuk 2.1 De ultrasoon sensor
![[Pasted image 20260929093515.png|403]][1]
De ultrasoon sensor ofwel de HC-SR04 ULTRASONISCHE AFSTANDS DETECTIE MODULE is een sensor die geluid gebruikt om dingen te detecteren. Dit component is speciaal omdat het ook de afstand van het object kan opmeten, wat niet een praktische applicatie heeft aan onze gestelde eisen. De ultra sonische sensor kan alleen een bal detecteren als de bal verder dan 2 cm is, dit lijkt op een klein probleem, maar in een flipperkast van ongeveer 20 cm is het een reden dan de ultrasoon sensor niet de eerste eis voldoet [2].

In een praktische experiment zijn de laatste twee eisen uitgetest. Uit het experiment is gekomen dat het reactie snelheid in de normen is van 200ms. Maar de derde eis is niet gelukt, er is opgemeten success kans van 80 % van het detecteren van een speelbal.

##### Hoofdstuk 2.2 De infrarood sensor 
![[Pasted image 20260929093826.png|253]][3]
De infrarood sensor gebruikt infrarood lichtgolven om een object te detecteren. Dit componenet heeft een praktische eigenschap, het namelijk veel kleiner dan de ultrasoon sensor wat goed is voor het pinball machine [4].

In een praktische experiment zijn de drie eisen uitgetest. De infrarood sensor heeft het eerste eis voldaan. Het reactietijd van het IR sensor is niet gebonden aan het snelheid van geluid(niet het geval voor de ultrasoon sensor), dus is de reactie tijd wel onder 200ms. In het hiervoorgenoemde heeft de sensor de speelbal alle 100 keer gedetecteerd.

##### Hoofdstuk 2.3 Hefboomswitch

![[Pasted image 20260929095112.png|324]][5]

De kinetische energie van een speelbal wordt gebruikt om de micro hefboomswitch, dit component is het kleinste component van alle drie.

Er werd een derde praktische experiment gedaan, hierin is er een speelbal tegen een hefboomsknop switch gepit. De speelbal had te weinig kracht om de hefboomswitch te activeren. Het componenet heeft de eerste eis gefaalt en daarmee ook de tweede en derde eisen. 

# Conclusie 

Hier is een samenvatting van de data in dit onderzoek:

|           | Eis 1 | EIs 2 | Eis 3 |
| --------- | ----- | ----- | ----- |
| Ultrasoon | ja    | ja    | nee   |
| IR sensor | ja    | ja    | ja    |
| Hefboom   | nee   | nee   | nee   |

Hieruit kan er een conclusie getrokken worden dat het IR sensor het beste is om gebruikt te worden in een flipperkast.
# Bronvermelding

[1]Opencircuit HC-SR04 Ultrasonische afstands detectie module_. (2024, January 29). Opencircuit. https://opencircuit.be/product/hc-sr04-ultrasonische-afstands-detectie-module

[2]Ultrasonic Ranging Module HC - SR04_. (n.d.). Sparkfun. https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf

[3]Mechaxil. (n.d.). _IR Obstacle Sensor HW-201_. https://mechaxil.com/products/obs-ir

[4]Nawazi, F. (2023, September 14). _HW201 Infrared (IR) Sensor Module_. Circuits DIY. https://www.circuits-diy.com/hw201-infrared-ir-sensor-module/

[5]_Rens Electronics - MicroSwitch_. (n.d.). https://rens-electronics.nl/pages/bakery/microswitch-20mm-hefboom-8329.php