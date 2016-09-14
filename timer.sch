EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:timer
LIBS:ESP8266
LIBS:timer-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X02 P6
U 1 1 57C73076
P 1250 1800
F 0 "P6" H 1250 1950 50  0000 C CNN
F 1 "CONN_LOAD" V 1350 1800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1250 1800 50  0001 C CNN
F 3 "" H 1250 1800 50  0000 C CNN
	1    1250 1800
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 57C730BA
P 1250 1100
F 0 "P2" H 1250 1250 50  0000 C CNN
F 1 "PWR_IN" V 1350 1100 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02" H 1250 1100 50  0001 C CNN
F 3 "" H 1250 1100 50  0000 C CNN
	1    1250 1100
	1    0    0    1   
$EndComp
$Comp
L POT RV1
U 1 1 57C73177
P 9775 900
F 0 "RV1" H 9775 820 50  0000 C CNN
F 1 "POT" H 9775 900 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Trimmer-Suntan-TSR-3386C" H 9775 900 50  0001 C CNN
F 3 "" H 9775 900 50  0000 C CNN
	1    9775 900 
	0    1    1    0   
$EndComp
$Comp
L FQP30N06 Q1
U 1 1 57C73479
P 975 2200
F 0 "Q1" H 1225 2275 50  0000 L CNN
F 1 "FQP30N06" H 1225 2200 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 1225 2125 50  0000 L CIN
F 3 "" H 975 2200 50  0000 L CNN
	1    975  2200
	-1   0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 57C734BC
P 1350 2500
F 0 "R4" V 1430 2500 50  0000 C CNN
F 1 "22K" V 1350 2500 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 1280 2500 50  0001 C CNN
F 3 "" H 1350 2500 50  0000 C CNN
	1    1350 2500
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 57C73517
P 1650 2250
F 0 "R2" V 1730 2250 50  0000 C CNN
F 1 "100R" V 1650 2250 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 1580 2250 50  0001 C CNN
F 3 "" H 1650 2250 50  0000 C CNN
	1    1650 2250
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 57C73566
P 2875 2750
F 0 "R6" V 2955 2750 50  0000 C CNN
F 1 "3.6K" V 2875 2750 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 2805 2750 50  0001 C CNN
F 3 "" H 2875 2750 50  0000 C CNN
	1    2875 2750
	1    0    0    -1  
$EndComp
$Comp
L ROTARY_ENCODER_SWITCH SW1
U 1 1 57C73617
P 3275 3250
F 0 "SW1" H 3275 3510 50  0000 C CNN
F 1 "ROTARY_ENCODER_SWITCH" H 3275 2990 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 3175 3410 50  0001 C CNN
F 3 "" H 3275 3510 50  0001 C CNN
	1    3275 3250
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 57C73670
P 3850 3675
F 0 "C5" H 3875 3775 50  0000 L CNN
F 1 "104pF" H 3875 3575 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 3888 3525 50  0001 C CNN
F 3 "" H 3850 3675 50  0000 C CNN
	1    3850 3675
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 57C736B5
P 2875 3675
F 0 "C4" H 2900 3775 50  0000 L CNN
F 1 "104pF" H 2900 3575 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 2913 3525 50  0001 C CNN
F 3 "" H 2875 3675 50  0000 C CNN
	1    2875 3675
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 57C73705
P 2600 3675
F 0 "C3" H 2625 3775 50  0000 L CNN
F 1 "104pF" H 2625 3575 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 2638 3525 50  0001 C CNN
F 3 "" H 2600 3675 50  0000 C CNN
	1    2600 3675
	1    0    0    -1  
$EndComp
$Comp
L CONN_HD44780 P5
U 1 1 57C74D2A
P 10625 1475
F 0 "P5" H 10625 2325 50  0000 C CNN
F 1 "CONN_HD44780" V 10725 1475 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x16" H 10625 1475 50  0001 C CNN
F 3 "" H 10625 1475 50  0000 C CNN
	1    10625 1475
	1    0    0    -1  
$EndComp
$Comp
L LM1117-5.0 U1
U 1 1 57C7508A
P 3175 1025
F 0 "U1" H 3275 775 50  0000 C CNN
F 1 "LM1117-5.0" H 3175 1275 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 3175 1025 50  0001 C CNN
F 3 "" H 3175 1025 50  0000 C CNN
	1    3175 1025
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 57C750E5
P 3825 1350
F 0 "C2" H 3850 1450 50  0000 L CNN
F 1 "22uF" H 3850 1250 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 3863 1200 50  0001 C CNN
F 3 "" H 3825 1350 50  0000 C CNN
	1    3825 1350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 57C75160
P 2525 1350
F 0 "C1" H 2550 1450 50  0000 L CNN
F 1 "10uF" H 2550 1250 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 2563 1200 50  0001 C CNN
F 3 "" H 2525 1350 50  0000 C CNN
	1    2525 1350
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR01
U 1 1 57C760AA
P 875 925
F 0 "#PWR01" H 875 775 50  0001 C CNN
F 1 "+12V" H 875 1065 50  0000 C CNN
F 2 "" H 875 925 50  0000 C CNN
F 3 "" H 875 925 50  0000 C CNN
	1    875  925 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 57C76124
P 875 1250
F 0 "#PWR02" H 875 1000 50  0001 C CNN
F 1 "GND" H 875 1100 50  0000 C CNN
F 2 "" H 875 1250 50  0000 C CNN
F 3 "" H 875 1250 50  0000 C CNN
	1    875  1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57C77450
P 875 2725
F 0 "#PWR03" H 875 2475 50  0001 C CNN
F 1 "GND" H 875 2575 50  0000 C CNN
F 2 "" H 875 2725 50  0000 C CNN
F 3 "" H 875 2725 50  0000 C CNN
	1    875  2725
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR04
U 1 1 57C78948
P 875 1700
F 0 "#PWR04" H 875 1550 50  0001 C CNN
F 1 "+12V" H 875 1840 50  0000 C CNN
F 2 "" H 875 1700 50  0000 C CNN
F 3 "" H 875 1700 50  0000 C CNN
	1    875  1700
	1    0    0    -1  
$EndComp
Text Label 1850 2250 0    60   ~ 0
PWR_CTRL
$Comp
L GND #PWR05
U 1 1 57C79D97
P 3825 1625
F 0 "#PWR05" H 3825 1375 50  0001 C CNN
F 1 "GND" H 3825 1475 50  0000 C CNN
F 2 "" H 3825 1625 50  0000 C CNN
F 3 "" H 3825 1625 50  0000 C CNN
	1    3825 1625
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 57C79DCD
P 2525 1625
F 0 "#PWR06" H 2525 1375 50  0001 C CNN
F 1 "GND" H 2525 1475 50  0000 C CNN
F 2 "" H 2525 1625 50  0000 C CNN
F 3 "" H 2525 1625 50  0000 C CNN
	1    2525 1625
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 57C79E4A
P 3175 1625
F 0 "#PWR07" H 3175 1375 50  0001 C CNN
F 1 "GND" H 3175 1475 50  0000 C CNN
F 2 "" H 3175 1625 50  0000 C CNN
F 3 "" H 3175 1625 50  0000 C CNN
	1    3175 1625
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR08
U 1 1 57C79F7F
P 2525 875
F 0 "#PWR08" H 2525 725 50  0001 C CNN
F 1 "+12V" H 2525 1015 50  0000 C CNN
F 2 "" H 2525 875 50  0000 C CNN
F 3 "" H 2525 875 50  0000 C CNN
	1    2525 875 
	1    0    0    -1  
$EndComp
Text Label 3625 1025 0    60   ~ 0
+5V
Text Label 6750 900  0    60   ~ 0
GND
Text Label 6725 1100 0    60   ~ 0
+5V
$Comp
L CONN_SPI P1
U 1 1 57C7A915
P 8575 900
F 0 "P1" H 8575 1100 50  0000 C CNN
F 1 "CONN_SPI" H 8575 700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 8575 -300 50  0001 C CNN
F 3 "" H 8575 -300 50  0000 C CNN
	1    8575 900 
	1    0    0    -1  
$EndComp
Text Label 6750 1000 0    60   ~ 0
~RST
Text Label 8025 1000 0    60   ~ 0
~RST
Text Label 9050 1000 0    60   ~ 0
GND
Text Label 9000 900  0    60   ~ 0
MOSI
Text Label 8025 900  0    60   ~ 0
SCK
Text Label 8000 800  0    60   ~ 0
MISO
Text Label 6725 1800 0    60   ~ 0
MOSI
Text Label 6725 1700 0    60   ~ 0
MISO
Text Label 6725 1600 0    60   ~ 0
SCK
$Comp
L R R1
U 1 1 57C7CAF5
P 6750 2100
F 0 "R1" V 6830 2100 50  0000 C CNN
F 1 "3.6K" V 6750 2100 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 6680 2100 50  0001 C CNN
F 3 "" H 6750 2100 50  0000 C CNN
	1    6750 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 57C7CB52
P 6750 2350
F 0 "#PWR09" H 6750 2100 50  0001 C CNN
F 1 "GND" H 6750 2200 50  0000 C CNN
F 2 "" H 6750 2350 50  0000 C CNN
F 3 "" H 6750 2350 50  0000 C CNN
	1    6750 2350
	1    0    0    -1  
$EndComp
Text Label 10150 725  0    60   ~ 0
GND
Text Label 10150 825  0    60   ~ 0
+5V
Text Label 10175 1025 0    60   ~ 0
RS
Text Label 10175 1125 0    60   ~ 0
RW
Text Label 10175 1225 0    60   ~ 0
EN
Text Label 10175 1725 0    60   ~ 0
DB4
Text Label 10175 1825 0    60   ~ 0
DB5
Text Label 10175 1925 0    60   ~ 0
DB6
Text Label 10175 2025 0    60   ~ 0
DB7
$Comp
L R R3
U 1 1 57C7FEDE
P 10150 2425
F 0 "R3" V 10230 2425 50  0000 C CNN
F 1 "47" V 10150 2425 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 10080 2425 50  0001 C CNN
F 3 "" H 10150 2425 50  0000 C CNN
	1    10150 2425
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 57C80865
P 9775 1150
F 0 "#PWR010" H 9775 900 50  0001 C CNN
F 1 "GND" H 9775 1000 50  0000 C CNN
F 2 "" H 9775 1150 50  0000 C CNN
F 3 "" H 9775 1150 50  0000 C CNN
	1    9775 1150
	1    0    0    -1  
$EndComp
Text Label 9625 675  0    60   ~ 0
+5V
$Comp
L R R5
U 1 1 57C84984
P 2600 2750
F 0 "R5" V 2680 2750 50  0000 C CNN
F 1 "3.6K" V 2600 2750 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 2530 2750 50  0001 C CNN
F 3 "" H 2600 2750 50  0000 C CNN
	1    2600 2750
	1    0    0    -1  
$EndComp
Text Label 2625 2450 0    60   ~ 0
+5V
Text Label 2300 3150 0    60   ~ 0
ROTA
Text Label 2300 3350 0    60   ~ 0
ROTB
$Comp
L GND #PWR011
U 1 1 57C85477
P 2600 3950
F 0 "#PWR011" H 2600 3700 50  0001 C CNN
F 1 "GND" H 2600 3800 50  0000 C CNN
F 2 "" H 2600 3950 50  0000 C CNN
F 3 "" H 2600 3950 50  0000 C CNN
	1    2600 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 57C854B5
P 2875 3950
F 0 "#PWR012" H 2875 3700 50  0001 C CNN
F 1 "GND" H 2875 3800 50  0000 C CNN
F 2 "" H 2875 3950 50  0000 C CNN
F 3 "" H 2875 3950 50  0000 C CNN
	1    2875 3950
	1    0    0    -1  
$EndComp
Text Label 3825 3150 0    60   ~ 0
ROTP
$Comp
L GND #PWR013
U 1 1 57C857FC
P 3850 3925
F 0 "#PWR013" H 3850 3675 50  0001 C CNN
F 1 "GND" H 3850 3775 50  0000 C CNN
F 2 "" H 3850 3925 50  0000 C CNN
F 3 "" H 3850 3925 50  0000 C CNN
	1    3850 3925
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 57C85FB0
P 3850 2750
F 0 "R7" V 3930 2750 50  0000 C CNN
F 1 "3.6K" V 3850 2750 50  0000 C CNN
F 2 "resistor-th:Resistor_Horizontal_RM12mm" V 3780 2750 50  0001 C CNN
F 3 "" H 3850 2750 50  0000 C CNN
	1    3850 2750
	1    0    0    -1  
$EndComp
Text Label 4850 800  0    60   ~ 0
RS
Text Label 4850 900  0    60   ~ 0
RW
Text Label 4850 1200 0    60   ~ 0
EN
Text Label 4850 1300 0    60   ~ 0
DB4
Text Label 4850 1400 0    60   ~ 0
DB5
Text Label 4850 1500 0    60   ~ 0
DB6
Text Label 4850 1600 0    60   ~ 0
DB7
Text Label 6750 1200 0    60   ~ 0
ROTA
Text Label 6750 1300 0    60   ~ 0
ROTB
Text Label 6750 1400 0    60   ~ 0
ROTP
$Comp
L CONN_ARDUINO_PRO_MINI_13_24 P4
U 1 1 57C8A9E7
P 7350 1350
F 0 "P4" H 7350 2000 50  0000 C CNN
F 1 "CONN_ARDUINO_PRO_MINI_13_24" V 7450 1350 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x12" H 7350 1350 50  0001 C CNN
F 3 "" H 7350 1350 50  0000 C CNN
	1    7350 1350
	1    0    0    -1  
$EndComp
Text Label 2725 3250 0    60   ~ 0
GND
Text Label 3575 3350 0    60   ~ 0
GND
Text Label 6725 1500 0    60   ~ 0
PWR_CTRL
Text Label 9000 800  0    60   ~ 0
+5V
Text Label 10150 2675 0    60   ~ 0
+5V
Text Label 875  1850 0    60   ~ 0
LOAD
$Comp
L CONN_01X01 P7
U 1 1 57CAD42F
P 5400 3075
F 0 "P7" H 5400 3175 50  0000 C CNN
F 1 "TP_GND" V 5500 3075 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 5400 3075 50  0001 C CNN
F 3 "" H 5400 3075 50  0000 C CNN
	1    5400 3075
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P8
U 1 1 57CAD4C5
P 6025 3075
F 0 "P8" H 6025 3175 50  0000 C CNN
F 1 "TP_12V" V 6125 3075 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 6025 3075 50  0001 C CNN
F 3 "" H 6025 3075 50  0000 C CNN
	1    6025 3075
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P9
U 1 1 57CAD531
P 6650 3075
F 0 "P9" H 6650 3175 50  0000 C CNN
F 1 "TP_5V" V 6750 3075 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 6650 3075 50  0001 C CNN
F 3 "" H 6650 3075 50  0000 C CNN
	1    6650 3075
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P10
U 1 1 57CAD5DE
P 7275 3075
F 0 "P10" H 7275 3175 50  0000 C CNN
F 1 "TP_DB7" V 7375 3075 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 7275 3075 50  0001 C CNN
F 3 "" H 7275 3075 50  0000 C CNN
	1    7275 3075
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P11
U 1 1 57CAD84E
P 8100 3075
F 0 "P11" H 8100 3175 50  0000 C CNN
F 1 "TP_PWR_CTRL" V 8200 3075 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 8100 3075 50  0001 C CNN
F 3 "" H 8100 3075 50  0000 C CNN
	1    8100 3075
	1    0    0    -1  
$EndComp
Wire Wire Line
	875  925  875  1050
Wire Wire Line
	875  1050 1050 1050
Wire Wire Line
	875  1250 875  1150
Wire Wire Line
	875  1150 1050 1150
Wire Wire Line
	1050 1750 875  1750
Wire Wire Line
	875  1750 875  1700
Wire Wire Line
	875  2000 875  1850
Wire Wire Line
	875  1850 1050 1850
Wire Wire Line
	1500 2250 1175 2250
Wire Wire Line
	1350 2350 1350 2250
Connection ~ 1350 2250
Wire Wire Line
	875  2400 875  2725
Wire Wire Line
	1350 2650 875  2650
Wire Wire Line
	875  2650 875  2675
Connection ~ 875  2675
Wire Wire Line
	1800 2250 2125 2250
Wire Wire Line
	2525 1625 2525 1500
Wire Wire Line
	3825 1625 3825 1500
Wire Wire Line
	3175 1625 3175 1325
Wire Wire Line
	2525 875  2525 1200
Wire Wire Line
	2525 1025 2875 1025
Wire Wire Line
	3475 1025 3825 1025
Wire Wire Line
	3825 1025 3825 1200
Connection ~ 2525 1025
Wire Wire Line
	6725 900  7150 900 
Wire Wire Line
	7150 1100 6725 1100
Wire Wire Line
	8825 1000 9225 1000
Wire Wire Line
	8825 800  9225 800 
Wire Wire Line
	8325 1000 8000 1000
Wire Wire Line
	7150 1000 6725 1000
Wire Wire Line
	8825 900  9225 900 
Wire Wire Line
	8325 900  8000 900 
Wire Wire Line
	8325 800  8000 800 
Wire Wire Line
	7150 1800 6725 1800
Wire Wire Line
	7150 1700 6725 1700
Wire Wire Line
	6725 1600 7150 1600
Wire Wire Line
	6750 1950 6750 1900
Wire Wire Line
	6750 1900 7150 1900
Wire Wire Line
	6750 2350 6750 2250
Wire Wire Line
	10425 825  10150 825 
Wire Wire Line
	10425 1025 10150 1025
Wire Wire Line
	10425 1125 10150 1125
Wire Wire Line
	10425 1225 10150 1225
Wire Wire Line
	10425 1725 10150 1725
Wire Wire Line
	10425 1825 10150 1825
Wire Wire Line
	10425 1925 10150 1925
Wire Wire Line
	10425 2025 10150 2025
Wire Wire Line
	10425 725  10150 725 
Wire Wire Line
	10150 2675 10150 2575
Wire Wire Line
	10150 2125 10150 2275
Wire Wire Line
	9775 750  9775 675 
Wire Wire Line
	9775 675  9600 675 
Wire Wire Line
	9925 900  10000 900 
Wire Wire Line
	10000 900  10000 925 
Wire Wire Line
	10000 925  10425 925 
Wire Wire Line
	9775 1150 9775 1050
Wire Wire Line
	5100 1200 4825 1200
Wire Wire Line
	5100 1300 4825 1300
Wire Wire Line
	5100 1400 4825 1400
Wire Wire Line
	5100 800  4825 800 
Wire Wire Line
	5100 900  4825 900 
Wire Wire Line
	5100 1500 4825 1500
Wire Wire Line
	5100 1600 4825 1600
Wire Wire Line
	2600 2600 2600 2450
Wire Wire Line
	2600 2450 3850 2450
Wire Wire Line
	2875 2450 2875 2600
Wire Wire Line
	2975 3150 2275 3150
Wire Wire Line
	2975 3350 2275 3350
Wire Wire Line
	2875 2900 2875 3525
Connection ~ 2875 3150
Wire Wire Line
	2600 2900 2600 3525
Connection ~ 2600 3350
Wire Wire Line
	2875 3950 2875 3825
Wire Wire Line
	2600 3950 2600 3825
Wire Wire Line
	3850 2900 3850 3525
Connection ~ 3850 3150
Wire Wire Line
	3850 3825 3850 3925
Wire Wire Line
	3850 2450 3850 2600
Connection ~ 2875 2450
Wire Wire Line
	7150 1200 6725 1200
Wire Wire Line
	7150 1300 6725 1300
Wire Wire Line
	7150 1400 6725 1400
Wire Wire Line
	3575 3350 3800 3350
Wire Wire Line
	2975 3250 2725 3250
Wire Wire Line
	3850 3150 3575 3150
Wire Wire Line
	7150 1500 6725 1500
Wire Wire Line
	5200 3075 5025 3075
Wire Wire Line
	5825 3075 5625 3075
Wire Wire Line
	6450 3075 6275 3075
Wire Wire Line
	7075 3075 6875 3075
Text Label 5025 3075 0    60   ~ 0
GND
Text Label 5625 3075 0    60   ~ 0
+12V
Text Label 6275 3075 0    60   ~ 0
+5V
Text Label 6875 3075 0    60   ~ 0
DB7
Wire Wire Line
	7575 3075 7900 3075
Text Label 7575 3075 0    60   ~ 0
PWR_CTRL
$Comp
L CONN_01X01 P12
U 1 1 57CAEB60
P 5400 3450
F 0 "P12" H 5400 3550 50  0000 C CNN
F 1 "TP_ROTA" V 5500 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 5400 3450 50  0001 C CNN
F 3 "" H 5400 3450 50  0000 C CNN
	1    5400 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P13
U 1 1 57CAECA5
P 6250 3450
F 0 "P13" H 6250 3550 50  0000 C CNN
F 1 "TP_ROTB" V 6350 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 6250 3450 50  0001 C CNN
F 3 "" H 6250 3450 50  0000 C CNN
	1    6250 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3450 4925 3450
Wire Wire Line
	6050 3450 5700 3450
Text Label 4925 3450 0    60   ~ 0
ROTA
Text Label 5700 3450 0    60   ~ 0
ROTB
Wire Wire Line
	10150 2125 10425 2125
Wire Wire Line
	10425 2225 10200 2225
Text Label 10200 2225 0    60   ~ 0
GND
Text Notes 8950 2650 0    60   ~ 0
Optional resistor. \nCan be shorted if the \ndisplay does not need \ncurrent limit for \nbackground light.
Wire Notes Line
	8900 2150 8900 2700
Wire Notes Line
	8900 2700 10000 2700
Wire Notes Line
	10000 2700 10000 2150
Wire Notes Line
	10000 2150 8900 2150
$Comp
L CONN_ARDUINO_PRO_MINI_1_12 P3
U 1 1 57D2CBFA
P 5300 1350
F 0 "P3" H 5300 2000 50  0000 C CNN
F 1 "CONN_ARDUINO_PRO_MINI_1_12" V 5400 1350 50  0000 C CNN
F 2 "" H 5300 1350 50  0000 C CNN
F 3 "" H 5300 1350 50  0000 C CNN
	1    5300 1350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
